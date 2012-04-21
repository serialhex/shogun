/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Heiko Strathmann
 */

#include <shogun/features/SubsetStack.h>
#include <shogun/io/SGIO.h>
#include <shogun/base/Parameter.h>

using namespace shogun;

CSubsetStack::CSubsetStack()
{
	init();
}

CSubsetStack::~CSubsetStack()
{
	SG_UNREF(m_active_subsets_stack);
	SG_UNREF(m_active_subset);
}

void CSubsetStack::remove_all_subsets()
{
	/* delete all active subsets, backwards due to DynArray implementation */
	for (index_t i=m_active_subsets_stack->get_num_elements()-1; i>=0; --i)
		m_active_subsets_stack->delete_element(i);

	SG_UNREF(m_active_subset);
}

void CSubsetStack::init()
{
	SG_ADD((CSGObject**)&m_active_subset, "active_subset",
			"Currently active subset", MS_NOT_AVAILABLE);
	SG_ADD((CSGObject**)&m_active_subsets_stack, "active_subsets_stack",
			"Stack of active subsets", MS_NOT_AVAILABLE);

	m_active_subset=NULL;
	m_active_subsets_stack=new CDynamicObjectArray<CSubset>();
	SG_REF(m_active_subsets_stack);
}

void CSubsetStack::add_subset(SGVector<index_t> subset)
{
	/* active subset will be changed anyway, no setting to NULL */
	SG_UNREF(m_active_subset);

	/* two cases: stack is empty/stack is not empty */
	if (m_active_subsets_stack->get_num_elements())
	{
		/* if there are alreay subsets, we need to map given one through
		 * existing ones */

		/* get latest current subset */
		CSubset* latest=m_active_subsets_stack->get_last_element();

		/* here the do_free flag is set to true to make automatic memory
		 * handling possible. However, this should be changed to ref-counting
		 * once that is possible. TODO
		 */
		SGVector<index_t> new_active_subset=SGVector<index_t>(subset.vlen, true);

		/* using the latest current subset, transform all indices by the latest
		 * added subset (dynamic programming greets you) */
		for (index_t i=0; i<subset.vlen; ++i)
			new_active_subset.vector[i]=latest->m_subset_idx[subset.vector[i]];

		/* replace active subset */
		m_active_subset=new CSubset(new_active_subset);
		SG_REF(m_active_subset);

		SG_UNREF(latest);
	}
	else
	{
		/* just use plain given subset since there is nothing to map */
		m_active_subset=new CSubset(subset);
		SG_REF(m_active_subset);
	}

	/* add current active subset on stack of active subsets in any case */
	m_active_subsets_stack->append_element(m_active_subset);
}

void CSubsetStack::remove_subset()
{
	index_t num_subsets=m_active_subsets_stack->get_num_elements();
	if (num_subsets)
	{
		/* unref current subset */
		SG_UNREF(m_active_subset);
		m_active_subset=NULL;

		/* delete last element on stack */
		if (num_subsets>=1)
		{
			index_t last_idx=m_active_subsets_stack->get_num_elements()-1;
			m_active_subsets_stack->delete_element(last_idx);

		}

		/* if there are subsets left on stack, set the next one as active */
		if (num_subsets>1)
		{
			/* use new last element on stack as active subset */
			index_t last_idx=m_active_subsets_stack->get_num_elements()-1;
			m_active_subset=m_active_subsets_stack->get_element(last_idx);
		}

		/* otherwise, active subset is just empty */
	}
	else
	{
		SG_WARNING("%s::remove_subset() was called but there is no subset set."
				"\n", get_name());
	}
}

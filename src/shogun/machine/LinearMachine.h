/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2009 Soeren Sonnenburg
 * Copyright (C) 1999-2009 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _LINEARCLASSIFIER_H__
#define _LINEARCLASSIFIER_H__

#include <shogun/lib/common.h>
#include <shogun/features/Labels.h>
#include <shogun/features/DotFeatures.h>
#include <shogun/machine/Machine.h>

#include <stdio.h>

namespace shogun
{
	class CDotFeatures;
	class CMachine;
	class CLabels;

/** @brief Class LinearMachine is a generic interface for all kinds of linear
 * machines like classifiers.
 *
 * A linear classifier computes
 *
 *  \f[
 * 		f({\bf x})= {\bf w} \cdot {\bf x} + b
 * 	\f]
 *
 * where \f${\bf w}\f$ are the weights assigned to each feature in training
 * and \f$b\f$ the bias.
 *
 * To implement a linear classifier all that is required is to define the
 * train() function that delivers \f${\bf w}\f$ above.
 *
 * Note that this framework works with linear classifiers of arbitraty feature
 * type, e.g. dense and sparse and even string based features. This is
 * implemented by using CDotFeatures that may provide a mapping function
 * \f$\Phi({\bf x})\mapsto {\cal R^D}\f$ encapsulating all the required
 * operations (like the dot product). The decision function is thus
 *
 *  \f[
 * 		f({\bf x})= {\bf w} \cdot \Phi({\bf x}) + b.
 * 	\f]
 *
 * 	The following linear classifiers are implemented
 * 	\li Linear Descriminant Analysis (CLDA)
 * 	\li Linear Programming Machines (CLPM, CLPBoost)
 * 	\li Perceptron (CPerceptron)
 * 	\li Linear SVMs (CSVMSGD, CLibLinear, CSVMOcas, CSVMLin, CSubgradientSVM)
 *
 * 	\sa CDotFeatures
 *
 * */
class CLinearMachine : public CMachine
{
	public:
		/** default constructor */
		CLinearMachine();

		/** destructor */
		virtual ~CLinearMachine();

		/** copy constructor */
		CLinearMachine(CLinearMachine* machine);

		/** get w
		 *
		 * @return weight vector
		 */
		inline SGVector<float64_t> get_w()
		{
			return w;
		}

		/** set w
		 *
		 * @param src_w new w
		 */
		inline void set_w(const SGVector<float64_t> src_w)
		{
			w=src_w;
		}

		/** set bias
		 *
		 * @param b new bias
		 */
		inline void set_bias(float64_t b)
		{
			bias=b;
		}

		/** get bias
		 *
		 * @return bias
		 */
		inline float64_t get_bias()
		{
			return bias;
		}

		/** set features
		 *
		 * @param feat features to set
		 */
		virtual inline void set_features(CDotFeatures* feat)
		{
			SG_UNREF(features);
			SG_REF(feat);
			features=feat;
		}

		/** apply linear machine to all examples
		 *
		 * @return resulting labels
		 */
		virtual CLabels* apply();

		/** apply linear machine to data
		 *
		 * @param data (test)data to be classified
		 * @return classified labels
		 */
		virtual CLabels* apply(CFeatures* data);

		/// get output for example "vec_idx"
		virtual float64_t apply(int32_t vec_idx)
		{
			return features->dense_dot(vec_idx, w.vector, w.vlen) + bias;
		}

		/** get features
		 *
		 * @return features
		 */
		virtual CDotFeatures* get_features() { SG_REF(features); return features; }

		/** Returns the name of the SGSerializable instance.  It MUST BE
		 *  the CLASS NAME without the prefixed `C'.
		 *
		 * @return name of the SGSerializable
		 */
		virtual const char* get_name() const { return "LinearMachine"; }

	protected:
		/** Stores feature data of underlying model. Does nothing because
		 * Linear machines store the normal vector of the separating hyperplane
		 * and therefore the model anyway
		 */
		virtual void store_model_features() {}

	private:

		void init();

	protected:
		/** w */
		SGVector<float64_t> w;
		/** bias */
		float64_t bias;
		/** features */
		CDotFeatures* features;
};
}
#endif

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Chiyuan Zhang
 * Copyright (C) 2012 Chiyuan Zhang
 */

#ifndef ECOCRANDOMSPARSEENCODER_H__
#define ECOCRANDOMSPARSEENCODER_H__

#include <shogun/mathematics/Math.h>
#include <shogun/multiclass/ecoc/ECOCEncoder.h>

namespace shogun
{

class CECOCRandomSparseEncoder: public CECOCEncoder
{
public:
    /** constructor
     * @param maxiter max number of iterations
     * @param codelen code length, if set to zero, will be computed automatically via get_default_code_length
     * @param pzero probability of zero
     * @param pposone probability of +1
     * @param pnegone probability of -1
     *
     * @see get_default_code_length
     */
    CECOCRandomSparseEncoder(int32_t maxiter=10000, int32_t codelen=0,
            float64_t pzero=0.3, float64_t pposone=0.35, float64_t pnegone=0.35);

    /** destructor */
    virtual ~CECOCRandomSparseEncoder() {}

    /** set probability
     * @param pzero probability of zero
     * @param pposone probability of +1
     * @param pnegone probability of -1
     */
    void set_probability(float64_t pzero, float64_t pposone, float64_t pnegone);

    /** get name */
    virtual const char* get_name() const { return "ECOCRandomSparseEncoder"; }

    /** get default code length
     * @param num_classes number of classes
     *
     * In Sparse Random Coding, 15 * log(num_classes) is suggested as code length.
     * See
     *
     *   S. Escalera, O. Pujol, and P. Radeva. Separability of ternary codes for sparse designs
     *   of error-correcting output codes. Pattern Recognition Letters, 30:285-297, 2009.
     */
    virtual int32_t get_default_code_length(int32_t num_classes) const
    {
        return static_cast<int32_t>(CMath::round(15 * CMath::log(num_classes)));
    }

    /** init codebook.
     * @param num_classes number of classes in this problem
     */
    virtual SGMatrix<int32_t> create_codebook(int32_t num_classes);

protected:
    int32_t   m_maxiter; // max number of iterations
    int32_t   m_codelen; // code length
    float64_t m_pzero;   // probability of zero
    float64_t m_pposone; // probability of +1
    float64_t m_pnegone; // probability of -1

private:
    /** ensure probability sum to one
     * @param pzero probability of zero
     * @param pposone probability of +1
     * @param pnegone probability of -1
     */
    bool check_probability(float64_t pzero, float64_t pposone, float64_t pnegone)
    {
        if (CMath::abs(pzero + pposone + pnegone - 1) > 1e-5)
            return false;
        return true;
    }

    /** init parameters */
    void init();
};

} /* shogun */

#endif /* end of include guard: ECOCRANDOMSPARSEENCODER_H__ */


/*
 * LmsNode.hpp
 *
 *  Created on: Aug 13, 2016
 *      Author: sabin
 */

#ifndef LMSNODE_HPP_
#define LMSNODE_HPP_

#include <adaptivefilter/ISystemFunction.h>
#include <adaptivefilter/LmsFilter.h>

class LmsNode
{
public:
    LmsNode(int weightNo);
    ~LmsNode();

    void lmsAdapt();
    void combineWith(std::vector<double>& neighWeights);

    std::vector<double> getWeightData() const;

    void set(const ISystemFunction::Input&  input);
    void set(const ISystemFunction::Output& output);
    void setNodeCoefficient(double coefficient);

    void dump();

private:

    LmsFilter m_lmsFilter;
    ISystemFunction::Input m_u;
    ISystemFunction::Output m_d;

    std::vector<double> m_estimatedWeights;
    std::vector<double> m_localWeights;
    double  m_nodeCoefficient;

};

#endif /* LMSNODE_HPP_ */

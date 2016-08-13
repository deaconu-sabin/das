/*
 * Node.hpp
 *
 *  Created on: Aug 13, 2016
 *      Author: sabin
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include <adaptivefilter/ISystemFunction.h>
#include <adaptivefilter/LmsFilter.h>

class Node
{
public:
    Node();
    ~Node();

    int getRank() const;
    void lmsAdapt();
    void combineWith(std::vector<double>& neighWeights);

    std::vector<double> getWeightData() const;

    void set(const ISystemFunction::Input&  input);
    void set(const ISystemFunction::Output& output);

    void dump();

private:
    double getWeightCoefficient() const;
private:
    int m_neigborsCount;

    LmsFilter m_lmsFilter;
    ISystemFunction::Input m_u;
    ISystemFunction::Output m_d;

    std::vector<double> m_estimatedWeights;
    std::vector<double> m_localWeights;

};

#endif /* NODE_HPP_ */

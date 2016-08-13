/*
 * Node.cpp
 *
 *  Created on: Aug 13, 2016
 *      Author: sabin
 */
#include "Node.hpp"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
/// Define Node
////////////////////////////////////////////////////////////////////////////////




Node::Node():
        m_neigborsCount(3),
        m_lmsFilter(3),
        m_u(0),
        m_d(0),
        m_estimatedWeights(),
        m_localWeights()
{
	m_estimatedWeights = m_lmsFilter.getWeights();
	m_localWeights = m_estimatedWeights;
}

Node::~Node()
{
}

void Node::lmsAdapt()
{
	m_localWeights = m_estimatedWeights;
	double error = LmsFilter::Adapt(m_u, m_d, m_localWeights);



    for(unsigned i = 0; i < m_estimatedWeights.size(); ++i)
    {
        m_estimatedWeights[i] = getWeightCoefficient() *
                                m_localWeights[i];
    }
}

void Node::combineWith(std::vector<double>& neighWeights)
{
    assert(m_estimatedWeights.size() == neighWeights.size());

    for(unsigned i = 0; i < m_estimatedWeights.size(); ++i)
    {
        m_estimatedWeights[i] += getWeightCoefficient() *
                                 neighWeights[i];
    }
}

std::vector<double> Node::getWeightData() const
{
    return m_localWeights;
}

void Node::set(const ISystemFunction::Input&  input)
{
	m_u = input;
}
void Node::set(const ISystemFunction::Output& output)
{
	m_d = output;
}

void Node::dump()
{
	std::cout << "NODE: U = " << m_u
		<< "; D = " <<  m_d
		<< "; Estim_W " <<  m_estimatedWeights
		<< std::endl;
}

double Node::getWeightCoefficient() const
{
    return 1.0/(m_neigborsCount+1);
}


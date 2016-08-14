/*
 * LmsNode.cpp
 *
 *  Created on: Aug 13, 2016
 *      Author: sabin
 */
#include "LmsNode.hpp"
#include "../Logging.hpp"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
/// Define LmsNode
////////////////////////////////////////////////////////////////////////////////
LmsNode::LmsNode(int weightNo)
    : m_lmsFilter(weightNo)
    , m_u(0)
    , m_d(0)
    , m_estimatedWeights()
    , m_localWeights()
    , m_nodeCoefficient(0.0)
{
	m_estimatedWeights = m_lmsFilter.getWeights();
	m_localWeights = m_estimatedWeights;
}

LmsNode::~LmsNode()
{
}

void LmsNode::lmsAdapt()
{
    log.Debug() << "LMS before adapt L : "
                << m_localWeights
                << " E : "
                << m_estimatedWeights
                << std::endl;
    // TODO: check if this should be uncommented.
	m_localWeights = m_estimatedWeights;

	double error = LmsFilter::Adapt(m_u, m_d, m_localWeights);

    for(unsigned i = 0; i < m_estimatedWeights.size(); ++i)
    {
        m_estimatedWeights[i] = m_nodeCoefficient *
                                m_localWeights[i];
    }
    log.Debug() << "LMS after  adapt L : "
                << m_localWeights
                << " E : "
                << m_estimatedWeights
                << std::endl;
}

void LmsNode::combineWith(std::vector<double>& neighWeights)
{
    log.Debug() << "LMS before combine L : "
                << m_localWeights
                << " E : "
                << m_estimatedWeights
                << std::endl;
    assert(m_estimatedWeights.size() == neighWeights.size());

    for(unsigned i = 0; i < m_estimatedWeights.size(); ++i)
    {
        m_estimatedWeights[i] += m_nodeCoefficient *
                                 neighWeights[i];
    }
    log.Debug() << "LMS after  combine L : "
                << m_localWeights
                << " E : "
                << m_estimatedWeights
                << std::endl;
}

std::vector<double> LmsNode::getWeightData() const
{
    return m_localWeights;
}

void LmsNode::set(const ISystemFunction::Input&  input)
{
	m_u = input;
}
void LmsNode::set(const ISystemFunction::Output& output)
{
	m_d = output;
}

void LmsNode::setNodeCoefficient(double coefficient)
{
    m_nodeCoefficient = coefficient;
}

void LmsNode::dump()
{
	log.Debug() << "LMS : Input = " << m_u
		<< " DsrOut = " <<  m_d
		<< " E " <<  m_estimatedWeights
		<< std::endl;
}

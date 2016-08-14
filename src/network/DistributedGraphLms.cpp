/*
 * DistributedGraphLms.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#include "DistributedGraphLms.hpp"
#include <adaptivefilter/LinearFunction.h>
#include "../Logging.hpp"

DistributedGraphLms::DistributedGraphLms(const std::vector<int>& neighborsRank)
    : IDistributedAlgorithm()
    , m_myRank(NetSim().getRank())
    , m_node(3)
    , m_neighbors(neighborsRank)
{
    std::vector<double> coefficients(3);
    coefficients[0] = 2;
    coefficients[1] = 6;
    coefficients[2] = 5;
    system = new MultivariateFunction(coefficients);
}

DistributedGraphLms::~DistributedGraphLms()
{
    delete system;
}
void DistributedGraphLms::setInitialData()
{
    m_node.setNodeCoefficient( 1.0 / (m_neighbors.size() + 1.0));
}
void DistributedGraphLms::readInputData()
{
    // we set the pair {d,u}
    // u - is input
    // d - is system outcome
    ISystemFunction::Input input = system->generateInput();
    m_node.set(input);
    m_node.set(system->evaluate(input));
}

void DistributedGraphLms::processData()
{
    for (int nodeRank = 0;
         nodeRank < NetSim().getSize();
         nodeRank++)
    {
        if(m_myRank == nodeRank)
        {
            m_node.lmsAdapt();

            for(unsigned neigh = 0; neigh < m_neighbors.size(); ++neigh)
            {
                if(m_neighbors[neigh] != m_myRank)
                {
                    std::vector<double> neighWeights(32);
                    NetSim().recvData(neighWeights);
                    m_node.combineWith(neighWeights);
                }
            }
        }
        else
        {
            if (isMyNeighbor(nodeRank))
            {
                NetSim().sendDataTo(m_node.getWeightData(), nodeRank);
            }
        }
    }
}

void DistributedGraphLms::writeOutputData()
{
    m_node.dump();
}

bool DistributedGraphLms::isMyNeighbor(int rank)
{
    bool isNeighbor = false;

    for (int idx = 0; idx < m_neighbors.size(); idx++)
    {
        if(m_neighbors[idx] == rank)
        {
            isNeighbor = true;
            break;
        }
    }

    return isNeighbor;
}

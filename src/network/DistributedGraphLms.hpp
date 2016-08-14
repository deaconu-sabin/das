/*
 * DistributedGraphLms.hpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#ifndef DISTRIBUTEDGRAPHLMS_HPP_
#define DISTRIBUTEDGRAPHLMS_HPP_

#include "NetworkSim.h"
#include "LmsNode.hpp"
#include <vector>

class DistributedGraphLms: public NetworkSim::IDistributedAlgorithm
{
    public:
        DistributedGraphLms(const std::vector<int>& neighborsRank);
        virtual ~DistributedGraphLms();

        virtual void setInitialData();
        virtual void readInputData();
        virtual void processData();
        virtual void writeOutputData();

    private:
        bool isMyNeighbor(int rank);
    private:
        int m_myRank;
        LmsNode m_node;
        std::vector<int> m_neighbors;

        // data simulation
        ISystemFunction* system;

};

#endif /* DISTRIBUTEDGRAPHLMS_HPP_ */

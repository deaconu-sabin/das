/*
 * NetworkSim.h
 *      Author: sabin
 */

#ifndef NETWORKSIM_H_
#define NETWORKSIM_H_

#include <mpi/mpi.h>

#include "ISystemFunction.h"
#include "LmsFilter.h"

class NetworkSim
{
public:
    class Node
    {
    public:
        ~Node();

        int getRank();
        void adaptThenCombine();

        void sendDataToNeighbor(int rank);
        void receiveDataFromNeighbors();

        // return data vector received from source
        std::vector<double> receiveDataFromNeighbor(int* source);

        void set(const ISystemFunction::Input&  input);
        void set(const ISystemFunction::Output& output);

        void dump();

        friend NetworkSim;
    private:
        Node(MPI::Graphcomm& graphComm);

    private:
        MPI::Graphcomm m_GraphComm;
        int m_rank;
        int m_neigborsCount;
        int* m_neighborsRanks;

        LmsFilter m_lmsFilter;
        ISystemFunction::Input m_u;
        ISystemFunction::Output m_d;

        std::vector<double> m_estimatedWeights;
        std::vector<double> m_localWeights;

    };

    ~NetworkSim();
    static NetworkSim& getInstance();

    Node* getNode();

    int getSize();


private:
    NetworkSim();
    void init();

private:
    int processId;
    bool m_isValid;
    int m_NetworkSize;
    Node* m_pNode;
};

#endif /* NETWORKSIM_H_ */

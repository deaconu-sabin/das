/*
 * NetworkSim.h
 *      Author: sabin
 */

#ifndef NETWORKSIM_H_
#define NETWORKSIM_H_

#include <mpi/mpi.h>

class NetworkSim
{
public:
    class Node
    {
    public:
        ~Node();

        int getRank();
        void adapt();
        void exchange();
        void combine();

        void sendDataToNeighbor(int rank);
        void receiveDataFromNeighbors();

        friend NetworkSim;
    private:
        Node(MPI::Graphcomm& graphComm);

    private:
        MPI::Graphcomm m_GraphComm;
        int m_rank;
        int m_neigborsCount;
        int* m_neighborsRanks;
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

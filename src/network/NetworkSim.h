/*
 * NetworkSim.h
 *      Author: sabin
 */

#ifndef NETWORKSIM_H_
#define NETWORKSIM_H_

#include <mpi/mpi.h>
#include "Node.hpp"


class NetworkSim
{
public:
    ~NetworkSim();
    static NetworkSim& getInstance();

    int getSize() const;
    int getProcessId() const;
    int getRank() const;
    int getTopology() const;

    bool recvData(std::vector<double>& receivedData);
    bool recvDataFrom(std::vector<double>& receivedData, int source);

    bool sendData(const std::vector<double>& inData);
    bool sendDataTo(const std::vector<double>& inData, int dest);


    void execute();

    bool loadFromCfgFile();
    Node* getNode();
    void init();
    void dump() const;
private:
    NetworkSim();

private:
    Node* m_pNode;
    MPI::Intracomm m_intraComm;

};

inline NetworkSim& NetSim()
{
    return NetworkSim::getInstance();
}

#endif /* NETWORKSIM_H_ */

/*
 * NetworkSim.h
 *      Author: sabin
 */

#ifndef NETWORKSIM_H_
#define NETWORKSIM_H_

#include <mpi/mpi.h>
#include "NetworkCfg.hpp"

class NetworkSim
{
public:
    static const int INVALID_VALUE;

    class IDistributedAlgorithm
    {
        public:
            IDistributedAlgorithm(){};
            virtual ~IDistributedAlgorithm(){}
            virtual void setInitialData() = 0;
            virtual void readInputData() = 0;
            virtual void processData() = 0;
            virtual void writeOutputData() = 0;
    };

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

    IDistributedAlgorithm* getAlgorithm() const;
    void setCfgFile(const char* file);
    void dump() const;
    bool init();

private:
    NetworkSim();
    bool createTopology(int topology);

private:
    IDistributedAlgorithm* m_algorithm;
    MPI::Intracomm m_intraComm;
    NetworkCfg m_netCfg;
    //! m_myNeighborsRank : also can be the node itself
    std::vector<int> m_myNeighborsRank;

};

inline NetworkSim& NetSim()
{
    return NetworkSim::getInstance();
}

#endif /* NETWORKSIM_H_ */

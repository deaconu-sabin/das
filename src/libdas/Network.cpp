/*
 * NetworkImpl.cpp
 *      Author: sabin
 */

#include <das/Network.hpp>
#include "Logging.hpp"
#include "AlgorithmLoader.hpp"
#include "Config.hpp"

#include <mpi/mpi.h>
#include <cassert>
#include <sstream>

using namespace das;

////////////////////////////////////////////////////////////////////////////////
/// Define Network
////////////////////////////////////////////////////////////////////////////////

const int Network::INVALID_VALUE = -1;

namespace das
{


class NetworkImpl
{
public:
    MPI::Intracomm intraComm;
    std::vector<int> neighborsList;
    Config config;
    static AlgorithmLoader algorithmLoader;
    mutable Logging log;

    NetworkImpl()
        : intraComm(MPI::COMM_NULL)
        , neighborsList()
        , config()
        , log("Network")
    {
        MPI::Init();    /* starts MPI */
    }

    ~NetworkImpl()
    {
        log.Info() << "END PROCESS "<< getProcessId() << std::endl;
        MPI::Finalize();
        log.close();
    }

    bool init()
    {
        std::stringstream fileName;
        fileName << config.outputFile << getProcessId() << ".log";
        log.open(fileName.str());
        log.setLevel(Logging::INFO);
        log.Info() << "Initialization of node "<< getProcessId() << std::endl;

        if (config.nodesNumber > MPI::COMM_WORLD.Get_size())
        {
            log.Fatal() << "Not enough processors. Expected "
                     << config.nodesNumber
                     << std::endl;
            return false;
        }

        if (!createTopology(config.topologyType))
        {
            log.Fatal() << "Could not create topology\n";
            return false;
        }
        return true;
    }

    int getSize() const
    {
        int size = Network::INVALID_VALUE;
        if ( intraComm != MPI::COMM_NULL)
        {
            size = intraComm.Get_size();
        }else
        {
            log.Err() << "getSize() returns invalid\n";
        }
        return size;
    }

    int getProcessId() const
    {
        return MPI::COMM_WORLD.Get_rank();
    }

    int getRank() const
    {
        int rank = Network::INVALID_VALUE;
        if ( intraComm != MPI::COMM_NULL)
        {
            rank = intraComm.Get_rank();
        }else
        {
            log.Err() << "getRank() returns invalid\n";
        }
        return rank;
    }

    int getTopology() const
    {
        int topology = Network::INVALID_VALUE;
        if ( intraComm != MPI::COMM_NULL)
        {
            topology = intraComm.Get_topology();
        }else
        {
            log.Err() << "getTopology() returns invalid\n";
        }
        return topology;
    }

    bool recvData(std::vector<double>& receivedData)
    {
        bool isDataReceived = false;
        if ( intraComm != MPI::COMM_NULL)
        {
            MPI::Status status;
            double buffer[100];
            intraComm.Recv(buffer, 100,
                           MPI::DOUBLE,
                           MPI::ANY_SOURCE,
                           /*tag*/ 100,
                           status);

            int count = status.Get_count(MPI::DOUBLE);
            receivedData = std::vector<double>(buffer, buffer+count);

            log.Info() << "RECV [ " << getRank()
                        << " <-- "
                        << status.Get_source()
                        << " ] data : "
                        << receivedData
                        << std::endl;
            isDataReceived = true;
        }else
        {
            log.Err() << "PID " << getProcessId()
                      << " failed to RECV"
                      << std::endl;
        }
        return isDataReceived;
    }

    bool recvDataFrom(std::vector<double>& receivedData, int source)
    {
        bool isDataReceived = false;

        // TODO: add implementation

        return isDataReceived;
    }

    bool sendData(const std::vector<double>& inData)
    {
        bool isDataSent = false;

        // TODO: Add sendData() implementation

        return isDataSent;
    }

    bool sendDataTo(const std::vector<double>& inData, int dest)
    {
        bool isDataSent = false;
        if ( intraComm != MPI::COMM_NULL)
        {
            log.Info() << "SEND [ " << getRank()
                       << " --> "
                       << dest
                       << " ] data : "
                       << inData
                       << std::endl;

            intraComm.Send(   &(inData[0]),
                                inData.size(),
                                MPI::DOUBLE,
                                dest, /*tag*/ 100);
            isDataSent = true;
        }else
        {
            log.Err() << "PID " << getProcessId()
                      << " failed to SEND\n";
        }
        return isDataSent;
    }

    void setCfgFile(const char* file)
    {
        config.setFileName(file);
    }

    void dump() const
    {
        log.Info() << "== WORLD NETWORK =="
                    << "\n PID : " << getProcessId()
                    << "\n WRLD_SZ : " << MPI::COMM_WORLD.Get_size()
                    << std::endl;

        if ( intraComm != MPI::COMM_NULL)
        {
            log.Info()<< "== My NETWORK =="
                    << "\n RNK : " << getRank()
                    << "\n TPG : " << getTopology()
                    << "\n NEIGH : " << neighborsList
                    << "\n NET_SZ : " << getSize()
                    << std::endl;
        }
    }

    bool createTopology(int topology)
    {
        if(topology == Config::TOPOLOGY_GRAPH)
        {
    //      Predifined topology
    //      convert adjacency matrix to the next format:
    //        int index1[] = {3,6,9,12};
    //        int edges[] = {1,2,3,
    //                0,2,3,
    //                0,1,3,
    //                0,1,2};

            int* const index = new int[config.nodesNumber];
            int totalEdges = 0;
            for(unsigned node = 0; node < config.nodesNumber; ++node)
            {
                for(int neighNode=0;
                        neighNode < config.nodeEdges[node].size();
                        ++neighNode)
                {
                    if(config.nodeEdges[node][neighNode] == 1)
                    {
                        ++totalEdges;
                    }
                }
                index[node] = totalEdges;
            }

            int* const edges = new int[totalEdges];
            unsigned edgesIdx = 0;
            for(unsigned node = 0; node < config.nodesNumber; ++node)
            {
                log.Debug() << "CreateTopology() Node : " << node
                            << "; Neighbors : " << config.nodeEdges[node]
                            << std::endl;
                for(int neighNode=0;
                        neighNode < config.nodeEdges[node].size();
                        ++neighNode)
                {
                    if(config.nodeEdges[node][neighNode] == 1)
                    {
                        log.Debug() << "CreateTopology() Edge created : "
                                    << node << " <-> " << neighNode
                                    << std::endl;

                        assert(edgesIdx < totalEdges);
                        edges[edgesIdx++] = neighNode;
                        if(node == getProcessId())
                        {
                            neighborsList.push_back(neighNode);
                        }
                    }
                }
            }
            log.Debug() << "CreateTopology() MyNeighborsRank : "
                        << neighborsList
                        << std::endl;

            intraComm = MPI::COMM_WORLD.Create_graph(config.nodesNumber, index, edges,false);

            delete [] index;
            delete [] edges;
        }else if (topology == Config::TOPOLOGY_CART)
        {
            // TODO : add implementation
        }else if (topology == Config::TOPOLOGY_INNER)
        {
            // TODO : add implementation
        }else if (topology == Config::TOPOLOGY_UNDEF)
        {
            intraComm = MPI::COMM_WORLD;
        }

        return (intraComm != MPI::COMM_NULL);
    }

};

AlgorithmLoader NetworkImpl::algorithmLoader;

}  /* namespace das */

Network::Network()
    : net(NULL)
{
    net = new NetworkImpl();
}

Network::~Network()
{
    delete net;
}

Network& Network::Instance()
{
    static Network instance;
    return instance;
}

int Network::GetMyId() const
{
    if(net)
    {
        return net->getProcessId();
    }
    return INVALID_VALUE;

}

int Network::GetMyRank() const
{
    if(net)
    {
        return net->getRank();
    }
    return INVALID_VALUE;

}

int Network::GetTopology() const
{
    if(net)
    {
        return net->getTopology();
    }
    return INVALID_VALUE;
}

int Network::GetSize() const
{
    if(net)
    {
        return net->getSize();
    }
    return INVALID_VALUE;

}

std::vector<int> Network::GetMyNeighbors() const
{
    return std::vector<int>();
}

bool Network::LoadConfiguration(const std::string& configFile) const
{
    if(net)
    {
        net->config.setFileName(configFile);
        net->config.deserialize();
        return net->init();
    }else
    {
        return false;
    }
}

IAlgorithm* Network::LoadAlgorithm() const
{
    IAlgorithm* algorithm = NULL;
    if(net)
    {
        std::stringstream nodeAlgorithm;
        nodeAlgorithm << "algorithms/"              // path
                     << net->config.nodeAlgorithm   // name
                     << ".algorithm";               // .extension
        algorithm = NetworkImpl::algorithmLoader.load(nodeAlgorithm.str());
        if(NULL == algorithm)
        {
            net->log.Err() << "Loading failed of"
                           << nodeAlgorithm.str()
                           << std::endl;
        }
    }

    return algorithm;
}

bool Network::RecvData(std::vector<double>& receivedData)
{
    if(net)
    {
        return net->recvData(receivedData);
    }
    return false;
}

bool Network::RecvDataFrom(std::vector<double>& receivedData, int source)
{
    if(net)
    {
        return net->recvDataFrom(receivedData, source);
    }
    return false;
}

bool Network::SendData(const std::vector<double>& inData)
{
    if(net)
    {
        return net->sendData(inData);
    }
    return false;
}

bool Network::SendDataTo(const std::vector<double>& inData, int dest)
{
    if(net)
    {
        return net->sendDataTo(inData, dest);
    }
    return false;
}

void Network::LogMessage(const std::string& message)
{
    if(net)
    {
        net->log.Info() << message << std::endl;
    }else
    {
        std::cout << message << std::endl;
    }
}

void Network::ToString() const
{
    if(net)
    {
        net->dump();
    }
}


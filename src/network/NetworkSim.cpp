/*
 * NetworkSim.cpp
 *      Author: sabin
 */

#include "NetworkSim.h"
#include "../Logging.hpp"
#include "DistributedGraphLms.hpp"
#include <cassert>
#include <sstream>



////////////////////////////////////////////////////////////////////////////////
/// Define NetworkSim
////////////////////////////////////////////////////////////////////////////////

const int NetworkSim::INVALID_VALUE = -1;

NetworkSim& NetworkSim::getInstance()
{
    static NetworkSim network;
    return network;
}

NetworkSim::NetworkSim()
    : m_algorithm(NULL)
    , m_intraComm(MPI::COMM_NULL)
    , m_netCfg()
    , m_myNeighborsRank()
{
    MPI::Init();    /* starts MPI */

    std::stringstream fileName;
    fileName << "NetSim" << getProcessId() << ".log";

    log.setFileName(fileName.str());
    if(getProcessId() == 0)
    {
        log.setLevel(Logging::DEBUG);
    }else
    {
        log.setLevel(Logging::INFO);
        log.open();
    }

    if(getProcessId() ==  1 || getProcessId() ==  2)
    {
        //log.setLevel(Logging::DEBUG);
    }
    log.Info() << "=>START PROCESS "<< getProcessId() << std::endl;
}

NetworkSim::~NetworkSim()
{
    if(m_algorithm)
        delete m_algorithm;
    log.Info() << "<= END PROCESS "<< getProcessId() << std::endl;
    MPI::Finalize();
    log.close();
}

bool NetworkSim::init()
{
    if (!m_netCfg.deserialize())
    {
        log.Err() << "NetworkSim::init() Failed to read cfg\n";
        return false;
    }

    if (!createTopology(m_netCfg.topologyType))
    {
        log.Err() << "NetworkSim::init() m_intraComm == MPI::COMM_NULL\n";
        return false;
    }

    if( m_algorithm )
    {
        delete m_algorithm;
        m_algorithm = 0;
    }
    if(m_netCfg.topologyType == NetworkCfg::TOPOLOGY_GRAPH)
    {
        if(m_netCfg.nodeType == NetworkCfg::NODE_LMS_ADAPT_AND_COMBINE)
        {
                m_algorithm = new DistributedGraphLms(m_myNeighborsRank);
        }
        else if( m_netCfg.nodeType == NetworkCfg::NODE_DEFAULT )
        {
            // TODO : add implementation
        }
    }

    NetSim().dump();
    return (m_algorithm != NULL);
}

int NetworkSim::getSize() const
{
    int size = INVALID_VALUE;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        size = m_intraComm.Get_size();
    }else
    {
        log.Info() << "NetworkSim::getSize() returns invalid\n";
    }
    return size;
}

int NetworkSim::getProcessId() const
{
    return MPI::COMM_WORLD.Get_rank();
}
int NetworkSim::getRank() const
{
    int rank = INVALID_VALUE;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        rank = m_intraComm.Get_rank();
    }else
    {
        log.Info() << "NetworkSim::getRank() returns invalid\n";
    }
    return rank;
}

int NetworkSim::getTopology() const
{
    int topology = INVALID_VALUE;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        topology = m_intraComm.Get_topology();
    }else
    {
        log.Info() << "NetworkSim::getTopology() returns invalid\n";
    }
    return topology;
}

bool NetworkSim::recvData(std::vector<double>& receivedData)
{
    bool isDataReceived = false;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        MPI::Status status;
        double buffer[100];
        m_intraComm.Recv(buffer, 100,
                       MPI::DOUBLE,
                       MPI::ANY_SOURCE,
                       /*tag*/ 100,
                       status);

        int count = status.Get_count(MPI::DOUBLE);
        receivedData = std::vector<double>(buffer, buffer+count);

        log.Info() << "RECV [ " << NetSim().getRank()
                    << " <-- "
                    << status.Get_source()
                    << " ] data : "
                    << receivedData
                    << std::endl;
        isDataReceived = true;
    }else
    {
        log.Err() << "PID " << NetSim().getProcessId()
                  << " failed to RECV"
                  << std::endl;
    }

    return isDataReceived;
}

bool NetworkSim::recvDataFrom(std::vector<double>& receivedData, int source)
{
    bool isDataReceived = false;

    // TODO: add implementation

    return isDataReceived;
}

bool NetworkSim::sendData(const std::vector<double>& inData)
{
    bool isDataSent = false;

    // TODO: add implementation

    return isDataSent;
}

bool NetworkSim::sendDataTo(const std::vector<double>& inData, int dest)
{
    bool isDataSent = false;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        log.Info() << "SEND [ " << NetSim().getRank()
                   << " --> "
                   << dest
                   << " ] data : "
                   << inData
                   << std::endl;

        m_intraComm.Send(   &(inData[0]),
                            inData.size(),
                            MPI::DOUBLE,
                            dest, /*tag*/ 100);
        isDataSent = true;
    }else
    {
        log.Err() << "PID " << NetSim().getProcessId()
                  << " failed to SEND\n";
    }
    return isDataSent;
}

NetworkSim::IDistributedAlgorithm* NetworkSim::getAlgorithm() const
{
    return m_algorithm;
}

void NetworkSim::setCfgFile(const char* file)
{
    m_netCfg.setFileName(file);
}

void NetworkSim::dump() const
{
    log.Info() << "== WORLD NETWORK =="
                << "\n PID : " << getProcessId()
                << "\n WRLD_SZ : " << MPI::COMM_WORLD.Get_size()
                << std::endl;

    if ( m_intraComm != MPI::COMM_NULL)
    {
        log.Info()<< "== My NETWORK =="
                << "\n RNK : " << getRank()
                << "\n TPG : " << getTopology()
                << "\n NEIGH : " << m_myNeighborsRank
                << "\n NET_SZ : " << getSize()
                << std::endl;
    }
}

bool NetworkSim::createTopology(int topology)
{
    if(topology == NetworkCfg::TOPOLOGY_GRAPH)
    {
//      Predifined topology
//      convert adjacency matrix to the next format:
//        int index1[] = {3,6,9,12};
//        int edges[] = {1,2,3,
//                0,2,3,
//                0,1,3,
//                0,1,2};

        int* const index = new int[m_netCfg.nodesNumber];
        int totalEdges = 0;
        for(unsigned node = 0; node < m_netCfg.nodesNumber; ++node)
        {
            for(int neighNode=0;
                    neighNode < m_netCfg.nodeEdges[node].size();
                    ++neighNode)
            {
                if(m_netCfg.nodeEdges[node][neighNode] == 1)
                {
                    ++totalEdges;
                }
            }
            index[node] = totalEdges;
        }

        int* const edges = new int[totalEdges];
        unsigned edgesIdx = 0;
        for(unsigned node = 0; node < m_netCfg.nodesNumber; ++node)
        {
            log.Debug() << "CreateTopology() Node : " << node
                        << "; Neighbors : " << m_netCfg.nodeEdges[node]
                        << std::endl;
            for(int neighNode=0;
                    neighNode < m_netCfg.nodeEdges[node].size();
                    ++neighNode)
            {
                if(m_netCfg.nodeEdges[node][neighNode] == 1)
                {
                    log.Debug() << "CreateTopology() Edge created : "
                                << node << " <-> " << neighNode
                                << std::endl;

                    assert(edgesIdx < totalEdges);
                    edges[edgesIdx++] = neighNode;
                    if(node == getProcessId())
                    {
                        m_myNeighborsRank.push_back(neighNode);
                    }
                }
            }
        }
        log.Debug() << "CreateTopology() MyNeighborsRank : "
                    << m_myNeighborsRank
                    << std::endl;

        m_intraComm = MPI::COMM_WORLD.Create_graph(m_netCfg.nodesNumber, index, edges,false);

        delete [] index;
        delete [] edges;
    }else if (topology == NetworkCfg::TOPOLOGY_CART)
    {
        // TODO : add implementation
    }else if (topology == NetworkCfg::TOPOLOGY_INNER)
    {
        // TODO : add implementation
    }

    return (m_intraComm != MPI::COMM_NULL);
}



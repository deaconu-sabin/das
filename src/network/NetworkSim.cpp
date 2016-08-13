/*
 * NetworkSim.cpp
 *      Author: sabin
 */

#include "NetworkSim.h"
#include <cassert>


////////////////////////////////////////////////////////////////////////////////
/// Define NetworkSim
////////////////////////////////////////////////////////////////////////////////

NetworkSim& NetworkSim::getInstance()
{
    static NetworkSim network;
    return network;
}

NetworkSim::NetworkSim()
    : m_pNode(NULL)
    , m_intraComm(MPI::COMM_NULL)
{
    MPI::Init();    /* starts MPI */
    std::cout << "=>START PROCESS "<< getProcessId() << std::endl;
}

NetworkSim::~NetworkSim()
{
    if(m_pNode)
        delete m_pNode;
    std::cout << "<= END PROCESS "<< getProcessId() << std::endl;
    MPI::Finalize();
}

void NetworkSim::init()
{
    // Predifined topology
    //TODO: read topology from net config
    // keep also the tag of MPI
    int graphSize = 4;
    int index[] = {3,6,9,12};
    int edges[] = {1,2,3,
            0,2,3,
            0,1,3,
            0,1,2};

    if( graphSize <= MPI::COMM_WORLD.Get_size())
    {
        m_intraComm = MPI::COMM_WORLD.Create_graph(graphSize, index, edges,false);
    }

    if ( m_intraComm != MPI::COMM_NULL)
    {
        m_pNode = new Node();
    }else
    {
        std::cout << "<= INIT FAILED NODE "<< getProcessId() << std::endl;
    }
}

Node* NetworkSim::getNode()
{
	return m_pNode;
}

int NetworkSim::getSize() const
{
    int size = 0;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        size = m_intraComm.Get_size();
    }
    return size;
}

int NetworkSim::getProcessId() const
{
    return MPI::COMM_WORLD.Get_rank();
}
int NetworkSim::getRank() const
{
    int rank = -1;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        rank = m_intraComm.Get_rank();
    }
    return rank;
}

int NetworkSim::getTopology() const
{
    int topology = -1;
    if ( m_intraComm != MPI::COMM_NULL)
    {
        topology = m_intraComm.Get_rank();
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

        isDataReceived = true;
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
        m_intraComm.Send(   &(inData[0]),
                            inData.size(),
                            MPI::DOUBLE,
                            dest, /*tag*/ 100);
        isDataSent = true;
    }
    return isDataSent;
}

void NetworkSim::execute()
{
    for (int nodeRank = 0;
         nodeRank < getSize();
         nodeRank++)
    {
        if(getRank() == nodeRank && m_pNode)
        {
            m_pNode->lmsAdapt();
            for(unsigned neigh = 0; neigh < getSize()-1; ++neigh)
            {
                std::vector<double> neighWeights(8);
                NetworkSim::getInstance().recvData(neighWeights);
                m_pNode->combineWith(neighWeights);
            }
        }
        else if(m_pNode)
        {
            sendDataTo(m_pNode->getWeightData(), nodeRank);
        }else
        {
            std::cout << "NOTHING TO EXECUTE - process " << getProcessId()
                      << std::endl;
        }
    }
}

void NetworkSim::dump() const
{
    if ( m_intraComm != MPI::COMM_NULL)
    {
        std::cout << "==Network=="
                << "\n *pid   " << getProcessId()
                << "\n *sz    " << getSize()
                << "\n *tpgy " << getTopology()
                << std::endl;
    }else
    {
        std::cout << "==WORLD Network=="
                << "\n *pid   " << MPI::COMM_WORLD.Get_rank()
                << "\n *sz    " << MPI::COMM_WORLD.Get_size()
                << std::endl;
    }
}



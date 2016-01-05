/*
 * NetworkSim.cpp
 *      Author: sabin
 */

#include "NetworkSim.h"

////////////////////////////////////////////////////////////////////////////////
/// Define NetworkSim::Node
////////////////////////////////////////////////////////////////////////////////

NetworkSim::Node::Node(MPI::Graphcomm& graphComm):
		m_GraphComm(graphComm),
		m_rank(-1),
		m_neigborsCount(0),
		m_neighborsRanks(NULL)
{
	m_rank = m_GraphComm.Get_rank();

	m_neigborsCount = m_GraphComm.Get_neighbors_count(m_rank);

	m_neighborsRanks = new int[m_neigborsCount];
	m_GraphComm.Get_neighbors(m_GraphComm.Get_rank(), m_neigborsCount, m_neighborsRanks);

	std::cout << "COMM_RANK "    << MPI::COMM_WORLD.Get_rank()
		<< "; Topology " << m_GraphComm.Get_topology()
		<< "; GRAPH_RANK " << m_rank
		<< "; NEIGHBORS COUNT " << m_neigborsCount
		<< "; NEIGHBORS: " <<  m_neighborsRanks[0] << m_neighborsRanks[1] << m_neighborsRanks[2] << m_neighborsRanks[3]
		<< std::endl;
}

NetworkSim::Node::~Node()
{
	delete [] m_neighborsRanks;
}


int NetworkSim::Node::getRank()
{
	return m_rank;
}
void NetworkSim::Node::adapt()
{

}
void NetworkSim::Node::exchange()
{

}
void NetworkSim::Node::combine()
{

}

void NetworkSim::Node::sendDataToNeighbor(int rank)
{
	double buffer[100] = {0};
	{
		buffer[0] = m_rank;
		std::cout << m_rank
			<< " send to "
			<< rank
			<< std::endl;
		m_GraphComm.Send(buffer, 1, MPI::DOUBLE, rank, /*tag*/ 100);
	}
}
void NetworkSim::Node::receiveDataFromNeighbors()
{
	for(int i = 0; i< m_neigborsCount; i++)
	{
		double buffer[100];
		if(m_neighborsRanks[i] == m_rank)
		{
		   //TODO:LOCAL
			buffer[0]=255.0;
		}
		else
		{
			MPI::Status status;
			m_GraphComm.Recv(buffer, 1, MPI::DOUBLE, MPI::ANY_SOURCE, /*tag*/ 100,status);
			std::cout << m_rank
				<< " recv from "
				<< status.Get_source()
				<< " data: "
				<< buffer[0]
				<< std::endl;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
/// Define NetworkSim
////////////////////////////////////////////////////////////////////////////////

NetworkSim& NetworkSim::getInstance()
{
	static NetworkSim network;
	return network;
}

NetworkSim::NetworkSim()
{
    init();
}

NetworkSim::~NetworkSim()
{
    if(m_pNode)
        delete m_pNode;
    std::cout << "========= Finishing processs: "<< processId << std::endl;
    MPI::Finalize();
}

void NetworkSim::init()
{
    m_isValid = true;
    m_pNode = NULL;

    //TODO: read topology from net config
    m_NetworkSize = 4;
    int index[] = {3,6,9,12};
    int edges[] = {1,2,3,
            0,2,3,
            0,1,3,
            0,1,2};

    MPI::Init ();      /* starts MPI */
    processId = MPI::COMM_WORLD.Get_rank();   /* get current process id */
    int size = MPI::COMM_WORLD.Get_size(); /* get number of processes */

    std::cout << "======= Starting processs "
    << processId
    << std::endl;


    if (m_NetworkSize != size)
    {
        if (processId == 0)
        {
            std::cout << "Exit. Not enough nodes! Expected nodes: "<< m_NetworkSize << std::endl;
        }
        m_isValid = false;
        return;
    }

    if (processId >= m_NetworkSize)
    {
        std::cout << "WARNING!! This node is out of network. NodeRank: "<< processId << std::endl;
        m_isValid = false;
        return;
    }
    MPI::Graphcomm graphComm = MPI::COMM_WORLD.Create_graph(m_NetworkSize, index, edges,true);

    if(graphComm.Get_topology() != MPI::GRAPH)
    {
        m_isValid = false;
        return;
    }

    m_pNode = new Node(graphComm);
}

NetworkSim::Node* NetworkSim::getNode()
{
	return m_pNode;
}

int NetworkSim::getSize()
{
	return m_NetworkSize;
}


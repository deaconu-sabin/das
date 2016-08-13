/*
 * NetworkSim.cpp
 *      Author: sabin
 */

#include "NetworkSim.h"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////
/// Define NetworkSim::Node
////////////////////////////////////////////////////////////////////////////////

NetworkSim::Node::Node(MPI::Graphcomm& graphComm):
		m_GraphComm(graphComm),
		m_rank(-1),
		m_neigborsCount(0),
		m_neighborsRanks(NULL),
		m_lmsFilter(3),
		m_u(0),
		m_d(0),
		m_estimatedWeights(),
		m_localWeights()
{
	m_rank = m_GraphComm.Get_rank();

	m_neigborsCount = m_GraphComm.Get_neighbors_count(m_rank);

	m_neighborsRanks = new int[m_neigborsCount];
	m_GraphComm.Get_neighbors(m_GraphComm.Get_rank(), m_neigborsCount, m_neighborsRanks);

	m_estimatedWeights = m_lmsFilter.getWeights();
	m_localWeights = m_estimatedWeights;

	std::cout << "COMM_RANK " << MPI::COMM_WORLD.Get_rank()
		<< "; Topology " << m_GraphComm.Get_topology()
		<< "; GRAPH_RANK " << m_rank
		<< "; NEIGHBORS COUNT " << m_neigborsCount
		<< "; NEIGH[0] " <<  m_neighborsRanks[0]
		<< "; NEIGH[1] " <<  m_neighborsRanks[1]
		<< "; NEIGH[2] " <<  m_neighborsRanks[2]
		//<< "; NEIGH[3] " <<  m_neighborsRanks[3]
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

void NetworkSim::Node::adaptThenCombine()
{
	const double NEIGH_DATA_COEFFICIENT =0.0;
	const double NEIGH_ESTIMATED_WEIGHT_COEFFICIENT = 1.0/(m_neigborsCount+1);

	// adapt local filter
	//m_lmsFilter.adapt(m_u, m_d);

	m_localWeights = m_estimatedWeights;
//	std::cout << m_rank
//			  << " ATC local W = "
//			  << m_localWeights
//			  <<std::endl;
	double error = LmsFilter::Adapt(m_u, m_d, m_localWeights);

	for(unsigned i = 0; i < m_estimatedWeights.size(); ++i)
	{
		m_estimatedWeights[i] = NEIGH_ESTIMATED_WEIGHT_COEFFICIENT *
								m_localWeights[i];
	}
	for(unsigned neighIdx = 0; neighIdx < m_neigborsCount; ++neighIdx)
	{
		int neighRank = -1;
		std::vector<double> neighWeights = receiveDataFromNeighbor(&neighRank);
		assert(m_estimatedWeights.size() == neighWeights.size());

		for(unsigned i = 0; i < m_estimatedWeights.size(); ++i)
		{
			m_estimatedWeights[i] += NEIGH_ESTIMATED_WEIGHT_COEFFICIENT *
				                	neighWeights[i];
		}
	}
	std::cout << m_rank
			  << " ATC estimated W = "
			  << std::fixed << m_estimatedWeights
			  << " Err = "
			  << std::fixed << error
			  <<std::endl;
}

void NetworkSim::Node::sendDataToNeighbor(int destination)
{
	double buffer[100] = {0};
	std::vector<double> weightsToSend = m_lmsFilter.getWeights();
//		std::cout << m_rank
//			<< " --> "
//			<< destination
//			<< " Data: "
//			<< m_localWeights
//			<< std::endl;
	m_GraphComm.Send(&(m_localWeights[0]), m_localWeights.size(), MPI::DOUBLE, destination, /*tag*/ 100);
}

void NetworkSim::Node::receiveDataFromNeighbors()
{
	for(int i = 0; i< m_neigborsCount; i++)
	{
		int source = -1;
		receiveDataFromNeighbor(&source);
	}
}

std::vector<double> NetworkSim::Node::receiveDataFromNeighbor(int* source)
{
	static std::vector<double> receivedWeights;

	MPI::Status status;
	double buffer[100];
	m_GraphComm.Recv(buffer, 100,
			         MPI::DOUBLE,
			         MPI::ANY_SOURCE,
			         /*tag*/ 100,
			         status);

	*source = status.Get_source();
	int count = status.Get_count(MPI::DOUBLE);
	receivedWeights = std::vector<double>(buffer, buffer+count);

//	std::cout << m_rank
//		<< " <-- "
//		<< status.Get_source()
//		<< " Data: "
//		<< receivedWeights
//		<< std::endl;

	return receivedWeights;
}

void NetworkSim::Node::set(const ISystemFunction::Input&  input)
{
	m_u = input;
}
void NetworkSim::Node::set(const ISystemFunction::Output& output)
{
	m_d = output;
}

void NetworkSim::Node::dump()
{
	std::cout << "Node[" << m_rank
		<< "]: U = " << m_u
		<< "; D = " <<  m_d
		<< "; Estim_W " <<  m_estimatedWeights
		<< std::endl;
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
    MPI::Init();      /* starts MPI */
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

    // Predifined topology
    //TODO: read topology from net config
    m_NetworkSize = 4;
    int index[] = {3,6,9,12};
    int edges[] = {1,2,3,
            0,2,3,
            0,1,3,
            0,1,2};


    processId = MPI::COMM_WORLD.Get_rank();   /* get current process id */
    int size = MPI::COMM_WORLD.Get_size(); /* get number of processes */

    std::cout << "======= Starting processs "
    << processId
    << std::endl;


    if (m_NetworkSize != size)
    {
        if (processId == 0)
        {
            std::cout << "Exit. Not enough nodes! Expected nodes: "
            		  << m_NetworkSize << std::endl;
        }
        m_isValid = false;
        return;
    }

    if (processId >= m_NetworkSize)
    {
        std::cout << "WARNING!! This node is out of network. NodeRank: "
        		  << processId << std::endl;
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



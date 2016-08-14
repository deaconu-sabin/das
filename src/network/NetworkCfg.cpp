/*
 * NetworkCfg.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#include "NetworkCfg.hpp"
#include "../Logging.hpp"
#include <fstream>

NetworkCfg::NetworkCfg()
    : nodesNumber(0)
    , logLevel(Logging::ERROR)
    , nodeType(NODE_UNDEF)
    , topologyType(TOPOLOGY_UNDEF)
    , nodeEdges()
    , m_filename("net.cfg")
{
}
void NetworkCfg::setFileName(const char* file)
{
    std::string newFile(file);
    m_filename = newFile;
}

bool NetworkCfg::deserialize()
{
    std::ifstream file;
    file.open(m_filename.c_str(), std::ifstream::in);

    if (!file.good())
    {
        log.Err() << "NetworkCfg : Cannot open file "
                  << m_filename << std::endl;
        return false;
    }

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];

    log.Info() << " Read Configuration\n";

    char tokenLeft;
    char tokenRight;
    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> nodesNumber;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "NetworkCfg : Reading error! (nodes)\n";
        return false;
    }else
    {
        log.Info() << " nodes = " << nodesNumber
                << std::endl;
    }
    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> logLevel;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);
    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "NetworkCfg : Reading error! (logLevel)\n";
        return false;
    }else
    {
        log.Info() <<" logLevel = " << logLevel
                << std::endl;
    }

    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> nodeType;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "NetworkCfg : Reading error! (nodeType)\n";
        return false;
    }else
    {
        log.Info() <<" nodeType = " << nodeType
                << std::endl;
    }

    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> topologyType;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "NetworkCfg : Reading error! (topologyType)\n";
        return false;
    }else
    {
        log.Info() <<" topologyType = " << topologyType
                << std::endl;
    }

    if(topologyType == NetworkCfg::TOPOLOGY_GRAPH)
    {
        //read adjacency matrix
        file.getline(buffer, BUFFER_SIZE);
        for(int node = 0; node < nodesNumber; node++)
        {
            file >> tokenLeft;
            for(int neighNode = 0; neighNode < nodesNumber; neighNode++)
            {
                int edge;
                file >> edge;
                nodeEdges[node].push_back(edge);
            }
            file >> tokenRight;
            if(tokenLeft != '[' || tokenRight != ']')
            {
                file.close();
                log.Err() << "NetworkCfg : Reading error! Matrix line "
                        << node << std::endl;
                return false;
            }else
            {
                log.Info() << nodeEdges[node] <<std::endl;
            }
        }
    }
    file.close();
    return true;
};

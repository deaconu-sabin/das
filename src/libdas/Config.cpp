/*
 * Config.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#include "Config.hpp"
#include "Logging.hpp"
#include <fstream>

using namespace das;

Config::Config()
    : nodesNumber(0)
    , logLevel(Logging::ERROR)
    , nodeAlgorithm("default")
    , topologyType(TOPOLOGY_UNDEF)
    , nodeEdges()
    , log("NetSim", "Config")
    , m_filename("net.cfg")
{
    log.setLevel(Logging::INFO);
}
void Config::setFileName(const std::string& filename)
{
    m_filename = filename;
}

bool Config::deserialize()
{
    std::ifstream file;
    file.open(m_filename.c_str(), std::ifstream::in);

    if (!file.good())
    {
        log.Err() << "Config : Cannot open file "
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
        log.Err() << "Config : Reading error! (nodes)\n";
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
        log.Err() << "Config : Reading error! (logLevel)\n";
        return false;
    }else
    {
        log.Info() <<" logLevel = " << logLevel
                << std::endl;
    }

    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> nodeAlgorithm;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "Config : Reading error! (nodeAlgorithm)\n";
        return false;
    }else
    {
        log.Info() <<" nodeAlgorithm = " << nodeAlgorithm
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
        log.Err() << "Config : Reading error! (topologyType)\n";
        return false;
    }else
    {
        log.Info() <<" topologyType = " << topologyType
                << std::endl;
    }

    if(topologyType == Config::TOPOLOGY_GRAPH)
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
                log.Err() << "Config : Reading error! Matrix line "
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

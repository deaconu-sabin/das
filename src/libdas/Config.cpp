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

const size_t STRING_SZ = 32;

Config::Config()
    : nodesNumber(0)
    , nodeAlgorithm(STRING_SZ, '\0')
    , outputFile(STRING_SZ, '\0')
    , logLevel(Logging::ERROR)
    , topologyType(TOPOLOGY_UNDEF)
    , nodeEdges()
    , m_filename(STRING_SZ, '\0')
{

}
void Config::setFileName(const std::string& filename)
{
    m_filename = filename;
}

bool Config::deserialize()
{
    Logging log("Network", "Configuration");

    std::ifstream file;
    file.open(m_filename.c_str(), std::ifstream::in);

    if (!file.good())
    {
        log.Err() << "Cannot open file "
                  << m_filename << std::endl;
        return false;
    }

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    char tokenLeft;
    char tokenRight;
    log.Info() << " Read Configuration\n";

    ////////////////////////////////////////////
    /// NODE NUMBER
    /////////////////////////////////////////////
    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> nodesNumber;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "Reading error! (nodes)\n";
        return false;
    }else
    {
        log.Info() << " nodes = " << nodesNumber
                << std::endl;
    }


    ////////////////////////////////////////////
    /// NODE ALGORITHM
    /////////////////////////////////////////////
    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> nodeAlgorithm;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "Reading error! (nodeAlgorithm)\n";
        return false;
    }else
    {
        log.Info() <<" nodeAlgorithm = " << nodeAlgorithm
                << std::endl;
    }


    ////////////////////////////////////////////
    /// OUPUT FILE
    /////////////////////////////////////////////
    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> outputFile;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "Reading error! (outputFile)\n";
        return false;
    }else
    {
        log.Info() <<" outputFile = " << outputFile
                << std::endl;
    }


    ////////////////////////////////////////////
    /// LOG LEVEL
    /////////////////////////////////////////////
    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> logLevel;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "Reading error! (logLevel)\n";
        return false;
    }else
    {
        log.Info() <<" logLevel = " << logLevel
                << std::endl;
    }


    ////////////////////////////////////////////
    /// TOPOLOGY TYPE
    /////////////////////////////////////////////
    file.getline(buffer, BUFFER_SIZE);
    file >> tokenLeft;
    file >> topologyType;
    file >> tokenRight;
    file.getline(buffer, BUFFER_SIZE);

    if(tokenLeft != '[' || tokenRight != ']')
    {
        file.close();
        log.Err() << "Reading error! (topologyType)\n";
        return false;
    }else
    {
        log.Info() <<" topologyType = " << topologyType
                << std::endl;
    }


    ////////////////////////////////////////////
    /// ADJACENCY MATRIX
    /////////////////////////////////////////////
    if(topologyType == Config::TOPOLOGY_GRAPH)
    {
        //read adjacency matrix
        file.getline(buffer, BUFFER_SIZE);
        for(int node = 0; node < nodesNumber; node++)
        {
            nodeEdges[node].reserve(nodesNumber);
            file >> tokenLeft;
            for(int neighNode = 0; neighNode < nodesNumber; neighNode++)
            {
                // TODO add neighbor ID instead of bool
                int edge;
                file >> edge;
                nodeEdges[node].push_back(edge);
            }
            file >> tokenRight;
            if(tokenLeft != '[' || tokenRight != ']')
            {
                file.close();
                log.Err() << "Reading error! Matrix line "
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

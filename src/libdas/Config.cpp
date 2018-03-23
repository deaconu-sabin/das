/*
 * Config.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#include "Config.hpp"
#include "Logging.hpp"
#include <fstream>


char das::Config::TOPOLOGY_UNDEF[] = "undef";
char das::Config::TOPOLOGY_INNER[] = "inner";
char das::Config::TOPOLOGY_GRAPH[] = "graph";
char das::Config::TOPOLOGY_CART[] = "cart";
char das::Config::TOPOLOGY_TOR[] = "tor";


bool das::Config::loadFromFile(const std::string& filename)
{
    das::Logging log;
    std::ifstream file(filename.c_str());

    if (!file.good())
    {
        throw std::runtime_error("Cannot open file " + filename);
    }

    log.Info() << " Read Configuration\n";

    ////////////////////////////////////////////
    /// NODES
    /////////////////////////////////////////////
    file.ignore(20, '=');
    file >> nodesNumber;
    if(!file)
    {
        throw std::runtime_error("Failed to read nodes number");   
    }

    ////////////////////////////////////////////
    ///ALGORITHM
    /////////////////////////////////////////////
    file.ignore(20, '=');
    file >> nodeAlgorithm;
    if(!file)
    {
        throw std::runtime_error("Failed to read algoritm name");   
    }

    ////////////////////////////////////////////
    /// OUPUT FILE
    /////////////////////////////////////////////
    file.ignore(20, '=');
    file >> outputFile;
    if(!file)
    {
        throw std::runtime_error("Failed to read log file name");   
    }

    ////////////////////////////////////////////
    /// LOG LEVEL
    /////////////////////////////////////////////
    file.ignore(20, '=');
    file >> logLevel;
    if(!file)
    {
        throw std::runtime_error("Failed to read log level");   
    }

    ////////////////////////////////////////////
    /// TOPOLOGY TYPE
    /////////////////////////////////////////////
    file.ignore(20, '=');
    file >> topologyType;
    if(!file)
    {
        throw std::runtime_error("Failed to read topology type");   
    }


    ////////////////////////////////////////////
    /// ADJACENCY MATRIX
    /////////////////////////////////////////////
    if(topologyType == Config::TOPOLOGY_GRAPH)
    {
        //read adjacency matrix
        for(int node = 0; node < nodesNumber; node++)
        {
            neighborMap[node].clear();
            neighborMap[node].reserve(nodesNumber);
            for(int neighNode = 0; neighNode < nodesNumber; neighNode++)
            {
                int edge;
                file >> edge;
                if(neighNode != node)
                {
                    if(edge != 0)
                    {
                        neighborMap[node].push_back(neighNode);
                    }
                }
            }
            if(!file)
            {
                throw std::runtime_error("Failed to read adjacency matrix");            }
        }
    }
    return true;
};

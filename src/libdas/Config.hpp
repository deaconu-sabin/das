/*
 * Config.hpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "Logging.hpp"
#include <string>
#include <vector>
#include <map>

namespace das{

class Config
{
    public:
        enum TopologyType
        {
            TOPOLOGY_UNDEF,
            TOPOLOGY_INNER,
            TOPOLOGY_GRAPH ,
            TOPOLOGY_CART,
            TOPOLOGY_TOR
        };

        Config();
        void setFileName(const std::string& filename);
        bool deserialize();
        bool serialize();

        int nodesNumber;
        std::string nodeAlgorithm;
        std::string outputFile;
        int logLevel;
        int topologyType;
        std::map<int, std::vector<int> > nodeEdges;
    private:
        std::string m_filename;
};

}
#endif /* CONFIG_HPP_ */

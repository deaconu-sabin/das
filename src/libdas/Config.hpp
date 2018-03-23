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
            static char TOPOLOGY_UNDEF[];
            static char TOPOLOGY_INNER[];
            static char TOPOLOGY_GRAPH[];
            static char TOPOLOGY_CART[];
            static char TOPOLOGY_TOR[];

            int nodesNumber;
            std::string nodeAlgorithm;
            std::string outputFile;
            std::string logLevel;
            std::string topologyType;
            std::map<int, std::vector<int> > neighborMap;

            bool loadFromFile(const std::string& filename);
    };

}
#endif /* CONFIG_HPP_ */

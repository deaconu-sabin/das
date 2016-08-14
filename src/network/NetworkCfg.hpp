/*
 * NetworkCfg.hpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#ifndef NETWORKCFG_HPP_
#define NETWORKCFG_HPP_

#include <string>
#include <vector>
#include <map>

class NetworkCfg
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
        enum NodeType
        {
            NODE_UNDEF,
            NODE_DEFAULT,
            NODE_LMS_ADAPT_AND_COMBINE,
        };

        NetworkCfg();
        void setFileName(const char* file);
        bool deserialize();
        bool serialize();

        int nodesNumber;
        int logLevel;
        int nodeType;
        int topologyType;
        std::map<int, std::vector<int> > nodeEdges;
    private:
        std::string m_filename;

};

#endif /* NETWORKCFG_HPP_ */

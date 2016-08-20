/*
 * Network.h
 *      Author: sabin
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <fstream>
#include <vector>
#include <das/IAlgorithm.hpp>


namespace das{

class NetworkImpl;

class Network
{
public:
    static const int INVALID_VALUE;
    Network();
    ~Network();
    static Network& Instance();

    int GetMyId() const;
    int GetMyRank() const;
    int GetTopology() const;
    int GetSize() const;
    std::vector<int> GetMyNeighbors() const;

    void LoadConfiguration(const std::string& configFile) const;
    IAlgorithm* LoadAlgorithm() const;

    bool RecvData(std::vector<double>& receivedData);
    bool RecvDataFrom(std::vector<double>& receivedData, int source);

    bool SendData(const std::vector<double>& inData);
    bool SendDataTo(const std::vector<double>& inData, int dest);

    void LogMessage(const std::string& message);
    void ToString() const;

private:
    Network(const Network&);
    Network& operator=(const Network&);

    NetworkImpl* net;
};

}
#endif /* NETWORK_H_ */

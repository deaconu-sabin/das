

#include "NetworkSim.h"

int main(int argc, char** argv)
{
    NetworkSim::Node* node = NetworkSim::getInstance().getNode();

    if(node != NULL)
    {
        for (int nodeRank = 0; nodeRank < NetworkSim::getInstance().getSize(); nodeRank++)
        {
            if(node->getRank() == nodeRank)
            {
                node->receiveDataFromNeighbors();
            }
            else
            {
                node->sendDataToNeighbor(nodeRank);
            }
        }
    }
    return 0;
}

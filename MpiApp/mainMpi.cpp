

#include <iostream>
#include "NetworkSim.h"
#include "LinearFunction.h"

int main(int argc, char** argv)
{

    NetworkSim::Node* node = NetworkSim::getInstance().getNode();

    if(node != NULL)
    {
    	ISystemFunction* system = new LinearFunction(2.0, 0.2);
    	unsigned maxTime = 20;
    	for(unsigned time = 0; time < maxTime; time++)
    	{
    		// this is value for regression vector (1 element)
    		// for this node at this time
    		double u = (time+0.3) * (node->getRank()+1);

    		// we set the pair {d,u}
    		// u - is input
    		// d - is system outcome
    		ISystemFunction::Input input(1,u);
    		node->set(input);
    		node->set(system->evaluate(input));

    		std::cout <<"Node["
    				  << node->getRank()
    				  << "] data: u = "
    				  << input[0]
    				  << "\td = "
    				  << system->evaluate(input)
    				  <<std::endl;

			for (int nodeRank = 0; nodeRank < NetworkSim::getInstance().getSize(); nodeRank++)
			{
				if(node->getRank() == nodeRank)
				{
					node->adaptThenCombine();
				}
				else
				{
					node->sendDataToNeighbor(nodeRank);
				}
			}

	    	node->dump();
    	}

    	delete system;
    }
    return 0;
}

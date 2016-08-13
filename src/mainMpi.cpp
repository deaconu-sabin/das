

#include <iostream>
#include "network/NetworkSim.h"
#include <adaptivefilter/LinearFunction.h>

int main(int argc, char** argv)
{

    NetworkSim::Node* node = NetworkSim::getInstance().getNode();

    if(node != NULL)
    {
    	//ISystemFunction* system = new LinearFunction(2.0, 0.2);

    	std::vector<double> coefficients;
    	coefficients.push_back(2);
    	coefficients.push_back(1);
    	coefficients.push_back(5);
    	ISystemFunction* system = new MultivariateFunction(coefficients);

    	unsigned maxTime = 500;
    	for(unsigned time = 0; time < maxTime; time++)
    	{
    		// we set the pair {d,u}
    		// u - is input
    		// d - is system outcome
    		ISystemFunction::Input input = system->generateInput();
    		node->set(input);
    		node->set(system->evaluate(input));

    		std::cout <<"Node["
    				  << node->getRank()
    				  << "] data: u = "
    				  << input
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

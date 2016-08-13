
#include <iostream>
#include "LinearFunction.h"
#include "LmsFilter.h"

int main (int argc, char** argv)
{
	LinearFunction f(2,0.5);

//	std::vector<double> coefficients;
//	coefficients.push_back(2);
//	coefficients.push_back(1);
//	coefficients.push_back(5);
//	MultivariateFunction f(coefficients);

	LmsFilter lmsFilter(f.generateInput().size());

	for (unsigned time = 0; (time < 500 && lmsFilter.getOutputError() > 0.0001) ; ++time)
	{
		ISystemFunction::Input input(f.generateInput());
		std::cout<< input << " -> "<< f.evaluate(input)<<"\n";

		lmsFilter.adapt(input, f.evaluate(input));

		std::cout 	<< time
					<< "; w = "
					<< lmsFilter.getWeights()<<"\n\n";
	}

	return 0;
}


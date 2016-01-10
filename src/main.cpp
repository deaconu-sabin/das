
#include <iostream>
#include "LinearFunction.h"
#include "LmsFilter.h"

int main (int argc, char** argv)
{
	// f(x) = 1.5x + 2;
	LinearFunction f(2,1);
	LmsFilter lmsFilter(1);

	for (double x = 20; x >= 0.0 ; x-=0.7)
	{
		ISystemFunction::Input input(1,x);
		std::cout<< x << " -> "<< f.evaluate(input)<<"\n";

		double error = lmsFilter.adapt(input, f.evaluate(input));
		std::cout <<"LMS == > error=" << error
				  <<"; lmsFilter.eval=" << lmsFilter.eval(input)<<"\n\n";
	}

	//
	ISystemFunction::Input input(1,10);
	std::cout <<"LMS == > error=" << lmsFilter.getError()
			  <<"; eval(10)=" << lmsFilter.eval(input)<<"\n";

	return 0;
}


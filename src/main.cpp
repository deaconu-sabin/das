
#include <iostream>
#include "LinearFunction.h"
#include "LmsFilter.h"

int main (int argc, char** argv)
{
	// f(x) = 1.5x + 2;
	LinearFunction f(2,1);

	LmsFilter::SampleData sampleData;
	for (double x = 20; x >= 0.0 ; x-=0.7)
	{
		std::cout<< x << " -> "<< f.eval(x)<<"\n";
		sampleData.push_back(std::pair<double, double>(x, f.eval(x)));
	}

	LmsFilter lmsFilter(1);

	double error = lmsFilter.adaptFor(sampleData);

	std::cout <<" == > error=" << error
			  <<"; eval(10)=" << lmsFilter.eval(10)<<"\n";

	return 0;
}


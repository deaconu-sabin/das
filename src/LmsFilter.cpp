
#include "LmsFilter.h"
#include <iostream>
#include <cassert>

LmsFilter::LmsFilter(int filterOrder):
	m_filterOrder(filterOrder),
	m_stepSize(0.001),
	m_weights(m_filterOrder, 0.0),
	m_error(99.99)
{
}


double LmsFilter::adapt(const ISystemFunction::Input&  input,
	     	 	 	 	const ISystemFunction::Output& output)
{

	m_error = output - eval(input);
	double err = m_error* m_error;
	std::cout << "E = " << err
			  << "; W = " << m_weights
			  << "; D = " << 2*m_error*(-input[0])
			  << "\n";

	m_weights[0] = m_weights[0] + m_stepSize * m_error * input[0];

	return m_error;
}

double LmsFilter::Adapt(const ISystemFunction::Input&  input,
	     	 	 	const ISystemFunction::Output& output,
	     	 	 	WeightVector& weights,
	     	 	 	double gradientStep)
{
	WeightVector oldWeight = weights;
	double error = output - (input[0]*weights[0]);
	weights[0] = weights[0] + gradientStep * error * input[0];

	//squared error
	error = error*error;
	std::cout << "Lms:Adapt: err = " << error
			  << "; oW = " << oldWeight
			  << " => nW " << weights
			  << std::endl;

	return error;
}

double LmsFilter::eval(const ISystemFunction::Input&  input)
{
	assert(m_weights.size() == input.size());
	return m_weights[0] * input[0];
}

double LmsFilter::getError()
{
	return m_error;
}

const std::vector<double>& LmsFilter::getWeights()
{
	return m_weights;
}

std::ostream& operator<<(std::ostream& os, std::vector<double> data)
{
	os << "[ ";
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		os << data[i] << " ";
	}
	os << "]";
	return os;
}

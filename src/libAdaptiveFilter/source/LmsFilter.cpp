
#include "LmsFilter.h"
#include <iostream>
#include <cassert>

LmsFilter::LmsFilter(int filterOrder):
	m_filterOrder(filterOrder),
	m_stepSize(0.00001),
	m_weights(m_filterOrder, 0.0),
	m_error(99.99)
{
}

double LmsFilter::adapt(const ISystemFunction::Input&  input,
	     	 	 	 	const ISystemFunction::Output& output)
{

	m_error = output - eval(input);
	for(unsigned i = 0; i < m_weights.size(); ++i)
	{
		double err = m_error* m_error;
		std::cout << "E = " << err
				  << "; W = " << m_weights[0]
				  << "; Deriv = " << 2*m_error*(-input[i])
				  << "\n";

		m_weights[i] = m_weights[i] + m_stepSize * m_error * input[i];
	}

	//return squared error
	return m_error*m_error;
}

double LmsFilter::Adapt(const ISystemFunction::Input&  input,
	     	 	 	const ISystemFunction::Output& desiredOutput,
	     	 	 	WeightVector& weights,
	     	 	 	double gradientStep)
{
	assert(weights.size() == input.size());

	WeightVector oldWeight = weights;

	double actualOutput = 0.0;
	for(unsigned i = 0; i<weights.size(); ++i)
	{
		actualOutput += weights[i] * input[i];
	}

	double error = desiredOutput - actualOutput;
	for(unsigned i = 0; i < weights.size(); ++i)
	{
		weights[i] = weights[i] + gradientStep * error * input[i];
	}

	//squared error
	error = error*error;
//	std::cout << "Lms:Adapt: err = " << error
//			  << "; oldW = " << oldWeight
//			  << " => newW " << weights
//			  << std::endl;

	return error;
}

double LmsFilter::eval(const ISystemFunction::Input&  input)
{
	assert(m_weights.size() == input.size());

	double out = 0.0;
	for(unsigned i = 0; i<m_weights.size(); ++i)
	{
		out += m_weights[i] * input[i];
	}

	return out;
}

double LmsFilter::getOutputError()
{
	return m_error*m_error;
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

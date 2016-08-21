
#include "LmsFilter.h"
#include <cassert>

LmsFilter::LmsFilter(int filterOrder):
	m_filterOrder(filterOrder),
	m_stepSize(0.00001),
	m_weights(m_filterOrder, 0.0),
	m_error(99.99)
{
}

double LmsFilter::adapt(const InputListType&    input,
                        const OutputType&       output)
{

	m_error = output - eval(input);
	for(unsigned i = 0; i < m_weights.size(); ++i)
	{
		m_weights[i] = m_weights[i] + m_stepSize * m_error * input[i];
	}

	return m_error*m_error;
}

double LmsFilter::Adapt(const InputListType&    input,
                        const OutputType&       desiredOutput,
                        WeightLisType&          weights,
                        double                  gradientStep)
{
	assert(weights.size() == input.size());

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

	return error;
}

double LmsFilter::eval(const InputListType&  input)
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


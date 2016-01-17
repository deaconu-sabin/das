
#include "LinearFunction.h"
#include "NumberGenerator.h"

#include <cassert>
#include <cstdlib>

LinearFunction::LinearFunction(double a, double b):
ISystemFunction(),
m_a(a),
m_b(b)
{
}

LinearFunction::~LinearFunction()
{
}

ISystemFunction::Output LinearFunction::evaluate(const ISystemFunction::Input& input)
{
	assert(1 == input.size());
	return (m_a*input[0] + m_b);
}

ISystemFunction::Input LinearFunction::generateInput()
{
	//create an one element vector;
	ISystemFunction::Input input(1,0.0);

	// generates numbers between 0 and 200
	input[0] = NumberGenerator::GenerateReal(0.0, 200.0);
	return input;
}


MultivariateFunction::MultivariateFunction(const std::vector<double>& coefficients):
		ISystemFunction(),
		m_coefficients(coefficients)
{
}

MultivariateFunction::~MultivariateFunction()
{
}

ISystemFunction::Output MultivariateFunction::evaluate(const ISystemFunction::Input& x)
{
	assert(x.size() == m_coefficients.size());

	ISystemFunction::Output output = 0;
	for(unsigned i = 0; i < m_coefficients.size(); ++i)
	{
		output += x[i] * m_coefficients[i];
	}

	return output;
}

ISystemFunction::Input MultivariateFunction::generateInput()
{
	//create an one element vector;
	ISystemFunction::Input input(m_coefficients.size(),0.0);

	for(unsigned int i = 0; i < input.size(); ++i)
	{
		// generates numbers between -100 and 100
		input[i] = NumberGenerator::GenerateReal(-100.0, 100.0);
	}

	return input;
}

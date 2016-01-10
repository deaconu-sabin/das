
#include "LinearFunction.h"

#include <cassert>

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

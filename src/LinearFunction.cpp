
#include "LinearFunction.h"

LinearFunction::LinearFunction(double a, double b):
m_a(a),
m_b(b)
{
}

double LinearFunction::eval(double x)
{
	return (m_a*x + m_b);
}

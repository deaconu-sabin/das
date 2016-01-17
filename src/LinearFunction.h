
#ifndef LINEARFUNCTION_H_
#define LINEARFUNCTION_H_

#include "ISystemFunction.h"

class LinearFunction: public ISystemFunction
{
public:
	LinearFunction(double a, double b);
	virtual ~LinearFunction();

	virtual ISystemFunction::Output evaluate(const ISystemFunction::Input& x);
	virtual ISystemFunction::Input  generateInput();

private:
	double m_a;
	double m_b;
};


class MultivariateFunction:public ISystemFunction
{
public:
	MultivariateFunction(const std::vector<double>& coefficients);
	virtual ~MultivariateFunction();

	virtual ISystemFunction::Output evaluate(const ISystemFunction::Input& x);
	virtual ISystemFunction::Input  generateInput();

private:
	std::vector<double> m_coefficients;
};

#endif /* LINEARFUNCTION_H_ */

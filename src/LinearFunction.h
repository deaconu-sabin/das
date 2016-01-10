
#ifndef LINEARFUNCTION_H_
#define LINEARFUNCTION_H_

#include "ISystemFunction.h"

class LinearFunction: public ISystemFunction
{
public:
	LinearFunction(double a, double b);

	virtual ISystemFunction::Output evaluate(const ISystemFunction::Input& x);
	virtual ~LinearFunction();

private:
	double m_a;
	double m_b;
};

#endif /* LINEARFUNCTION_H_ */

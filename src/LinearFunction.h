
#ifndef LINEARFUNCTION_H_
#define LINEARFUNCTION_H_

class LinearFunction {
public:
	LinearFunction(double a, double b);

	double eval(double x);

private:
	double m_a;
	double m_b;
};

#endif /* LINEARFUNCTION_H_ */

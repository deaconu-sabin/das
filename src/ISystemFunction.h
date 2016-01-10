
#ifndef ISYSTEMFUNCTION_H_
#define ISYSTEMFUNCTION_H_

#include <vector>

class ISystemFunction
{
public:
	typedef std::vector<double> Input;
	typedef double 				Output;

	virtual Output evaluate(const Input& input) = 0;
	virtual ~ISystemFunction(){};
};

#endif

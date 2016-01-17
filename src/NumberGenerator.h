
#ifndef NUMBERGENERATOR_H_
#define NUMBERGENERATOR_H_

#include <vector>

class NumberGenerator {

public:
	static double GenerateReal();
	static double GenerateReal(int min, int max);

	static int GenerateInt();
	static int GenerateInt(int min, int max);

	static std::vector<double> GenerateDistribution(int 	count,
													double 	deviation=1,
													double 	mean = 0);

};

#endif /* NUMBERGENERATOR_H_ */

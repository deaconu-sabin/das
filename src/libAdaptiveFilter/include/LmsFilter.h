
#ifndef LMSFILTER_H_
#define LMSFILTER_H_

#include "ISystemFunction.h"

#include <vector>

class LmsFilter
{
public:

	typedef std::vector<double> WeightVector;
	/**
	 * Creates LmsFilter.
	 * @param Order - order of filter (number of weights)
	 */
	LmsFilter(int order);

	double adapt(const ISystemFunction::Input&  input,
			     const ISystemFunction::Output& output);

	/**
	 * @param input  - system input
	 * @param output - system output
	 * @param weight - filter weight to be updated
	 * @return squared error
	 */
	static double Adapt(const ISystemFunction::Input&  input,
		     	 	 	const ISystemFunction::Output& desiredOutput,
		     	 	 	WeightVector& weights,
		     	 	 	double gradientStep = 0.00001);

	/**
	 * Evaluate data and return a value
	 * @param	input - data to be interpreted
	 * @return 	value - result of filter
	 */
	double eval(const ISystemFunction::Input&  input);

	/**
	 * @return squared error
	 */
	double getOutputError();

	const std::vector<double>& getWeights();

private:
	int						m_filterOrder;
	double					m_stepSize;
	std::vector<double>		m_weights;
	double 					m_error;
};

#endif /* LMSFILTER_H_ */

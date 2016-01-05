
#ifndef LMSFILTER_H_
#define LMSFILTER_H_

#include <vector>

class LmsFilter {
public:
	// sample data is pair between output and desired data
	typedef std::vector<std::pair<double, double> > SampleData;

	/**
	 * Creates LmsFilter.
	 * @param Order - order of filter (number of weights)
	 */
	LmsFilter(int order);


	double adaptFor(SampleData );

	/**
	 * Evaluate data and return a value
	 * @param	input - data to be interpreted
	 * @return 	value - result of filter
	 */
	double eval(double input);

private:
	int						m_filterOrder;
	double					m_stepSize;
	std::vector<double>		m_weights;
};

#endif /* LMSFILTER_H_ */

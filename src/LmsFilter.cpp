
#include "LmsFilter.h"
#include <iostream>

LmsFilter::LmsFilter(int filterOrder):
	m_filterOrder(filterOrder),
	m_stepSize(0.001),
	m_weights(m_filterOrder, 0.0)
{
}


double LmsFilter::adaptFor(SampleData data)
{
	double error = 99.99;
//	 m_weights[0] = data[0].second / data[0].first;
	for(int i=0;i<3;i++)
	for(unsigned int idx = 0; idx < data.size(); ++idx)
	{
		error = data[idx].second - m_weights[0] * data[idx].first;
		double err = error* error;
		std::cout <<"error^2=" << err
				  << "; weight=" <<m_weights[0]
				  <<"; derivative=" << 2*error*(-data[idx].first)
				  <<"\n";

		m_weights[0] = m_weights[0] + m_stepSize * error * data[idx].first;

	}
	return error;
}

double LmsFilter::eval(double input)
{
	return m_weights[0]*input;
}

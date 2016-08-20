/*
 * IAlgorithm.hpp
 *
 *  Created on: Aug 15, 2016
 *      Author: sabin
 */

#ifndef IALGORITHM_HPP_
#define IALGORITHM_HPP_



namespace das
{

class IAlgorithm
{
    public:
        virtual ~IAlgorithm(){}
        virtual void setInitialData() = 0;
        virtual bool readInputData() = 0;
        virtual void processData() = 0;
        virtual void writeOutputData() = 0;
};

} /* namespace das */

extern "C" das::IAlgorithm* Create();
extern "C" void Destroy(das::IAlgorithm*);

#endif /* IALGORITHM_HPP_ */

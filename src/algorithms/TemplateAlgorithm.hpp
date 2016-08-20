/*
 * TemplateAlgorithm.hpp
 */

#ifndef TEMPLATEALGORITHM_HPP_
#define TEMPLATEALGORITHM_HPP_

#include <das/IAlgorithm.hpp>
#include <das/Network.hpp>

class TemplateAlgorithm: public das::IAlgorithm
{
    public:
        TemplateAlgorithm();
        virtual ~TemplateAlgorithm();

        ////////////////////////////////
        ///  IAlgorithm methods
        ////////////////////////////////
        virtual bool setInitialData();
        virtual bool readInputData();
        virtual bool processData();
        virtual bool writeOutputData();
        virtual bool isFinished();

};

#endif /* TEMPLATEALGORITHM_HPP_ */

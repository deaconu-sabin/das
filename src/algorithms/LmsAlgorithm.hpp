
////////////////////////////////////////////////
/// File generataed by generateAlgorithms.sh ///
////////////////////////////////////////////////


/*
 * LmsAlgorithm.hpp
 */

#ifndef LmsALGORITHM_HPP_
#define LmsALGORITHM_HPP_

#include <das/IAlgorithm.hpp>
#include <das/Network.hpp>

class LmsAlgorithm: public das::IAlgorithm
{
    public:
        LmsAlgorithm();
        virtual ~LmsAlgorithm();

        ////////////////////////////////
        ///  IAlgorithm methods
        ////////////////////////////////
        virtual bool setInitialData();
        virtual bool readInputData();
        virtual bool processData();
        virtual bool writeOutputData();
        virtual bool isFinished();

};

#endif /* LmsALGORITHM_HPP_ */

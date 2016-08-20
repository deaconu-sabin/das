
////////////////////////////////////////////////
/// File generataed by generateAlgorithms.sh ///
////////////////////////////////////////////////


/*
 * LmsAlgorithm.cpp
 *
 */

#include "LmsAlgorithm.hpp"


LmsAlgorithm::LmsAlgorithm()
{
    // TODO Auto-generated LmsAlgorithm constructor stub
}

LmsAlgorithm::~LmsAlgorithm()
{
    // TODO Auto-generated LmsAlgorithm destructor stub
}

bool LmsAlgorithm::setInitialData()
{
    das::Network::Instance().LogMessage("LmsAlgorithm is starting");

    // TODO Add LmsAlgorithm::setInitialData proper implementation

    return true;
}
bool LmsAlgorithm::readInputData()
{
    // TODO Add LmsAlgorithm::readInputData implementation
    return false;
}
bool LmsAlgorithm::processData()
{
    // TODO Add LmsAlgorithm::processData implementation
    return false;
}
bool LmsAlgorithm::writeOutputData()
{
    // TODO Add LmsAlgorithm::writeOutputData implementation
    return false;
}

bool LmsAlgorithm::isFinished()
{
    das::Network::Instance().LogMessage("LmsAlgorithm is finished");

    // TODO Add LmsAlgorithm::isFinished proper implementation

    return true;
}


extern "C"
{
    das::IAlgorithm* Create()
    {
        return new LmsAlgorithm();
    }

    void Destroy(das::IAlgorithm* algorithm)
    {
        delete algorithm;
    }
}

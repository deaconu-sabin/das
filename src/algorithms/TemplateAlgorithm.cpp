/*
 * TemplateAlgorithm.cpp
 *
 */

#include "TemplateAlgorithm.hpp"


TemplateAlgorithm::TemplateAlgorithm()
{
    // TODO Auto-generated TemplateAlgorithm constructor stub
}

TemplateAlgorithm::~TemplateAlgorithm()
{
    // TODO Auto-generated TemplateAlgorithm destructor stub
}

bool TemplateAlgorithm::setInitialData()
{
    das::Network::Instance().LogMessage("TemplateAlgorithm is starting");

    // TODO Add TemplateAlgorithm::setInitialData proper implementation

    return true;
}
bool TemplateAlgorithm::readInputData()
{
    // TODO Add TemplateAlgorithm::readInputData implementation
    return false;
}
bool TemplateAlgorithm::processData()
{
    // TODO Add TemplateAlgorithm::processData implementation
    return false;
}
bool TemplateAlgorithm::writeOutputData()
{
    // TODO Add TemplateAlgorithm::writeOutputData implementation
    return false;
}

bool TemplateAlgorithm::isFinished()
{
    das::Network::Instance().LogMessage("TemplateAlgorithm is finished");

    // TODO Add TemplateAlgorithm::isFinished proper implementation

    return true;
}


das::IAlgorithm* Create()
{
    return new TemplateAlgorithm();
}

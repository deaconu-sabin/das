

#include <das/IAlgorithm.hpp>
#include <das/Network.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    das::Network& network = das::Network::Instance();

    if(argc < 2)
    {
        network.LoadConfiguration("Network.cfg");
    }else
    {
        network.LoadConfiguration(argv[1]);
    }

    network.LogMessage("*****************************");
    network.LogMessage("           START             ");
    network.LogMessage("*****************************");

    das::IAlgorithm* algorithm = network.LoadAlgorithm();

    if(algorithm)
    {
        if(algorithm->setInitialData())
        {
            while (algorithm->isFinished() == false)
            {
                if(algorithm->readInputData())
                {
                    network.LogMessage("Algorithm::readInputData() failed!\n");
                    break;
                }

                if(!algorithm->processData())
                {
                    network.LogMessage("Algorithm::processData() failed!\n");
                    break;
                }

                if(!algorithm->writeOutputData())
                {
                    network.LogMessage("Algorithm::writeOutputData() failed!\n");
                    break;
                }
            }
        }
        else
        {
            network.LogMessage("Algorithm::setInitialData() failed!\n");
        }
    }else
    {
        std::cerr << "MainApp: Network initialization failed for PID "
                  << das::Network::Instance().GetMyId()<< std::endl;
    }

    das::Network::Instance().LogMessage("*****************************");
    das::Network::Instance().LogMessage("          MAIN END           ");
    das::Network::Instance().LogMessage("*****************************");
    return 0;
}

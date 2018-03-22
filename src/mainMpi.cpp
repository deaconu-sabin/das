


#include <das/IAlgorithm.hpp>
#include <das/Network.hpp>
#include <iostream>


int main(int argc, char** argv)
{
    try
    {
        das::Network& network = das::Network::Instance();

        bool isLoaded = false;
        if(argc < 2)
        {
            isLoaded = network.LoadConfiguration("Network.cfg");
        }else
        {
            isLoaded = network.LoadConfiguration(argv[1]);
        }

        if(!isLoaded)
        {
            std::cerr << "Network could NOT be loaded !\n";
            return 1;
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
                    if(!algorithm->readInputData())
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
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() <<std::endl;
    }
    return 0;
}

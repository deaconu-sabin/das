

#include <das/IAlgorithm.hpp>
#include <das/Network.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    das::Network::Instance().LogMessage("*****************************\n");
    das::Network::Instance().LogMessage("          MAIN START         \n");
    das::Network::Instance().LogMessage("*****************************\n");

    if(argc < 2)
    {
        das::Network::Instance().LoadConfiguration("net.cfg");
    }else
    {
        das::Network::Instance().LoadConfiguration(argv[1]);
    }
    das::IAlgorithm* algorithm =
                        das::Network::Instance().LoadAlgorithm();

    if(algorithm)
    {
        algorithm->setInitialData();
        while (algorithm->readInputData())
        {
            algorithm->processData();
            algorithm->writeOutputData();
        }
    }else
    {
        std::cerr << "MainApp: Network initialization failed for PID "
                  << das::Network::Instance().GetMyId()<< std::endl;
    }

    das::Network::Instance().LogMessage("*****************************\n");
    das::Network::Instance().LogMessage("          MAIN END           \n");
    das::Network::Instance().LogMessage("*****************************\n");
    return 0;
}

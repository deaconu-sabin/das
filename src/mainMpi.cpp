

#include "Logging.hpp"
#include "network/NetworkSim.h"
#include <adaptivefilter/LinearFunction.h>

int main(int argc, char** argv)
{
    if(NetSim().init())
    {
        NetSim().getAlgorithm()->setInitialData();

        for(unsigned time = 0; time < 100; time++)
        {
            log.Debug()<<"*****************************\n";
            log.Debug()<<"      STEP "<< time <<      "\n";
            log.Debug()<<"*****************************\n";

            NetSim().getAlgorithm()->readInputData();
            NetSim().getAlgorithm()->processData();
        }
        NetSim().getAlgorithm()->writeOutputData();
    }else
    {
        log.Err()<< "MainApp: Network initialization failed for PID "
                <<NetSim().getProcessId()<< std::endl;
    }
    return 0;
}

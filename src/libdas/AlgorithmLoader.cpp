/*
 * AlgorithmLoader.cpp
 *
 *  Created on: Aug 15, 2016
 *      Author: sabin
 */

#include "AlgorithmLoader.hpp"
#include "Logging.hpp"

#include <dlfcn.h>
#include <cassert>

using namespace das;

typedef IAlgorithm* (*CreatePtrFcn)(void);
typedef void (*DestroyPtrFcn)(IAlgorithm*);

CreatePtrFcn CreateFcn = NULL;
DestroyPtrFcn DestroyFcn = NULL;

static void* algoLib = NULL;
static IAlgorithm* algorithm = NULL;


IAlgorithm* AlgorithmLoader::load(const std::string& name)
{
    Logging log("Network","AlgorithmLoader");
    if ( algorithm )
    {
        return algorithm;
    }

    // load the algorithm library
    algoLib = dlopen(name.c_str(), RTLD_LAZY);
    if (!algoLib)
    {
        log.Err()   <<  dlerror() << std::endl;
        return NULL;
    }
    // reset errors
    dlerror();

    // load the symbols
    CreateFcn = (CreatePtrFcn) dlsym(algoLib, "Create");
    const char* dlsym_error = dlerror();
     if (dlsym_error)
     {
        log.Err() << "Cannot load symbol [Create]: " << dlsym_error << '\n';
        dlclose(algoLib);
        return NULL;
     }

    DestroyFcn = (DestroyPtrFcn) dlsym(algoLib, "Destroy");
    dlsym_error = dlerror();
    if (dlsym_error)
    {
        log.Err() << "Cannot load symbol [Destroy] : " << dlsym_error << '\n';
        dlclose(algoLib);
        return NULL;
    }
    return CreateFcn();
}
AlgorithmLoader::~AlgorithmLoader()
{
   if (algorithm)
   {
       DestroyFcn(algorithm);
       dlclose(algoLib);
   }

}


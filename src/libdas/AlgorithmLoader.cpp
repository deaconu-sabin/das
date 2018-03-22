/*
 * AlgorithmLoader.cpp
 *
 *  Created on: Aug 15, 2016
 *      Author: sabin
 */

#include "AlgorithmLoader.hpp"
#include "Logging.hpp"

#include <dlfcn.h>
#include <stdexcept>
#include <cassert>

using namespace das;

typedef IAlgorithm* (*CreatePtrFcn)(void);


IAlgorithm* AlgorithmLoader::load(const std::string& name)
{
    Logging log("Network","AlgorithmLoader");

    // load the algorithm library
    void* algoLib = dlopen(name.c_str(), RTLD_LAZY);
    if (!algoLib)
    {
        throw std::runtime_error("Cannot open " + name);
    }

    // load the symbols
    CreatePtrFcn createFcn = (CreatePtrFcn) dlsym(algoLib, "Create");
     if (!createFcn)
     {
        dlclose(algoLib);
        throw std::runtime_error("Cannot load 'Create'");
     }

    return createFcn();
}



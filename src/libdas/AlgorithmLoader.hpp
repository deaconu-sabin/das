/*
 * AlgorithmLoader.hpp
 *
 *  Created on: Aug 15, 2016
 *      Author: sabin
 */

#ifndef ALGORITHMLOADER_HPP_
#define ALGORITHMLOADER_HPP_

#include <das/IAlgorithm.hpp>
#include <string>

namespace das
{

class AlgorithmLoader
{
    public:
        ~AlgorithmLoader();
        IAlgorithm* load(const std::string& name);
};

} /* namespace das */

#endif /* ALGORITHMLOADER_HPP_ */

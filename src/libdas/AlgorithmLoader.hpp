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

	namespace AlgorithmLoader
	{
        IAlgorithm* load(const std::string& name);
	} /* AlgorithmLoader */

} /* namespace das */

#endif /* ALGORITHMLOADER_HPP_ */

/*
 * logging.hpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include <vector>
#include <string>
#include <fstream>

namespace das {

class Logging
{
    public:
        enum LogLevel
        {
            FATAL,
            ERROR,
            INFO,
            DEBUG
        };
        Logging();

        void            open(const std::string& fileName);
        void            setLevel(LogLevel level);
        void            setPrefix(const std::string& prefix);

        std::ostream&   Fatal();
        std::ostream&   Err();
        std::ostream&   Info();
        std::ostream&   Debug();

    private:
       std::ofstream    m_ofs;
       LogLevel         m_level;
       std::string      m_prefix;
};

}
std::ostream& operator<<(std::ostream& os, std::vector<double> data);
std::ostream& operator<<(std::ostream& os, std::vector<int> data);

#endif /* LOGGING_HPP_ */

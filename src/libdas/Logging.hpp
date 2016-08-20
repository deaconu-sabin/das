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
        Logging(const std::string& appName,
                const std::string& className = std::string());
        ~Logging();

        void            open(const std::string& fileName);
        void            close();

        void            setClassName(const std::string& className);
        void            setLevel(LogLevel level);
        std::ostream&   Fatal();
        std::ostream&   Err();
        std::ostream&   Info();
        std::ostream&   Debug();

    private:
       std::string      m_appName;
       std::string      m_className;
       LogLevel         m_level;
       std::ofstream    m_ofs;
       std::ofstream    m_nullStream;
};

}
std::ostream& operator<<(std::ostream& os, std::vector<double> data);
std::ostream& operator<<(std::ostream& os, std::vector<int> data);

#endif /* LOGGING_HPP_ */

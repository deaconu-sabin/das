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
        Logging(const std::string& fileName);

        std::ostream& Err();
        std::ostream& Info();
        std::ostream& Debug();

        void setLevel(LogLevel lvl);
        void setFileName(const std::string& fileName);

        void open();
        void close();
    private:
       std::string m_fileName;
       LogLevel m_level;
       std::ofstream m_ofs;
       std::ofstream m_nullStream;
};
std::ostream& operator<<(std::ostream& os, std::vector<double> data);
std::ostream& operator<<(std::ostream& os, std::vector<int> data);

extern Logging log;

#endif /* LOGGING_HPP_ */

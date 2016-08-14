/*
 * Logging.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#include "Logging.hpp"
#include <iostream>

 Logging log;

Logging::Logging()
    : m_fileName("LoggingApplication.log")
    , m_level(INFO)
{
}

Logging::Logging(const std::string& fileName)
    : m_fileName(fileName)
    , m_level(INFO)
{
}

std::ostream& Logging::Err()
{
    if(m_level >= ERROR)
    {
        if(m_ofs.is_open())
        {
            m_ofs << "ERROR: ";
            return m_ofs;
        }
        else
        {
            std::cerr << "ERROR: ";
            return std::cerr;
        }
    }else
    {
        return m_nullStream;
    }
}
std::ostream& Logging::Info()
{
    if(m_level >= INFO)
    {
        if(m_ofs.is_open())
        {
            m_ofs << "INFO: ";
            return m_ofs;
        }
        else
        {
            std::cout << "INFO: ";
            return std::cout;
        }
    }else
    {
        return m_nullStream;
    }
}

std::ostream& Logging::Debug()
{
    if(m_level >= DEBUG)
    {
        if(m_ofs.is_open())
        {
            m_ofs << "DEBUG: ";
            return m_ofs;
        }
        else
        {
            std::cout << "DEBUG: ";
            return std::cout;
        }
    }else
    {
        return m_nullStream;
    }
}

void Logging::setLevel(LogLevel lvl)
{
    m_level = lvl;
}

void Logging::setFileName(const std::string& fileName)
{
    m_fileName = fileName;
}
void Logging::open()
{
    if(m_ofs.is_open())
    {
        m_ofs.close();
    }

    m_ofs.open(m_fileName.c_str(), std::ios_base::out);
}
void Logging::close()
{
    m_ofs.close();
}

std::ostream& operator<<(std::ostream& os, std::vector<double> data)
{
    os << "[ ";
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        os << data[i] << " ";
    }
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, std::vector<int> data)
{
    os << "[ ";
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        os << data[i] << " ";
    }
    os << "]";
    return os;
}

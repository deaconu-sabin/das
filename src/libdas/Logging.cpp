/*
 * Logging.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#include "Logging.hpp"
#include <iostream>
#include <sstream>

using namespace das;

Logging::Logging(const std::string& appName, const std::string& className)
    : m_appName(appName)
    , m_className(className)
    , m_level(Logging::ERROR)
    , m_ofs()
    , m_nullStream()
{
}

Logging::~Logging()
{
    close();
}

void Logging::open(const std::string& fileName)
{
    close();
    m_ofs.open(fileName.c_str(), std::ios_base::out);
}
void Logging::close()
{
    if(m_ofs.is_open())
    {
        m_ofs.close();
    }
}

void Logging::setClassName(const std::string& className)
{
    m_className = className;
}

void Logging::setLevel(LogLevel level)
{
    m_level = level;
}

std::ostream& Logging::Fatal()
{
    static std::stringstream prefix;
    prefix.str("");
    prefix << m_appName
            << ":"
            << m_className
            << ":"
            << "FATAL: ";
    if(m_ofs.is_open())
    {
        m_ofs << prefix.str();
        return m_ofs;
    }
    else
    {
        std::cerr << prefix.str();
        return std::cerr;
    }
}

std::ostream& Logging::Err()
{
    static std::stringstream prefix;
    if(m_level >= ERROR)
    {
        prefix.str("");
        prefix << m_appName
                << ":"
                << m_className
                << ":"
                << "ERROR: ";
        if(m_ofs.is_open())
        {
            m_ofs << prefix.str();
            return m_ofs;
        }
        else
        {
            std::cerr << prefix.str();
            return std::cerr;
        }
    }else
    {
        return m_nullStream;
    }
}

std::ostream& Logging::Info()
{
    static std::stringstream prefix;
    if(m_level >= INFO)
    {
        prefix.str("");
        prefix << m_appName
                << ":"
                << m_className
                << ":"
                << "INFO: ";
        if(m_ofs.is_open())
        {
            m_ofs << prefix.str();
            return m_ofs;
        }
        else
        {
            std::cout << prefix.str();
            return std::cout;
        }
    }else
    {
        return m_nullStream;
    }
}

std::ostream& Logging::Debug()
{
    static std::stringstream prefix;
    if(m_level >= DEBUG)
    {
        prefix.str("");
        prefix << m_appName
                << ":"
                << m_className
                << ":"
                << "DEBUG: ";
        if(m_ofs.is_open())
        {
            m_ofs << prefix.str();
            return m_ofs;
        }
        else
        {
            std::cout << prefix.str();
            return std::cout;
        }
    }else
    {
        return m_nullStream;
    }
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

/*
 * Logging.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: sabin
 */

#include "Logging.hpp"
#include <iostream>

using namespace das;

static std::ofstream nullStream;

Logging::Logging()
    : m_ofs()
    , m_level(Logging::ERROR)
    , m_prefix()
{
}

void Logging::open(const std::string& fileName)
{
    if(m_ofs.is_open())
        m_ofs.close();
    m_ofs.open(fileName.c_str(), std::ios_base::out);
}

void Logging::setLevel(LogLevel level)
{
    m_level = level;
}

void Logging::setPrefix(const std::string& prefix)
{
    m_prefix = prefix;
}

std::ostream& Logging::Fatal()
{
    if(m_ofs.is_open())
    {
        m_ofs << "FATAL:" << m_prefix <<": ";
        return m_ofs;
    }
    return nullStream;
}

std::ostream& Logging::Err()
{
    if(m_level >= ERROR)
    {
        m_ofs << "ERROR:" << m_prefix <<": ";
        return m_ofs;
    }
    return nullStream;
}

std::ostream& Logging::Info()
{
    if(m_level >= INFO)
    {
        m_ofs << "INFO:" << m_prefix <<": ";
        return m_ofs;
    }
    return nullStream;
}

std::ostream& Logging::Debug()
{
    if(m_level >= DEBUG)
    {
        m_ofs << "Debug:" << m_prefix <<": ";
        return m_ofs;
    }
    return nullStream;
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

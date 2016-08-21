
////////////////////////////////////////////////
/// File generataed by generateAlgorithms.sh ///
////////////////////////////////////////////////


/*
 * LmsAlgorithm.cpp
 *
 */

#include "LmsAlgorithm.hpp"
#include <cassert>
#include <sstream>
#include <fstream>

std::ostream& operator<<(std::ostream& os, std::vector<double> data);

double LmsFilter::Adapt(const InputListType&    input,
                        const OutputType&       desiredOutput,
                        WeightLisType&          weights,
                        double                  gradientStep)
{
    assert(weights.size() == input.size());

    double actualOutput = 0.0;
    for(unsigned i = 0; i<weights.size(); ++i)
    {
        actualOutput += weights[i] * input[i];
    }

    double error = desiredOutput - actualOutput;
    for(unsigned i = 0; i < weights.size(); ++i)
    {
        weights[i] = weights[i] + gradientStep * error * input[i];
    }

    //squared error
    error = error*error;

    return error;
}


LmsAlgorithm::LmsAlgorithm()
    : IAlgorithm()
    , m_u(3,0)
    , m_d()
    , m_weights(3,0)
    , m_tempWeights(3,0)
    , m_datafile()
{

}

LmsAlgorithm::~LmsAlgorithm()
{
    m_datafile.close();
}

bool LmsAlgorithm::setInitialData()
{
    das::Network::Instance().LogMessage("LmsAlgorithm is starting");

    std::stringstream ss;
    ss  << "input"
        << das::Network::Instance().GetMyId()
        << ".dat";
    m_datafile.open(ss.str().c_str(), std::ifstream::in);

    if (!m_datafile.good())
    {
        ss << " could not be open for read!";
        das::Network::Instance().LogMessage(ss.str());
        return false;
    }
    return true;
}

bool LmsAlgorithm::readInputData()
{
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];

    char charRead;
    double data;

    ///////////////////////////////////////
    ///     READ INPUT DATA FOR ALGORITHM
    ///////////////////////////////////////

    //find begining of data ( '[' )
    while(m_datafile.good())
    {
        m_datafile.get(charRead);
        if(charRead == '[')
        {
            break;
        }
    }
    unsigned int indexData = 0;

    //while no error and no ending of data
    while(m_datafile.good() && charRead != ']')
    {
        m_datafile.get(charRead);
        if((charRead >= '0' && charRead <= '9') )
        {
            assert(indexData < m_u.size());

            m_datafile.putback(charRead);
            m_datafile >> data;
            m_u[indexData] = data;
            indexData++;
        }
    }


    ///////////////////////////////////////
    ///     READ OUTPUT DATA FOR ALGORITHM
    ///////////////////////////////////////
    m_datafile >> charRead;
    if(charRead != '[')
    {
        return false;
    }
    m_datafile >> m_d;
    m_datafile >> charRead;
    if(charRead != ']')
    {
        return false;
    }

    std::stringstream inputData;
    inputData << "LmsAlgorithm: InputData "<< m_u << " [ "<< m_d << " ]";
    das::Network::Instance().LogMessage(inputData.str());

    return m_datafile.fail();
}
bool LmsAlgorithm::processData()
{
    static das::Network& network = das::Network::Instance();
    static const double nodeCoefficient = 1.0 / network.GetMyNeighbors().size() + 1;

    for (int nodeRank = 0;
         nodeRank < network.GetSize();
         nodeRank++)
    {
        if(network.GetMyRank() == nodeRank)
        {
            m_tempWeights = m_weights;

            double error = LmsFilter::Adapt(m_u, m_d, m_tempWeights);

            for(unsigned i = 0; i < m_weights.size(); ++i)
            {
                m_weights[i] = nodeCoefficient *
                               m_tempWeights[i];
            }

            for(unsigned neigh = 0;
                neigh < network.GetMyNeighbors().size();
                ++neigh)
            {
                if(network.GetMyNeighbors()[neigh] != network.GetMyRank())
                {
                    LmsFilter::WeightLisType neighWeights(32);
                    network.RecvData(neighWeights);

                    assert(m_weights.size() == neighWeights.size());
                    for(unsigned i = 0; i < m_weights.size(); ++i)
                    {
                        m_weights[i] += nodeCoefficient *
                                        neighWeights[i];
                    }
                }
            }
        }
        else
        {
            if (isMyNeighbor(nodeRank))
            {
                network.SendDataTo(m_tempWeights, nodeRank);
            }
        }
    }
    return true;
}
bool LmsAlgorithm::writeOutputData()
{
    std::stringstream output;

    output << "LmsAlgorithm: Weights "<< m_weights;
    das::Network::Instance().LogMessage(output.str());

    return true;
}

bool LmsAlgorithm::isFinished()
{
    if(m_datafile.eof())
    {
        das::Network::Instance().LogMessage("LmsAlgorithm is finished");
        return true;
    }

    return false;
}

bool LmsAlgorithm::isMyNeighbor(int rank)
{
    bool isNeighbor = false;

    for (unsigned int idx = 0;
         idx < das::Network::Instance().GetMyNeighbors().size();
         idx++)
    {
        if(das::Network::Instance().GetMyNeighbors()[idx] == rank)
        {
            isNeighbor = true;
            break;
        }
    }

    return isNeighbor;
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

extern "C"
{
    das::IAlgorithm* Create()
    {
        return new LmsAlgorithm();
    }

    void Destroy(das::IAlgorithm* algorithm)
    {
        delete algorithm;
    }
}

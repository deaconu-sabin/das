
////////////////////////////////////////////////
/// File generataed by generateAlgorithms.sh ///
////////////////////////////////////////////////


/*
 * LmsAlgorithm.hpp
 */

#ifndef LmsALGORITHM_HPP_
#define LmsALGORITHM_HPP_

#include <das/IAlgorithm.hpp>
#include <das/Network.hpp>


class LmsFilter
{
    public:
        typedef std::vector<double> InputListType;
        typedef double              OutputType;
        typedef std::vector<double> WeightLisType;


        static double Adapt(const InputListType&    input,
                            const OutputType&       desiredOutput,
                            WeightLisType&          weights,
                            double                  gradientStep  = 0.0001);
};


class LmsAlgorithm: public das::IAlgorithm
{
    public:
        LmsAlgorithm();
        virtual ~LmsAlgorithm();

        bool isMyNeighbor(int rank);

        ////////////////////////////////
        ///  IAlgorithm methods
        ////////////////////////////////
        virtual bool setInitialData();
        virtual bool readInputData();
        virtual bool processData();
        virtual bool writeOutputData();
        virtual bool isFinished();

    private:
        LmsFilter::InputListType m_u;
        LmsFilter::OutputType    m_d;
        LmsFilter::WeightLisType m_weights;
        LmsFilter::WeightLisType m_tempWeights;

        std::ifstream m_datafile;
};

#endif /* LmsALGORITHM_HPP_ */

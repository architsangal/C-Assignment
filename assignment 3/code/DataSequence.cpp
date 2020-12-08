#include <iostream>
#include "DataSequence.h"
#include "Histogram.h"
#include "FiveNumberSummary.h"
#include<cmath>
#include<math.h>
#include <vector>

using namespace std;

// Constructor
DataSequence::DataSequence(vector<double> seq,Histogram *h):fns(0.0,0.0,0.0,0.0,0.0)// just for the sake of initialisation
{
    hist = h;
    bins = 10;
    length = seq.size();
    sequence = new double[length];
    for(int i=0;i<length;i++)
    {
        sequence[i] = seq[i];
    }
    sortSequence();
    fns.setMin(getMin());
    fns.setMax(getMax());
    fns.setMedian(getMedian());
    fns.setFQ(getFQ());
    fns.setTQ(getTQ());
    makeHistogram();
}

// Copy constructor
DataSequence::DataSequence(const DataSequence &dataSequence): fns(dataSequence.fns)
{
    hist = dataSequence.hist;
    bins = 10;
    length = dataSequence.length;
    sequence = new double[length];
    for(int i=0;i<length;i++)
    {
        sequence[i] = dataSequence.sequence[i];
    }
    makeHistogram();
}

// destructor
DataSequence::~DataSequence()
{
    delete[](sequence);
}

// calculates the start of every interval and store them in intervals
void DataSequence::binIntervals(double *intervals)
{
    // for the cases when there is only one element or all the elements are same
    if(getMax() == getMin())
    {
        double increment = ((getMax()+0.5)-(getMin()-0.5))/bins;
        double sum = getMin()-0.5;
        intervals[0] = sum;
        for(int i=1;i<bins;i++)
        {
            sum += increment;
            intervals[i] = sum;
        }

    }
    else // normal cases
    {

        double increment = (getMax()-getMin())/bins;
        double sum = getMin();
        intervals[0] = sum;
        for(int i=1;i<bins;i++)
        {
            sum += increment;
            intervals[i] = sum;
        }
        
    }
    
}

// iterates on interval and finds the frequency
void DataSequence::calcFreq(double *frequency,double *interval)
{
    // initialisation of the frequency
    for(int i=0;i<bins;i++)
    {
        frequency[i] = 0;
    }

    // for normal cases
    for(int i=0;i<length-1 && getMax()!=getMin();i++)
    {
        int j,f=0;
        for(j=0;j<bins-1;j++)
        {
            if(sequence[i] >= interval[j] && sequence[i]<interval[j+1])
            {
                f=1;
                frequency[j]++;
                continue;
            }
        }
        if(f==0)
            frequency[bins-1]++;
    }
    if(getMin() != getMax())// normal cases
        frequency[bins-1]++;
    else
    {
        // for the cases when there is only one element or all the elements are same
        for(int i=0;i<length;i++)
        {
            int j,f=0;
            for(j=0;j<bins-1;j++)
            {
                if(sequence[i] >= interval[j] && sequence[i]<interval[j+1])
                {
                    f=1;
                    frequency[j]++;
                    continue;
                }
            }
            if(f==0)
                frequency[bins-1]++;
        }
    }


}

// stores the information in Histogram object
void DataSequence::makeHistogram()
{
    hist->setNs(length);

    double *intervals = new double[bins];
    binIntervals(intervals);
    hist->setInterval(intervals);
    
    double *frequency = new double[bins];
    calcFreq(frequency,intervals);
    hist->setFreq(frequency);
    
}

// calc first quartile
double DataSequence::getFQ()
{
    double indices = 0.25*(length-1);
    int index1 = ceil(indices);
    int index2 = floor(indices);
    return 0.5*(sequence[index1]+sequence[index2]);
}

// calc third quartile
double DataSequence::getTQ()
{
    double indices = 0.75*(length-1);
    int index1 = ceil(indices);
    int index2 = floor(indices);
    return 0.5*(sequence[index1]+sequence[index2]);
}

// calculating median
double DataSequence::getMedian()
{
    double indices = 0.5*(length-1);
    int index1 = ceil(indices);
    int index2 = floor(indices);
    return 0.5*(sequence[index1]+sequence[index2]);
}

// calc max
double DataSequence::getMax()
{
    return sequence[length-1];
}

// calc min
double DataSequence::getMin()
{
    return sequence[0];
}

// adding a value
// called when we get 'A'
void DataSequence::add(double value)
{
    length = length+1;
    sequence[length-1] = value;
    sortSequence();
    fns.setMin(getMin());
    fns.setMax(getMax());
    fns.setMedian(getMedian());
    fns.setFQ(getFQ());
    fns.setTQ(getTQ());
    makeHistogram();
}

// Used a simple sorting algo
void DataSequence::sortSequence()
{
    for (int i = 0; i < length-1; i++)       
    {
        for (int j = 0; j < length-i-1; j++) 
        {
            if (sequence[j] > sequence[j+1]) 
            {
                double temp = sequence[j];
                sequence[j] = sequence[j+1];
                sequence[j+1] = temp;
            }
        }
    }
}

// Reference taken from GFG
void operator<<(DataSequence& d, ostream& mycout) 
{
    d.fns << cout;
    *(d.hist) << cout;
    // handling the corner case when there is one element or all the elements are identical
    if(d.getMax()!=d.getMin())
        mycout<<d.truncfunc(d.getMax())<<" ";
    else
        mycout<<d.truncfunc((d.getMax()+0.5))<<" ";
    *(d.hist) >> cout;
    mycout<<" ";
}

// Reference taken from GFG
void operator>>(DataSequence& d, ostream& mycout) 
{
    d.fns << cout;
    *(d.hist) << cout;
    // handling the corner case when there is one element or all the elements are identical
    if(d.getMax()!=d.getMin())
        mycout<<d.truncfunc(d.getMax())<<" ";
    else
        mycout<<d.truncfunc((d.getMax()+0.5))<<" ";
    *(d.hist) >> cout;
}

// used for rounding off upto 4 decimal places
double DataSequence::truncfunc(double x)
{
    return floor((floor(x*1e5)*1e-5+1e-5)*1e4)*1e-4;
}

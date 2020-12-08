#include "DataSequence.h"
#include "Histogram.h"
#include<iostream>

using namespace std;

// Copy constructor
DataSequence::DataSequence(const DataSequence &dataSequence)
{
    sequence = new float[100000];
    for(int i = 0; i < length; i++)
    {
        sequence[i] = dataSequence.sequence[i];
    }

    bins = dataSequence.bins;
    max = dataSequence.max;
    min = dataSequence.min;
}

// destructor
DataSequence::~DataSequence()
{
    delete[](sequence);
}

// Constructor
DataSequence::DataSequence(float *seq, int size, int divisions)
{
    bins = divisions;
    sequence = new float[100000];
    length = size;
    min = seq[0];
    max = seq[0];
    for(int i=0;i<length;i++)
    {
        sequence[i] = seq[i];
        if(min>seq[i])
            min=seq[i];
        if(max<seq[i])
            max=seq[i];
    }
    sortSequence();
}

// calculates the start of every interval and store them in intervals
void DataSequence::binIntervals(float *intervals)
{
    // for the cases when there is only one element or all the elements are same
    if(max == min)
    {

        float increment = ((max+0.5)-(min-0.5))/bins;
        float sum = min-0.5;
        intervals[0] = sum;
        for(int i=1;i<bins;i++)
        {
            sum += increment;
            intervals[i] = sum;
        }

    }
    else // normal cases
    {

        float increment = (max-min)/bins;
        float sum = min;
        intervals[0] = sum;
        for(int i=1;i<bins;i++)
        {
            sum += increment;
            intervals[i] = sum;
        }
        
    }
    
}

// iterates on interval and finds the frequency
void DataSequence::calcFreq(int *frequency,float *interval)
{
    // initialisation of the frequency
    for(int i=0;i<bins;i++)
    {
        frequency[i] = 0;
    }

    // for normal cases
    for(int i=0;i<length-1 && max!=min;i++)
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
    if(min != max)// normal cases
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
void DataSequence::makeHistogram(Histogram &histogram)
{
    float *intervals = new float[100000];
    binIntervals(intervals);
    histogram.setInterval(intervals);
    int *frequency = new int[100000];
    calcFreq(frequency,intervals);
    histogram.setFreq(frequency);
    
    delete[](intervals);
    delete[](frequency);
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
                float temp = sequence[j];
                sequence[j] = sequence[j+1];
                sequence[j+1] = temp;
            }
        }
    }
}

// calculating median
float DataSequence::median()
{
    if(length%2 == 1)
        return sequence[length/2];
    else
        return ((sequence[length/2]+sequence[length/2-1])/2);
}

// calculating mean
float DataSequence::mean()
{
    float sum=0;
    for(int i=0;i<length;i++)
    {
        sum += sequence[i];
    }
    return sum/length;
}

// getter for the variable max
float DataSequence::getMax()
{
    return max;
}

// getter for the variable min
float DataSequence::getMin()
{
    return min;
}
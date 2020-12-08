#include "Histogram.h"

using namespace std;

// copy constructor
Histogram::Histogram(const Histogram &histogram)
{
    bins = histogram.bins;
    interval = new float[10000];
    freq = new int[100000];
    for(int i = 0; i < bins; i++)
    {
        interval[i] = histogram.interval[i];
        freq[i] = histogram.freq[i];
    }
}

// copy the interval_original to interval
void Histogram::setInterval(float *interval_original)
{
    for(int i=0;i<bins;i++)
        interval[i] = interval_original[i];
}

// copy the frequency to freq
void Histogram::setFreq(int *frequency)
{
    for(int i=0;i<bins;i++)
        freq[i] = frequency[i];
}

// getter for freq
int* Histogram::getFreq()
{
    int* copy = new int[100000];
    for(int i=0;i<bins;i++)
        copy[i] = freq[i];
    return copy;
}

// getter for interval
float* Histogram::getInterval()
{
    float* copy = new float[100000];
    for(int i=0;i<bins;i++)
        copy[i] = interval[i];

    return copy;
}
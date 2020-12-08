#include "Histogram.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// copy constructor
Histogram::Histogram(const Histogram &histogram)
{
    Ns = histogram.Ns;
    bins = histogram.bins;
    interval = new double[bins];
    freq = new double[bins];
    for(int i = 0; i < bins; i++)
    {
        interval[i] = histogram.interval[i];
        freq[i] = histogram.freq[i];
    }
}

// copy the interval_original to interval
void Histogram::setInterval(double *interval_original)
{
    for(int i=0;i<bins;i++)
        interval[i] = interval_original[i];
}

// copy the frequency to freq
void Histogram::setFreq(double *frequency)
{
    for(int i=0;i<bins;i++)
        freq[i] = frequency[i];
    
    // probability
    for(int i=0;i<bins;i++)
    {
        freq[i] = freq[i]/Ns;
    }

}

void Histogram::setNs(int length)
{
    Ns = length;
}

// getter for freq
double* Histogram::getFreq()
{
    return freq;
}

// getter for interval
double* Histogram::getInterval()
{
    return interval;
}

double Histogram::truncfunc(double x)
{
    return floor((floor(x*1e5)*1e-5+1e-5)*1e4)*1e-4;
}

void operator<<(Histogram& d, ostream& mycout)
{
    for(int i=0;i<d.bins;i++)
    {
        mycout<<d.truncfunc(d.interval[i])<<",";
    }
}

void operator>>(Histogram& d, ostream& mycout)
{
    for(int i=0;i<d.bins-1;i++)
    {
        mycout<<d.truncfunc(d.freq[i])<<",";
    }
    cout<<d.truncfunc(d.freq[d.bins-1])<<" -1";

}

#include "Histogram.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//constructor
Histogram::Histogram()
{
    bins = 0;
    length = 0;
    interval = new double[100000];
    freq = new double[100000];
    sequence = new double[100000];
}

// copy constructor
Histogram::Histogram(const Histogram &histogram)
{
    length = histogram.length;
    bins = histogram.bins;
    interval = new double[bins];
    freq = new double[bins];
    for(int i = 0; i < bins; i++)
    {
        interval[i] = histogram.interval[i];
        freq[i] = histogram.freq[i];
    }
    for(int i = 0; i < length; i++)
    {
        sequence[i] = histogram.sequence[i];
    }
}

// destructor
Histogram::~Histogram()
{
    delete[] sequence;
    delete[] interval;
    delete[] freq;
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

}

// getter for freq
double* Histogram::getSeq()
{
    return sequence;
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

// calculates the start of every interval and store them in interval
void Histogram::binInterval(double *sorted_sequence,int length)
{
    double min = sorted_sequence[0];
    double max = sorted_sequence[length-1];

    if(max == min) // for the cases when there is only one element or all the elements are same
    {
        double increment = ((max+0.5)-(min-0.5))/bins;
        double sum = min-0.5;
        interval[0] = sum;
        for(int i=1;i<bins;i++)
        {
            sum += increment;
            interval[i] = sum;
        }

    }
    else // normal cases
    {

        double increment = (max-min)/bins;
        double sum = min;
        interval[0] = sum;
        for(int i=1;i<bins;i++)
        {
            sum += increment;
            interval[i] = sum;
        }
        
    }
    
}

void Histogram::calcFreq(double *sorted_sequence,int length) // iterates on interval and finds the frequency
{
    double min = sorted_sequence[0];
    double max = sorted_sequence[length-1];

    // initialisation of the frequency
    for(int i=0;i<bins;i++)
    {
        freq[i] = 0;
    }

    // for normal cases
    for(int i=0;i<length-1 && max!=min;i++)
    {
        int j,f=0;
        for(j=0;j<bins-1;j++)
        {
            if(sorted_sequence[i] >= interval[j] && sorted_sequence[i]<interval[j+1])
            {
                f=1;
                freq[j]++;
                continue;
            }
        }
        if(f==0)
            freq[bins-1]++;
    }
    if(min != max)// normal cases
        freq[bins-1]++;
    else
    {
        // for the cases when there is only one element or all the elements are same
        for(int i=0;i<length;i++)
        {
            int j,f=0;
            for(j=0;j<bins-1;j++)
            {
                if(sorted_sequence[i] >= interval[j] && sorted_sequence[i]<interval[j+1])
                {
                    f=1;
                    freq[j]++;
                    continue;
                }
            }
            if(f==0)
                freq[bins-1]++;
        }
    }
}

// mathematical aspects taken from internet
double klDivergence(Histogram &h1,Histogram &h2)
{
    if(h1.length != h2.length)
    {
        cerr << "-1 ";
        return -1;
    }

    double *vector1 = h1.getSeq();
    double *vector2 = h2.getSeq();
    int n = h1.length;
    double sum=0;
    for(int i=0; i<n; i++)
    {
        sum += vector1[i] * log(vector1[i]/vector2[i]);
    }
    return sum;
}

// mathematical aspects taken from internet
double klDivergence(double *vector1,double *vector2,int length)
{
    int n = length;
    double sum=0;
    for(int i=0; i<n; i++)
    {
        sum += vector1[i] * log(vector1[i]/vector2[i]);
    }
    return sum;
}

// mathematical aspects taken from internet
double manDist(Histogram &h1,Histogram &h2)
{

    if(h1.length != h2.length)
    {
        cerr << "-1 ";
        return -1;
    }

    double *vector1 = h1.getSeq();
    double *vector2 = h2.getSeq();
    int n = h1.length;

    double dist = 0;
    for(int i=0; i<n; i++){
        dist +=  fabs(vector1[i]-vector2[i]);
    }
    return dist;
}

// mathematical aspects taken from internet
double eucDist(Histogram &h1,Histogram &h2)
{
    if(h1.length != h2.length)
    {
        cerr << "-1 ";
        return -1;
    }

    double *vector1 = h1.getSeq();
    double *vector2 = h2.getSeq();
    int n = h1.length;

    double squareSum = 0;
    for(int i=0; i<n; i++)
    {
        squareSum += pow(vector1[i]-vector2[i], 2);
    }

    return sqrt(squareSum);
}

// mathematical aspects taken from internet
double cheDistance(Histogram &h1,Histogram &h2)
{
    if(h1.length != h2.length)
    {
        cerr << "-1 ";
        return -1;
    }

    double *vector1 = h1.getSeq();
    double *vector2 = h2.getSeq();
    int n = h1.length;

    double dist = 0;
    for(int i=0; i<n; i++){
        if(dist < fabs(vector1[i]-vector2[i])){
            dist = fabs(vector1[i]-vector2[i]);
        }
    } return dist;
}

// mathematical aspects taken from internet
double jsDistance(Histogram &h1,Histogram &h2)
{
    if(h1.length != h2.length)
    {
        cerr << "-1 ";
        return -1;
    }

    double *vector1 = h1.getSeq();
    double *vector2 = h2.getSeq();
    int n = h1.length;

    double *m = new double[n];
    double sum = 0;
    for(int i=0;i<n;i++)
    {
        m[i] = (vector1[i]+vector2[i])/2;
    }
    sum = (klDivergence(h1.getSeq(),m,h1.length)+klDivergence(h2.getSeq(),m,h2.length))/2;
    return sqrt(sum);
}
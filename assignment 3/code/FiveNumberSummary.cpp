#include "FiveNumberSummary.h"
#include <iostream>
#include <vector>
#include<cmath>
using namespace std;

// constructor
FiveNumberSummary::FiveNumberSummary(double minimum,double firstq,double med,double thirdq,double maximum)
{
    min = minimum;
    fq = firstq;
    median = med;
    sq = thirdq;
    max = maximum;
}

// copy constructor
FiveNumberSummary::FiveNumberSummary(const FiveNumberSummary &fns)
{
    min = fns.min;
    fq = fns.fq;
    median = fns.median;
    sq = fns.sq;
    max = fns.max;
}

double FiveNumberSummary::getMin()     // getter for the min
{
    return min;
}
double FiveNumberSummary::getFQ()      // getter for the first quartile
{
    return fq;
}
double FiveNumberSummary::getMedian()  // getter for the median
{
    return median;
}
double FiveNumberSummary::getTQ()      // getter for the third quartile
{
    return sq;
}
double FiveNumberSummary::getMax()     // getter for the max
{
    return max;
}

void FiveNumberSummary::setMin(double minimum)     // setter for the min
{
    min = minimum;
}
void FiveNumberSummary::setFQ(double firstq)       // setter for the first quartile
{
    fq = firstq;
}
void FiveNumberSummary::setMedian(double med)      // setter for the median
{
    median = med;
}
void FiveNumberSummary::setTQ(double thirdq)      // setter for the third quartile
{
    sq = thirdq;
}
void FiveNumberSummary::setMax(double maximum)     // setter for the max
{
    max = maximum;
}

void operator<<(FiveNumberSummary& d, ostream& mycout)
{
    mycout << d.truncfunc(d.getMin()) << ","; 
    mycout << d.truncfunc(d.getFQ()) << ","; 
    mycout << d.truncfunc(d.getMedian()) << ","; 
    mycout << d.truncfunc(d.getTQ()) << ","; 
    mycout << d.truncfunc(d.getMax()) << " "; 
}

double FiveNumberSummary::truncfunc(double x)
{
    return floor((floor(x*1e5)*1e-5+1e-5)*1e4)*1e-4;
}

FiveNumberSummary::~FiveNumberSummary() // destructor
{
    // left empty
}
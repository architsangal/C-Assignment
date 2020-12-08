#pragma once
#include <iostream>
#include <vector>
using namespace std;

class FiveNumberSummary
{
    // class variables
    double min;     // stores the min in the sequence
    double fq;      // stores first quartile
    double median;  // stores first quartile
    double sq;      // stores third quartile
    double max;     // stores the max in the sequence

    public:
    FiveNumberSummary(double minimum,double firstq,double med,double thirdq,double maximum); // constructor 
    FiveNumberSummary(const FiveNumberSummary &fns);   // copy constructor

    double getMin();     // getter for the min
    double getFQ();      // getter for the first quartile
    double getMedian();  // getter for the median
    double getTQ();      // getter for the third quartile
    double getMax();     // getter for the max

    void setMin(double minimum);     // setter for the min
    void setFQ(double firstq);       // setter for the first quartile
    void setMedian(double med);      // setter for the median
    void setTQ(double thirdq);      // setter for the third quartile
    void setMax(double maximum);     // setter for the max

    friend void operator<<(FiveNumberSummary& d, ostream& mycout); 
    double truncfunc(double x);
    ~FiveNumberSummary(); // destructor

};
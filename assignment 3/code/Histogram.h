#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Histogram
{
    // class variables
    double* interval;
    double* freq;
    int bins;
    int Ns;

    public:
    Histogram()                              // constructor
    {
        Ns=0;
        bins = 10;
        interval = new double[bins];
        freq = new double[bins];
    }

    Histogram(const Histogram &histogram);   // copy constructor

    // destructor
    ~Histogram()
    {
        delete[] (interval);
        delete[] (freq);
    }

    void setNs(int length);
    void setInterval(double*);  // setter for interval
    double* getInterval();      // getter for interval
    void setFreq(double*);      // setter for freq
    double* getFreq();          // getter for freq
    friend void operator<<(Histogram& d, ostream& mycout); 
    friend void operator>>(Histogram& d, ostream& mycout); 
    double truncfunc(double x);
};
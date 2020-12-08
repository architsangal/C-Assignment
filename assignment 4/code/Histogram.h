#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Histogram
{
    // class variables
    protected:
    double* interval;
    double* freq;
    double* sequence;
    int length;
    int bins;

    public:
    Histogram();                              // constructor
    Histogram(const Histogram &histogram);    // copy constructor
    ~Histogram();                             // destructor
    
    double* getSeq();           // getter for sequence
    void setInterval(double*);  // setter for interval
    double* getInterval();      // getter for interval
    void setFreq(double*);      // setter for freq
    double* getFreq();          // getter for freq
    double truncfunc(double x);
    void binIntervals(double *interval);
    void binInterval(double *sorted_sequence,int length);
    void calcFreq(double *sorted_sequence,int length);

    friend double klDivergence(Histogram &h1,Histogram &h2);
    friend double manDist(Histogram &h1,Histogram &h2);
    friend double eucDist(Histogram &h1,Histogram &h2);
    friend double cheDistance(Histogram &h1,Histogram &h2);
    friend double jsDistance(Histogram &h1,Histogram &h2);
};
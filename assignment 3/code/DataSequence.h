#pragma once
#include <iostream>
#include <vector>
#include "Histogram.h"
#include "FiveNumberSummary.h"
using namespace std;

class DataSequence
{
    // class variables
    Histogram *hist;
    double* sequence; // stores the sequence
    int length;      // stores the length of the sequence
    int bins;        // stores the number of bins in the histogram
    FiveNumberSummary fns;

    public:
    DataSequence(vector<double> seq,Histogram *h); // constructor
    DataSequence(const DataSequence &dataSequence);   // copy constructor
    double getMedian();  // finds the median
    double getMax();  // finds the max in the sequence
    double getMin();  // finds the min in the sequence
    double getFQ();
    double getTQ();
    void add(double value);
    void binIntervals(double*); // stores the starting points of all the bins
    void calcFreq(double*,double*);// calculates the frequencies and stores them into the int locations passed to it
    void makeHistogram();// this functions store the related data calculations into the object that was passed
    void sortSequence();
    friend void operator<<(DataSequence& d, ostream& mycout); 
    friend void operator>>(DataSequence& d, ostream& mycout);
    double truncfunc(double x);

    ~DataSequence(); // destructor

};
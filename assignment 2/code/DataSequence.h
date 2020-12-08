#pragma once
#include "Histogram.h"
using namespace std;

class DataSequence
{
    // class variables
    float* sequence; // stores the sequence
    int length;  // stores the length of the sequence
    int bins;    // stores the number of bins in the histogram
    float max;   // stores the max in the sequence
    float min;   // stores the min in the sequence

    public:
    DataSequence(float *seq, int size,int divisions); // constructor
    DataSequence(const DataSequence &dataSequence);   // copy constructor
    float mean();    // finds the mean
    float median();  // finds the median
    float getMax();  // finds the max in the sequence
    float getMin();  // finds the min in the sequence
    void binIntervals(float*); // stores the starting points of all the bins
    void calcFreq(int*,float*);// calculates the frequencies and stores them into the int locations passed to it
    void makeHistogram(Histogram&);// this functions store the related data calculations into the object that was passed
    ~DataSequence(); // destructor

    private:
    void sortSequence(); // sorts the sequence
    void binIntervals(); // stores the starting points of all the bins in binIntervals
};
#pragma once

using namespace std;

class Histogram
{
    float* interval;
    int* freq;
    int bins;

    public:

    // constructor    
    Histogram(int no_of_bins)
    {
        bins = no_of_bins;
        interval = new float[100000];
        freq = new int[100000];
    }

    // copy constructor
    Histogram(const Histogram &histogram);

    // destructor
    ~Histogram()
    {
        delete[] (interval);
        delete[] (freq);
    }

    // setter for interval
    void setInterval(float*);
    
    // getter for interval
    float* getInterval();
    
    // setter for freq
    void setFreq(int*);
    
    // getter for freq
    int* getFreq();

};
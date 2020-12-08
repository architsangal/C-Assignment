#pragma once
#include "Histogram.h"
#include <iostream>
using namespace std;

class BinomialDistribution : public Histogram
{
    // class variables
    int n;
    double p;

    public:
    BinomialDistribution(int n,double p_success);                 // constructor
    BinomialDistribution(const BinomialDistribution &bd);         // constructor
    ~BinomialDistribution();                                      // destructor

    void sortSequence(double *sequence,int length);
    void compute();

    double factorial(double i);
    double nCr(double n,double r);
    double sequence_element(double n,double r,double p);
};
#include "BinomialDistribution.h"
#include "Histogram.h"
#include <iostream>
#include <cmath>
using namespace std;

BinomialDistribution::BinomialDistribution(int n_given,double p_success)
{
    n = n_given;
    length = n+1;
    bins = length;
    p = p_success;
}

BinomialDistribution::BinomialDistribution(const BinomialDistribution &bd)
{
    n = bd.n;
    length = bd.length;
    bins = bd.bins;
    p = bd.p;
  
    for(int i = 0; i < bins; i++)
    {
        interval[i] = bd.interval[i];
        freq[i] = bd.freq[i];
    }
    for(int i=0;i<length;i++)
    {
        sequence[i] = bd.sequence[i];
    }
}

BinomialDistribution::~BinomialDistribution()
{

}

double BinomialDistribution::factorial(double i)
{
    if(i == 0)
        return 1;
    if(i<0)
        return -1;

    double fact = 1;
    for(double j=1;j<=i;j++)
    {
        fact = fact * j;
    }
    return fact;
}

double BinomialDistribution::nCr(double n,double r)
{
    if(n<r || n<0 || r<0)
        return -1;

    return factorial(n)/(factorial(n-r)*factorial(r));
}

double BinomialDistribution::sequence_element(double n,double r,double p)
{
    double ncr = nCr(n,r);
    double a = pow(p,r);
    double b = pow(1-p,n-r);
    return ncr*a*b;
}

void BinomialDistribution::compute()
{
    for(int i=0;i<length;i++)
    {
        sequence[i] = sequence_element((double)length-1,(double)i,p);
    }
    double *sorted_sequence = new double[length];
    for(int i=0;i<length;i++)
    {
        sorted_sequence[i] = sequence[i];
    }
    sortSequence(sorted_sequence,length);
    binInterval(sorted_sequence,length);
    calcFreq(sorted_sequence,length);

    // double sum = 0;
    // for(int i=0;i<length;i++)
    // {
    //     sum+=sequence[i];
    //     cout<<sequence[i]<<" ";
    // }
    // cout<<sum <<" "<<endl;

}

// Used a simple sorting algo
void BinomialDistribution::sortSequence(double *sequence,int length)
{
    for (int i = 0; i < length-1; i++)
    {
        for (int j = 0; j < length-i-1; j++)
        {
            if (sequence[j] > sequence[j+1]) 
            {
                double temp = sequence[j];
                sequence[j] = sequence[j+1];
                sequence[j+1] = temp;
            }
        }
    }
}

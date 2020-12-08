#include <iostream>
#include <cstring>
#include <cmath>
#include "BinomialDistribution.h"
using namespace std;

// length of the string
int size(char* input)
{
    int length = 0;
    while(input[length] != '\0')
        length++;
    return length;
}

// just checking that if a number is valid or not
// it should not have any special characters other than '-' or '.' and atmost these should be there atmost once.
bool isValidNumber(char* number)
{
    int i=0;
    int flag=0;
    while(number[i] != '\0')
    {
        if(number[i] == '-' && i!=0)
            return false;
        else if(number[i] == '.' && flag==1)
            return false;
        else if(number[i] == '.')
            flag = 1;
        else if(number[i]>'9' && number[i]<'0')
            return false;
        i++;
    }
    return true;
}

bool isValid(char *input_cpy,char ** strings,int &n,double &p1,double &p2)
{
    // dividing the strings which are seperated by ' '
    strings[0] = strtok(input_cpy," ");

    // rest of the number in the string "input" are being tokanised
    int i = 0;
    while (strings[i] != NULL)
    { 
        i++;
        strings[i] = strtok(NULL, " ");
    }

    if(i != 3)
        return false;

    if(!(isValidNumber(strings[0]) && isValidNumber(strings[1]) && isValidNumber(strings[2])))
        return false;
    
    double numbers,p1_success,p2_success;
    sscanf(strings[0],"%lf",&numbers);
    sscanf(strings[1],"%lf",&p1_success);
    sscanf(strings[2],"%lf",&p2_success);
    
    if(numbers <= 0)
        return false;

    if(numbers == ceil(numbers))
        n = (int)numbers;
    else
        return false;

    if(p1_success <= 0 || p1_success >= 1)
        return false;
    else
        p1 = p1_success;

    if(p2_success <= 0 || p2_success >= 1)
        return false;
    else
        p2 = p2_success;

    return true;
}

double truncfunc(double x)
{
    return floor((floor(x*1e5)*1e-5+1e-5)*1e4)*1e-4;
}

int main()
{
    cout.precision(4) ;
    cout << fixed ;

    char *input = new char[100000];
    cin.getline(input,100000);

    char *input_cpy = new char[100000];
    strcpy(input_cpy,input);

    char **strings = new char*[100000];

    int n;
    double p1,p2;
    if(! isValid(input_cpy,strings,n,p1,p2))
    {
        cout<< "-1";
        return 0;
    }

    BinomialDistribution obj1 = BinomialDistribution(n,p1);
    BinomialDistribution obj2 = BinomialDistribution(n,p2);

    obj1.compute();
    obj2.compute();


    // printing the respective distances
    double distance;
    distance = manDist(obj1,obj2);
    if(distance == -1)
    {
        return 0;
    }
    cout<< truncfunc(distance) << " ";


    distance = eucDist(obj1,obj2);
    if(distance == -1)
    {
        return 0;
    }
    cout<< truncfunc(distance) << " ";

    distance = cheDistance(obj1,obj2);
    if(distance == -1)
    {
        return 0;
    }
    cout<< truncfunc(distance) << " ";
    
    distance = klDivergence(obj1,obj2)+klDivergence(obj2,obj1);
    if(distance == -1)
    {
        return 0;
    }
    cout<< truncfunc(distance) << " ";
    
    distance = jsDistance(obj1,obj2);
    if(distance == -1)
    {
        return 0;
    }
    cout<< truncfunc(distance);

    return 0;
}
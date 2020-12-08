#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
#include "DataSequence.h"
#include "Histogram.h"

using namespace std;

inline float truncfunc(float x) { return floor((floor(x*1e5)*1e-5+1e-5)*1e4)*1e-4  ;  }

int size(char* input)
{
    // length of the string
    int length = 0;
    while(input[length] != '\0')
        length++;
    return length;
}

// convert the string to natural number.
int stringToNaturalNumber(char *input, int length)
{
    // finds the "size of vector"
    int n;

    if(input[0]<='9' && input[0]>='0')
    {
        n = input[0]-'0';
    }
    else
    {
        return -1;
    }
    
    for(int i=1;input[i]!='\0';i++)
    {
        if(input[i]<='9' && input[i]>='0')
        {
            int digit = input[i] - '0';
            n = n*10 + digit;
        }
        else if(input[i] > '9' || input[i]<'0')
        {
            return -1;
        }
    }

    return n;

}

// Just check if relative placing of ',' and ' ' is valid or not.
// we are using counters so as to relatively find commas and spaces.
bool isValid(char *input,int length, int n)
{
    int comma_counter = 0;
    int space_counter = 0;
    for(int i=0;i<length;i++)
    {
        if(input[i] == ' ')
        {
            space_counter++;
            if(space_counter == 1 || space_counter == 2)
                if(comma_counter == 0)
                    continue;
                else
                    return false;
            else if(space_counter == 3 || space_counter == 4 || space_counter == 5)
                if(comma_counter == n-1)
                    continue;
                else
                    return false;
            else if(space_counter == 6)
                return false;
        }
        else if(input[i] == ',')
        {
            comma_counter++;
        }
    }

    // to check if there are any extra spaces or comma at the end of the input
    if(space_counter != 5 || comma_counter != n-1)
        return false;

    return true;
}

// just checking that if a number is valid or not
// it should not have any special characters other than '-' or '.' and atmost these should be there atmost once.
bool isValidNumber(char number[])
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

int main()
{
    char *input = new char[100000];;
    cin.getline(input,100000);

    char *input_cpy = new char[100000];
    strcpy(input_cpy,input);
    
    int length = size(input);

    // dividing the numbers which are seperated by ',' or ' '
    char **numbers = new char*[10000];
    for(int i=0;i<10000;i++)
    {
        numbers[i] = new char[100];
    }
    numbers[0] = strtok(input," ,");

    // converting the n from string to integer
    int n = stringToNaturalNumber(numbers[0],length);
    if(n == -1)
    {
        printf("-1");
        return 0;
    }

    // checking of the commas and the spaces are in proper order.
    if(! isValid(input_cpy,length,n))
    {
        printf("-1");
        return 0;
    }
    
    // rest of the number in the string "input" are being tokanised
    int i = 0;
    while (numbers[i] != NULL)
    { 
        i++;
        numbers[i] = strtok(NULL, ", ");
    }

    // temp is just a variable to convert the string "-1" to -1(float)
    float temp;
    sscanf(numbers[1],"%f",&temp);

    // varidity of the input is being checked as after 'n' (i.e. the size of the vector there should be a -1).
    if(temp != -1)
    {
        printf("-1");
        return 0;
    }

    float *sequence = new float[n];

    // converting number in "string" to float
    int k=0;
    for(int j=2;j<=n+1;j++)
    {
        // beforing using sscanf we want to check if the string is a valid string or not.
        if(isValidNumber(numbers[j]))
        {
            sscanf(numbers[j],"%f",&sequence[k]);
            k++;
        }
        else
        {
            printf("-1");
            return 0;
        }
        
    }

    // we are checking if the numbers in the sequence is positive
    for(int i=0;i<n;i++)
    {
        if(sequence[i]<=0)
        {
            printf("-1");
            return 0;
        }
    }

    sscanf(numbers[n+2],"%f",&temp);
    if(temp != -1)
    {
        printf("-1");
        return 0;
    }

    int bins = stringToNaturalNumber(numbers[n+3],length);
    if(bins <= 0)
    {
        printf("-1");
        return 0;
    }

    sscanf(numbers[n+4],"%f",&temp);
    if(temp != -1)
    {
        printf("-1");
        return 0;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Validity is checked

// Now main logic begins

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Objects created
    DataSequence dataSequence(sequence,n,bins);
    Histogram histogram(bins);

    // Histogram object is passed to DataSequence object
    dataSequence.makeHistogram(histogram);

    cout << setprecision(4);
    cout << fixed ;
    // upto 4 decimal places only
    cout<<truncfunc(dataSequence.getMin())<<" -1 ";
    cout<<truncfunc(dataSequence.mean())<<" -1 ";
    cout<<truncfunc(dataSequence.median())<<" -1 ";
    cout<<truncfunc(dataSequence.getMax())<<" -1 ";
    
    float* interval = histogram.getInterval();
    int* frequency = histogram.getFreq();
    
    for(int i=0;i<bins;i++)
    {
        cout<<truncfunc(interval[i])<<",";
    }
    
    // handling the corner case when there is one element or all the elements are identical
    if(dataSequence.getMax()!=dataSequence.getMin())
        cout<<truncfunc(dataSequence.getMax())<<" -1 ";
    else
        cout<<truncfunc((dataSequence.getMax()+0.5))<<" -1 ";
    
    for(int i=0;i<bins-1;i++)
    {
        cout<<frequency[i]<<",";
    }
    cout<<frequency[bins-1]<<" -1"<<endl;
    


    delete[](input);
    delete[](input_cpy);
    delete[](sequence);
    delete[](numbers);
    delete[](interval);
    delete[](frequency);

    return 0;
}
#include<iostream>
#include<cstring>
#include<cmath>
#include<iostream>
#include "DataSequence.h"
#include "Histogram.h"
#include "FiveNumberSummary.h"
#include<vector>
using namespace std;

// length of the string
int size(char* input)
{
    int length = 0;
    while(input[length] != '\0')
        length++;
    return length;
}

// convert the string to natural number.
int stringToNaturalNumber(char *input)
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

// many other vectors and pointers are passed which helps in storing useful information
bool checkingValidity(char *input,vector<vector<double>> &sequences,vector<DataSequence> &DSvector,vector<Histogram> &hist,vector<int> &length_of_series,char **strings,int &strings_length)
{

    // this is required as we will use strtok
    char *input_cpy = new char[10000];
    strcpy(input_cpy,input);
    
    // dividing the strings which are seperated by ',' or ' '
    strings[0] = strtok(input_cpy," ,");

    // rest of the number in the string "input" are being tokanised
    int i = 0;
    while (strings[i] != NULL)
    { 
        i++;
        strings[i] = strtok(NULL, ", ");
    }
    // stores the number of rows in strings
    strings_length = i;
    
    // first character must be N as adding an element to a data sequence which does not exist is invalid input
    // this loop inside if helps us to create a vector length_of_series which stores the "intergers" after N
    int count = 0;
    if(size(strings[count]) == 1 && strings[count][0] == 'N')
    {
        int flag = 1;
        count++;
        while(count != strings_length)
        {
            if(isValidNumber(strings[count]) && flag == 1)
            {
                flag = 0;
                int number = stringToNaturalNumber(strings[count]);
                if(number < 0)
                {
                    return false;
                }
                length_of_series.push_back(number);
            }
            else if(size(strings[count])==1 && strings[count][0] == 'N')
            {
                flag = 1;
            }
            count++;
        }
    }
    else
    {
        return false;
    }

    // check if no there are invalid characters in the input
    for(int i=0;i<size(input);i++)
    {
        if((input[i]<='9' && input[i]>='0') || input[i] == 'A' || input[i] == 'N' || input[i] == '.' || input[i] == ' ' || input[i] == '-' || input[i] == ',')
            continue;
        else
            return false;
    }

    // similar to strings but the delimiter this time will be "-"
    char **commands = new char*[100];

    // similar to input_cpy
    char *input_cpy2 = new char[10000];
    strcpy(input_cpy2,input);

    for(int i=0;i<100;i++)
    {
        commands[i] = new char[1000];
    }
    
    commands[0] = strtok(input_cpy2,"-");

    // rest of the number in the string "input" are being tokanised
    i = 0;
    while (commands[i] != NULL)
    { 
        i++;
        commands[i] = strtok(NULL, "-");
    }

    // final validity testing after this we will check validity when we get the elements in double or intergers
    int f1=0,index=0;
    for(int j=0;j<i;j++)
    {
        if(commands[j][0] == '1' && commands[j][1] == ' ')
        {
            // when we have A
            if(commands[j][2] == 'A')
            {
                int comma = 0, spaces = 0;
                for(int k = 3;k<size(commands[j]);k++)
                {
                    if(commands[j][k] == ',')
                    {
                        comma++;
                    }
                    else if(commands[j][k] == ' ')
                    {
                        spaces++;
                    }
                }
                if(comma == 2 && spaces == 1) 
                {
                    continue;
                }
                else
                {
                    return false;
                }   
            }
            else if(commands[j][2] == 'N')// when we have N
            {
                int comma = 0, spaces = 0;
                for(int k = 3;k<size(commands[j]);k++)
                {
                    if(commands[j][k] == ',')
                    {
                        comma++;
                    }
                    else if(commands[j][k] == ' ')
                    {
                        spaces++;
                    }
                }

                // ignore
                if(length_of_series.at(index) == 0 && comma == 1 && spaces == 1)
                {
                    index++;
                    continue;
                }
                // incorrect as number of comma and spaces are not correct
                else if(length_of_series.at(index) == 0)
                {
                    return false;
                }

                if(comma == length_of_series.at(index) && spaces == 2) 
                {
                    index++;
                    continue;
                }
                else
                {
                    return false;
                }   
            }

        }
        else if(commands[j][0] == '1')// don't do much it is the left over and has to occur only once so f1 is used
        {
            if(commands[j][1] != '\0' || f1 == 1)
            {
                return false;
            }
            else
            {
                f1++;
            }
        }
        else if(commands[j][0] == 'N') // first time this will be called
        {
            int comma = 0, spaces = 0;
            for(int k = 0;k<size(commands[j]);k++)
            {
                if(commands[j][k] == ',')
                {
                    comma++;
                }
                else if(commands[j][k] == ' ')
                {
                    spaces++;
                }
            }
            
            if(length_of_series.at(index) == 0 && comma == 1 && spaces == 1)
            {
                index++;
                continue;
            }
            else if(length_of_series.at(index) == 0)
            {
                return false;
            }

            if(comma == length_of_series.at(index) && spaces == 2) 
            {
                index++;
                continue;
            }
            else
            {
                return false;
            }   
        }
        else
        {
            return false;
        }
        
    }

    return true;
}

int main()
{
    cout.precision(4) ;
    cout << fixed ;

    // input is stored in 'input'
    char *input = new char[100000];
    cin.getline(input,100000);

    // locally stores the sequences in main()
    vector<vector<double>> sequences;

    // stores the objects of Datasequences
    vector<DataSequence> DSvector;

    // stores the objects of Histograms
    vector<Histogram> hist;

    // stores the length of the series mentioned after N
    vector<int> length_of_series;
    
    // stores the number of tokens when delimeters are ' ' and ','
    int strings_length;

    // so that the address don't change frequently
    hist.reserve(100000);

    // stores the tokens when delimeters are ' ' and ','
    char **strings = new char*[1000];
    for(int i=0;i<1000;i++)
    {
        strings[i] = new char[100];
    }

    // this function in if checks the validities and updates various vectors ans pointers
    if(!checkingValidity(input,sequences,DSvector,hist,length_of_series,strings,strings_length))
    {
        cout<<"-1";
        return 0;
    }
    
    // count is used to keep a count on how many token we have processed in strings
    int count = 0;

    // index is a variable that keeps an account about how many values are been checked in length_of_series
    int index = 0;

    while(count != strings_length)
    {
        // first element cannot be A therefore it will have '1' before it
        if(size(strings[count])==1 && strings[count][0] == 'A')
        {
            count++;
            int indexOfSeq;
            sscanf(strings[count],"%d",&indexOfSeq);

            count++;
            double temp;
            sscanf(strings[count],"%lf",&temp);

            if(temp<0)
            {
                cout<<"-1";
                return 0;
            }

            // checking the validity of the input
            if(indexOfSeq<(int)sequences.size())
            {
                sequences[indexOfSeq].push_back(temp);
                DSvector[indexOfSeq].add(temp);
            }
            else
            {
                cout<<"-1";
                return 0;
            }
            count += 2;
            
        }
        else if(size(strings[count])==1 && strings[count][0] == 'N')
        {
            int length = length_of_series.at(index);
            if(length == 0)
            {
                count += 3;
                continue;
            }
            
            index++;
            count = count + 2;
            vector<double> seq;// stores the sequence when given with 'N'
            for(int i=0;i<length;i++)
            {
                double temp;
                sscanf(strings[count],"%lf",&temp);
                
                if(temp<0)
                {
                    cout<<"-1";
                    return 0;
                }

                seq.push_back(temp);
                count++;
            }
            
            // necessary steps for calculations
            Histogram *h = new Histogram();
            hist.push_back(*h);
            DataSequence temp1(seq,&hist[hist.size()-1]);
            DSvector.push_back(temp1);
            sequences.push_back(seq);

            count++;
        }
        else // not a valid input
        {
            cout<<"-1";
            return 0;
        }

    }

    int times = DSvector.size();
    for(int i=0;i<times-1;i++)
    {
        DSvector[i] << cout;
    }
    DSvector[DSvector.size()-1] >> cout;


    return 0;
}
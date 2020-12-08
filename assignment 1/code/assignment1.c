#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

static inline float truncfunc(float x) { return floor((floor(x*1e5)*1e-5+1e-5)*1e4)*1e-4  ;  }

// Just check if relative placing of ',' and ' ' is valid or not.
// we are using counters so as to relatively find commas and spaces.
bool isValid(char input[],int length, int n)
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
            else if(space_counter == 3 || space_counter == 4)
                if(comma_counter == n-1)
                    continue;
                else
                    return false;
            else if(space_counter == 5)
                if(comma_counter == 2*(n-1))
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
    if(space_counter != 5 || comma_counter != 2*(n-1))
        return false;
    return true;
}

// convert the string to natural number.
int findN(char input[], int length)
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

// mathematical aspects taken from internet
float klDivergence(float vector1[], float vector2[], int n)
{
    float sum=0;
    for(int i=0; i<n; i++)
    {
        sum += vector1[i] * log(vector1[i]/vector2[i]);
    }
    return sum;
}

// mathematical aspects taken from internet
float manDist(float vector1[], float vector2[], int n){
    float dist = 0;
    for(int i=0; i<n; i++){
        dist +=  fabs(vector1[i]-vector2[i]);
    } return dist;
}

// mathematical aspects taken from internet
float eucDist(float vector1[], float vector2[], int n)
{
    float squareSum = 0;
    for(int i=0; i<n; i++)
    {
        squareSum += pow(vector1[i]-vector2[i], 2);
    }

    return sqrt(squareSum);
}

// mathematical aspects taken from internet
float cheDistance(float vector1[], float vector2[], int n)
{
    float dist = 0;
    for(int i=0; i<n; i++){
        if(dist < fabs(vector1[i]-vector2[i])){
            dist = fabs(vector1[i]-vector2[i]);
        }
    } return dist;
}

// mathematical aspects taken from internet
float jsDistance(float vector1[],float vector2[],int n)
{
    float m[n];
    float sum = 0;
    for(int i=0;i<n;i++)
    {
        m[i] = (vector1[i]+vector2[i])/2;
        sum = (klDivergence(vector1,m,n)+klDivergence(vector2,m,n))/2;
    }
    return sqrt(sum);
}


int main()
{
    // taking input which is a string with spaces, etc.
    char input[100000];
    char inputcpy[100000];
    scanf ("%[^\n]%*c", input);

    strcpy(inputcpy,input);
    // length of the string
    int length = 0;
    while(input[length] != '\0')
    {
        length++;
    }

    // dividing the numbers which are seperated by ',' or ' '
    char *numbers[100000];
    numbers[0] = strtok(input," ,");
    
    // converting the n from string to integer
    int n = findN(numbers[0],length);
    if(n == -1)
    {
        printf("-1");
        return 0;
    }

    // checking of the commas and the spaces are in proper order.
    if(! isValid(inputcpy,length,n))
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


    // two arrays to store the vectors subparts.
    float vector_one[n];
    float vector_two[n];

    // converting each sub-part from "string" to float
    // we are working on vector one
    int k=0;
    for(int j=2;j<=n+1;j++)
    {
        // beforing using sscanf we want to check if the string is a valid string or not.
        if(isValidNumber(numbers[j]))
        {
            sscanf(numbers[j],"%f",&vector_one[k]);
            k++;
        }
        else
        {
            printf("-1");
            return 0;
        }
        
    }

    // we are checking if the sub-parts of the vector one is positive or not
    for(int i=0;i<n;i++)
    {
        if(vector_one[i]<=0)
        {
            printf("-1");
            return 0;
        }        
    }

    // at the at of the vector 1 we again have a "-1"
    sscanf(numbers[n+2],"%f",&temp);

    if(temp != -1)
    {
        printf("-1");
        return 0;
    }


    // converting each sub-part of vector 2 from "string" to float
    k=0;
    for(int j=n+3;j<2*n+3;j++)
    {
        if(isValidNumber(numbers[j]))
        {
            sscanf(numbers[j],"%f",&vector_two[k]);
            k++;
        }
        else
        {
            printf("-1");
            return 0;
        }
    }

    for(int i=0;i<n;i++)
    {
        if(vector_two[i]<=0)
        {
            printf("-1");
            return 0;
        }        
    }

    // normalising vectors
    float sum=0;
    for(int i=0;i<n;i++)
    {
        sum += vector_one[i]; 
    }
    for(int i=0;i<n;i++)
    {
        vector_one[i] = vector_one[i]/sum;
    }

    // normalising vectors
    sum=0;
    for(int i=0;i<n;i++)
    {
        sum += vector_two[i]; 
    }
    for(int i=0;i<n;i++)
    {
        vector_two[i] = vector_two[i]/sum;
    }

    float mD = truncfunc(manDist(vector_one,vector_two,n)) ;
    float eD = truncfunc(eucDist(vector_one,vector_two,n)) ;
    float cD = truncfunc(cheDistance(vector_one,vector_two,n)) ;
    float klD = truncfunc((klDivergence(vector_one,vector_two,n)+klDivergence(vector_two,vector_one,n)));
    float jsD = truncfunc(jsDistance(vector_one,vector_two,n));

    // printing the respective distances
    // mathematcal part has been taken from internet but I have code this myself.
    printf("%.4f,",mD);
    printf("%.4f,",eD);
    printf("%.4f,",cD);
    printf("%.4f,",klD);
    printf("%.4f",jsD);

    return 0;
}

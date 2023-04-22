#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype> //I add this header file
#include <string> //I add this header file 
#include <ctime> //I add 
#include <cstdlib> //I add 

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::string temp=k; 
        unsigned long long w[5] {0, 0, 0, 0, 0}; 
        HASH_INDEX_T result=0; //the h(k) result 
        int stringLength = temp.size(); //get the string length 
        int remainder=0, divisor=0; 
        divisor=stringLength/6;  //get the number of groups pf 6 letters 
        remainder=stringLength%6; //get the leftover number of letters 
        for (int i=4; i>4-divisor; i--)
        {
            std::string subStr=temp.substr(temp.size()-6, 6); 
            HASH_INDEX_T a[6];
            for (int j=0; j<6; j++)
            {
                a[j]=letterDigitToNumber(subStr[j]);
                //std::cout<<"print a[j]= "<<a[j]<<std::endl;
            }
            w[i]=static_cast<unsigned long long>(((((((a[0])*36+a[1])*36+a[2])*36+a[3])*36+a[4])*36+a[5]));
            temp=temp.substr(0, temp.size()-6); 
        }
        if (remainder!=0)
        {
            HASH_INDEX_T a[6]={0, 0, 0, 0, 0, 0};
            for (int g=0; g<remainder; g++)
            {
 
                a[5-g]=letterDigitToNumber(temp[temp.size()-1-g]);   
            }
            w[4-divisor]=static_cast<unsigned long long>(((((((a[0])*36+a[1])*36+a[2])*36+a[3])*36+a[4])*36+a[5]));
        }
        //std::cout<<"print w[3]= "<<w[3]<<std::endl; 
        //std::cout<<"print w[4]= "<<w[4]<<std::endl; 
        result=rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4]; 
        return result; 

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T index=0; 
        if (letter>= 'A' && letter<= 'Z')
        {
            letter=tolower(letter);
        }
        if (letter>='a' && letter<='z')
        {
            index=static_cast<HASH_INDEX_T>(letter-'a');
            return index; 
        }
        if (letter>='0' && letter <='9')
        {
            index=static_cast<HASH_INDEX_T>(letter-'0'+26);
            return index; 
        }
     
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif



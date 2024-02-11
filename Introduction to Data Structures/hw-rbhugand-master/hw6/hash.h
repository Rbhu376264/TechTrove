#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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

        HASH_INDEX_T w[5];

        
        for(size_t i = 0; i<5; i++)
        {
            w[i] = 0;
        }

        size_t idx = 4;

        HASH_INDEX_T res = 0;

        int terms = 0;

        if(k.size() > 6)
        {
            int counter = k.size()/6;

            int q = k.size();

            int start = q-6;

            int ctr = 0;

            while(ctr != counter)
            {
                
                if(terms == 6)
                {
                    start = start - 6;
                    w[idx] = res;
                    idx--;
                    terms = 0;
                    res = 0;
                    ctr++;
                    continue;
                    
                    
                }
                if(terms == 0)
                {
                    
                    res += letterDigitToNumber(k[start + terms]);
                    
                    terms++;
            
                }
                else
                {
                    
                    res = 36*res;
                    
                    res += letterDigitToNumber(k[start+terms]);
                    
                    terms++;
                    
                }
            }

            if(start<0)
            {
                int finish = start + 6;

                for(int i = 0; i<finish; i++)
                {

                    if(terms == 0)
                    {
                        
                        res += letterDigitToNumber(k[i]);
                        
                        terms++;
                        
                    }
                    else
                    {
                        
                        res = 36*res;
                        
                        res += letterDigitToNumber(k[i]);
                        
                        terms++;
                        
                    }

                }

                w[idx] = res;
            }



            
        }
        if(k.size() <= 6)
        {
            for(size_t i = 0; i<k.size(); i++)
            {
                
                if(terms == 6)
                {
                    w[idx] = res;
                    idx--;
                    terms = 0;
                    res = 0;
                    
                }
                if(terms == 0)
                {
                    
                    res += letterDigitToNumber(k[i]);
                    
                    terms++;
                    
                }
                else
                {
                    
                    res = 36*res;
                    
                    res += letterDigitToNumber(k[i]);
                    
                    terms++;
                }
                
                
            }
        }


        

        if(k.size()<=6 || terms<=6)
        {
            w[idx] = res;
        }


        HASH_INDEX_T final_result = 0;
        
        for(size_t i = 0; i<5; i++)
        {
            
            
            final_result += w[i]*rValues[i];
            
            
        }

        

        return final_result;

    }


    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter>='A' && letter<= 'Z')
        {
            return(HASH_INDEX_T)(letter+32-'a');
        }
        if(letter>='a' && letter <= 'z')
        {
            // std::cout<<HASH_INDEX_T(letter-'a')<<std::endl;
            return (HASH_INDEX_T)(letter-'a');
        }
        else
        {
            return (HASH_INDEX_T)(('z'-'a' + 1)+letter-'0');
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

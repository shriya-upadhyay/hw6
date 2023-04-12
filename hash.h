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

			unsigned long long w[5];
			for(int l = 0; l < 5; l++) {
				w[l] = 0;
			}
			
			int i = 4;
			int counter = 0;
		
			unsigned long long val = 0;
			unsigned long long power = 1;
			for(int j = k.length() - 1; j >= 0; j--) {
				val += power* letterDigitToNumber(k[j]);
				counter++;
				power *= 36;

				if(counter == 6){
					w[i] = val;
					power = 1;
					val = 0;
					counter = 0;
					i--;
				}

			}

			if (i >= 0 && counter < 6) {
				w[i] = val;
			}

			HASH_INDEX_T hash_val = 0;

			for (int i = 0; i < 5; i++ ) {
				//std:: cout << "i: " << w[i] << std::endl;
			}
			for (int p = 0; p < 5; p++) {
				hash_val += (rValues[p] * w[p]);
			}
        
        
		return hash_val;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        size_t val;

				if (letter >= 'A' && letter <= 'Z') {
        	letter = tolower(letter);
				}

        if (letter >= 'a' && letter <= 'z') {
            val = letter - 'a';
        }

        else if (letter >= '0' && letter <= '9') {
            val = letter - '0' + 26;
        }

        return val;

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

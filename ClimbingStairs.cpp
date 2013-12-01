#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>

double count_possibilities(double steps);
double binomial_coefficient(double n, double k);


/*---------------------------------------------------------------------------*/
int main(int argc, char* argv[]){
/*---------------------------------------------------------------------------*/
    ifstream file;
    file.open(argv[1]);
    string lineBuffer;
    while(!file.eof()){
        getline(file, lineBuffer);
        if(lineBuffer.length() == 0){
            continue;
        }
        else{
            stringstream ss;
            ss << lineBuffer;
            double input;
            ss >> input;
            cout << count_possibilities(input) << '\n';
        }
    }
    return(0);
}

/*---------------------------------------------------------------------------*/
double count_possibilities(double steps){
/*---------------------------------------------------------------------------*/
//the binomial coefficient counts how many ways to distribute k elements across
//n total. We use this to count all the different ways to place the 2 step increments. 
    double half_steps = steps / 2;
    modf(half_steps, &half_steps);
    double possibilities = 0;
    for(double i = 0.0; i <= half_steps; i += 1){
        possibilities += binomial_coefficient(steps - i, i);
    }
    return(possibilities);
}

/*---------------------------------------------------------------------------*/
double binomial_coefficient(double n, double k){
/*---------------------------------------------------------------------------*/
    double result = 1;
    for(double i = 1.0; i <= k; i += 1){
        result *= (n - k - i)/i;
    }
    return(result);
}


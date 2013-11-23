#include <string>
#include <fstream> //open file
#include <cmath> //modf and sqrt
#include <iostream> //print results
#include <sstream>

using namespace std;

int NumOfSquares(int M); //return the number ways to write M as a sum of squares
bool isInt(double y); //checks if y is an int
const double Cos45 = .707106; //cosine of 45 degrees

int main(int argc, char* argv[]){
    string lineBuffer;
    bool firstline = true;
    ifstream file;
    file.open(argv[1]);
    while (!file.eof()) {
        getline(file, lineBuffer);
        if (lineBuffer.length() == 0)
            continue; //ignore all empty lines
        else{
            if(firstline){firstline = false;}
            else{
                stringstream str;
                str << lineBuffer;
                int M;
                str >> M;
                cout << NumOfSquares(M) << "\n";
            }
        }
    }
    return(0);
}

int NumOfSquares(int M){
    int Count = 0;
    double y;
    int Start;
    double intPart;
    double fracPart = modf(sqrt(static_cast<double> (M)) * Cos45, &intPart);
    Start = static_cast<int> (intPart);
    if(fracPart != 0.0){
        Start++; //round up, since this is the first possible candidate
    }
    for(int i = Start; i < sqrt(static_cast<double> (M)); i++){
        y = sqrt(static_cast<double> (M - i*i));
        if(isInt(y)){
            Count++;
        }
    }
    return(Count);
}

bool isInt(double y){
    double intpart, fracpart;
    fracpart = modf(y, &intpart);
    return(y == intpart);
}
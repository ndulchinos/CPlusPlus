#include <iostream>
#include <thread>

using namespace std;

const float STEP = 0.01;
void integrate(float * output, float start, float stop, float (* f)(float));
float square(float x);
float cube(float x);

int main(){
    cout << "integrating several functions from 0 to 40" << '\n';
    float (*f)(float); //function pointer
    f = &square; //set pointer to point to func
    float exact;
    float result1, result2, result3, result4;
    thread region1 (integrate, &result1, 0, 10, f);
    thread region2 (integrate, &result2, 10, 20, f);
    thread region3 (integrate, &result3, 20, 30, f);
    thread region4 (integrate, &result4, 30, 40, f);
    region1.join();
    region2.join();
    region3.join();
    region4.join();
    cout << "x^2 result " << result1 + result2 + result3 + result4 << '\n';
    f = &cube;
    thread region5 (integrate, &result1, 0, 10, f);
    thread region6 (integrate, &result2, 10, 20, f);
    thread region7 (integrate, &result3, 20, 30, f);
    thread region8 (integrate, &result4, 30, 40, f);
    region6.join();
    region7.join();
    region8.join();
    region5.join();
    cout << "x^3 result " << result1 + result2 + result3 + result4 << '\n';
    cin >> result1;
    return(0);
}

float cube(float x){ 
    return(x*x*x);
}

float square(float x){ // for now f = x^2
    return (x*x);
}

void integrate(float * output, float start, float stop, float (* f)(float)){ //for now f = x^2
    float answer = 0;
    for(float i = start; i < stop; i = i + STEP){
        float val;
        val = (*f) (i);
        answer = answer + val*STEP;
    }
    *output = answer; 
}
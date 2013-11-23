#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string Getf(char c, string str);
string Getb(char c, string str);

int main(int argc, char* argv[]){
    
string lineBuffer;

ifstream file;
file.open(argv[1]);
while (!file.eof()) 
   {
       getline(file, lineBuffer);
       if (lineBuffer.length() == 0)
           continue; //ignore all empty lines
       else 
       {
           string strA = Getb(',', lineBuffer);
           string strB = Getf(',', lineBuffer);
           bool contained = true;
           for(int i = 0; i < strB.length(); i++){
               if(strB[i] != strA[strA.length() - strB.length() + i]){
                   contained = false;
               }
           }
           if(contained){
               cout << 1 << '\n';
           }
           else{
               cout << 0 << '\n';
           }
       }
}

return(0);
}

/*------------------------------------------------------------------------------------------------------------*/
string Getf(char c, string str){ // get characters that follow first instance of c in str
/*------------------------------------------------------------------------------------------------------------*/
    bool start = false;
    string result = "";
    for (int i = 0; i < str.length(); i++){
        if(start){
            result.push_back(str[i]);
        }
        if(str[i] == c){
            start = true;
        }
    }
    return(result);

}
/*------------------------------------------------------------------------------------------------------------*/
string Getb(char c, string str){ //get characters that preceed first instance of c in str
/*------------------------------------------------------------------------------------------------------------*/
    string result = "";
    bool stop = false;
    for (int i = 0; i < str.length(); i++){
        if(str[i] == c){
            stop = true;
        }
        if(!stop){
            result.push_back(str[i]);
        }
    }
    return(result);
}
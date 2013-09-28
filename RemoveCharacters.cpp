#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string Getf(char c, string str);
string Getb(char c, string str);

int main (int argc, char* argv[]){

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
           vector<char> Remove; //letters to be removed
           string toParse = Getb(',', lineBuffer);
           string toRemove = Getf(',', lineBuffer);
           string toPrint = "";
           
           for( int i = 0; i < toRemove.length(); i++){
               if(toRemove[i] != ' '){
                   Remove.push_back(toRemove[i]); //get letters to be removed
               }
           }
           
           for (int i = 0; i < toParse.length(); i++){
               bool toAdd = true;
               for(int j = 0; j < Remove.size(); j++){
                   if (toParse[i] == Remove[j]){
                       toAdd = false;
                   }
               }
               if(toAdd){
                   toPrint.push_back(toParse[i]);
               }
           }
           
           cout << toPrint << '\n';
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
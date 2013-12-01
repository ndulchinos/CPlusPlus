#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool check_line(string line);
void split_line(string line, char split, string *left_output, string *right_output);

/*---------------------------------------------------------------------------*/
int main(int argc, char* argv[]){
/*---------------------------------------------------------------------------*/
    ifstream file;
    string lineBuffer;
    file.open(argv[1]);
    while (!file.eof()){
        getline(file, lineBuffer);
        if (lineBuffer.length() == 0){
            continue;
        }
        else{
            if (check_line(lineBuffer)){
                cout << "true" << "\n";
            }
            else{
                cout << "false" << "\n";
            }
        }
    }
    return(0);
}
/*---------------------------------------------------------------------------*/
bool check_line(string line){
/*---------------------------------------------------------------------------*/
//we expect a line, with the main string to the left of a comma,
//and the tested substring to the right. return true if the right
//is inside the left
    string left = "";
    string right = "";
    split_line(line, ',', &left, &right);
    int substring_depth = 0; //we use this to keep track of how far into the substring we have matched
    bool match_mode = false; //are we using the * function?
    for(string::iterator it = left.begin(); it != left.end(); it++){
        if(match_mode){ // in this mode, we search for the next element of right, ignoring non matches
            int tmp_substring_depth = substring_depth;
            for(string::iterator itt = it; itt != left.end(); itt++){
                if(*itt == right[tmp_substring_depth]){
                    tmp_substring_depth++;
                    if(tmp_substring_depth == right.length()){
                        return(true);
                    }
                }
                else{
                    tmp_substring_depth = substring_depth;
                }
            }
            match_mode = false; //if we read the end without completing the string, we need to reset
            substring_depth = 0;
        }
        else{
            if(*it == right[substring_depth]){
                substring_depth++; // the current character matches, check the next one
                if(substring_depth == right.length()){
                    return(true); //if we don't early exit here, the next line will seg fault
                }
                if(right[substring_depth] == '.'){
                    match_mode = true;
                    substring_depth++;
                }
            }
            else{
                substring_depth = 0; //the current character does not match, start looking for the first again
            }
        }
    }
    if(substring_depth == right.length()){
        return(true);
    }
    else{
        return(false);
    }
}

/*---------------------------------------------------------------------------*/
void split_line(string line, char split, string *left_output, string *right_output){
/*---------------------------------------------------------------------------*/
//split line into that which appears before split, and that which appears after
//characters should be either numbers or letters. however, we expect some
//characters in the right string to be "\", and "*". A "*" means pattern match,
//and the "\" is used to treat "\*" as *
    bool left_side = true;
    bool escape = false; //are we in an escape sequence?
    for(string::iterator it = line.begin(); it != line.end(); it++){
        if(*it == split){
            left_side = false; 
        }
        else if(left_side){
            left_output->push_back(*it);
        }
        else if(!escape){ //we're in the right side now, but not in the escape sequence
            if(*it == '\\'){ //found the start of an escape sequence
                escape = true;
            }
            else if(*it == '*'){
                right_output->push_back('.'); //we use a period to mark the pattern match character
            }
            else{
                right_output->push_back(*it);
            }
        }
        else{ //still in the right side, finishing the escape sequence
            right_output->push_back('*'); 
            escape = false;
        }
    }
}


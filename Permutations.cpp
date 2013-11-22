#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void extend_permutation(string candidates, string permutation, vector<string> &output); //recursively extends a permutation, creating all permutations, and puts them in output
string reduce_candidates(string candidates, int toRemove); //takes candidates for one step of extend_permutations, and returns the candidates for the next

/*-------------------------------*/
int main(int argc, char* argv[]){
/*-------------------------------*/
    string lineBuffer;
    ifstream file;
    file.open(argv[1]);
    while (!file.eof()){
        getline(file, lineBuffer);
        if (lineBuffer.length() == 0)
            continue; //ignore all empty lines
        else {
    	    vector<string> permutations;
            sort(lineBuffer.begin(), lineBuffer.end()); //prepare the string for the next step
            extend_permutation(lineBuffer, "", permutations);
			for(int i = 0; i < permutations.size(); i++){
			    cout << permutations[i];
				if(i != permutations.size() - 1){
				    cout << ",";
				}
			}
			cout << "\n";
        }
    }
    return(0);
}

/*----------------------------------------------------------------------------------------*/
void extend_permutation(string candidates, string permutation, vector<string> &output){
/*----------------------------------------------------------------------------------------*/
    if(candidates.length() == 1){ //base case. 
	    permutation.append(candidates);
		output.push_back(permutation);
	}
	else{
        for(int i = 0; i < candidates.length(); i++){
	        string buffer = permutation;
            buffer.push_back(candidates[i]);
		    extend_permutation(reduce_candidates(candidates, i), buffer, output);
	    }
	}
}

/*------------------------------------------------------------*/
string reduce_candidates(string candidates, int toRemove){
/*------------------------------------------------------------*/
    string result = "";
    for(int i = 0; i < candidates.length(); i++){
	    if(i != toRemove){
		    result.push_back(candidates[i]);
		}
	}
	return (result);
}
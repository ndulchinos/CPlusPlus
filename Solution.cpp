#include <iostream>     // std::cout
#include <istream>      // std::cin
#include <fstream>      // std::ifstream
#include <vector>       // for vectors
#include <string>       // for strings
#include <algorithm>    //std::sort
#include <sstream>      //std::stringstream

std::string SubStringb(std::string s, char c);
std::string SubStringf(std::string s, char c);
void merge(std::vector<std::string> output);
std::string GetLine(std::string path, int n);
std::string ParsePunc(std::string buffer);


int main () {
  const int JUMP = 100; //roughly the size of each "chunk"
  const int LENGTH = 50;  //Length of assumed longest word
  bool debug = true; //set to true for debug info
  std::ifstream is ("C:\\Users\\Nick\\Desktop\\notes.txt", std::ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
	is.seekg (0, is.beg); // first entry is the offset
	char * buffer = new char [LENGTH]; 
	std::vector<long long int> stops; //long long is required since these in principle need to enumerate positions up to 100 billion
	for(int i = JUMP; i < length; i = i + JUMP){ 
		is.read(buffer, LENGTH);
		for(int j = LENGTH - 1; j > -1; j--){
			int diff = LENGTH - 1 - j;
			if (j >= 0){ //protect against out of range index
				if (buffer[j] == ' ' || buffer[j] == '\n'){
					stops.push_back(i - diff); 
					j = -2; //early exit, necessary because we only want the last character
				}
			}
		}
		if(debug){std::cout.write (buffer, LENGTH);}
	
	}
	delete[] buffer;
	char * buffer2 = new char [JUMP + 20]; 
	//file parsing, in principle this can be parallelized
	for (int i = 0; i < stops.size(); i++){
		std::vector<std::string> words;
		std::string wordbuffer;
		std::ofstream myfile;
		std::string Str;
		std::string Num = std::to_string(i+1);
		Str = "C:\\Users\\Nick\\Desktop\\test\\output";
		Str.append(Num);
		Str.append(".txt");
		myfile.open(Str);
		if(i == 0){ // special case to include first segment of the file
			std::ofstream tmpfile;
			Str = "C:\\Users\\Nick\\Desktop\\test\\output";
			Str.append(std::to_string(i));
			Str.append(".txt");
			tmpfile.open(Str);
			is.seekg (0, is.beg);
			is.read(buffer2, stops[i]);
			for (int j = 0; j < stops[i]; j++){
				if (buffer2[j] != ' ' && buffer2[j] != '\n'){
					wordbuffer.push_back(buffer2[j]);
				}
				else{
					words.push_back(ParsePunc(wordbuffer));
					wordbuffer = "";
				}
			}
			//insert sort here
			std::sort (words.begin(), words.end()); //sort the words, makes the merging easier
			for (int j = 0; j < words.size(); j++){
				int counter = 1; // set to 0 if word has already been counted
				if( j > 0){
					for (int k = 0; k < j; k++){
						if (words[k] == words[j]){
							counter = 0;
						}
					}
				}
				if(counter > 0){
					for (int k = j + 1; k < words.size(); k++){
						if (words[k] == words[j]){
							counter++;
							
						}
					}
					tmpfile << counter << " " << words[j] << "\n";
				}
				
			}
		}
	
		 if(i < stops.size() - 2){ //prevent index out of range error
			is.seekg (stops[i], is.beg);
			is.read(buffer2, stops[i+1] - stops[i]);
			for (int j = 0; j < stops[i+1] - stops[i]; j++){
				if (buffer2[j] != ' ' && buffer2[j] != '\n'){
					wordbuffer.push_back(buffer2[j]);
				}
				else{					
					words.push_back(ParsePunc(wordbuffer));
					wordbuffer = "";
				}
			}
			//insert sort here, sort words
			std::sort (words.begin(), words.end()); // sort the words, makes merging the files easier
			for (int j = 0; j < words.size(); j++){
				int counter = 1; // set to 0 if word has already been counted
				if( j > 0){
					for (int k = 0; k < j; k++){
						if (words[k] == words[j]){
							counter = 0;
						}
					}
				}
				if(counter > 0){
					for (int k = j + 1; k < words.size(); k++){
						if (words[k] == words[j]){
							counter++;
						}
					}
					myfile << counter <<  " " << words[j] << "\n";
				}
			
			}
		}
		
		else{
			/*
			//PROBLEM FOUND! IT"S HERE! WOOOOOOOO!
			is.seekg (stops[i], is.beg);
			is.read(buffer2, 2*JUMP); //read the rest of the file
			myfile << buffer2; */
		}

		myfile.close();
	}
	delete[] buffer2;

	//merge results
	std::vector<std::string> output; //the middle range output files
	for (int i = 1; i < stops.size() + 1; i++){ // create ifstreams for each output file
		std::string Str = "C:\\Users\\Nick\\Desktop\\test\\output";
		Str.append(std::to_string(i));
		Str.append(".txt");
		output.push_back(Str);
	} 
	merge(output); //this merges everything
	


	//debug code
	if (debug){
	std::cout << "\n";
	char * test = new char [1];
	for (int i = 0; i < stops.size(); i++){
		is.seekg (stops[i] - 1, is.beg);
		is.read(test, 1);
		std::cout << "character " << i << " is at " << stops[i] << " and is ";
		std::cout.write (test, 1);
		std::cout << "\n";
	}
	}
	//debug code

	is.close();

    std::cout << "done";
	//debug code
	char x; 
	std::cin >> x; //this is just here so the output pauses
	//end debug code
  }

  return 0;
}

std::string SubStringf(std::string s, char c){ //get the part of the string after character c
	std::string str = "";
	bool start = false;
	for(int i = 0; i < s.size(); i++){
		if(start){str.push_back(s[i]);}
		if (s[i] == c){
			start = true;
		}
	}
	return(str);
}

std::string SubStringb(std::string s, char c){ //get the part of the string before character c
	std::string str = "";
	for(int i = 0; i < s.size(); i++){
		if(s[i] != c){
			str.push_back(s[i]);
		}
		else{return(str);}
	}	
	return(str);
}

void merge (std::vector<std::string> output){
	std::vector<std::string> lines; //buffer that holds the next line in each file to be considered
	std::vector<unsigned int> freqs; //frequencies of lines
	std::vector<int> toUpdate; //list of files to be incremented
	std::vector<int> increments; //number of times each list has to be incremented
	std::ofstream result; //file to write to
	result.open("C:\\Users\\Nick\\Desktop\\test\\final.txt");
	for(int i = 0; i < output.size(); i++){ //reads into the buffers
		lines.push_back("");
		lines[i] = GetLine(output[i], 0);
		increments.push_back(1);
		//result << lines[i] << "\n";
		std::stringstream str;
		str << SubStringb(lines[i], ' ');
		unsigned int x;
		str >> x;
		freqs.push_back(x);
		lines[i] = SubStringf(lines[i], ' ');
	}
	bool eof; // signals end of file hit
	int max; //location of max in buffer
	unsigned int total; //total frequency of word in all files
	bool NotFinished = true;
	while (NotFinished){
		toUpdate.clear(); //reset this list
		max = 0; //reset max location
		total = 0;
		for(int i = 1; i < lines.size(); i++){//find the max
			if(lines[i] != "eof"){
				if(lines[i] > lines[i-1]){max = i;}
			}
		}
		for(int i = 0; i < lines.size(); i++){
			if(lines[i] == lines[max]){
				toUpdate.push_back(i);
				increments[i]++;
			}
		}
		result << lines[max] << " "; //write the word
		for(int i = 0; i < toUpdate.size(); i++){
			unsigned int counter;
			std::stringstream str;
			str << freqs[toUpdate[i]];
			str >> counter;
			total = total + counter;
			lines[toUpdate[i]] = GetLine(output[toUpdate[i]], increments[toUpdate[i]]);
			if(lines[toUpdate[i]] != "eof"){
				std::stringstream str2;
				str2 << SubStringb(lines[toUpdate[i]], ' ');
				unsigned int x;
				str2 >> x;
				freqs[toUpdate[i]] = x;
				lines[toUpdate[i]] = SubStringf(lines[toUpdate[i]], ' ');
			}
		}
		result << total << "\n";
		//bool done = true;
		unsigned int cntr = 0;
		for(int i = 0; i < lines.size(); i++){
			if(lines[i] == "eof"){cntr++;}
		}
		/*for(int i = 0; i < lines.size(); i++){
			if(lines[i] != "eof"){done = false;}
		}*/
		if(cntr == lines.size()){NotFinished = false;}
	}
}

std::string ParsePunc(std::string buffer){// removes the punctuation at the end of a word, so that eg "frequency" and "frequency," are the same word
	if(buffer.size() > 0){ //error handling
		if(buffer.back() == '.'){
			buffer.erase(buffer.length()-1, 1);
			return(buffer);
		}
		if(buffer.back() == ','){
			buffer.erase(buffer.length()-1, 1);
			return(buffer);
		}
		if(buffer.back() == '!'){
			buffer.erase(buffer.length()-1, 1);
			return(buffer);
		}
		if(buffer.back() == ':'){
			buffer.erase(buffer.length()-1, 1);
			return(buffer);
		}
		if(buffer.back() == ';'){
			buffer.erase(buffer.length()-1, 1);
			return(buffer);
		}
		if(buffer.back() == '?'){
			buffer.erase(buffer.length()-1, 1);
			return(buffer);
		}
	}
	else{return(buffer);}
	return(buffer); //error handling
}

std::string GetLine(std::string path, int n){ //returns nth line from file
	std::string str;
	std::ifstream input;
	input.open(path);
	for(int i = 0; i < n; i++){
		std::getline(input, str);
	}
	input.close();
	if(input.eof()){return "eof";}
	else{return(str);}
}






	

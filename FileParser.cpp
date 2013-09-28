#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;

void PartitionFile(string filepath, vector<long long> * PartBndrys);
void ParsePartition(long long start, long long stop, int PartNum, string str);
string ParseWord(string str);
void Merge(vector<long long> * PartBndrys);

const int JUMP = 200; //rough size of each partition to load in memory
const int WORD = 50; // assumed size of largest word, + some extra to be conservative

/*------------------------------------------------------------------------------------------------------------*/
int main(){
/*------------------------------------------------------------------------------------------------------------*/
	ofstream debug;
	debug.open("C:\\Users\\Nick\\Desktop\\test\\debug.txt");
	debug << "Starting \n";
	vector<long long> PartBndrys; //partitions boundries
	debug << "About to Partition file" << "\n";
	PartitionFile("C:\\Users\\Nick\\Desktop\\notes.txt", &PartBndrys);
	debug << "file partitioned" << "\n";
	debug << PartBndrys.size() << " partitions \n";
	for(int i = 0; i < PartBndrys.size(); i++){
		if (i == 0){
			debug << "parsing first partition stops at" << PartBndrys[i] << "\n";
			ParsePartition(0, PartBndrys[i], i, "C:\\Users\\Nick\\Desktop\\notes.txt");
		}
		else{
			debug << "parsing partition stops at " << PartBndrys[i] << " starts at " << PartBndrys[i-1] << "\n";
			debug << "size of partition is " << PartBndrys[i] - PartBndrys[i-1] << "\n";
			ParsePartition(PartBndrys[i - 1], PartBndrys[i], i, "C:\\Users\\Nick\\Desktop\\notes.txt");
		}
	}
	debug << "all partitions parsed \n";
	debug << "about to merge \n";
	Merge(&PartBndrys);
	debug << "merging complete \n";
	debug.close();
	return(0);
}

/*------------------------------------------------------------------------------------------------------------*/
void PartitionFile(string filepath, vector<long long> * PartBndrys){ //Partitions the file into readable sections.
/*------------------------------------------------------------------------------------------------------------*/
	char * buffer = new char[WORD];
	ifstream is;
	is.open(filepath, std::ifstream::binary);
	is.seekg (0, is.end);
    long long length = is.tellg(); //size of file, long long to capture large data file (size > 4GB)
    is.seekg (0, is.beg);
	for(long long i = JUMP; i < length; i += JUMP){
		long long n = i; //copy i
		is.read(buffer, WORD);
		for(int j = 0; j < WORD; j++){
			n--;
			if(buffer[WORD - j - 1] == ' ' || buffer[WORD - j - 1] == '\n'){
				PartBndrys->push_back(n);//record location of end of last word in buffer
				j = WORD; //early exit
			}
		}

	}
	//Last partition ends at the end of the file
	PartBndrys->push_back(length);
	is.close();
	delete[] buffer;
}



/*------------------------------------------------------------------------------------------------------------*/
void ParsePartition(long long start, long long stop, int PartNum, string FilePath){//this function could be paralellized.
/*------------------------------------------------------------------------------------------------------------*/
	char * buffer = new char[JUMP + WORD]; // largest partition potential partition
	string wordbuffer = ""; // word in construction
	vector<string> words; //words to be sorted prior to output
	string Str;
	stringstream sstrm;
	sstrm << "C:\\Users\\Nick\\Desktop\\test\\output" << PartNum << ".txt"; 
	sstrm >> Str;
	
	ofstream output;
	output.open(Str);
	ifstream is;
	
	is.open(FilePath, ifstream::binary);
	is.seekg (start, is.beg);
	is.read (buffer, stop - start);
	for(int i = 0; i < stop - start; i++){
		if (buffer[i] == ' ' || buffer[i] == '\n'){ //checks for the end of a word
			if(wordbuffer.length() > 0){ //makes sure there is a word ready in the buffer
				words.push_back(ParseWord(wordbuffer));
				wordbuffer.clear();
			}
		}
		else {
			wordbuffer += buffer[i];
		}
	}
	sort(words.begin(), words.end()); //sort the words
	int cntr = 1; //counts instances of a word in this partition
	for (int i = 0; i < words.size() - 1; i++){
		cntr = 1; //reset counter
		bool ToAdd = true;
		for (int j = 0; j < i; j++){ //check to see if word has already been considered
			if (words[i] == words[j]){
				ToAdd = false;
			}
		}
		if(ToAdd){
			for (int j = i + 1; j < words.size(); j++){ //count how many times the word occurs
				if (words[i] == words[j]){
					cntr++;
				}
				if (words[i] != words[j]){
					j = words.size(); //since we sorted words, we know there are no more instances -> early exit
				}
			}
			output << cntr << " " << words[i] << "\n";
		}
		
		
	}

	output.close();

}

/*------------------------------------------------------------------------------------------------------------*/
string ParseWord(string str){ //remove punctuation at the end of str
/*------------------------------------------------------------------------------------------------------------*/
	if(str == ""){return(str);}
	if(str.back() == '.'){
		str.pop_back();
	}
	if(str.back() == ','){
		str.pop_back();
	}
	if(str.back() == ':'){
		str.pop_back();
	}
	if(str.back() == ';'){
		str.pop_back();
	}
	if(str.back() == '?'){
		str.pop_back();
	}
	return(str);
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

/*------------------------------------------------------------------------------------------------------------*/
string GetLine(int LineNum, string path){ //get line n of file "path"
/*------------------------------------------------------------------------------------------------------------*/
	string result = "";
	ifstream is;
	is.open(path, ifstream::binary);
	bool eof;

	for(int i = 0; i < LineNum + 1; i++){
		result.clear();
		eof = getline(is, result);
	}
	if(!eof) {return("eof");} //reached end of file
	return(result); //otherwise, print line LineNum
}

/*------------------------------------------------------------------------------------------------------------*/
void Merge(vector <long long> * PartBndrys){ //Merge the intermediate output files
/*------------------------------------------------------------------------------------------------------------*/
	vector<string> lines; //line in consideration for each file
	vector<string> slines; //sorted lines, to find the next line to write
	vector<int> increments; //which line each file is on
	vector<string> paths; //paths to intermediate output files

	stringstream sstrm;
	for(int i = 0; i < PartBndrys->size(); i++){ //initialize paths
		sstrm.clear();
		sstrm << "C:\\Users\\Nick\\Desktop\\test\\output" << i << ".txt";
		string str = "";
		sstrm >> str;
		paths.push_back(str);
	}

	for(int i = 0; i < PartBndrys->size(); i++){ //initialize lines, increments
		lines.push_back(GetLine(0,paths[i]));
		increments.push_back(0);
	}

	ofstream result;
	result.open("C:\\Users\\Nick\\Desktop\\test\\result.txt"); //open file to print out result
	
	bool NotFinished = true;
	while(NotFinished){//loop for merging files
		slines.clear(); //reset sorted lines vector
		for(int i = 0; i < lines.size(); i++){
			if(lines[i] != "eof"){ //load lines from files that still have unmerged data
				slines.push_back(Getf(' ', lines[i]));
			}
		}
		sort(slines.begin(), slines.end()); //this actually wastes some time, since we only need to know which element of slines is the max. it doesn't matter if the rest are sorted
		//since slines is sorted, highest is first entry
		int cntr = 0; //counts total number of time word appears in the entire input file
		for(int i = 0; i < lines.size(); i++){
			if(Getf(' ', lines[i]) == slines[0]){
				int x;
				sstrm.clear();
				sstrm << Getb(' ', lines[i]);
				sstrm >> x;
				cntr += x;
				increments[i]++;
			}
		}
		result << slines[0] << "   " << cntr << "\n"; //print word, then tab, then frequency
		NotFinished = false;
		for(int i = 0; i < lines.size(); i++){ //load next lines, check if done
			lines[i] = GetLine(increments[i], paths[i]);
			if (lines[i] != "eof"){NotFinished = true;}
		}
		
	}



}
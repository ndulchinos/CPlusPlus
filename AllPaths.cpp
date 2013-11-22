#include <list>
#include <vector>
#include <iostream>

using namespace std;

void construct_graph(list<int>* output[]); //initialize the squares
void extend_path(int end, vector<int> path, list<int>* graph[], int &output); //recursively extend path, creating all paths
bool check_path(int next, vector<int> &path); //test if next appears in path

/*----------------------------------------------------------------------------------*/
int main(){
/*----------------------------------------------------------------------------------*/
    //initialization code
    int count = 0;
	list<int>* graph[16];
	list<int> edges[16]; //we use these to initialize graph
	for(int i = 0; i < 16; i++){
	    graph[i] = &edges[i];
	}
	construct_graph(graph);
	vector<int> path;
	path.push_back(0); //0 is the first square
	path.push_back(1); //by symmetry, we only need to consider paths that start this way, then multiply by two
	//main execution
	extend_path(15, path, graph, count); //15 is the last square
	count = count * 2; //see above symmetry comment
	cout << count;
    return(0);
}

/*----------------------------------------------------------------------------------*/
void extend_path(int end, vector<int> path, list<int>* graph[], int &output){
/*----------------------------------------------------------------------------------*/
    int lastsquare = path[path.size() - 1];
	for(list<int>::iterator it = graph[lastsquare]->begin(); it != graph[lastsquare]->end(); it++){
	    if(*it == end){ //this is a good path, so count it
		    output++;
		}
		else{ //otherwise, move on to the next valid path
	        vector<int> next_path = path;
		    if(check_path(*it, path)){
		        next_path.push_back(*it);
		        extend_path(15, next_path, graph, output);
		    }
		}
	}
}

/*----------------------------------------------------------------------------------*/
bool check_path(int next, vector<int> &path){ //return true if good path, false if bad path
/*----------------------------------------------------------------------------------*/
    for(vector<int>::iterator it = path.begin(); it != path.end(); it++){
	    if(*it == next){
		    return(false);
		}
	}
	return(true);
}

/*----------------------------------------------------------------------------------*/
void construct_graph(list<int>* output[]){
/*----------------------------------------------------------------------------------*/
    /* The grid convention is:
	  0,  1,  2,  3
	  4,  5,  6,  7
	  8,  9, 10, 11
	 12, 13, 14, 15 */
	
	//output[0]->push_front(1); //can be removed for optimization, but will only optimize this function
	//output[0]->push_front(4);
	
	output[1]->push_front(2);
	//output[1]->push_front(0); //removed for optimization (optimizes extend_path)
	output[1]->push_front(5);
	
	//output[2]->push_front(1); //removed for optimization (optimizes extend_path)
	output[2]->push_front(3);
	output[2]->push_front(6);
	
	output[3]->push_front(2);
	output[3]->push_front(7);
	
	//output[4]->push_front(0); //removed for optimization (optimizes extend_path)
	output[4]->push_front(5);
	output[4]->push_front(8);
	
	output[5]->push_front(4);
	output[5]->push_front(6);
	//output[5]->push_front(1); //removed for optimization (optimizes extend_path)
	output[5]->push_front(9);
	
	output[6]->push_front(7);
	output[6]->push_front(5);
	output[6]->push_front(2);
	output[6]->push_front(10);
	
	output[7]->push_front(6);
	output[7]->push_front(3);
	output[7]->push_front(11);
	
	output[8]->push_front(4);
	output[8]->push_front(9);
	output[8]->push_front(12);
	
	output[9]->push_front(5);
	output[9]->push_front(8);
	output[9]->push_front(10);
	output[9]->push_front(13);
	
	output[10]->push_front(6);
	output[10]->push_front(9);
	output[10]->push_front(11);
	output[10]->push_front(14);
	
	output[11]->push_front(7);
	output[11]->push_front(10);
	output[11]->push_front(15);
	
	output[12]->push_front(8);
	output[12]->push_front(13);
	
	output[13]->push_front(9);
	output[13]->push_front(12);
	output[13]->push_front(14);
	
	output[14]->push_front(13);
	output[14]->push_front(15);
	output[14]->push_front(10);
	
	//output[15]->push_front(11); //these can also be removed for optimization, but will only effect this function
	//output[15]->push_front(14);
}
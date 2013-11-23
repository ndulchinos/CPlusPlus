#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[]) {
  std::ifstream file;
  std::string lineBuffer;
  file.open(argv[1]);
  while (!file.eof()){
    getline(file, lineBuffer);
    if (lineBuffer.length() == 0)
        continue; //ignore all empty lines
    else{
        bool done = false;
        for (int i = 0; i < lineBuffer.length(); i++){
            bool bad = false;
            for (int j = i + 1; j < lineBuffer.length(); j++){
                if (lineBuffer[i] == lineBuffer[j]){
                    bad = true;
                }
            }
            if (bad == false){
                if (done == false){
                    std::cout << lineBuffer[i] << "\n";
                    done == true;
                }
            }
        }
    }
  }
  return 0;
}
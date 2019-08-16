/*
 * Author: Mario Palma
 * Date: 4/6/2019
 * References: Starting out With C++ 7th edition
 */

#include<iostream>
#include<fstream>

using namespace std;

void printLastKLines(string, int);

int main(){
  string fileName;
  long k; 

  cout << "Enter the name of a file and I will print the last K lines." << endl;
  getline(cin, fileName);

  cout << "Enter a value for K: ";
  cin >> k;

  printLastKLines(fileName, k);
}

void printLastKLines(string fileName, int k){
  ifstream myInputFile;
  string currLine;
  string fileLine[k];
  int linesRead = 0;

  myInputFile.open(fileName.c_str(), ios::in);

  if(!myInputFile){
    cout << "ERROR: Could not open file " << fileName << endl;
    cout << "Exiting program..." << endl;
    return;
  }

  while(myInputFile.peek() != EOF){
    getline(myInputFile, currLine);
    fileLine[ linesRead % k  ] = currLine;
    ++linesRead;
  }
  
  //Now print the last K lines of the file
  int startIndex = linesRead > k ? linesRead % k : 0;
  int size = min(linesRead, k); //You must know how much of fileLine[k] cells you filled

  cout << "Here are the last " << k << " lines of file " << fileName << endl;
  for(int i = 0; i < size; i++){
    cout << fileLine[ startIndex % size  ] << endl;
    ++startIndex;
    //the preceding two lines could be more succinctly written as
    //cout<<L[(startIndex + i) %k]<<endl;
  }
  
}

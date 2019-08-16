/*
 *Author: Mario Palma
 *Date: 3/27/2019
 *About: Printing a diamond with the number of rows specified by the user.
 */


#include <iostream>

using namespace std;

int main(){
  int totalRows,
      numTopRows,
      whitespace,
      //numBottomRows,
      row;

  cout << "Enter the number of rows: ";
  cin  >> totalRows;

  do{
    while(totalRows < 3){
      cout << "ERROR...you must input a number GREATER than 2: "<<endl;
      cout << "Enter the number of rows: ";
      cin >> totalRows;
    }

    whitespace = numTopRows = totalRows/2;
    row = 0;
    //numBottomRows = number - numTopRows;

    for(row; row <= numTopRows; ++row){
      for(int i = 0; i < whitespace; ++i){
        cout << " ";
      }

      for(int i = 0; i < 2*row  + 1; ++i){
        cout << "*";
      }
      cout << endl;
      whitespace--;
    }
    
    whitespace = 1;

    for(row; row < totalRows; ++row){
      for( int i = 0; i < whitespace; ++i){
        cout << " ";
      }
      for( int i = 0; i < 2*(totalRows-row-1)+1; ++i){
        cout << "*";
      }
      cout << endl;
      whitespace++;
    }


  
    cout << "Enter the number of rows: ";
    cin >> totalRows;
  }while(totalRows != -1);
  
  cout << "Bye!" << endl;
  return 0;
}

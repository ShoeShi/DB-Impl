#include "funcs.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(int args, char *argv[])
{
  Funcs f;

  string mystr;
  vector<string> myv;
  cout << "Enter your command: " <<
    "\n\tq1: BPlusTree 1 Q1command.txt" <<
    "\n\tq2: ExtSorting 2 3 SIDs.txt SortedSIDs.txt" <<
    "\n\tq3: Join Students.txt Enrolled.txt Q3aux.txt\n";
  getline (cin, mystr);
  myv = f.split(mystr, ' ');

  for(int i=0; i < myv.size(); i++){
    cout << "[" << i << "] : " << myv[i] << endl;
  }


  return 0;
}

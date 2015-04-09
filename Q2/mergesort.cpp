#include "mergesort.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>     
#include <algorithm>    
#include <math.h>     

typedef std::vector<int> buffer_t;
int MergeSort::itemsPerPage;
int MergeSort::pagesPerBuffer;
int MergeSort::numBuffers;
int MergeSort::numPages;
std::string MergeSort::filename;
std::vector<buffer_t> MergeSort::listOfBuffers;

MergeSort::MergeSort(int pageSize, int buffers, std::string filename) {
  this->filename = filename;
  this->itemsPerPage = pageSize;
  this->numBuffers = buffers;
}

MergeSort::~MergeSort(){}

//read file, put ints(pages) into a buffer.
// * There is no "page" type, but the "buffer" vector size 
// is determined by itemsPerPage * pagesPerBuffer 

void MergeSort::pass0() {
  std::string tempBuffer;
  int numItems = 0;
  int itemsPerBuffer = 0;

  //write to temporary file
  //std::ofstream f_pass0( "tmp/pass0.txt" );
  std::ofstream f_pass0( "pass0.txt");
  if (f_pass0.fail()) {
    std::cout << "Error Opening pass0.txt" << std::endl;
    return;
  }

  //open input file
  std::ifstream f_in( filename, std::ifstream::in);
  if (f_in.fail()) {
    std::cout << "Error Opening " << filename << std::endl;
    return;
  }

  //// get length of file:
  /*is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);*/

  //Counting number of data. (lines)
  while( std::getline( f_in, tempBuffer ) ) {
    numItems++;
  }
  //numItems=13; //TODO

  //set pointer back to beginning
  f_in.clear();
  f_in.seekg(0);

  //initialize important variables for simulation.
  numPages = ceil( ( double ) numItems / ( double ) itemsPerPage );
  pagesPerBuffer = ceil( ( double ) numPages / ( double ) numBuffers );
  itemsPerBuffer = ceil( itemsPerPage * pagesPerBuffer );


  /*std::cout << itemsPerPage << std::endl;
    std::cout << numBuffers << std::endl;
    std::cout << pagesPerBuffer << std::endl;
    std::cout << itemsPerBuffer << std::endl;
    std::cout << numPages << std::endl;*/

  //intialize buffer list with buffers
  for( int i = 0; i < numBuffers; i++ ) {
    listOfBuffers.push_back( buffer_t() );
  }


  //Add OpenMP clause to simulate B pages read simultaneously for outer j loop.
  //causes simultaneous write errors, unless written to separate temp file per buffer page, or something like this.
  //Read items(pages of items) into buffer and sort after read.
  std::cout << std::endl << "Pass 0" <<std::endl;
  std::stringstream output;
  int temp;
  for( int i = 0; i < numBuffers; i++ ) {

    output.str("");
    //read
    std::cout << "Read [";
    for( int j = 0; j < itemsPerBuffer; j++ ) { 
      if(! (f_in >> temp)) break;
      output << temp << " ";  
      listOfBuffers[i].push_back(temp);
    }
    std::cout << output.str().substr(0, output.str().size()-1);
    std::cout << "]" << std::endl;

    //sort the buffer after you read the data.
    std::sort(listOfBuffers[i].begin(), listOfBuffers[i].end());
    //No need for InnerSort here, as it is pass0.

    //Would need to be changed if OpenMP is used
    //Each buffer writes to a line in "pass.txt"
    std::cout << "Write [";
    for( int j = 0; j < listOfBuffers[i].size(); j++ ) {
      f_pass0 << listOfBuffers[i][j];
      std::cout << listOfBuffers[i][j];
      if( j != listOfBuffers[i].size() - 1 ){
	f_pass0 << " ";
	std::cout << " ";
      }
    } 
    f_pass0 << std::endl;
    std::cout << "]" << std::endl;
  }

  f_pass0.close();
  f_in.close();
}// end pass0

void MergeSort::passN(int n)
{
  std::ostringstream s_in;
  std::ostringstream s_out;
  s_in << "pass" << n-1 << ".txt";
  s_out << "pass" << n << ".txt";

  //open input file
  std::ifstream f_in( s_in.str(), std::ifstream::in);
  if (f_in.fail()) {
    std::cout << "Error Opening " << s_in.str() << std::endl;
    return;
  }


  //open output file
  std::ofstream f_out( s_out.str(), std::ofstream::out );
  if (f_out.fail()) {
    std::cout << "Error Opening " << s_out.str() << std::endl;
    return;
  }


  if(numBuffers/(pow(2, n-1)) < 1 )
    return;

  // Read, Sort, Write
  std::cout << std::endl << "Pass " << n << std::endl;
  std::string line;
  std::stringstream output;
  buffer_t a;
  buffer_t b;
  int temp;
  for( int i = 0; i < numBuffers/(pow(2, n-1)); i++ ) {
    listOfBuffers[i].clear();
    //read 2 lines (each line contains multiple data)
    a.clear();
    b.clear();
    output.str("");

    if(!std::getline( f_in, line) || line == "") break;
    std::cout << "Read [";
    std::stringstream splitter(line);
    while( splitter >> temp ) {
      a.push_back( temp );
      output << temp << " "; 
    }
    std::cout << output.str().substr(0, output.str().size()-1);

    std::cout << "] [";
    output.str("");
    std::getline( f_in, line);
    std::stringstream splitter2(line);
    while( splitter2 >> temp) {
      b.push_back( temp );
      output << temp << " "; 
    }
    std::cout << output.str().substr(0, output.str().size()-1);


    std::cout << "]" << std::endl;

    //sort the buffer after you read the data.
    listOfBuffers[i] = innerSort(a, b);
    //std::sort(listOfBuffers[i].begin(), listOfBuffers[i].end());

    //Would need to be changed if OpenMP is used
    //Each buffer writes to a line in "pass.txt"
    std::cout << "Write [";
    for( int j = 0; j < listOfBuffers[i].size() ; j++ ) {
      f_out << listOfBuffers[i][j];
      std::cout << listOfBuffers[i][j];
      if( j != listOfBuffers[i].size() - 1 ){
	f_out << " ";
	std::cout << " ";
      }
    } 
    std::cout << "]" << std::endl;
    f_out << std::endl;
  }

  f_out.close();
  f_in.close();

  passN(n+1);
}

//void MergeSort::print(){
//}
//

//Compare the top of each vector then place into bigger vector
buffer_t MergeSort::innerSort( buffer_t a, buffer_t b ) {
  buffer_t c; 
  int i = 0;
  int j = 0;

  while( i < a.size() && j < b.size() ) {
    if (a[i] < b[j]){
      c.push_back(a[i]);
      i++;
    } else {
      c.push_back(b[j]);
      j++;
    }
  }

  while ( i < a.size() ) {
    c.push_back(a[i]);
    i++;
  }

  while ( j < b.size() ) {
    c.push_back(b[j]);
    j++;
  }

  return c;
}

void MergeSort::run(){
  pass0();
  passN(1);
}



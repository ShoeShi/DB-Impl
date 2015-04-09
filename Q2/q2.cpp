/****************************************
 * External merge sort implementation 
 *
 * Uses custom innersort as well as vectors
 * to simulate buffers, and pages.
 *
 * COMP4380
 * Authors: JX, ES
 * Due date: 4.9.15
 *
 * Command line Example: ./q2 2 3 SIDs.txt
 * *************************************/

#include "mergesort.h"
#include <cstdlib>
#include <string>     
#include <iostream>

int main( int argc, char **argv ) {
  if( argc != 4 ) {
    std::cout << "Invalid arguments" << std::endl;
    return EXIT_SUCCESS;
  }

  size_t pageSize = atoi(argv[1]);
  size_t numBuffers = atoi(argv[2]);
  std::string datafile = argv[3];

  MergeSort* xsort = new MergeSort( pageSize, numBuffers, datafile );
  xsort -> run();
  delete xsort;

  return 0;
}

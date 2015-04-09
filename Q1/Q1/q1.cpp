#include <cstdlib>
#include <cstdint>

#include <iostream>
#include <string>

#include "BPTree.hpp"

void printUsage(void);

int main( int argc, char** argv ) {
	if ( argc != 3 ) {
		printUsage();
		return EXIT_SUCCESS;
	}

	auto d = std::stoi( argv[1] );
	

	return EXIT_SUCCESS;
}

void printUsage() {
	std::cout << "Usage: BPlusTree <d> <commandfile>";
}
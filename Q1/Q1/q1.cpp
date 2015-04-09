#include <cstdlib>
#include <cstdint>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "BPTree.hpp"

void printUsage(void);

int main( int argc, char** argv ) {
	if ( argc != 3 ) {
		printUsage();
		return EXIT_SUCCESS;
	}

	auto d = atoi( argv[1] );

	Q1::BPTree tree( d );
	
	std::ifstream commandsIn( argv[2], std::ifstream::in );
	std::string line;

	if( !commandsIn.is_open() ) {
		std::cout << "Bad command file" << std::endl;
		return EXIT_SUCCESS;
	}

	std::size_t lineNum = 0;
	while( std::getline( commandsIn, line ) ) {
		std::vector<std::string> words;
		std::string buffer;
		std::stringstream splitter( line );

		while( splitter >> buffer ) {
			words.push_back(buffer);
		}

		if( words.size() > 1 ) {
			if( words[0].compare( "INSERT" ) == 0 ) {
				int32_t data = atoi( words[1].c_str() );
				tree.insert( data );
			} else if( words[0].compare( "DELETE" ) == 0 ){
				int32_t data = atoi( words[1].c_str() );
				tree.del( data );
			} else if( words[0].compare( "PRINT" ) == 0 ) {
				tree.printTree();
				std::cout.flush();
			} else {
				std::cout << "Bad command \"" << line << "\" detected on line " << lineNum << "--skipping." << std::endl;
			}
		}

		++lineNum;
	}

	return EXIT_SUCCESS;
}

void printUsage() {
	std::cout << "Usage: BPlusTree <d> <commandfile>";
}
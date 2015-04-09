#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

typedef std::vector<std::string> buffer_t;

int main( int argc, char **argv ) {
	if( argc != 4 ) {
		std::cout << "Invalid arguments" << std::endl;
		return EXIT_SUCCESS;
	}

	std::string t1File = argv[1];
	std::string t2File = argv[2];
	std::string params = argv[3];

	std::size_t t1PerPage;
	std::size_t t2PerPage;
	std::size_t t1Column;
	std::size_t t2Column;
	std::size_t numBuffers;

	//Read parameter input
	std::ifstream paramsIn( params, std::ifstream::in );
	std::string line;

	if( !paramsIn.is_open() ) {
		std::cout << "Bad param file" << std::endl;
		return EXIT_SUCCESS;
	}

	for( std::size_t i = 0; i < 4 && std::getline( paramsIn, line ); ++i ) {
		std::vector<std::string> words;
		std::string buffer;

		std::stringstream splitter( line );
		
		while( splitter >> buffer ) {
			words.push_back( buffer );
		}

		switch( i ) {
		case 0:
		case 1:
			if( words.size() != 3 || words[0].compare( "PAGE" ) || words[1].compare( "SIZE" ) ) {
				std::cout << "Invalid parameter on line " << i << ": " << line << std::endl;
				return EXIT_SUCCESS;
			}

			if( i == 0 ) {
				t1PerPage = std::stoi( words[2] );

				if( t1PerPage <= 0 ){
					std::cout << "Invalid tuples per page on line " << i << std::endl;
					return EXIT_SUCCESS;
				}
			} else {
				t2PerPage = std::stoi( words[2] );

				if( t2PerPage <= 0 ){
					std::cout << "Invalid tuples per page on line " << i << std::endl;
					return EXIT_SUCCESS;
				}
			}
			

			break;
		case 2:

			if( words.size() != 4 || words[0].compare( "COMMON" ) || words[1].compare( "COLUMN" ) ) {
				std::cout << "Invalid parameter on line " << i << ": " << line << std::endl;
				return EXIT_SUCCESS;
			}

			t1Column = std::stoi( words[2] );
			t2Column = std::stoi( words[3] );

			if( t1Column <= 0 || t2Column <= 0 ) {
				std::cout << "Invalid columns on line " << i << std::endl;
				return EXIT_SUCCESS;
			}

			break;

		case 3:
			if( words.size() != 2 || words[0].compare( "BUFFER" ) ) {
				std::cout << "Invalid parameter on line " << i << ": " << line << std::endl;
				return EXIT_SUCCESS;
			}

			numBuffers = stoi( words[1] );

			if( numBuffers <= 2 ) {
				std::cout << "Invalid number of buffers on line " << i << std::endl;
				return EXIT_SUCCESS;
			}
			break;
		default:
			std::cout << "Invalid parameter on line " << i << ": " << line << std::endl;
			return EXIT_SUCCESS;
		}
	}

	paramsIn.close();

	//Set up buffers

	std::vector<buffer_t> pageBuffers;

	for( std::size_t i = 0; i < numBuffers; ++i ) {
		pageBuffers.push_back( buffer_t() );
	}

	buffer_t *innerBuffer = &pageBuffers[numBuffers - 2];
	buffer_t *outputBuffer = &pageBuffers[numBuffers - 1];

	std::size_t numOuterBuffers = numBuffers - 2;

	//Get the number of records in each table

	std::string tempBuffer;

	std::ifstream t1Temp( t1File );
	std::size_t t1NumLines = 0;

	while( std::getline( t1Temp, tempBuffer ) ) {
		++t1NumLines;
	}

	t1Temp.close();

	std::ifstream t2Temp( t2File );
	std::size_t t2NumLines = 0;

	while( std::getline( t2Temp, tempBuffer ) ) {
		++t2NumLines;
	}

	t2Temp.close();

	std::size_t t1Pages = std::ceil( ( double )t1NumLines / ( double )t1PerPage );
	std::size_t t2Pages = std::ceil( ( double )t2NumLines / ( double )t2PerPage );
	std::size_t numChunks = std::ceil( ( double )t1Pages / ( double )numOuterBuffers );

	std::cout << "With page size=" << t1PerPage << " records per page, N1=" << t1NumLines << " records in " << t1File << " can fit into P1=" << t1Pages << " pages." << std::endl;
	std::cout << "With page size=" << t2PerPage << " records per page, N2=" << t2NumLines << " records in " << t2File << " can fit into P1=" << t2Pages << " pages." << std::endl;
	std::cout << "The common columns are Column " << t1Column << " in " << t1File << " and Column " << t2Column << " in " << t2File << "." << std::endl;
	std::cout << "These records are joined using a block nested loop join with B=" << numBuffers << " buffer pages." << std::endl << std::endl;

	//Do join (Chunk Nested-Loop Join)

	std::ifstream t1In( t1File );
	std::string t1Line;

	for( std::size_t chunk = 0; chunk < numChunks; ++chunk ) {
		
		//Fill outer buffers
		for( std::size_t outerPage = 0; outerPage < numOuterBuffers; ++outerPage ) {
			pageBuffers[outerPage].clear();

			if( t1In.peek() != EOF ) {
				for( std::size_t outerRecord = 0; outerRecord < t1PerPage; ++outerRecord ) {
					if( std::getline( t1In, t1Line ) ) {
						pageBuffers[outerPage].push_back( t1Line );
					} else {
						break;
					}
				}
			}
		}

		std::ifstream t2In( t2File );
		std::string t2Line;

		for( std::size_t innerPage = 0; innerPage < t2Pages; ++innerPage ) {
			innerBuffer->clear();

			if( t2In.peek() != EOF ) {
				for( std::size_t innerRecord = 0; innerRecord < t2PerPage; ++innerRecord ) {
					if( std::getline( t2In, t2Line ) ) {
						innerBuffer->push_back( t2Line );
					} else {
						break;
					}
				}
			}

			for( std::size_t outerPage = 0; outerPage < numOuterBuffers && pageBuffers[outerPage].size() > 0; ++outerPage ) {
				for( buffer_t::iterator r = pageBuffers[outerPage].begin(); r != pageBuffers[outerPage].end(); ++r ) {
					for( buffer_t::iterator s = innerBuffer->begin(); s != innerBuffer->end(); ++s ) {
						std::vector<std::string> rElems;
						std::vector<std::string> sElems;
						std::string buffer;

						std::stringstream splitter( *r );

						while( splitter >> buffer ) {
							rElems.push_back( buffer );
						}

						splitter = std::stringstream( *s );

						while( splitter >> buffer ) {
							sElems.push_back( buffer );
						}

						if( rElems[t1Column - 1].compare( sElems[t2Column - 1] ) == 0 ) {
							std::stringstream outStream;

							outStream << rElems[t1Column - 1] << " ";

							for( std::size_t i = 0; i < rElems.size(); ++i ) {
								if( i != t1Column - 1 ) {
									outStream << rElems[i] << " ";
								}
							}

							for( std::size_t i = 0; i < sElems.size(); ++i ) {
								if( i != t2Column - 1 ) {
									outStream << sElems[i] << " ";
								}
							}

							std::cout << outStream.str() << std::endl;
						}
					}
				}
			}

		}

		t2In.close();
	}

	t1In.close();

	return EXIT_SUCCESS;
}

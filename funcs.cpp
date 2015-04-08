#include "funcs.h"
#include <string>
#include <sstream>
#include <vector>

// sets the airplane and time corresponding to this Splitfunc
//

// empty destructor since there is no heap-based memory here

Funcs::Funcs(){}
Funcs::~Funcs(){}

std::vector<std::string> &split_inner(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Funcs::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split_inner(s, delim, elems);
    return elems;
}

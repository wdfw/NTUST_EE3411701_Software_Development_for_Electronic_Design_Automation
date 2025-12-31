#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Utils.hpp"
#include "CircuitStructure.hpp"

using namespace std;
using namespace std::filesystem ;

vector<string> DEF_Scanner(const string& dir_text); //DEF
vector<string> CFG_Scanner(const string& file_text); //CFG
vector<string> CM_Scanner(const string& file_text); //Connection matrix


DEF_Block Top_DEF_Parser(const string& dir_name) ;
Blocks CFG_Parser(const string& file_name) ;
Nets CM_Parser(const string& file_name) ;


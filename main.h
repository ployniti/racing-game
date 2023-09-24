//This is the .h file for the client/main program. It'll contain prototypes for functions
//that interact with the user

//Constants
const int SIZE {100};

#pragma once
#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <memory>
#include <array>
using namespace std;

//This is the function to prompt the user for the track length
void get_length(int & length);

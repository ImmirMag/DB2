#ifndef _CONFIG_
#define _CONFIG_ 

#include <iostream>
#include <string>
#include <deque>


#include "iniparser.h"

using namespace std;

class Config
{
public:
	Config(const string config_filepath);
	~Config();
	string MainPath;

private:

};

#endif
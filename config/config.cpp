#include "config.h"

#include <stdio.h>

Config::Config(const string config_filepath){

	dictionary * ini = iniparser_load(config_filepath.c_str());
	if (ini == NULL)
	{
		cout << "ini-file not found: " << config_filepath << endl;
		exit(0);
	}

	const char * db_folders_path = iniparser_getstring(ini, ":db_folders_path", NULL);

	MainPath = string(db_folders_path);

	cout << "MainPath: " << MainPath << endl;

	//printf("db_folders_path: %s\n", db_folders_path);
	//cout << "db_folders_path: " << db_folders_path << endl;

}


Config::~Config(){
	
}

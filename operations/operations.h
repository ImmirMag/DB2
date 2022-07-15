#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

//#include "../commands/command.h"

#include <vector>
#include <initializer_list>
#include <map>
#include <deque>
#include <list>

#include <utility>

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <errno.h>

#include "../config/config.h"
#include "../commands/structures.h"
#include "../data_format/data_format.h"


using namespace std;


template <typename JsonContainer>
string convertToJsonString(JsonContainer attributes)
{
	string json_string = "{";
	for(attr_type & attr: attributes)
	{
		json_string += "\"" + attr.first + "\"" + ":" + "\"" + attr.second + "\"" + ",";
	}
	json_string.pop_back();
	json_string += "}";

	return json_string;
}

string createMetaDataForNoteTable(const string note_table_name, table_struct_container & attributes);






namespace Operations {


	class State;

	using PathContainer = initializer_list<string>;

	string PathToString(PathContainer &);
	bool CreateFolder(PathContainer);
	bool CreateFile(PathContainer);
	bool DeleteFolder(PathContainer);
	bool DeleteFile(PathContainer);
	bool FolderIsExist(PathContainer);
	bool FileIsExist(PathContainer);
	int InsertIntoFile(State &, const string);
	int FileAppend(State &, string, string);
	int FileWrite(State &, string, const string); //LSEEK ??
	int FileSeek (State &, string, const int pos);


	class State
	{
	public:
		
		const Config & cfg;

		State(const Config & cfg_) : cfg(cfg_){};
		~State(){};
		const string & getCurrentPartition() { return curr_path; }
		bool setCurrentPartition(string && new_current_path) { 
			
			if (!FolderIsExist({cfg.MainPath, new_current_path}))
				return false;

			curr_path = new_current_path; 
			return true;
		}


		DataFormat & getMetaDataForNoteTable(const string note_table_name){
			auto result = metadataNoteTable.find(note_table_name);
			if (result == metadataNoteTable.end())
			{
				//open from file
			}
			return result->second;
		}

	private:
		string curr_path;
		map<string, FILE *> files;
		map<string, DataFormat> metadataNoteTable;
	};

};


#endif

/*class DataOperatorsFields
{
public:
	DataOperatorsFields(const Config & cfg_) : cfg(cfg_) {}
	~DataOperatorsFields(){}
	const Config & cfg;
	ifstream dataFile;	
};

class DataOperatorCommand
{
public:
	virtual Resulter * execute(DataOperatorsFields & DataOperatorsFields) = 0;
};


class DataOperator
{
public:
	DataOperator(const Config & cfg) : DataOperatorsFields_(cfg){}
	~DataOperator(){}
	Resulter * operate(DataOperatorCommand & DataOperatorCommand) {
		return DataOperatorCommand.execute(DataOperatorsFields_);
	}
protected:
	DataOperatorsFields DataOperatorsFields_;
};







class CreateFolderDB : public DataOperatorCommand
{
public:
	CreateFolderDB(const string folderName) : folderName(folderName) {}
	virtual Resulter * execute(DataOperatorsFields & DataOperatorsFields) override;	
private:
	const string folderName;
};

class CreateMetafileDB : public DataOperatorCommand
{
public:
	virtual Resulter * execute(DataOperatorsFields & DataOperatorsFields) override;	
};

class ReadTable : public DataOperatorCommand
{
public:
	virtual Resulter * execute(DataOperatorsFields & DataOperatorsFields) override;	
};

*/
/*
	bool openFile(const string & filename);
	bool closeFile();
	bool createFile();
	bool deleteFile();

	bool createTable();
	bool deleteTable();

	void readFromFile();
	void writeToFile();
	void deleteFromFile();
	void findNote();
	const int countOfNotes();
*/


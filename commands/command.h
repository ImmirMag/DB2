#ifndef _COMMAND_H_
#define _COMMAND_H_ 


#include <iostream>
#include <string>
#include <cctype>

#include <initializer_list>

#include <type_traits>
#include <utility>

#include "resulter.h"
#include "structures.h"
#include "../data_format/data_format.h"
#include "../operations/operations.h"

using namespace std;

class Result;
class DataOperator;

namespace op = Operations;


class Command 
{
public:
	virtual string getName() const = 0;
	virtual Result * executeCommand(op::State &) = 0;
};


template <const char * CommandName>
class CommandTemplated : public Command
{
public:
	virtual string getName() const override {return CommandName;};
	static string getNameStatic() {return CommandName;};
	
};



class Unknown : public CommandTemplated<CMD::Unknown>
{
public:
	virtual Result * executeCommand(op::State &) override ;
};



class ErrorMessage : public CommandTemplated<CMD::ErrorMessage>
{
public:
	ErrorMessage(const string & error_msg) : error_msg(error_msg) {};
	~ErrorMessage(){};
	virtual Result * executeCommand(op::State &) override ;
private:
	const string error_msg;
};


class Connect : public CommandTemplated<CMD::Connect>
{
public:
	Connect(command_string_type & commandstring){
	
		if(commandstring.size() != 2)
			throw "Wrong count of arguments";
	
		partition_name = commandstring[1];
	};
	~Connect() {};
	virtual Result * executeCommand(op::State &) override ;
private:
	string partition_name;
};


class Disconnect : public CommandTemplated<CMD::Disconnect>
{
public:
	Disconnect(command_string_type & commandstring){};
	~Disconnect(){};
	virtual Result * executeCommand(op::State &) override ;
	
};


class CreatePartition : public CommandTemplated<CMD::CreatePartition>
{
public:
	CreatePartition(command_string_type & commandstring) {

		if(commandstring.size() != 2)
			throw "Wrong count of arguments";
	
		partition_name = commandstring[1];		
	}	
	~CreatePartition(){};
	virtual Result * executeCommand(op::State &) override ;
private:
	string partition_name;
};


class CreateNoteTable : public CommandTemplated<CMD::CreateNoteTable>
{
public:
	CreateNoteTable(command_string_type & commandstring) {
			
		if(commandstring.size() < 5)
			throw "Wrong count of arguments";
		
		/* FIXME: Reserve space for vector*/
		/* FIXME: Delete ")" and "(" */

		auto iter = commandstring.begin();
		note_table_name = *(++iter);//commandstring[1]

		auto checkStringOnAlpha = [](const string & source) //-> bool
		{
			for(const char & c : source)
				if (isalpha(c))
					return true;
			return false;
		};

		if (!checkStringOnAlpha(note_table_name))
			throw "Wrong note_table name";

		if ( (*(++iter)).front() != (SpecSymbs::CommamdArgsOpenSymb) )
			throw "Wrong symbol?";
		++iter;		

		while(iter != commandstring.end())
		{
			cout << "^^\"" << *iter << "\"" << endl;

			if ( (*iter).front() == (SpecSymbs::CommamdArgsCloseSymb) )
				break;

			auto type = typeCheckingStruct.find(*iter);
			if (type == typeCheckingStruct.end())
				throw "Not found datatype: " + *iter;
			const string Typename = *(iter++);

			if(iter == commandstring.end()) 
				throw "Wrong structure of notetable";
			const string Columname = *(iter++);

			attributes.push_back(attr_type(Columname, Typename));
		}

		for(auto & p : attributes)
		{
			cout << "# " << p.first << ": " << p.second << endl;
		}

		//throw "isalpha + iter++( ";


	}	
	~CreateNoteTable(){};
	virtual Result * executeCommand(op::State &) override ;
private:
	string note_table_name;
	table_struct_container attributes;

};


class DropPartition : public CommandTemplated<CMD::DropPartition>
{
public:
	DropPartition(command_string_type & commandstring) : partition_name(commandstring[1]){}	
	~DropPartition(){};
	virtual Result * executeCommand(op::State &) override ;
private:
	const string partition_name;
};

class DropNoteTable : public CommandTemplated<CMD::DropNoteTable>
{
public:
	DropNoteTable(command_string_type & commandstring) : note_table_name(commandstring[1]){}	
	~DropNoteTable(){};
	virtual Result * executeCommand(op::State &) override ;
private:
	const string note_table_name;
};


class AlterNoteTable :  public CommandTemplated<CMD::AlterNoteTable>
{
public:
	AlterNoteTable(command_string_type & commandstring){};
	~AlterNoteTable(){};
	virtual Result * executeCommand(op::State &) override ;
	
};



class Insert : public CommandTemplated<CMD::Insert>
{
public:
	Insert(command_string_type & commandstring){};
	~Insert(){};
	virtual Result * executeCommand(op::State &) override ;
private:
	string NoteTableForInsert;
	list<string> InsertValues;
};

class Update : public CommandTemplated<CMD::Update>
{
public:
	Update(command_string_type & commandstring){};
	~Update(){};
	virtual Result * executeCommand(op::State &) override ;

};

class Delete : public CommandTemplated<CMD::Delete>
{
public:
	Delete(command_string_type & commandstring){};
	~Delete(){};
	virtual Result * executeCommand(op::State &) override ;

};


class Select : public CommandTemplated<CMD::Select>
{
public:
	Select(command_string_type & commandstring){};
	~Select(){};
	virtual Result * executeCommand(op::State &) override ;

};

//return new ErrorMessage(commandstring[0]);
//if (command.size() < 3)
//return new ErrorMessage("Need 2 arguments"); 

template <typename CommandType, typename CommandConstructArgs = const vector<string>>
constexpr pair<string, function<Command*(CommandConstructArgs & args)>> 
createCommandMapInstance()
{
	return make_pair( CommandType::getNameStatic(),
		[](command_string_type & args) -> Command *
		{
			return new CommandType(args);
		}
	);	
}

extern const map<string, function<Command*(const vector<string> & args)>> command_map;

Command * command_parser(command_string_type & commandstring_line);

#endif
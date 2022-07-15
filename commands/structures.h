#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_ 

#include <utility>
#include <map>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

namespace CMD {

	using type = const char[];
	extern type Unknown;
	extern type ErrorMessage;

	extern type CreatePartition ;
	extern type CreateNoteTable ;
	extern type DropPartition ;
	extern type DropNoteTable ;
	extern type AlterNoteTable;


	extern type Select ;
	extern type Connect ;
	extern type Disconnect ;

	extern type Insert;
	extern type Update;
	extern type Delete;

};

namespace SpecSymbs {

	using type = const char;

	type CommamdArgsOpenSymb = '(';
	type CommamdArgsCloseSymb = ')';
	type CommamdArgsDelimiter = ',';
	type CommamdEnd = ';';

};


const string MetaDataFileName = "metadata";

vector<char> sortChars(vector<char> chars);

const vector<char> SortedSplitingChars (move(sortChars({

	SpecSymbs::CommamdArgsOpenSymb,
	SpecSymbs::CommamdArgsCloseSymb,
	SpecSymbs::CommamdArgsDelimiter,
	SpecSymbs::CommamdEnd

})));


using attr_type = pair<string, string>;
using table_struct_container = list< attr_type >;
using command_string_type = const vector<string>;

struct PartitionMetaData
{	
	vector< attr_type > structure;
	string creation_date;
};


const map<const string, function<bool(const string &)>> typeCheckingStruct = {
	{"string", 	[](const string & value){ return true; }},
	{"int", 	[](const string & value){ return atoi(value.c_str()); }}
};




#endif
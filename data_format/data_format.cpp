#include "data_format.h"



template <>
void checkArg<int>(ValueHolder & curr_value, int index){

	if (curr_value.Size() < index)
		throw "Out of array";
}


template <>
void checkArg<string>(ValueHolder & curr_value, string index){

	if (!curr_value.HasMember(index.c_str()))
		throw "No member: " + index;
}	

template <>
void checkArg<const char *>(ValueHolder & curr_value, const char * index){

	if (!curr_value.HasMember(index))
		throw "No member: ";
}	


template <>
int get<int>(const ValueHolder & curr_value)
{
	if (!curr_value.IsInt())		throw "Not int";
	return curr_value.GetInt();
}


template <> 
string get<string>(const ValueHolder & curr_value)
{
	if (!curr_value.IsString())	throw "Not string";
	return curr_value.GetString();
}


template <> 
bool get<bool>(const ValueHolder & curr_value)
{
	if (!curr_value.IsBool())		throw "Not boolean";
	return curr_value.GetBool();
}

template <> 
pair<string, string> get<pair<string, string>>(const MemberHolder & curr_value)
{
	return pair<string, string>(curr_value.name.GetString(), curr_value.value.GetString());
}







/**/
#ifndef _DataFormat_H_
#define _DataFormat_H_ 


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <utility>

using namespace std;
using namespace rapidjson;



using ValueHolder = GenericValue<rapidjson::UTF8<> >;
using MemberHolder = GenericMember<rapidjson::UTF8<>,ValueHolder::AllocatorType >; //RAPIDJSON_DEFAULT_ALLOCATOR 

template <typename V>
V get(const ValueHolder & curr_value)	{	throw "Function is not define"; return V();	}

template <typename V>
V get(const MemberHolder & curr_value)	{	throw "Function is not define"; return V();	}


template <typename V>	
void checkArg(ValueHolder & curr_value, V v){ throw "Unknow argument type"; }	

template <typename T>
ValueHolder & findValueHolder(ValueHolder & curr_value, T index)
{
	//cout << "last" << endl;
	checkArg<T>(curr_value, index);
	return curr_value[index];
}

template <typename T, typename ... Types>
ValueHolder & findValueHolder(ValueHolder & curr_value, T index, Types ... args)
{
	//cout << "inner" << endl;
	//if (!curr_value.IsObject())	throw "Is not Object";
	checkArg<T>(curr_value, index);
	return findValueHolder(curr_value[index], args...);
}




class DataFormat
{
public:

	DataFormat(const string & initialize_value){ //const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
		data.Parse(initialize_value.c_str());
		if (!data.IsObject())	throw "Is not Object@";
	}
	~DataFormat(){};
	const string getRawData(GenericValue<rapidjson::UTF8<> > & d){
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);	
		return buffer.GetString();
	}	


	class iterator
	{
	public:
		iterator(const ValueHolder & data) : 
		itr    (data.MemberBegin()), //!data.IsObject() ?  throw "Its not name" : 
		itr_end(data.MemberEnd()) 
		{};
		~iterator(){};				
		iterator & operator++(){
			itr++;
			return *this;
		}
		bool operator!=(const iterator & cmp){
			return itr != cmp.itr;
		}
		bool is_end(){
			return itr == itr_end;
		}
		string name(){
			return itr->name.GetString();
		}

		string type(){
			return "";
		}

		template <typename T>
		string value(){
			return get<T>(itr->value); //.GetString();
		}

		template <typename T1, typename T2>
		pair<T1, T2> value(){
			return get<pair<T1, T2>>(itr->value); //.GetString();
		}

		template <typename ... Types>
		iterator begin(Types ... args) {	

			return iterator( findValueHolder(itr->value, args...) );	
			//if (!val.IsArray())
			//	throw "Is not Array";
		}

		iterator begin() {	
			return iterator(itr->value);	
		}

	private:
		friend class DataFormat;
		ValueHolder::ConstMemberIterator itr;
		ValueHolder::ConstMemberIterator itr_end;
	};


	template <typename ... Types>
	iterator begin(Types ... args) {	

		return iterator( findValueHolder(data, args...) );	
		//if (!val.IsArray())
		//	throw "Is not Array";
	}

	iterator begin() {	
		return iterator(data);	
	}


	template <typename V, typename ... Types>
	V getValue(Types ... args)
	{
		cout << "args" << endl;
		auto & val = findValueHolder(data, args...);
		return get<V>(val);
	}

	int MemberCount(){
		return data.MemberCount();
	}

private:
	Document data;
};



/*
	// 2. Modify it by DOM.
	Value& s = d["stars"];
	s.SetInt(s.GetInt() + 1);

	// 3. Stringify the DOM


	DataFormat & operator[](const char * index)
	{
		if (!curr_value)
		{
			if (!data.HasMember(index))
				throw "No member";
			curr_value = &data[index];
		}	
		else
		{
			if (!curr_value->HasMember(index))
				throw "No member";				
			curr_value = &(*curr_value)[index];
		}

		//return *this;//
	}


*/  





#endif
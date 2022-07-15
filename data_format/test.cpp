#include <iostream>
#include <sys/stat.h>


#include "data_format.h"

using namespace std;


int main(int argc, char const *argv[])
{


//	cout << setCurrentPartitionPath("/home/im/app/") << endl;//System/DB2/data/test/


	try
	{
		//DataFormat df( R"({ "a":1,"b":"2","c":[{"s":1},{"w":"q"}],"d":{"e":"12","f":[5,7,9]} })" );
		DataFormat df( R"({ 

			"structure":[
				{"name":"id", 		"type":"int"},
				{"name":"name", 	"type":"string"},
				{"name":"surname", 	"type":"string"},
				{"name":"weight", 	"type":"float"}	
			]

		 })" );

		//cout << df.getValue<string>("d","e") << endl;
		
auto it = df.begin("structure");
		//for(; !it.is_end(); ++it)
		{
			//auto p = it.value< string, string >();

			//cout << p.first << endl;
		}

		//string a = df["d"]["x"];
		//cout << a << endl;

	}
	catch(const char * err)
	{
		cout << "err: " << err << endl;
	}


	
	return 0;
}
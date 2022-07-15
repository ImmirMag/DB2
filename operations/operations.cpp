#include "operations.h"


string createMetaDataForNoteTable(const string note_table_name, table_struct_container & attributes){

	string json_string = R"({"structure" : )" + convertToJsonString(attributes) + "}";
	//metadataNoteTable.emplace(note_table_name, json_string.c_str() );
	return json_string;
}

string Operations::PathToString(PathContainer & path){

	string res = "";

	for(const auto & node : path)
		res += node + "/";

	/* slow. replace on res[-1] = '\0' */res.pop_back();

	return res;
}


bool Operations::CreateFolder(PathContainer dirpath){

	string dir = PathToString(dirpath);
	cout << "Creating Folder: " << dir << endl;
	if(mkdir(dir.c_str(), S_IRWXU) == -1)
		return false;
	return true;
}

bool Operations::CreateFile(PathContainer filepath){


	string file = PathToString(filepath);

	cout << "Creating File: " << file << endl;
	if( creat(file.c_str(), O_RDWR) == -1 )
		return false;
	return true;
}



bool Operations::DeleteFolder(PathContainer dirpath){


	string dir = PathToString(dirpath);
	cout << "Deleting Folder: " << dir << endl;

	if (rmdir(dir.c_str()) == -1)
	{
		cout << "errr" << errno << endl;
		return false;
	}

	return true;
}

bool Operations::DeleteFile	(PathContainer filepath){

	string file = PathToString(filepath);
	cout << "Deleting File: " << file << endl;
	if (remove(file.c_str()) == -1)
		return false;
	return true;

}
bool Operations::FolderIsExist(PathContainer dirpath){

	string dir = PathToString(dirpath);

	struct stat fsdata;
	if(stat(dir.c_str(), &fsdata) == -1)
		return false;
	//cout << "Path?: " << cfg.MainPath + "/" + new_current_path << endl;
	if (!S_ISDIR(fsdata.st_mode))
		return false;

	return true;
}

bool Operations::FileIsExist(PathContainer filepath){

	string file = PathToString(filepath);

	struct stat fsdata;
	stat(file.c_str(), &fsdata);
	//cout << "Path?: " << cfg.MainPath + "/" + new_current_path << endl;
	if (!S_ISREG(fsdata.st_mode))
		return false;

	return true;
}



int Operations::InsertIntoFile(State & state, const string filepath){
	return 1;
}

int Operations::FileWrite(State &, string, const string){return 0;};
int Operations::FileAppend(State &, string, const string){return 0;};

/*Resulter * CreateFolderDB::execute(){

	cout << "CreateFolderDB" << endl;
	//check on existing



	return new Resulter();
}
*/
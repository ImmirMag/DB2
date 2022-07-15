#include "structures.h"




vector<char> sortChars(vector<char> chars)
{
	sort(chars.begin(), chars.end(), [](char & first, char & last){ return(first>last); });
	return move(chars);
}




extern const CMD::type CMD::Unknown 		= "unknown";
extern const CMD::type CMD::ErrorMessage 	= "error_message";

extern const CMD::type CMD::CreatePartition = "create_partition";
extern const CMD::type CMD::CreateNoteTable = "create_note_table";
extern const CMD::type CMD::DropPartition 	= "drop_partition";
extern const CMD::type CMD::DropNoteTable 	= "drop_note_table";


extern const CMD::type CMD::Select 			= "select";
extern const CMD::type CMD::Connect 		= "connect";
extern const CMD::type CMD::Disconnect 		= "disconnect";

extern const CMD::type CMD::AlterNoteTable 	= "alter_note_table";
extern const CMD::type CMD::Insert 			= "insert";
extern const CMD::type CMD::Update 			= "update";
extern const CMD::type CMD::Delete 			= "delete";


/*
*/
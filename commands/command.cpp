#include "command.h"

Command * command_parser(const vector<string> & command_line){

	if (command_line.size() < 2)
		throw "command_line is empty";

	const string command_name = command_line.at(0);

	if(command_map.find(command_name) == command_map.end()) 
		throw "not found command:" + command_name ;

	return command_map.at(command_name)(command_line);
}


extern const map<string, function<Command*(const vector<string> & args)>> command_map {

	createCommandMapInstance<CreatePartition>(),
	createCommandMapInstance<CreateNoteTable>(),
	createCommandMapInstance<DropPartition>(),
	createCommandMapInstance<DropNoteTable>(),
	createCommandMapInstance<AlterNoteTable>(),

	createCommandMapInstance<Select>(),
	createCommandMapInstance<Connect>(),
	createCommandMapInstance<Disconnect>(),

	createCommandMapInstance<Insert>(),
	createCommandMapInstance<Update>(),
	createCommandMapInstance<Delete>()
};


Result * Connect::executeCommand(op::State & state)  {

	cout << "Connecting..." << endl;

	if(!op::FolderIsExist({state.cfg.MainPath, partition_name}))
		return new ResultStatus("Partition doesnt exist");

	if(!state.setCurrentPartition(move(partition_name)))
		return new ResultStatus("Cannot connect to partition");

	return new ResultStatus("done");
}

Result * Disconnect::executeCommand(op::State & state)  {

	cout << "Disconnect..." << endl;

	string empty = "";

	if(!state.setCurrentPartition(move(empty)))
		return new ResultStatus("Cannot disconnect from partition");

	return new ResultStatus("done");
}



Result *  CreatePartition::executeCommand(op::State & state)  {

	cout << "CreatePartition..." << endl;

	if(op::FolderIsExist({state.cfg.MainPath, partition_name}))
		return new ResultStatus("Partition is exist");

	if(!op::CreateFolder({state.cfg.MainPath, partition_name}))
		return new ResultStatus("Cannot create Partition");

	if(!op::CreateFile({state.cfg.MainPath, partition_name, MetaDataFileName}))
		return new ResultStatus("Cannot create file metadata");

	//Insert something in metafile

	return new ResultStatus("done");
}


Result *  DropPartition::executeCommand(op::State & state)  {

	const string & curr_part = state.getCurrentPartition();

	if(curr_part == partition_name)
		return new ResultStatus("Disconnecting before droping");

	if(!op::FolderIsExist({state.cfg.MainPath, partition_name}))
		return new ResultStatus("No found Partition");

	if(!op::DeleteFolder({state.cfg.MainPath, partition_name}))
		return new ResultStatus("Cannot delete Partition");

	return new ResultStatus("done");
}

Result *  CreateNoteTable::executeCommand(op::State & state)  {

	/*more complex*/ cout << "CreateNoteTable..." << endl;

	/*string empty = "";
	const string & curr_part = state.getCurrentPartition();

	if(curr_part == empty)
		return new ResultStatus("Disconnected => Cannot create");

	if(op::FolderIsExist({state.cfg.MainPath, curr_part, note_table_name}))
		return new ResultStatus("NoteTable is Exist");	

	if(!op::CreateFolder({state.cfg.MainPath, curr_part, note_table_name}))
		return new ResultStatus("Cannot create NoteTable");

	if(!op::CreateFile({state.cfg.MainPath, curr_part, note_table_name, MetaDataFileName}))
		return new ResultStatus("Cannot create metafile for NoteTable");

	for (const attr_type & attribute : attributes)
		if(!op::CreateFile( {state.cfg.MainPath, curr_part, note_table_name, attribute.first} ))
		{
			op::DeleteFolder( {state.cfg.MainPath, curr_part, note_table_name);	
			return new ResultStatus("Cannot create NoteTable");
		}

	string MetaDataFileNoteInfo = createMetaDataForNoteTable(note_table_name, attributes);

	//op::FileWrite(state, MetaFilePath, MetaDataFileNoteInfo);*/

	return new ResultStatus("done");
}




Result *  DropNoteTable::executeCommand(op::State & state)  {

	const string & curr_part = state.getCurrentPartition();

	if(!op::FolderIsExist({state.cfg.MainPath, curr_part, note_table_name}))
		return new ResultStatus("No found Partition");

	if(op::DeleteFolder({state.cfg.MainPath, curr_part, note_table_name}))
		return new ResultStatus("Cannot delete Partition");

	return new ResultStatus();
}



Result * AlterNoteTable::executeCommand(op::State & state)  {


	return new ResultStatus();
}


bool checkTypeForColumn(const string & value, const string & type){

	auto checkFunc = typeCheckingStruct.find(type);

	if (checkFunc == typeCheckingStruct.end())
		return false;

	return checkFunc->second(value);
}

Result * Insert::executeCommand(op::State & state)  {

	//get structure
	//check values and structure
	//in loop ...
	//	get col
	//	write colfile data

	DataFormat & meta = state.getMetaDataForNoteTable(NoteTableForInsert);

	if (InsertValues.size() !=	meta.MemberCount())
		throw "Count of values != count of table members";

	auto valuesIterator = InsertValues.begin();
	auto it = meta.begin("structure");

	for (int i = 0; i < InsertValues.size(); ++i)
	{
		const string datatype = it.type();
		if(!checkTypeForColumn(*valuesIterator, datatype))
			throw "Wrong value type";		
		
		++it, ++valuesIterator;
	}

	for(it = meta.begin("structure"); !it.is_end(); ++it)
	{
		const string filename = it.name();
		//string filepath = op::PathToString({state.getCurrentPartition(), NoteTableForInsert, it.name()});
		//op::FileAppend(state, filepath, "info");
	}
	//meta.getValue<string>("a");

	return new ResultStatus();
}


Result * Update::executeCommand(op::State & state)  {
	return new ResultStatus();
}


Result * Delete::executeCommand(op::State & state)  {
	return new ResultStatus();
}



Result * Select::executeCommand(op::State & state)  {

	//read from table all data-linklist
	//GetAllData();

	return new ResultStatus("done");
}



Result *  Unknown::executeCommand(op::State & state)  { 
	return new ResultStatus("done");
}


Result *  ErrorMessage::executeCommand(op::State & state)  { 
	cout << error_msg << endl;
	return new ResultStatus("done");
}

#include "iface.h"


InterfaceCommandServer * InterfaceCommandServer::currentInterfaceServer = nullptr;


Interface::Interface(const Config & cfg){
	commandServers.push_back(new CLI(threadSync));
	//commandServers.push_back(new PIPE(threadSync));
}


CommandCollection Interface::getNewCommands(){

	unique_lock<mutex> command_lock(threadSync.mutexForNewCommand);
	threadSync.waitNewCommand.wait(command_lock);
	/*thread-safe?*/return InterfaceCommandServer::getCurrentInterfaceServer()->getNewCommands();
}

Result * Interface::handleResult(Result * result){
	return 0;
}

Interface::~Interface(){}

CommandCollection InterfaceCommandServer::getNewCommands()
{ 
	CommandCollection tmp = newCommands;
	newCommands.clear();
	return tmp;	
}

//------------------------------------------------------------------------

void cli_thread(CLI * CLI);

CLI::CLI(thread_sync & threadSync) : InterfaceCommandServer(threadSync) {

	thread(cli_thread, this).detach();
}




void addCommandFromWord(int & end_pos, vector<string> & command_words, string & new_word)
{
	string first_half_of_word = new_word.substr(0, end_pos);
	if (first_half_of_word != "")
		command_words.push_back(move(first_half_of_word));		
	command_words.push_back( string(1, new_word[end_pos]) );

	new_word 	= new_word.substr(end_pos+1);
	end_pos 	= 0;
}

void addSplitedWords(vector<string> & command_words, string & new_word)
{
	for (int end_pos = 0; end_pos < new_word.size(); ++end_pos)
	{
		char & symb = new_word[end_pos];	//cout << "symb(" << symb << ")" << endl;

		for(const char & spec_symb : SortedSplitingChars)
			if (symb > spec_symb)
				break;
			else
			if (symb == spec_symb)
			{
				addCommandFromWord(end_pos, command_words, new_word);
				if (symb == SpecSymbs::CommamdEnd)
					return;
			}		
	}
	if (new_word != "")
		command_words.push_back(move(new_word));		
}

		//if(find(SortedSplitingChars.begin(), SortedSplitingChars.end(), symb) != SortedSplitingChars.end())
			//command_words.push_back(command_buffer);		
		//size_t end_pos = command_buffer.find(CommamdDelimiter);
		//size_t notFoundPosition = string::npos;
//end_pos != notFoundPosition
			//string last_word = command_buffer.substr(0, end_pos);
			//if(last_word != "")
			//	command_words.push_back(move(last_word));		
		//command_buffer = command_buffer.substr(1);


void cli_thread(CLI * CLI){

	vector<string> command_words;
	string command_buffer;

	while(cin >> command_buffer) 
	{
		//cout << "cin: " << command_buffer << endl;
		addSplitedWords(command_words, command_buffer);
		if (command_words.back().front() != SpecSymbs::CommamdEnd)
			continue;

		cout << "--------------------------------------------------" << endl;
		for(const auto & s : command_words)
			cout << "\t~ \"" << s << "\"" << endl;
		cout << "--------------------------------------------------" << endl;

		try {
			auto CommandObject = command_parser(command_words);
			CLI->newCommands.push_back(move(CommandObject));	
			CLI->setCurrentInterfaceServer(CLI);
			CLI->threadSync.waitNewCommand.notify_one();
		} 
		catch(const char * err) {
			cout << "Error: " << err << endl;
		}
		catch(string & err) {
			cout << "Error: " << err << endl;
		}
		catch(...) {
			cout << "Error while creating command_words" << endl;
		}/**/

		command_words.clear();

	} 
}

CLI::~CLI(){}

//------------------------------------------------------------------------


void pipe_thread(PIPE * PIPE);

PIPE::PIPE(thread_sync & threadSync)  : InterfaceCommandServer(threadSync) {
	
	thread(pipe_thread, this).detach();
}

void pipe_thread(PIPE * PIPE){

	cout << "PIPE thread" << endl;
	fstream f;
	//f.open("/tmp/fifo", ios_base::in);
	int fd = open("/tmp/fifo", O_RDONLY);
	cout << "fd is" << fd << endl;

	cout << "File opening ..." << endl;

	if (!f.is_open())
	{
		cout << "Cannot open file" << endl;
		exit(1);
	}
	else
		cout << "File is open" << endl;

	while(1){

	}


}

PIPE::~PIPE(){}


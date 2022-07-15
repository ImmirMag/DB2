#include "config/config.h"
#include "handler/handler.h"
#include "iface/iface.h"
#include <memory>

#include <iostream>


using namespace std;


int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		cout << "Need more arguments" << endl;
		return 0;
	}
	
	const Config cfg(argv[1]);
	Interface Interface(cfg);
	op::State State(cfg);

	while(1){

		try
		{
			CommandCollection newCommands = Interface.getNewCommands();
			for(Command * cmd : newCommands)		
			{
				cout << "Command(" << cmd->getName() << ") ###############################" << endl;
				auto CommandResult = cmd->executeCommand(State);
				unique_ptr<Result> Result_(CommandResult);
				Result_->doResultAction();
				//Interface.handleResult(Result_);
				cout << "############################### Command(" << cmd->getName() << ")" << endl << endl;
			}
		}
		catch(char const * err){
			cout << "Main err: " << err << endl;
		}
		catch(...)
		{
			cout << "Occur main error" << endl;
		}

	}

	return 0;
}


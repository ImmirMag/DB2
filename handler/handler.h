#ifndef _HANDLER_H_
#define _HANDLER_H_


#include <map>
#include <iostream>


#include "../config/config.h"
#include "../iface/iface.h"
//#include "../commands/command.h"


using namespace std;

class Handler
{
public:
	Handler(const Config & cfg)  {

		//...somehandeling
	};
	~Handler(){};
	Result * update(Command & cmd);
private:
	//DataOperator DataOperator_;

};



#endif


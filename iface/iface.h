#ifndef _IFACE_
#define _IFACE_ 

#include <vector>
#include <array>
#include <initializer_list>

#include <iostream>
#include <fstream>

#include <unistd.h>
#include <fcntl.h>

#include <utility>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "../config/config.h"
#include "../commands/command.h"
#include "../commands/resulter.h"
#include "../commands/structures.h"


class Result;
class Command;

using namespace std;
using CommandCollection = vector<Command*>;

struct thread_sync
{
	condition_variable waitNewCommand;
	mutex mutexForNewCommand;			
};

class InterfaceCommandServer;

class Interface
{
public:
	Interface(const Config & cfg);
	~Interface();
	CommandCollection getNewCommands();
	Result * handleResult(Result * result);
private:
	vector<InterfaceCommandServer*> commandServers;	
	CommandCollection commands;
	thread_sync threadSync;

};

class InterfaceCommandServer
{
public:
	InterfaceCommandServer(thread_sync & threadSync) : threadSync (threadSync) {}
	~InterfaceCommandServer() {}
	CommandCollection getNewCommands();
	static InterfaceCommandServer * getCurrentInterfaceServer(){ return currentInterfaceServer; } 
protected:
	static void setCurrentInterfaceServer(InterfaceCommandServer * currentInterfaceServer) {
		InterfaceCommandServer::currentInterfaceServer = currentInterfaceServer;
	}
	CommandCollection newCommands;
	thread_sync & threadSync;
private:
	static InterfaceCommandServer * currentInterfaceServer;

};


class CLI : public InterfaceCommandServer
{
public:
	CLI(thread_sync & threadSync);
	~CLI();
	friend void cli_thread(CLI * CLI);
};


class PIPE  : public InterfaceCommandServer
{
public:
	PIPE(thread_sync & threadSync);
	~PIPE();
	friend void pipe_thread(PIPE * PIPE);

};

#endif
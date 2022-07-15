#ifndef _RESULTER_H_
#define _RESULTER_H_

#include <iostream>

#include "../config/config.h"
#include "../iface/iface.h"

using namespace std;

class Interface;

class Result
{
public:
	virtual void redefineInterface(Interface & Interface){}
	virtual void doResultAction() = 0;
};


class ResultStatus : public Result
{
public:
	ResultStatus() : errmsg("no error") {}
	ResultStatus(const string errmsg_) : errmsg(errmsg_) {};
	virtual void doResultAction() override;
private:
	const string errmsg;
};



#endif
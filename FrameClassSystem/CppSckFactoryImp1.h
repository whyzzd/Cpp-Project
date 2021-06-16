#pragma once
#include<iostream>
#include"cppsocketprotocol.h"
using namespace std;
class CppSckFactoryImp1 :public CPPSocketProtocol
{
public:

	virtual int cltSocketInit() ;
	virtual int cltSocketSend(unsigned char *buf, int buflen) ;
	virtual int cltSocketRev(unsigned char *buf, int *buflen) ;
	virtual int cltSocketDestory() ;
protected:
private:
	unsigned char *p;
	int len;
};
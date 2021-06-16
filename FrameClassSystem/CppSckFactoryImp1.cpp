#pragma once
#include"CppSckFactoryImp1.h"
int CppSckFactoryImp1::cltSocketInit()
{
	p = nullptr;
	len = 0;
	return 0;
}
int CppSckFactoryImp1::cltSocketSend(unsigned char *buf, int buflen)
{
	p = new unsigned char[buflen + 1];
	if (p == nullptr)
	{
		return -1;
	}
	memcpy(p, buf, buflen + 1);
	this->len = buflen;
	return 0;
}
int CppSckFactoryImp1::cltSocketRev(unsigned char *buf, int *buflen)
{
	if (this->p == nullptr || this->len == 0)
	{
		return -1;
	}
	*buflen = this->len;
	memcpy(buf, this->p, this->len + 1);
	return 0;
}
int CppSckFactoryImp1::cltSocketDestory()
{
	int ret = -1;
	if (p != nullptr)
	{
		delete[]p;
		p = nullptr;
		len = 0;
		ret = 0;
	}
	return ret;
}

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"cppsocketprotocol.h"
#include"CppSckFactoryImp1.h"
#include"CppSckFactoryImp2.h"
#include"CppEncDesProtocol.h"
#include"HwEncDec.h"
#include"FrameClass.h"

int main()
{
	int ret=0;
	unsigned char in[4096] = {0};
    int inlen;
	unsigned char out[4096] = {0};
    int outlen=0;

    strcpy((char *)in,"bbbbbbbbbbbbbbbbbbbb");
	inlen = 8;
	//框架类定义
	FrameClass *fc = new FrameClass;

	//通信抽象类
	CPPSocketProtocol *sp = nullptr;
	//通信厂商一分配内存：
	//sp=new CppSckFactoryImp1;
	//通信厂商二分配内存：
	sp = new CppSckFactoryImp2;

	//加解密抽象类
	CppEncDesProtocol *ed = nullptr;
	//加解密厂商一分配内存：
	ed = new HwEnDec;
	
	//将厂商设入框架类中
	fc->setED(ed);
	fc->setSP(sp);
	//调用框架类
	ret = fc->SckSendAndRec(in, inlen, out, &outlen);

	if (ret!=0)
	{
		cout << " SckSendAndRec的结果是 "<<ret;
		return ret;
	}

	delete fc;
	fc = nullptr;
	delete sp;
	sp = nullptr;
	delete ed;
	ed = nullptr;

    system("pause");	
	return 0;
}

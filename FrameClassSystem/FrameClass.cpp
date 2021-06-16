#include"FrameClass.h"
FrameClass::FrameClass()
{
	this->m_ed = nullptr;
	this->m_sp = nullptr;
}
FrameClass::~FrameClass()
{
}
FrameClass::FrameClass(CPPSocketProtocol *sp, CppEncDesProtocol *ed)
{
	this->m_ed = ed;
	this->m_sp = sp;
}
void FrameClass::setSP(CPPSocketProtocol *sp)
{
	this->m_sp = sp;
}
void FrameClass::setED(CppEncDesProtocol *ed)
{
	this->m_ed = ed;
}

int FrameClass::SckSendAndRec(unsigned char *in, int inlen, unsigned char*out, int *outlen)
{
	int ret = 0;

	//定义中间量，用来存储发送的密文
	unsigned char smdata[4096];
	int smdatalen;

	//定义中间量，用来存储接受的密文
	unsigned char rmdata[4096];
	int rmdatalen;

	//①先加密
	ret = this->m_ed->EncData(in, inlen, smdata, &smdatalen);
	if (ret != 0)
	{
		goto End;
	}
	//②发送密文数据
	ret = this->m_sp->cltSocketInit();
	if (ret != 0)
	{
		goto End;
	}
	ret = m_sp->cltSocketSend(smdata, smdatalen);
	if (ret != 0)
	{
		goto End;
	}

	//③接收密文数据
	ret = m_sp->cltSocketRev(rmdata, &rmdatalen);
	if (ret != 0)
	{
		goto End;
	}

	//④进行解密，最后输出
	ret = this->m_ed->DecData(rmdata, rmdatalen, out, outlen);
	if (ret != 0)
	{
		goto End;
	}
End:
	//释放内部内存
	ret = m_sp->cltSocketDestory();
	return ret;
}

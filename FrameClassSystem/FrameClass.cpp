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

	//�����м����������洢���͵�����
	unsigned char smdata[4096];
	int smdatalen;

	//�����м����������洢���ܵ�����
	unsigned char rmdata[4096];
	int rmdatalen;

	//���ȼ���
	ret = this->m_ed->EncData(in, inlen, smdata, &smdatalen);
	if (ret != 0)
	{
		goto End;
	}
	//�ڷ�����������
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

	//�۽�����������
	ret = m_sp->cltSocketRev(rmdata, &rmdatalen);
	if (ret != 0)
	{
		goto End;
	}

	//�ܽ��н��ܣ�������
	ret = this->m_ed->DecData(rmdata, rmdatalen, out, outlen);
	if (ret != 0)
	{
		goto End;
	}
End:
	//�ͷ��ڲ��ڴ�
	ret = m_sp->cltSocketDestory();
	return ret;
}

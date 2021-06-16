#pragma once
#include"CppEncDesProtocol.h"
#include"cppsocketprotocol.h"
class FrameClass
{
public:
	FrameClass();	
	~FrameClass();	
	FrameClass(CPPSocketProtocol *sp ,CppEncDesProtocol *ed);

	void setSP(CPPSocketProtocol *sp);
	void setED(CppEncDesProtocol *ed);
	int SckSendAndRec(unsigned char *in, int inlen, unsigned char*out, int *outlen);

protected:
private:
	CPPSocketProtocol *m_sp;
	CppEncDesProtocol *m_ed;

};
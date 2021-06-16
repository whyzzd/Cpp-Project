#pragma once
class CppEncDesProtocol
{
public:
	CppEncDesProtocol()
	{
		
	}
	virtual ~CppEncDesProtocol()
	{
		
	}
	virtual int EncData(unsigned char *plain, int plainlen, unsigned char*cryptdata, int *cryptlen)=0 ;
	virtual int DecData(unsigned char*cryptdata, int cryptlen, unsigned char *plain, int *plainlen)=0 ;
};
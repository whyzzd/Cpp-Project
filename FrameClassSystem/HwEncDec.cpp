#include"HwEncDec.h"
#include"des.h"
int DesEnc(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen);
int HwEnDec::EncData(unsigned char *plain, int plainlen, unsigned char*cryptdata, int *cryptlen)
{
	int ret;
	ret=DesEnc(plain,plainlen, cryptdata, cryptlen);
	if (ret != 0)
	{
		cout << "Enc ret的值是：" << ret << endl;
		return ret;
	}
	return ret;
}
int DesDec(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen);
int HwEnDec::DecData(unsigned char*cryptdata, int cryptlen, unsigned char *plain, int *plainlen)
{
	int ret;
	ret=DesDec(cryptdata, cryptlen, plain, plainlen);
	if (ret != 0)
	{
		cout << "Dec ret的值是：" << ret << endl;
		return ret;
	}
	return ret;
}
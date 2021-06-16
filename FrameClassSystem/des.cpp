#include"des.h"
#include<iostream>

int DesEnc(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen)
{
	unsigned char temp[4096];
	int i;
	for (i = 0; i < nInDataLen; i++)
	{
		temp[i]= pInData[i] + 1;
	}
	temp[i] = 0;
	if (temp == nullptr)
	{
		return -1;
	}
	strcpy((char*)pOutData, (char*)temp);
	*pOutDataLen = nInDataLen;
	return 0;
}
int DesDec(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen)
{
	unsigned char temp[4096];
	int i;
	for (i = 0; i < nInDataLen; i++)
	{
		temp[i] = pInData[i] - 1;
	}
	temp[i] = 0;
	if (temp == nullptr)
	{
		return -1;
	}
	strcpy((char*)pOutData, (char*)temp);
	*pOutDataLen = nInDataLen;
	return 0;
}
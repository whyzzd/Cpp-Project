#pragma once
#define _CRT_SECURE_NO_WARNINGS
extern "C" 
{

//����
int DesEnc(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen);
//����
int DesDec(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen);
}
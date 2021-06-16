#pragma once
#define _CRT_SECURE_NO_WARNINGS
extern "C" 
{

//º”√‹
int DesEnc(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen);
//Ω‚√‹
int DesDec(
	unsigned char*pInData,
	int nInDataLen,
	unsigned char *pOutData,
	int *pOutDataLen);
}
#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Boss :public Worker
{
public:
	Boss(int id, string name, int did);
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDeptName();//�״�㣺�������治�ܻ���д�ɴ��麯���������ܱ�ʵ����
};
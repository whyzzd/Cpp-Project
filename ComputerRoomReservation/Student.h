#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include"ComputerRoom.h"
#include<vector>
#include"OrderFile.h"
class Student :public Identity
{
public:
	//Ĭ�Ϲ��캯��
	Student();

	//�вι��캯��
	Student(int id, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴���е�ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();


	//ѧ��ѧ��
	int m_Id;

	//��������
	vector<ComputerRoom>m_Vcom;
};

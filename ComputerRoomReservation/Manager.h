#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>
#include"Teacher.h"
#include"Student.h"
#include<algorithm>
#include"ComputerRoom.h"
class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι��� ����Ա����������
	Manager(string name, string pwd);

	//ѡ��˵�
	virtual void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ
	void cleanFile();

	//��ʼ����ʦ��ѧ������
	void initVector();

	//����˺��Ƿ����ظ�
	bool checkRepeat(int id,int type);



	//��ʦ����
	vector<Teacher> m_VTer;

	//ѧ������
	vector<Student> m_VStd;

	//��������
	vector<ComputerRoom> m_Vcom;
};
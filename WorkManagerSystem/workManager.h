#pragma//��ֹ�ظ�����
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"
class WorkManager
{
public:
	WorkManager();//�����������δʵ��

	void Show_Menu();
	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ�� 
	Worker **m_EmpArray;

	//���ְ��
	void Add_Emp();

	//����Ϣ���浽�ļ�����ȥ
	void Save();

	//�ļ��Ƿ�Ϊ��...�ļ�������Ҳ��ʹ�����
	bool m_FileIsEmpty;

	//�õ�Ա��������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//չʾְ����Ϣ
	void show_Emp();

	//ɾ��ְ��
	void del_Emp();

	//�ж�ְ���Ƿ����,���������򷵻�-1
	int isExist(int n);

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��������ְ����ź�������
	void Find_Emp();

	//��ְ����������������
	void Sort_Emp();

	//�ļ������
	void Clean_File();
	~WorkManager();
};
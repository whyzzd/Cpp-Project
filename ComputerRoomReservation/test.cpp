#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include"globalFile.h"
#include"Identity.h"
#include"Student.h"
#include"Teacher.h"
#include"Manager.h"

//ѧ������˵�����
void StudentMenu(Identity*&student)
{
	//��Ҫ��ǿת�������ָ�룬��Ϊ����ָ���޷������������еĶ���
	Student *stu = (Student*)student;
	while (true)
	{
		stu->operMenu();
		int select;
		cout << "���������ѡ��";
		cin >> select;
		if (select == 1)
		{
			//����ԤԼ
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//�鿴ԤԼ
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			//�鿴����ԤԼ
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//ȡ��ԤԼ
			stu->cancelOrder();
		}
		else
		{
			delete stu;
			cout << "�ѳɹ�ע����¼" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void TeacherMenu(Identity* &teacher)
{
	Teacher *tea = (Teacher*)teacher;
	while (true)
	{
		tea->operMenu();
		int select;
		cout << "���������ѡ��" << endl;
		cin >> select;
		if (select == 1)
		{
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			tea->validOrder();
		}
		else
		{
			system("pause");
			system("cls");
			return;
		}
	}
}
//����Ա�˵�����
void ManagerMenu(Identity* &manager)
{
	Manager *man = (Manager*)manager;
	while (true)
	{
		man->operMenu();
		int select;
		cin >> select;
		if (select == 1)//����˺�
		{
			man->addPerson();
		}
		else if (select == 2)//�鿴�˺�
		{
			man->showPerson();
		}
		else if (select==3)//�鿴������Ϣ
		{
			man->showComputer();
		}
		else if(select==4)//���ԤԼ
		{
			man->cleanFile();
		}
		else
		{
			delete man;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//��¼����
void LoginIn(string fileName, int type)
{
	//���������ָ��
	Identity *person;
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	int id;
	string name;
	string pwd;
	
	if (type == 1)
	{
		cout << "���������ѧ�ţ�" ;
		cin >> id;
	}
	else if(type==2)
	{
		cout << "���������ְ���ţ�";
		cin >> id;
	}
	cout << "���������������";
	cin >> name;
	cout << "������������룺";
	cin >> pwd;

	if (type == 1)
	{
		//ѧ����֤
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid&&ifs >> fname&&ifs >> fpwd)
		{
			if (fid == id&&fname == name&&fpwd == pwd)
			{
				cout << "ѧ����Ϣ��֤�ɹ�" << endl;
				person = new Student(fid, fname, fpwd);
				system("pause");
				system("cls");
				StudentMenu(person);
				return;
			}
		}
	}
	else if(type == 2)
	{
		//��ʦ��֤
		int fid;
		string fname;
		string fpwd;
		while(ifs >> fid&&ifs >> fname&&ifs >> fpwd)
		{
			if (fid == id&&fname == name&&fpwd == pwd)
			{
				cout << "��ʦ�����֤�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(fid, fname, fpwd);
				//��ȥ�Ӳ˵�
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա��֤
		string fname;
		string fpwd;
		while (ifs >> fname&&ifs >> fpwd)
		{
			if (fname == name&&fpwd == pwd)
			{
				cout << "����Ա�����֤ͨ��" << endl;
				system("pause");
				system("cls");
				person = new Manager(fname, fpwd);

				ManagerMenu(person);
				return;
			}
		}
	}
	cout << "��¼��֤ʧ��" << endl;
	system("pause");
	system("cls");
	return;
	
}
int main()
{
	int select;
	while (true)
	{
		cout << "��ӭ��������ԤԼϵͳ" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t--------------------------------\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           1.ѧ������         |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           2.��   ʦ          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           3. ����Ա          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           0.��   ��          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t--------------------------------\n";
		cout << "�������ѡ��";
		cin >> select;
		switch (select)
		{
		case 1://ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://�˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}
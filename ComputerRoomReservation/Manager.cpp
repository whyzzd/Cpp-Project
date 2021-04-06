#include"Manager.h"
//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι��� ����Ա����������
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	initVector();

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom cr;
	while (ifs >> cr.m_ComId&&ifs >> cr.m_MaxNum)
	{
		this->m_Vcom.push_back(cr);
	}
	ifs.close();
}

//ѡ��˵�
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t--------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           1.����˺�         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           2.�鿴�˺�         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           3.�鿴����         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           4.���ԤԼ         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           0.ע����¼         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t--------------------------------\n";
	cout << "�������ѡ��"<<endl;
}

//����˺�
void Manager::addPerson()
{
	
	cout << "��������Ҫ��ӵ��˺����ͣ�" << endl;
	cout << "1.��ʦ" << endl;
	cout << "2.ѧ��" << endl;
	int select;
	cin >> select;

	ofstream ofs;
	string fname;
	string tip;
	string errorTip;
	if (select == 1)
	{
		fname = TEACHER_FILE;
		tip = "������ְ�����:";
		errorTip = "ְ��������ظ�������������";
	}
	else
	{
		fname = STUDENT_FILE;
		tip = "������ѧ��ѧ��:";
		errorTip = "ѧ��ѧ�����ظ�������������";
	}

	//Ȼ��ʼ���ļ���ѧ������ʦ���ݼ�������ͬ�����ñ���
	ofs.open(fname, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	
	
	//�����ж��Ƿ����ظ���ѧ�ţ���������������ѧ��
	while (true)
	{
		cout << tip;
		cin >> id;
		if (this->checkRepeat(id, select))
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}


	cout << "������������" ;
	cin >> name;
	
	cout << "���������룺" ;
	cin >> pwd;
	
	ofs << id << " " << name << " " << pwd << endl;
	cout << "����˺ųɹ���" << endl;

	this->initVector();
	ofs.close();
	system("pause");
	system("cls");
	return;
}

//�鿴�˺�
void printTeacher(Teacher &t)
{
	cout << "ְ����ţ�" << t.m_EmpId << " " << "����" << t.m_Name << " ���룺" << t.m_Pwd << endl;
}
void printStudent(Student &s)
{
	cout << "ѧ�ţ�" <<s.m_Id<< " " << "����" << s.m_Name << " ���룺" << s.m_Pwd << endl;
}
void Manager::showPerson()
{
	cout << "��ѡ��Ҫ�鿴����Ϣ��" << endl;
	cout << "1.��ʦ��Ϣ" << endl;
	cout << "2.ѧ����Ϣ" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		cout << "���н�ʦ��Ϣ���£�" << endl;
		for_each(this->m_VTer.begin(), this->m_VTer.end(), printTeacher);
	}
	else
	{
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(this->m_VStd.begin(), this->m_VStd.end(), printStudent);
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = this->m_Vcom.begin(); it != this->m_Vcom.end(); it++)
	{
		cout << it->m_ComId << "�Ż��������ǣ�" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//���ԤԼ
void Manager::cleanFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "ԤԼ��Ϣ��ճɹ���" << endl;
	system("pause");
	system("cls");
}

//��ʼ����ʦ��ѧ������
void Manager::initVector()
{
	this->m_VStd.clear();
	this->m_VTer.clear();

	ifstream ifs;

	//��ѧ���ļ����ж�ȡ
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id&&ifs >> s.m_Name&&ifs >> s.m_Pwd)
	{
		this->m_VStd.push_back(s);
	}
	cout << "��ǰ��ѧ������Ϊ��" << this->m_VStd.size() << endl;
	ifs.close();

	//����ʦ�ʼ۵��ж�ȡ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ʦ�ļ���ʧ��" << endl;
		return ;
	}

	Teacher t;
	while (ifs >> t.m_EmpId&&ifs >> t.m_Name&&ifs >> t.m_Pwd)
	{
		this->m_VTer.push_back(t);
	}
	cout << "��ǰ����ʦ��������" << this->m_VTer.size() << endl;
	ifs.close();
}

//����˺��Ƿ����ظ�
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Teacher>::iterator it = this->m_VTer.begin(); it != this->m_VTer.end(); it++)
		{
			if (it->m_EmpId == id)
			{
				return true;
			}
		}
	}
	else if (type == 2)
	{
		for (vector<Student>::iterator it = this->m_VStd.begin(); it != this->m_VStd.end(); it++)
		{
			if (it->m_Id == id)
			{
				return true;

			}
		}
	}
	return false;
}
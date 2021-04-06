#include"Teacher.h"
//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι���
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//�˵�����
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t--------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           1.�鿴����ԤԼ     |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           2.���ԤԼ         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           0.ע����¼         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t--------------------------------\n";
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "ԤԼ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		//stringתint
		//string ���� .c_str()תconst char *
		//���� atoi(const char *)תint
		cout << i + 1 << ".";
		cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"] << " ";
		cout << "ʱ��Σ�" << ((atoi(of.m_OrderData[i]["interval"].c_str()) == 1) ? "����" : "����") << " ";
		cout << "�����ţ�" << of.m_OrderData[i]["roomId"] << " ";
		cout << "ѧ�ţ�" << of.m_OrderData[i]["stdId"] << " ";
		cout << "������" << of.m_OrderData[i]["stdName"] << " ";
		string stat = "״̬��";
		//0 ȡ����ԤԼ 1�����  2��ԤԼ -1ԤԼʧ��
		if (of.m_OrderData[i]["status"] == "0")
		{
			stat += "ԤԼ��ȡ��";
		}
		else if (of.m_OrderData[i]["status"] == "1")
		{
			stat += "�����";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			stat += "ԤԼ�ɹ�";
		}
		else
		{
			stat += "���δͨ����ԤԼʧ�ܣ�";
		}
		cout << stat << endl;

	}
	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ǰû��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˵�ԤԼ��" << endl;
	int index = 0;
	vector<int>v;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_OrderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << ".";
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"] << " ";
			cout << "ʱ��Σ�" << ((atoi(of.m_OrderData[i]["interval"].c_str()) == 1) ? "����" : "����") << " ";
			cout << "�����ţ�" << of.m_OrderData[i]["roomId"] << " ";
			cout << "ѧ�ţ�" << of.m_OrderData[i]["stdId"] << " ";
			cout << "������" << of.m_OrderData[i]["stdName"] << " ";
			cout << "״̬�������" << endl;
		}
	}
	cout << "��������Ҫ��˵���ţ�" << endl;
	while (true)
	{
		int select;
		cin >> select;
		if (select >= 0 && select <= index)
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "��������˵Ľ����" << endl;
				cout << "1.ͨ��" << endl;
				cout << "2.��ͨ��" << endl;
				int ret;
				cin >> ret;
				if (ret == 1)
				{
					of.m_OrderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "��˽���" << endl;
				break;
			}
		}
		else
		{
			cout << "��������������������" << endl;
		}
	}
	system("pause");
	system("cls");
}
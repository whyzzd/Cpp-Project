#include"Student.h"
//Ĭ�Ϲ��캯��
Student::Student()
{

}

//�вι��캯��
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
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

//�˵�����
void Student::operMenu()
{
	cout << "��ӭѧ������" << this->m_Name << "��¼��" << endl;
	cout << "\t\t--------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           1.����ԤԼ         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           2.�鿴�ҵ�ԤԼ     |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           3.�鿴����ԤԼ     |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           4.ȡ��ԤԼ         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           0.ע����¼         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t--------------------------------\n";

}

//����ԤԼ
void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date << 5)
		{
			break;
		}
		cout << "�������ڴ�������������" << endl;
	}

	cout << "������ԤԼ��ʱ��Σ�" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "ʱ�������������������룡" << endl;
	}

	cout << "��ѡ����Ҫ����Ļ���:" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "�����ţ�" << this->m_Vcom[i].m_ComId << " " << "���������" << this->m_Vcom[i].m_MaxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room == 1 || room == 2||room==3)
		{
			break;
		}
		cout << "���������������" << endl;
	}

	//���������Ϣ¼�뵽�ļ�����
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "roomId:" << room << " ";
	ofs << "stdId:" << this->m_Id << " ";
	ofs << "stdName:" << this->m_Name << " ";
	ofs << "status:" << 1 << endl;
	
	ofs.close();
	cout << "ԤԼ����ɹ�����ȴ���ˣ�" << endl;

	system("pause");
	system("cls");


}

//�鿴����ԤԼ
void Student::showMyOrder()
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
		if (this->m_Id ==atoi(of.m_OrderData[i]["stdId"].c_str()))
		{
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"] << " ";
			cout << "ʱ��Σ�" <<( (atoi(of.m_OrderData[i]["interval"].c_str()) == 1) ? "����" : "����" )<< " ";
			cout << "�����ţ�" << of.m_OrderData[i]["roomId"] << " ";
			string stat="״̬��";
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
	}
	system("pause");
	system("cls");
}

//�鿴���е�ԤԼ
void Student::showAllOrder()
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
		cout << i+1 << ".";
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

//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	vector<int>v;//������� ����ѧ�ŵĴ�map�±�
	int index = 0;//�����������ѧ�ŵĸ���
	if (of.m_Size == 0)
	{
		cout << "��ǰû��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л���ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
	for (int i= 0; i < of.m_Size; i++)
	{
		if (this->m_Id == atoi(of.m_OrderData[i]["stdId"].c_str()))
		{
			if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << ++index << ".";
				cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
				cout << "ʱ��Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
				cout << "������ţ�" << of.m_OrderData[i]["roomId"];
				string stat = "״̬��";
				//0 ȡ����ԤԼ 1�����  2��ԤԼ -1ԤԼʧ��
				
				if (of.m_OrderData[i]["status"] == "1")
				{
					stat += "�����";
				}
				else if (of.m_OrderData[i]["status"] == "2")
				{
					stat += "ԤԼ�ɹ�";
				}
				cout << stat << endl;
			}
		}
	}
	
	
	//ͨ���û���������������map������״̬
	cout << "������ȡ���ļ�¼��0������" << endl;
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
				of.m_OrderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				break;
			}
		}
		else
		{
			cout << "������������������" << endl;
		}
	}
	system("pause");
	system("cls");
}
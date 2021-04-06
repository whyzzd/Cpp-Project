#include"OrderFile.h"


//���캯��
OrderFile::OrderFile() 
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string date;
	string interval;
	string roomId;
	string stdId;
	string stdName;
	string status;
	this->m_Size = 0;
	while (ifs >> date&&ifs >> interval&&ifs >> roomId&&ifs >> stdId&&ifs >> stdName&&ifs >> status)
	{
		//���ַ������зָ�
		string key;
		string value;
		map<string, string>mkv;
		//��ȡ����
		int pos=date.find(":");
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			mkv.insert(make_pair(key, value));
		}

		//��ȡʱ���
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			mkv.insert(make_pair(key, value));
		}
		//��ȡ�����
		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			mkv.insert(make_pair(key, value));
		}
		//��ȡѧ��ѧ��
		pos = stdId.find(":");
		if (pos != -1)
		{
			key = stdId.substr(0, pos);
			value = stdId.substr(pos + 1, stdId.size() - pos - 1);
			mkv.insert(make_pair(key, value));
		}
		//��ȡѧ������
		pos = stdName.find(":");
		if (pos != -1)
		{
			key = stdName.substr(0, pos);
			value = stdName.substr(pos + 1, stdName.size() - pos - 1);
			mkv.insert(make_pair(key, value));
		}
		//��ȡ״̬��Ϣ
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			mkv.insert(make_pair(key, value));
		}
		this->m_OrderData.insert(make_pair(this->m_Size, mkv));
		/*cout << date << endl;
		cout << interval << endl;
		cout << roomId << endl;
		cout << stdId << endl;
		cout << stdName << endl;
		cout << status << endl;*/
		this->m_Size++;
	}
	ifs.close();

	//��������
	/*for (map<int, map<string, string>>::iterator it = this->m_OrderData.begin(); it != this->m_OrderData.end(); it++)
	{
		cout << "��" << it->first + 1 << "��¼��";
		for (map<string, string>::iterator itm = (*it).second.begin(); itm != (*it).second.end(); itm++)
		{
			cout << itm->first<<":" << itm->second<<" ";
		}
		cout << endl;
	}
	system("pause");
	system("cls");*/
}

//����ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:"<< this->m_OrderData[i]["date"]<<" ";
		ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
		ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
		ofs << "stdId:" << this->m_OrderData[i]["stdId"] << " ";
		ofs << "stdName:" << this->m_OrderData[i]["date"] << " ";
		ofs << "status:" << this->m_OrderData[i]["status"] << endl;
	}
	ofs.close();
	cout << "�������" << endl;
	
}
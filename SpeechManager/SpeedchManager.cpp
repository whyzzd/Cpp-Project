#include<iostream>
using namespace std;
#include"SpeechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
}
//�˵�չʾ
void SpeechManager::show_Menu()
{
	cout << "*******************************************"<<endl;
	cout << "**************��ӭ�μ��ݽ�����*************" << endl;
	cout << "***************1.��ʼ�ݽ�����**************" << endl;
	cout << "***************2.�鿴�����¼**************" << endl;
	cout << "***************3.��ձ�����¼**************" << endl;
	cout << "***************0.�˳���������**************" << endl;
	cout << endl;
	
}
//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´��ٴ�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}
//��ʼ������������
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}
//����12��ѡ��
void SpeechManager::creatSpeaker()
{
	string name_Seed = "ABCDEFGHIJKL";
	string name;
	for (int i = 0; i < name_Seed.size(); i++)
	{
		name = "ѡ��";
		name += name_Seed[i];
		Speaker speaker;
		speaker.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			speaker.m_Score[j] = 0;
		}
		
		//����ѡ�ֱ�ţ��ڴ���ѡ�ֵ�ʱ��ͬʱ������ţ�
		this->v1.push_back(10001 + i);

		//��ѡ�ֱ�ź�ѡ�ַ���map������
		this->m_Speaker.insert(make_pair(10001 + i, speaker));


	}
	
}
//��ʼ����
void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();

	this->m_Index++;

	//�ڶ��ֱ���
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showScore();
	//4.�������
	this->saveRecord();

	//���������ʹ�ô˳���Ļ���ÿ�������Ӧ�����³�ʼ������
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();


	cout << "�������������" << endl;
	system("pause");
	system("cls");
}
//��ѡ�ֽ��г�ǩ
void SpeechManager::speechDraw()
{
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = this->v1.begin(); it != this->v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
		cout << "---------------------------------------------" << endl;
	}
	else
	{

		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
		cout << "---------------------------------------------" << endl;
	}
	system("pause");
}
//��ʽ����
void SpeechManager::speechContest()
{
	cout << "��" << this->m_Index << "�ֱ�����ʽ��ʼ" << endl;
	cout << "----------------------------------------------" << endl;
	cout << endl;
	//����ѡ�ֱ�������
	vector<int>v_Src;

	//������������,���ѡ�ֵľ��ֺͱ��
	multimap<double, int,greater<double>>group_Map;

	//���
	int num = 0;
	if (this->m_Index == 1)
	{
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}

	//��������ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί��ѡ�ִ��
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//greater��Ҫ�����ڽ���������
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.f);
		double avg = sum / (double)d.size();

		//������ƽ���ɼ��Ž���ʱ�������map��������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//�������ɼ����������������
		group_Map.insert(make_pair(avg, *it));

		//�������ɼ����з���
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "��ĵ÷�������£�" << endl;
			//������������
			for (multimap<double, int>::iterator it = group_Map.begin(); it != group_Map.end(); it++)
			{
				cout << "��ţ�" << it->second << " " << "������" << this->m_Speaker[it->second].m_Name
					<< "�ɼ���" << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}
			//ȡÿ�����ǰ����
			int cont = 0;
			for (multimap<double, int>::iterator it = group_Map.begin(); it != group_Map.end(), cont < 3; it++, cont++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back(it->second);
				}
				else
				{
					this->vVictory.push_back(it->second);
				}
			}
			group_Map.clear();
		}
	}
	cout << "��" << this->m_Index << "�ֱ�������" << endl;
	cout << "----------------------------------------------" << endl;
	cout << endl;
	system("pause");
}
//��ʾ�÷�
void SpeechManager::showScore()
{
	cout << "��" << this->m_Index << "����ѡ�����£�" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "���:" << *it << " ������" << this->m_Speaker[*it].m_Name
			<< "������" << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//����÷�
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	//������д���ļ�����ȥ
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1]<<",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	//Ҫ��fileIsEmpty��Ϊfalse����Ϊ��һ��ʼ�ļ�Ϊ�յĻ�������һ����¼֮������ȥ�鿴��¼���ǲ鿴���˵�
	this->fileIsEmpty = false;
}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	//�ļ�����Ϊ�յ�ʱ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ����ڵ���Ϊ�ա�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch); //���ոն������ĵ����ַ��Ż�ȥ

	//����ȡ��������ʾ����
	string data;
	//�����ݽ������ĵڼ���
	int index = 0;
	while (ifs >> data)//ifs>>ÿ�ζ�һ������
	{
		int start=0;
		vector<string>v;//���������������
		while (true)
		{
			//start������¼��ʼ��λ�ã�pos������¼������λ��
			int pos = data.find(",", start);
			if (pos == -1)
			{
				//û���ҵ�������
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			start = pos + 1;
			//�������ŵ�vector��������
			v.push_back(temp);
		}
		//��vector�������е����ݷ��룬map��������
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	//��ÿ��ĳɼ���ӡ����
	/*for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	{
		cout << it->first << " " << it->second[0] << " " << it->second[1] << endl;;
	}*/
}

//�鿴�����¼
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڣ����߼�¼Ϊ��" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
		{
			cout << "��" << it->first + 1 << "��"
				<< "�ھ���ţ�" << it->second[0] << "������" << it->second[1]
				<< "�Ǿ���ţ�" << it->second[2] << "������" << it->second[3]
				<< "������ţ�" << it->second[4] << "������" << it->second[5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);
		ofs.close();

		//ע��˴������ļ��б����¼һ��������Ҫ�����ݽ��г�ʼ�����Ա�������߲鿴
		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager()
{

}
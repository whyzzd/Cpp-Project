#include<iostream>
using namespace std;
#include"SpeechManager.h"
#include<string>
#include<ctime>
int main()
{
	srand((unsigned int)time(NULL));
	//�������������
	SpeechManager sm;
	int t;
	while (true)
	{
	/*	map<int, Speaker>::iterator it = sm.m_Speaker.begin();
		cout << it->first << " " << it->second.m_Name << " " << it->second.m_Score[0] << endl;*/
		sm.show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> t;
		switch (t)
		{
		//��ʼ�ݽ�����
		case 1:
			sm.startSpeech();
			break;

		//�鿴�����¼
		case 2:
			sm.showRecord();
			break;

		//��ձ�����¼
		case 3:
			sm.clearRecord();
			break;

		//�˳���������
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
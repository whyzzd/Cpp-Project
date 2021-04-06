#include<iostream>
using namespace std;
#include"SpeechManager.h"
#include<string>
#include<ctime>
int main()
{
	srand((unsigned int)time(NULL));
	//创建管理类对象
	SpeechManager sm;
	int t;
	while (true)
	{
	/*	map<int, Speaker>::iterator it = sm.m_Speaker.begin();
		cout << it->first << " " << it->second.m_Name << " " << it->second.m_Score[0] << endl;*/
		sm.show_Menu();
		cout << "请输入你的选择：" << endl;
		cin >> t;
		switch (t)
		{
		//开始演讲比赛
		case 1:
			sm.startSpeech();
			break;

		//查看往届记录
		case 2:
			sm.showRecord();
			break;

		//清空比赛记录
		case 3:
			sm.clearRecord();
			break;

		//退出比赛程序
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
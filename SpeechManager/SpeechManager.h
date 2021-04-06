#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"Speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<fstream>

class SpeechManager
{
public:
	//构造
	SpeechManager();

	//菜单展示
	void show_Menu();

	//退出系统
	void exitSystem();
	
	//初始化容器及变量
	void initSpeech();

	//创建12名选手
	void creatSpeaker();

	//开始比赛
	void startSpeech();

	//对选手进行抽签
	void speechDraw();

	//正式比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存得分
	void saveRecord();

	//读取记录
	void loadRecord();

	//查看往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	//析构
	~SpeechManager();
	//成员变量
	//用来存放第一轮选手的容器
	vector<int> v1;

	//用来存放第二轮选手的容器
	vector<int> v2;

	//用来存放获胜选手的容器
	vector<int>vVictory;

	//用来存放选手及其对应编号
	map<int, Speaker>m_Speaker;

	//用来存放比赛的轮数
	int m_Index;

	//文件为空的标志
	bool fileIsEmpty;

	//存放往届的记录
	map<int, vector<string>>m_Record;
};
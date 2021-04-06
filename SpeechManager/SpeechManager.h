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
	//����
	SpeechManager();

	//�˵�չʾ
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();
	
	//��ʼ������������
	void initSpeech();

	//����12��ѡ��
	void creatSpeaker();

	//��ʼ����
	void startSpeech();

	//��ѡ�ֽ��г�ǩ
	void speechDraw();

	//��ʽ����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//����÷�
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//�鿴�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//����
	~SpeechManager();
	//��Ա����
	//������ŵ�һ��ѡ�ֵ�����
	vector<int> v1;

	//������ŵڶ���ѡ�ֵ�����
	vector<int> v2;

	//������Ż�ʤѡ�ֵ�����
	vector<int>vVictory;

	//�������ѡ�ּ����Ӧ���
	map<int, Speaker>m_Speaker;

	//������ű���������
	int m_Index;

	//�ļ�Ϊ�յı�־
	bool fileIsEmpty;

	//�������ļ�¼
	map<int, vector<string>>m_Record;
};
#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include"ComputerRoom.h"
#include<vector>
#include"OrderFile.h"
class Student :public Identity
{
public:
	//默认构造函数
	Student();

	//有参构造函数
	Student(int id, string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有的预约
	void showAllOrder();

	//取消预约
	void cancelOrder();


	//学生学号
	int m_Id;

	//机房容器
	vector<ComputerRoom>m_Vcom;
};

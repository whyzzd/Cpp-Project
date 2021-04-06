#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>
#include"Teacher.h"
#include"Student.h"
#include<algorithm>
#include"ComputerRoom.h"
class Manager :public Identity
{
public:
	//默认构造
	Manager();

	//有参构造 管理员姓名，密码
	Manager(string name, string pwd);

	//选择菜单
	virtual void operMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约
	void cleanFile();

	//初始化教师和学生容器
	void initVector();

	//检测账号是否有重复
	bool checkRepeat(int id,int type);



	//老师容器
	vector<Teacher> m_VTer;

	//学生容器
	vector<Student> m_VStd;

	//机房容器
	vector<ComputerRoom> m_Vcom;
};
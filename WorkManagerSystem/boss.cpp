#include<iostream>
using namespace std;
#include"boss.h"


Boss::Boss(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
void Boss::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名" << this->m_Name
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责：规划全公司的任务" << endl;
}
;
//获取岗位名称
string Boss::getDeptName()
{
	return string("老板");//将c语言的字符串转为string的字符串
}
#pragma once
#include<iostream>
using namespace std;
#include<map>
#include<string>
#include<fstream>
#include"globalFile.h"
class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_Size;

	//记录所有预约信息的容器 key记录条数
	map<int, map<string, string>>m_OrderData;
};
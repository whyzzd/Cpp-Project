#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Manager :public Worker
{
public:
	Manager(int id, string name, int did);
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName() ;//易错点：子类里面不能还是写成纯虚函数，否则不能被实例化
};
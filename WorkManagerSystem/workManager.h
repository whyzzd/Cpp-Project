#pragma//防止重复包含
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"
class WorkManager
{
public:
	WorkManager();//构造和析构中未实现

	void Show_Menu();
	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针 
	Worker **m_EmpArray;

	//添加职工
	void Add_Emp();

	//将信息保存到文件当中去
	void Save();

	//文件是否为空...文件不存在也是使用这个
	bool m_FileIsEmpty;

	//得到员工的人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//展示职工信息
	void show_Emp();

	//删除职工
	void del_Emp();

	//判断职工是否存在,若不存在则返回-1
	int isExist(int n);

	//修改职工
	void Mod_Emp();

	//查找职工（按照职工编号和姓名）
	void Find_Emp();

	//对职工进行升序降序排列
	void Sort_Emp();

	//文件的清空
	void Clean_File();
	~WorkManager();
};
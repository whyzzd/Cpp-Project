#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include"globalFile.h"
#include"Identity.h"
#include"Student.h"
#include"Teacher.h"
#include"Manager.h"

//学生代表菜单函数
void StudentMenu(Identity*&student)
{
	//需要先强转成子类的指针，因为父类指针无法调用子类特有的东西
	Student *stu = (Student*)student;
	while (true)
	{
		stu->operMenu();
		int select;
		cout << "请输入你的选择：";
		cin >> select;
		if (select == 1)
		{
			//申请预约
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//查看预约
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			//查看所有预约
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//取消预约
			stu->cancelOrder();
		}
		else
		{
			delete stu;
			cout << "已成功注销登录" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void TeacherMenu(Identity* &teacher)
{
	Teacher *tea = (Teacher*)teacher;
	while (true)
	{
		tea->operMenu();
		int select;
		cout << "请输入你的选择：" << endl;
		cin >> select;
		if (select == 1)
		{
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			tea->validOrder();
		}
		else
		{
			system("pause");
			system("cls");
			return;
		}
	}
}
//管理员菜单函数
void ManagerMenu(Identity* &manager)
{
	Manager *man = (Manager*)manager;
	while (true)
	{
		man->operMenu();
		int select;
		cin >> select;
		if (select == 1)//添加账号
		{
			man->addPerson();
		}
		else if (select == 2)//查看账号
		{
			man->showPerson();
		}
		else if (select==3)//查看机房信息
		{
			man->showComputer();
		}
		else if(select==4)//清空预约
		{
			man->cleanFile();
		}
		else
		{
			delete man;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
//登录函数
void LoginIn(string fileName, int type)
{
	//创建父类的指针
	Identity *person;
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//文件不存在的情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	int id;
	string name;
	string pwd;
	
	if (type == 1)
	{
		cout << "请输入你的学号：" ;
		cin >> id;
	}
	else if(type==2)
	{
		cout << "请输入你的职工号：";
		cin >> id;
	}
	cout << "请输入你的姓名：";
	cin >> name;
	cout << "请输入你的密码：";
	cin >> pwd;

	if (type == 1)
	{
		//学生验证
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid&&ifs >> fname&&ifs >> fpwd)
		{
			if (fid == id&&fname == name&&fpwd == pwd)
			{
				cout << "学生信息验证成功" << endl;
				person = new Student(fid, fname, fpwd);
				system("pause");
				system("cls");
				StudentMenu(person);
				return;
			}
		}
	}
	else if(type == 2)
	{
		//教师验证
		int fid;
		string fname;
		string fpwd;
		while(ifs >> fid&&ifs >> fname&&ifs >> fpwd)
		{
			if (fid == id&&fname == name&&fpwd == pwd)
			{
				cout << "教师身份验证成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(fid, fname, fpwd);
				//进去子菜单
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员验证
		string fname;
		string fpwd;
		while (ifs >> fname&&ifs >> fpwd)
		{
			if (fname == name&&fpwd == pwd)
			{
				cout << "管理员身份验证通过" << endl;
				system("pause");
				system("cls");
				person = new Manager(fname, fpwd);

				ManagerMenu(person);
				return;
			}
		}
	}
	cout << "登录验证失败" << endl;
	system("pause");
	system("cls");
	return;
	
}
int main()
{
	int select;
	while (true)
	{
		cout << "欢迎来到机房预约系统" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t--------------------------------\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           1.学生代表         |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           2.老   师          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           3. 管理员          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|           0.退   出          |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t--------------------------------\n";
		cout << "输入你的选择：";
		cin >> select;
		switch (select)
		{
		case 1://学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0://退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}
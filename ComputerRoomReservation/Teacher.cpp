#include"Teacher.h"
//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//菜单界面
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
	cout << "\t\t--------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           1.查看所有预约     |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           2.审核预约         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           0.注销登录         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t--------------------------------\n";
}

//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "预约记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		//string转int
		//string 利用 .c_str()转const char *
		//利用 atoi(const char *)转int
		cout << i + 1 << ".";
		cout << "预约日期：周" << of.m_OrderData[i]["date"] << " ";
		cout << "时间段：" << ((atoi(of.m_OrderData[i]["interval"].c_str()) == 1) ? "上午" : "下午") << " ";
		cout << "机房号：" << of.m_OrderData[i]["roomId"] << " ";
		cout << "学号：" << of.m_OrderData[i]["stdId"] << " ";
		cout << "姓名：" << of.m_OrderData[i]["stdName"] << " ";
		string stat = "状态：";
		//0 取消的预约 1审核中  2已预约 -1预约失败
		if (of.m_OrderData[i]["status"] == "0")
		{
			stat += "预约已取消";
		}
		else if (of.m_OrderData[i]["status"] == "1")
		{
			stat += "审核中";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			stat += "预约成功";
		}
		else
		{
			stat += "审核未通过，预约失败！";
		}
		cout << stat << endl;

	}
	system("pause");
	system("cls");
}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "当前没有预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约：" << endl;
	int index = 0;
	vector<int>v;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_OrderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << ".";
			cout << "预约日期：周" << of.m_OrderData[i]["date"] << " ";
			cout << "时间段：" << ((atoi(of.m_OrderData[i]["interval"].c_str()) == 1) ? "上午" : "下午") << " ";
			cout << "机房号：" << of.m_OrderData[i]["roomId"] << " ";
			cout << "学号：" << of.m_OrderData[i]["stdId"] << " ";
			cout << "姓名：" << of.m_OrderData[i]["stdName"] << " ";
			cout << "状态：审核中" << endl;
		}
	}
	cout << "请输入你要审核的序号：" << endl;
	while (true)
	{
		int select;
		cin >> select;
		if (select >= 0 && select <= index)
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核的结果：" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				int ret;
				cin >> ret;
				if (ret == 1)
				{
					of.m_OrderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "审核结束" << endl;
				break;
			}
		}
		else
		{
			cout << "你输入有误，请重新输入" << endl;
		}
	}
	system("pause");
	system("cls");
}
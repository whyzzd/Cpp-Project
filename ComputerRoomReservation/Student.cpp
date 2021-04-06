#include"Student.h"
//默认构造函数
Student::Student()
{

}

//有参构造函数
Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom cr;
	while (ifs >> cr.m_ComId&&ifs >> cr.m_MaxNum)
	{
		this->m_Vcom.push_back(cr);
	}
	ifs.close();
}

//菜单界面
void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
	cout << "\t\t--------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           1.申请预约         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           2.查看我的预约     |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           3.查看所有预约     |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           4.取消预约         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           0.注销登录         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t--------------------------------\n";

}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放时间为周一至周五" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	cout << "请输入申请预约的时间：" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date << 5)
		{
			break;
		}
		cout << "输入日期错误，请重新输入" << endl;
	}

	cout << "请输入预约的时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "时间段输入错误，请重新输入！" << endl;
	}

	cout << "请选择你要申请的机房:" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "机房号：" << this->m_Vcom[i].m_ComId << " " << "最大容量：" << this->m_Vcom[i].m_MaxNum << endl;
	}

	while (true)
	{
		cin >> room;
		if (room == 1 || room == 2||room==3)
		{
			break;
		}
		cout << "请重新输入机房号" << endl;
	}

	//将申请的信息录入到文件当中
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "roomId:" << room << " ";
	ofs << "stdId:" << this->m_Id << " ";
	ofs << "stdName:" << this->m_Name << " ";
	ofs << "status:" << 1 << endl;
	
	ofs.close();
	cout << "预约申请成功，请等待审核！" << endl;

	system("pause");
	system("cls");


}

//查看自身预约
void Student::showMyOrder()
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
		if (this->m_Id ==atoi(of.m_OrderData[i]["stdId"].c_str()))
		{
			cout << "预约日期：周" << of.m_OrderData[i]["date"] << " ";
			cout << "时间段：" <<( (atoi(of.m_OrderData[i]["interval"].c_str()) == 1) ? "上午" : "下午" )<< " ";
			cout << "机房号：" << of.m_OrderData[i]["roomId"] << " ";
			string stat="状态：";
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
	}
	system("pause");
	system("cls");
}

//查看所有的预约
void Student::showAllOrder()
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
		cout << i+1 << ".";
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

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	vector<int>v;//用来存放 满足学号的大map下标
	int index = 0;//用来存放满足学号的个数
	if (of.m_Size == 0)
	{
		cout << "当前没有预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或者预约成功的记录可以取消，请输入取消的记录" << endl;
	for (int i= 0; i < of.m_Size; i++)
	{
		if (this->m_Id == atoi(of.m_OrderData[i]["stdId"].c_str()))
		{
			if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << ++index << ".";
				cout << "预约日期：周" << of.m_OrderData[i]["date"];
				cout << "时间段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << "机房编号：" << of.m_OrderData[i]["roomId"];
				string stat = "状态：";
				//0 取消的预约 1审核中  2已预约 -1预约失败
				
				if (of.m_OrderData[i]["status"] == "1")
				{
					stat += "审核中";
				}
				else if (of.m_OrderData[i]["status"] == "2")
				{
					stat += "预约成功";
				}
				cout << stat << endl;
			}
		}
	}
	
	
	//通过用户输入的序号来更改map容器中状态
	cout << "请输入取消的记录，0代表返回" << endl;
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
				of.m_OrderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				break;
			}
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
		}
	}
	system("pause");
	system("cls");
}
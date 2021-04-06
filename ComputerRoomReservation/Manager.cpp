#include"Manager.h"
//默认构造
Manager::Manager()
{

}

//有参构造 管理员姓名，密码
Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	initVector();

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

//选择菜单
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t--------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           1.添加账号         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           2.查看账号         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           3.查看机房         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           4.清空预约         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|           0.注销登录         |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t--------------------------------\n";
	cout << "输入你的选择："<<endl;
}

//添加账号
void Manager::addPerson()
{
	
	cout << "请输入你要添加的账号类型：" << endl;
	cout << "1.教师" << endl;
	cout << "2.学生" << endl;
	int select;
	cin >> select;

	ofstream ofs;
	string fname;
	string tip;
	string errorTip;
	if (select == 1)
	{
		fname = TEACHER_FILE;
		tip = "请输入职工编号:";
		errorTip = "职工编号有重复，请重新输入";
	}
	else
	{
		fname = STUDENT_FILE;
		tip = "请输入学生学号:";
		errorTip = "学生学号有重复，请重新输入";
	}

	//然后开始打开文件，学生和老师数据几乎都相同，共用变量
	ofs.open(fname, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	
	
	//首先判断是否有重复的学号，若有则重新输入学号
	while (true)
	{
		cout << tip;
		cin >> id;
		if (this->checkRepeat(id, select))
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}


	cout << "请输入姓名：" ;
	cin >> name;
	
	cout << "请输入密码：" ;
	cin >> pwd;
	
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加账号成功！" << endl;

	this->initVector();
	ofs.close();
	system("pause");
	system("cls");
	return;
}

//查看账号
void printTeacher(Teacher &t)
{
	cout << "职工编号：" << t.m_EmpId << " " << "姓名" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}
void printStudent(Student &s)
{
	cout << "学号：" <<s.m_Id<< " " << "姓名" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void Manager::showPerson()
{
	cout << "请选择要查看的信息：" << endl;
	cout << "1.教师信息" << endl;
	cout << "2.学生信息" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		cout << "所有教师信息如下：" << endl;
		for_each(this->m_VTer.begin(), this->m_VTer.end(), printTeacher);
	}
	else
	{
		cout << "所有学生信息如下：" << endl;
		for_each(this->m_VStd.begin(), this->m_VStd.end(), printStudent);
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	for (vector<ComputerRoom>::iterator it = this->m_Vcom.begin(); it != this->m_Vcom.end(); it++)
	{
		cout << it->m_ComId << "号机房容量是：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//清空预约
void Manager::cleanFile()
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "预约信息清空成功！" << endl;
	system("pause");
	system("cls");
}

//初始化教师和学生容器
void Manager::initVector()
{
	this->m_VStd.clear();
	this->m_VTer.clear();

	ifstream ifs;

	//从学生文件当中读取
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id&&ifs >> s.m_Name&&ifs >> s.m_Pwd)
	{
		this->m_VStd.push_back(s);
	}
	cout << "当前的学生数量为：" << this->m_VStd.size() << endl;
	ifs.close();

	//从老师问价当中读取
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "老师文件打开失败" << endl;
		return ;
	}

	Teacher t;
	while (ifs >> t.m_EmpId&&ifs >> t.m_Name&&ifs >> t.m_Pwd)
	{
		this->m_VTer.push_back(t);
	}
	cout << "当前的老师的数量：" << this->m_VTer.size() << endl;
	ifs.close();
}

//检测账号是否有重复
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Teacher>::iterator it = this->m_VTer.begin(); it != this->m_VTer.end(); it++)
		{
			if (it->m_EmpId == id)
			{
				return true;
			}
		}
	}
	else if (type == 2)
	{
		for (vector<Student>::iterator it = this->m_VStd.begin(); it != this->m_VStd.end(); it++)
		{
			if (it->m_Id == id)
			{
				return true;

			}
		}
	}
	return false;
}
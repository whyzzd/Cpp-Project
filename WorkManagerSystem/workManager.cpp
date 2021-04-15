#include"workManager.h"

WorkManager::WorkManager()
{
	//初始化属性
	//在运行的初期，就尝试去读文件
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	
	//1.文件不存在的时候
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->m_EmpNum = 0;//初始化人数
		this->m_EmpArray = NULL;//数组置空
		this->m_FileIsEmpty = true;//初始化文件为空标识:重要标志
		ifs.close();
		return;
	}

	//2.文件存在，但是为空的情况
	if (ifs.eof())
	{
		//cout << "文件存在，但是为空" << endl;
		this->m_EmpArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在，记录数据
	int num;
	num = this->get_EmpNum();
	/*cout << "文件里面一共有" << num << "行数据" << endl;*/
	this->m_EmpNum = num;
	
	//测试初始化员工函数
	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];

	//将文件中的数据存到数组中
	this->init_Emp();

	/*测试是否已经存到数组当中*/
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}*/
	
}
void WorkManager:: Show_Menu()
{
	cout << "*********************************************"<<endl;
	cout << "*************欢迎使用职工管理系统************" << endl;
	cout << "*************   0.退出管理程序   ************ " << endl;
	cout << "*************   1.增加职工信息   ************ " << endl;
	cout << "*************   2.显示职工信息   ************ " << endl;
	cout << "*************   3.删除离职员工   ************ " << endl;
	cout << "*************   4.修改职工信息   ************ " << endl;
	cout << "*************   5.查找职工信息   ************ " << endl;
	cout << "*************   6.排序职工信息   ************ " << endl;
	cout << "*************   7.清空所有文档   ************ " << endl;
	cout << "*********************************************" << endl;
	cout << endl;
}
void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkManager::Add_Emp()
{
	cout << "请添加职工数量：" << endl;
	int addNum = 0;//新添加的用户的总数
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;

		//开辟新的空间
		Worker **newSpace = new Worker*[newSize];

		//将原来的空间的数据拷贝到新的空间中
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//将新添加的加入到新的空间中
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个职工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个职工姓名" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "个部门编号" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			//以下为多态的使用
			Worker *worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有的空间
		delete[] this->m_EmpArray;
		//指向新的空间
		this->m_EmpArray = newSpace;
		//更新职工人数
		this->m_EmpNum = newSize;
		cout << "成功添加" << addNum << "名新职工"<<endl;
		this->Save();//通过this指针来
		this->m_FileIsEmpty = false;
	}
	else
	{
		cout << "数据输入有误" << endl;
	}
	system("pause");
	system("cls");
}

void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//打开的方式
	//将每个人输入到文件当中
	for (int i=0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

int WorkManager::get_EmpNum()//命名空间容易忽略
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int num=0;
	int id;
	string name;
	int did;
	while (ifs >> id&&ifs >> name&&ifs >> did)
	{
		num++;
	}
	return num;
}

void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id&&ifs >> name&&ifs >> did)
	{
		Worker *worker = NULL;
		if (did == 1)
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)
		{
			worker = new Manager(id, name, did);
		}
		else
		{
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index++] = worker;
	}
	//别忘记了关闭文件
	ifs.close();
}

void WorkManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件位空或者文件不存在" << endl;
	}
	else
	{
		cout << "请输入想要删除的编号" << endl;
		int index;
		cin >> index;
		if (this->isExist(index)!=-1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->Save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "你要删除的编号不存在" << endl;
		}
	}
	system("pause");
	system("cls");
}
int WorkManager::isExist(int n)
{
	int index=-1;
	for (int i = 0; i < this->get_EmpNum(); i++)
	{
		if (this->m_EmpArray[i]->m_Id == n)
		{
			index = i;
			break;  
		}
	}
	return index;
}

void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
		
	}
	else
	{
		cout << "请输入你要修改的编号" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret==-1)
		{
			cout << "你所要修改的职工不存在"<<endl;
		
		}
		else
		{
			delete m_EmpArray[ret];
			int newId = 0;
			string name = "";
			int dselect = 0;
			cout << "请输入职工编号：" << endl;
			cin >> newId;
			cout << "请输入职工姓名" << endl;
			cin >> name;
			cout << "请选择职工职位:" << endl;
			cout << "1,普通职工"<<endl;
			cout << "2,部门经理" << endl;
			cout << "3,老板" << endl;
			cin >> dselect;
			//Worker对象要提前定义，因为下面的case不一定会执行，这样会导致wker对象不能赋值到数组当中。
			Worker* wker=NULL;
			switch (dselect)
			{
			case 1:
				wker = new Employee(newId, name, dselect);
				break;
			case 2:
				wker = new Manager(newId, name, dselect);
				break;
			case 3:
				wker = new Boss(newId, name, dselect);
				break;
			}
			this->m_EmpArray[ret] = wker;
			cout << this->m_EmpArray[ret]->m_Id << "编号修改成功" << endl;
			this->Save();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空" << endl;
	}
	else
	{
		cout << "请输入查找方式："<<endl;
		cout << "1,按照职工编号进行查找" << endl
			<< "2,按照姓名查找" << endl;
		int sid;
		cin >> sid;
		if (sid == 1)
		{
			cout << "请输入职工编号" << endl;
			int pid;
			cin >> pid;
			int ret;
			ret = this->isExist(pid);
			if (ret!=-1)
			{
				cout << "查找成功" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{ 
				cout << "你所查找的职工不存在!" << endl;
			}
		}
		else if (sid == 2)
		{
			cout << "请输入职工的姓名"<<endl;
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (name == this->m_EmpArray[i]->m_Name)
				{
					cout << "根据姓名查找成功！" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "你所查找的员工不存在！"<<endl;
			}

		}
		else
		{
			cout << "请重新输入"<<endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Sort_Emp()
{
	if (!this->m_FileIsEmpty)
	{
		cout << "请选择排序的方式:" << endl;
		cout << "1,升序" << endl;
		cout << "2,降序" << endl;
		int sid;
		cin >> sid;
		int MinorMax;
		for (int i = 0; i < this->m_EmpNum - 1; i++)
		{
			MinorMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (sid == 1)
				{
					if (this->m_EmpArray[MinorMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						MinorMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[MinorMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						MinorMax = j;
					}
				}
			}
			if (MinorMax != i)
			{
				Worker* temp = this->m_EmpArray[MinorMax];
				this->m_EmpArray[MinorMax] = this->m_EmpArray[i];
				this->m_EmpArray[i] = temp;
			}
		}
		cout << "排序成功，排序后的结果是：" << endl;
		this->Save();
		this->show_Emp();
	}
	else
	{
		cout << "文件为空" << endl;
		system("pause");
		system("cls");
	}
}

void WorkManager::Clean_File()
{
	cout << "确定要清空文件吗？" << endl;
	cout << "1,确认" << endl;
	cout << "2,返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[]this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！"<<endl;
	}
	system("pause");
	system("cls");
}
WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
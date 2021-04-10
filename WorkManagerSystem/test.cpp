#include<iostream>
using namespace std;
#include<string>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

int main()
{
	//测试代码
	/*Worker *wker1=NULL;
	wker1= new Employee(1, "张三", 4); 
	wker1->showInfo();
	Worker *wker2 = NULL;
	wker2 = new Manager(2, "李四", 4);
	wker2->showInfo();
	Worker *wker3 = NULL;
	wker3 = new Boss(3, "李四", 5);
	wker3->showInfo();*/
	WorkManager wm;
	int choice=0;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:	//退出系统
			wm.ExitSystem();
			break;
		case 1:	//增加职工
			wm.Add_Emp();
			break;
		case 2:	//显示职工
			wm.show_Emp();
			break;
		case 3:	//删除职工
			wm.del_Emp();
			break;
		case 4:	//修改职工
			wm.Mod_Emp();
			break;
		case 5:	//查找职工 
			wm.Find_Emp();
			break;
		case 6:	//排序职工
			wm.Sort_Emp();
			break;
		case 7:	//清空职工
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
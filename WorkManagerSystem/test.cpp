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
	//���Դ���
	/*Worker *wker1=NULL;
	wker1= new Employee(1, "����", 4); 
	wker1->showInfo();
	Worker *wker2 = NULL;
	wker2 = new Manager(2, "����", 4);
	wker2->showInfo();
	Worker *wker3 = NULL;
	wker3 = new Boss(3, "����", 5);
	wker3->showInfo();*/
	WorkManager wm;
	int choice=0;
	while (true)
	{
		wm.Show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:	//�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1:	//����ְ��
			wm.Add_Emp();
			break;
		case 2:	//��ʾְ��
			wm.show_Emp();
			break;
		case 3:	//ɾ��ְ��
			wm.del_Emp();
			break;
		case 4:	//�޸�ְ��
			wm.Mod_Emp();
			break;
		case 5:	//����ְ�� 
			wm.Find_Emp();
			break;
		case 6:	//����ְ��
			wm.Sort_Emp();
			break;
		case 7:	//���ְ��
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
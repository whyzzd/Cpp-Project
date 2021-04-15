#include"workManager.h"

WorkManager::WorkManager()
{
	//��ʼ������
	//�����еĳ��ڣ��ͳ���ȥ���ļ�
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	
	//1.�ļ������ڵ�ʱ��
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;//��ʼ������
		this->m_EmpArray = NULL;//�����ÿ�
		this->m_FileIsEmpty = true;//��ʼ���ļ�Ϊ�ձ�ʶ:��Ҫ��־
		ifs.close();
		return;
	}

	//2.�ļ����ڣ�����Ϊ�յ����
	if (ifs.eof())
	{
		//cout << "�ļ����ڣ�����Ϊ��" << endl;
		this->m_EmpArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�ļ����ڣ���¼����
	int num;
	num = this->get_EmpNum();
	/*cout << "�ļ�����һ����" << num << "������" << endl;*/
	this->m_EmpNum = num;
	
	//���Գ�ʼ��Ա������
	//���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];

	//���ļ��е����ݴ浽������
	this->init_Emp();

	/*�����Ƿ��Ѿ��浽���鵱��*/
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
	cout << "*************��ӭʹ��ְ������ϵͳ************" << endl;
	cout << "*************   0.�˳��������   ************ " << endl;
	cout << "*************   1.����ְ����Ϣ   ************ " << endl;
	cout << "*************   2.��ʾְ����Ϣ   ************ " << endl;
	cout << "*************   3.ɾ����ְԱ��   ************ " << endl;
	cout << "*************   4.�޸�ְ����Ϣ   ************ " << endl;
	cout << "*************   5.����ְ����Ϣ   ************ " << endl;
	cout << "*************   6.����ְ����Ϣ   ************ " << endl;
	cout << "*************   7.��������ĵ�   ************ " << endl;
	cout << "*********************************************" << endl;
	cout << endl;
}
void WorkManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkManager::Add_Emp()
{
	cout << "�����ְ��������" << endl;
	int addNum = 0;//����ӵ��û�������
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;

		//�����µĿռ�
		Worker **newSpace = new Worker*[newSize];

		//��ԭ���Ŀռ�����ݿ������µĿռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//������ӵļ��뵽�µĿռ���
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "��ְ�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "��ְ������" << endl;
			cin >> name;
			cout << "�������" << i + 1 << "�����ű��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;

			//����Ϊ��̬��ʹ��
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

		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;
		//ָ���µĿռ�
		this->m_EmpArray = newSpace;
		//����ְ������
		this->m_EmpNum = newSize;
		cout << "�ɹ����" << addNum << "����ְ��"<<endl;
		this->Save();//ͨ��thisָ����
		this->m_FileIsEmpty = false;
	}
	else
	{
		cout << "������������" << endl;
	}
	system("pause");
	system("cls");
}

void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//�򿪵ķ�ʽ
	//��ÿ�������뵽�ļ�����
	for (int i=0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

int WorkManager::get_EmpNum()//�����ռ����׺���
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
	//�������˹ر��ļ�
	ifs.close();
}

void WorkManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
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
		cout << "�ļ�λ�ջ����ļ�������" << endl;
	}
	else
	{
		cout << "��������Ҫɾ���ı��" << endl;
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
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "��Ҫɾ���ı�Ų�����" << endl;
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
		cout << "�ļ������ڣ�" << endl;
		
	}
	else
	{
		cout << "��������Ҫ�޸ĵı��" << endl;
		int id;
		cin >> id;
		int ret = this->isExist(id);
		if (ret==-1)
		{
			cout << "����Ҫ�޸ĵ�ְ��������"<<endl;
		
		}
		else
		{
			delete m_EmpArray[ret];
			int newId = 0;
			string name = "";
			int dselect = 0;
			cout << "������ְ����ţ�" << endl;
			cin >> newId;
			cout << "������ְ������" << endl;
			cin >> name;
			cout << "��ѡ��ְ��ְλ:" << endl;
			cout << "1,��ְͨ��"<<endl;
			cout << "2,���ž���" << endl;
			cout << "3,�ϰ�" << endl;
			cin >> dselect;
			//Worker����Ҫ��ǰ���壬��Ϊ�����case��һ����ִ�У������ᵼ��wker�����ܸ�ֵ�����鵱�С�
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
			cout << this->m_EmpArray[ret]->m_Id << "����޸ĳɹ�" << endl;
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
		cout << "�ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��"<<endl;
		cout << "1,����ְ����Ž��в���" << endl
			<< "2,������������" << endl;
		int sid;
		cin >> sid;
		if (sid == 1)
		{
			cout << "������ְ�����" << endl;
			int pid;
			cin >> pid;
			int ret;
			ret = this->isExist(pid);
			if (ret!=-1)
			{
				cout << "���ҳɹ�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{ 
				cout << "�������ҵ�ְ��������!" << endl;
			}
		}
		else if (sid == 2)
		{
			cout << "������ְ��������"<<endl;
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (name == this->m_EmpArray[i]->m_Name)
				{
					cout << "�����������ҳɹ���" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "�������ҵ�Ա�������ڣ�"<<endl;
			}

		}
		else
		{
			cout << "����������"<<endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Sort_Emp()
{
	if (!this->m_FileIsEmpty)
	{
		cout << "��ѡ������ķ�ʽ:" << endl;
		cout << "1,����" << endl;
		cout << "2,����" << endl;
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
		cout << "����ɹ��������Ľ���ǣ�" << endl;
		this->Save();
		this->show_Emp();
	}
	else
	{
		cout << "�ļ�Ϊ��" << endl;
		system("pause");
		system("cls");
	}
}

void WorkManager::Clean_File()
{
	cout << "ȷ��Ҫ����ļ���" << endl;
	cout << "1,ȷ��" << endl;
	cout << "2,����" << endl;
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
		cout << "��ճɹ���"<<endl;
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
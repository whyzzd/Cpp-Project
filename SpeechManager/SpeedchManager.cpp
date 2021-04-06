#include<iostream>
using namespace std;
#include"SpeechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
}
//菜单展示
void SpeechManager::show_Menu()
{
	cout << "*******************************************"<<endl;
	cout << "**************欢迎参加演讲比赛*************" << endl;
	cout << "***************1.开始演讲比赛**************" << endl;
	cout << "***************2.查看往届记录**************" << endl;
	cout << "***************3.清空比赛记录**************" << endl;
	cout << "***************0.退出比赛程序**************" << endl;
	cout << endl;
	
}
//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次再次使用！" << endl;
	system("pause");
	exit(0);
}
//初始化容器及变量
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}
//创建12名选手
void SpeechManager::creatSpeaker()
{
	string name_Seed = "ABCDEFGHIJKL";
	string name;
	for (int i = 0; i < name_Seed.size(); i++)
	{
		name = "选手";
		name += name_Seed[i];
		Speaker speaker;
		speaker.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			speaker.m_Score[j] = 0;
		}
		
		//创建选手编号（在创建选手的时候同时创建编号）
		this->v1.push_back(10001 + i);

		//将选手编号和选手放入map容器中
		this->m_Speaker.insert(make_pair(10001 + i, speaker));


	}
	
}
//开始比赛
void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();

	this->m_Index++;

	//第二轮比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showScore();
	//4.保存分数
	this->saveRecord();

	//如果持续的使用此程序的话，每届比赛都应该重新初始化数据
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();


	cout << "本届比赛结束！" << endl;
	system("pause");
	system("cls");
}
//对选手进行抽签
void SpeechManager::speechDraw()
{
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = this->v1.begin(); it != this->v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
		cout << "---------------------------------------------" << endl;
	}
	else
	{

		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = this->v2.begin(); it != this->v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
		cout << "---------------------------------------------" << endl;
	}
	system("pause");
}
//正式比赛
void SpeechManager::speechContest()
{
	cout << "第" << this->m_Index << "轮比赛正式开始" << endl;
	cout << "----------------------------------------------" << endl;
	cout << endl;
	//创建选手比赛容器
	vector<int>v_Src;

	//创建分组容器,存放选手的均分和编号
	multimap<double, int,greater<double>>group_Map;

	//序号
	int num = 0;
	if (this->m_Index == 1)
	{
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}

	//遍历比赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委给选手打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//greater需要导入内建函数对象
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.f);
		double avg = sum / (double)d.size();

		//将比赛平均成绩放进临时的自身的map容器当中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//将比赛成绩放入分组容器当中
		group_Map.insert(make_pair(avg, *it));

		//将比赛成绩进行分组
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "组的得分情况如下：" << endl;
			//遍历分组容器
			for (multimap<double, int>::iterator it = group_Map.begin(); it != group_Map.end(); it++)
			{
				cout << "编号：" << it->second << " " << "姓名：" << this->m_Speaker[it->second].m_Name
					<< "成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}
			//取每个组的前三名
			int cont = 0;
			for (multimap<double, int>::iterator it = group_Map.begin(); it != group_Map.end(), cont < 3; it++, cont++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back(it->second);
				}
				else
				{
					this->vVictory.push_back(it->second);
				}
			}
			group_Map.clear();
		}
	}
	cout << "第" << this->m_Index << "轮比赛结束" << endl;
	cout << "----------------------------------------------" << endl;
	cout << endl;
	system("pause");
}
//显示得分
void SpeechManager::showScore()
{
	cout << "第" << this->m_Index << "晋级选手如下：" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号:" << *it << " 姓名：" << this->m_Speaker[*it].m_Name
			<< "分数：" << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//保存得分
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	//将数据写到文件当中去
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1]<<",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	//要将fileIsEmpty置为false，因为若一开始文件为空的话，保存一条记录之后，立即去查看记录，是查看不了的
	this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in);

	//文件不存在的情况
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	//文件存在为空的时候
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件存在但是为空。" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch); //将刚刚读出来的单个字符放回去

	//将读取的数据显示出来
	string data;
	//定义演讲比赛的第几届
	int index = 0;
	while (ifs >> data)//ifs>>每次读一行数据
	{
		int start=0;
		vector<string>v;//用来存放六个数据
		while (true)
		{
			//start用来记录开始的位置，pos用来记录结束的位置
			int pos = data.find(",", start);
			if (pos == -1)
			{
				//没有找到逗号了
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			start = pos + 1;
			//将结果存放到vector容器当中
			v.push_back(temp);
		}
		//将vector容器当中的数据放入，map容器当中
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	//将每届的成绩打印出来
	/*for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	{
		cout << it->first << " " << it->second[0] << " " << it->second[1] << endl;;
	}*/
}

//查看往届记录
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或者记录为空" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
		{
			cout << "第" << it->first + 1 << "届"
				<< "冠军编号：" << it->second[0] << "姓名：" << it->second[1]
				<< "亚军编号：" << it->second[2] << "姓名：" << it->second[3]
				<< "季军编号：" << it->second[4] << "姓名：" << it->second[5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);
		ofs.close();

		//注意此处和在文件中保存记录一样，都需要将数据进行初始化，以便可以在线查看
		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager()
{

}
## 文章目录

本文是对前段时间刚学习的小项目之一----职工管理系统的设计思路、具体代码的编写进行较为详细的整理。一可以对自己的C++的知识进行再进行强化，另一方面也可以为正在学习这块知识的人提供一些帮助。

[TOC]

### 一、运行环境

- windows10系统

- Visual Studio 2015

  如果想锻炼一下能力的话，也可以使用文本编辑器+编译器来运行调试代码，但是IDE还是真的香～

### 二、必要知识储备

#### 	1.VS2015的基本操作

- 新建项目或文件设置
- 项目基本的调试、运行
- 常用快捷键的使用(可自定义)
- 其它


#### 2.C++基础知识


### 三、成品展示

- #### 增加职工信息

11

- #### 显示职工信息

22

- #### 删除离职员工

33

- #### 修改职工信息

44

- #### 查找职工信息

55

- #### 排序职工信息

66

- #### 清空所有文档

77

### 四、大体结构分析

前言：本节内容可以选看，可以进一步的加深对此项目的理解

#### 1.从文件目录结构分析 

88

​	图中可以分为三块内容，分别是头文件、源文件和资源文件，头文件夹中有五个文件，分别对应的是源文件中源文件中的五个.cpp文件，源文件夹中另一个test.cpp即是整个程序的入口，另外资源文件夹中的empFile.txt则是用来存放员工的信息。

下面具体来分析一下这些文件之间的关联：

首先，职员的种类一共分为三种，老板(`boss`)、经理(`manager`)和普通员工(`employee`)，那么就对应着有三对文件(.h/.cpp),本项目中的特色就是多态的应用，这三种职员全部都是`Worker`的子类，履行着各自的职责。另外一个职工管理类`(workerManager)(.h/ .cpp)`则是统筹全局，控制着所有的员工及所有的功能。`test.cpp`是整个程序的入口，展示着界面菜单，接受用户的输入，并根据输入调用职工管理类实例化出的对象来调用相应的功能。最后empFile文件则是保存着职工的数据，包括职工的编号、姓名和部门编号，在初始化或者每一次对员工的数据有任何操作的时候，都会将数据更新到这个文件当中，这样即使程序运行结束了，数据依然可以保存，以便下一次运行进行加载。

以上以文件的目录的角度来分析这个项目，可以对大致的轮廓进行了解。



#### 2.从用户角度(需求)出发分析整个项目

99

- 从展示的主界面菜单来看，实际上整个展示菜单是通过调用函数实现的。`WorkManager wm;`实例化一个WorkManager类的对象，然后通过调用`wm.Show_Menu();`,即可显示整个展示界面。

  Show_Menu()的实现：

  ```C++
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
  ```


- 用户通过展示菜单来确定自己需要输入的选项，通过while循环来控制当每次执行完某个功能之后能够重新的显示菜单栏和等待用户输入：

  ```C++
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
  ```


- 当程序第一次加载的时候，如果想要查看内容，但是还没有进行输入，那么数据是来源于txt文件，此时不难想到：首先，需要有一个文本文件，里面存放着用户信息，如果没有那么就创建一个；其次，如果有这么一个文本文件，需要判断一下这个文件是否为空，如果为空，就可以告诉用户文件为空或者文件不存在了；如果文件不为空，那么就需要想办法把文件里面的内容读出来然后展示给用户看，通过一开始的查看功能不难想到这一步。具体代码如下：

  ```C++
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
  //开辟空间
  this->m_EmpArray = new Worker*[this->m_EmpNum];
  //将文件中的数据存到数组中
  this->init_Emp();

  //以上有不清楚的变量或者函数可以去源码中查看
  ```

  根据菜单可以发现，几乎每一个功能都会用到职工信息，都会对数据进行操作，如果每一次都是直接对文件进行增删查改，那么会造成程序非常臃肿和系统资源浪费的问题，更好的解决方式是：在一开始，文件的内容被读出来后，可以使用一个中间量将它保存起来，接着当需要用到的时候，就直接对这个中间量进行操作，如果只是查看信息，那么将所有的信息展示出来即可，如果是需要对它进行增删改之类的操作，那么可以先对这个中间量进行增删改，在操作完成之后，再将这个中间量更新到文件当中。在所有的操作当中，“删除”和“清空”是两个很特殊的操作，因为做了这两个操作之后是可能会导致中间量和txt文件为空的，从而使得在做“显示”、“修改”、“查找”、“排序”这几个操作是会有一定影响(“增加”并不受影响)，为了增加用户体验，在做这些操作的时候，都需要判断一下这个中间量是否为空，只有不为空才能继续进行下去，于是，项目中引入了一个判断文件是否为空的变量。

  对于上文所说的中间量，它的源头定义的位置是在`workManager.h`文件中，即职工的数组指针`Worker **m_EmpArray;`，第一次打开的时候为它在堆上分配的空间和将.txt的文件的数据存入里面的代码在正上面(最后两行代码)。

  对于上文所说的用来判断“文件”("中间量")是否空，使用bool类型的变量`m_FileIsEmpty;`。

- 本项目中最为核心的部分是多态，项目的文件结构在""四.1"当中已经解释说明，接下来以示意图的方式来说明Boss类、WorkerManager类、Employee类与Worker类之间的关系：

  101010

  如上图所示，Worker类是父类，由此衍生出了三个子类(Boss类、Manager类、Employee类)，在父类中定义了两个纯虚函数和三个成员变量，发生多态的条件就是有继承关系和子类重写父类的虚函数。对于三个子类来说，它们都重写了这两个纯虚函数，其中一个函数是展示职工的所有信息，另外一个是通过判断m_DeptId的值来返回对应的职位名称，多态的特点是父类的指针初始指向是不确定的，只有当运行时才能确定，如果调用时是父类的对象就调用父类的函数，如果是子类对象就调用那个的子类的对象。

  在本项目中，体现多态的地方主要有以下几处(都在WorkerManager类当中)：

  第一处：Add_Emp()函数中，根据用户输入的部门编号，确定要添加的职工，最后只需将Worker放入数组当中。

  ```C++
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
  ```

  第二处：init_Emp()函数当中，从文件中读取信息后，然后根据部门编号的值来初始化对应部门的职员。

  ```C++
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
  ```

  第三处：Mod_Emp()函数中，根据选择的部门编号，来初始化对应部门的职员

  ```C++
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
  ```

  再次提醒，如果以上有的地方看得不是很懂的话，请结合源码查看。

  

### 五、功能模块分析

用户输入相应的序号，即调用相应的功能

#### 0.退出管理程序

```
void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
```

退出程序较为简单，当用户选择0之后，进入此函数并暂停屏幕，当用户输入任何内容时就调用exit(0)退出程序。

#### 1.增加职工信息

```
void WorkManager::Add_Emp()
{
	cout << "请添加职工数量：" << endl;
	int addNum = 0;//新添加的用户的总数
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker **newSpace = new Worker*[newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
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
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
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
```



#### 2.显示职工信息

```
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
```

注意，这里首先要判断文件内容是否为空，如果为空就不需要进行下去了(这里的m_FileIsEmpty不单单是文件为空，作为中间量的员工数组也是空的哦，因此每次操作都是先对员工数组进行操作再将它保存至文件中)。

#### 3.删除离职员工

```

```



#### 4.修改职工信息

```

```



#### 5.查找职工信息

```

```



#### 6.排序职工信息

```

```



#### 7.清空所有文档

```

```



### 六、完整源码展示

### 七、反思和总结

### 八、后续可能的改进
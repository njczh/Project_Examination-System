#include "Teacher.h"
#include <iomanip>
#include <cstdio>

Teacher::Teacher(string name,string sex,string workNum,string password):Person(name,sex)
{
	this->workNum=workNum;
	this->classSum=0;
	this->stuSum=0;
	this->password=password;
}
Teacher::~Teacher()
{
	 
}

/*成员属性获取*/
string Teacher::getWorkNum()
{
	return this->workNum;
}
string Teacher::getPassword()
{
	return this->password;
}
int Teacher::getClassSum()
{
	return this->classSum;
}
string Teacher::getCourseName(int index)				//获取教师所教第index个课程的科目名称
{
	return this->courses[index].getName();
}
string Teacher::getCourseClassNum(int index)		//获取教师所教第index个课程的班级名称
{
	//return courses[in.size();
	return "aa";
}


/*成员属性修改*/
void Teacher::setWorkNum(string workNum)
{
	this->workNum=workNum;
}
void Teacher::setPassword(string password)
{
	this->password=password;
}
void Teacher::setClassSum(int classSum)
{
	this->classSum=classSum;
}
void Teacher::setAllData(string name,string sex,string workNum,int classSum,string password)		//重置教师所有基本信息
{
	this->name=name;
	this->sex=sex;
	this->workNum=workNum;
	this->classSum=classSum;
	this->password=password;
}

/*成员函数*/
void Teacher::showTeacherInfo()											//打印教师基本信息（工号、姓名、性别、所教科目）
{
	cout<<setw(7)<<this->workNum<<setw(6)<<this->name<<setw(4)<<this->sex<<"   ";
	for(int i=0;i<this->classSum;i++)
		cout<<setw(6)<<courses[i].getName();
	cout<<endl;
}
void Teacher::showTeacherAllCourses()					//打印教师下所有的课程名称（遍历课程vector，调用课程的print函数）
{
	for(int i=0;i<this->classSum;i++)
	{
		cout<<"【课程"<<i+1<<"】"<<endl;
		courses[i].showInfo();
	}
	cout<<endl;
}
//void showScore();												//打印某门课下的所有学生分数
//void showCourseOfStudents();							//打印某门课下的所有学生

//void Teacher::amendCheck()												//修改考核标准
//{
//}
//void Teacher::copy(Teacher &t)											//深层拷贝（备用）
void Teacher::addCourse(Course &c)									//增加课程（给你一个课程，然后你要把这个课程加到你的课程vector里边）
{
	courses.push_back(c);
	this->classSum++;
}
void Teacher::deleteCourse(Course &c)								//删除某一门课程（先遍历教师下的学生vector，再删除教师的课程记录）
{
	int loc;
	if(this->is_ExistCourse(c,loc))
	{
		for (int i = 0; i < students.size(); i++)
		{
			Student stu = *students[i];
			if (stu.is_ExistCourse(c))
			{
				stu.deleCourse(c);
			}
		}
		vector<Course>::iterator iter=courses.begin()+loc;
		courses.erase(iter);
		this->classSum--;
	}else
	{
		cout << this->name << "老师没有<" << c.getName() << ">这门课程" << endl;
	}
}
bool Teacher::is_ExistCourse(Course &c,int &index)				//判断该教师是否有这门课;存在，则index记录其位置，不存在，index=-1
{
	for(index=0;index<this->classSum;index++)
	{
		if(courses[index].getNumber()==c.getNumber())	return true;		// if课程编号匹配
	}
	index=-1;
	return false;
}
bool Teacher::is_ExistCourse(Course &c)				//判断该教师是否有这门课
{
	for(int i=0;i<this->classSum;i++)
	{
		if(courses[i].getNumber()==c.getNumber())	return true;		// if课程编号匹配
	}
	return false;
}

void Teacher::addStudent(Student &s)
{
	students.push_back(&s);
	this->stuSum++;
}
void Teacher::deleStudent(Student &s)
{
	int loc;			//记录学生位置
	if(this->is_ExistStudent(s,loc))
	{
		vector<Student*>::iterator it=students.begin()+loc;
		
		this->stuSum--;
		this->students.erase(it);
	}else
	{
		cout<<this->name<<"老师没有"<<s.getName()<<"学生，删除失败"<<endl;
	}
}
bool Teacher::is_ExistStudent(Student &s,int &index)				//判断该教师是否有这个学生;存在，则index记录其位置，不存在，index=-1
{
	for(index=0;index<this->students.size();index++)
	{
		if((*students[index]).getStuNum()==s.getStuNum())	return true;		// if课程编号匹配
	}
	index=-1;
	return false;
}
bool Teacher::is_ExistStudent(Student &s)				//判断该教师是否有这个学生
{
	for(int i=0;i<this->students.size();i++)
	{
		if((*students[i]).getStuNum()==s.getStuNum())	return true;		// if课程编号匹配
	}
	return false;
}

bool Teacher::addStuMark()					//添加某个学生的某门课程下的某项成绩，找不到学生、课程、考核项目时，输出提示信息，并返回false
{		//学生->课程->项目->添加成绩
	if(students.size()<=0) 
	{
		cout<<"该老师下没有任何学生！无法添加学生成绩。"<<endl;
		system("pause");
		return false;
	}
	
	cout<<setw(5)<<"编号"<<setw(10)<<"学号"<<setw(8)<<"姓名"<<setw(4)<<"性别"<<setw(14)<<"学院"
	<<setw(12)<<"专业"<<setw(12)<<"班级"<<endl;
	for(int i=0;i<students.size();i++)
	{
		cout<<setw(4)<<i+1<<".";
		students[i]->showStuInfo();
	}
	cout<<endl;

	bool flag=true;			//用于判断输入是否合理
	string answer;
	string NO_len;
	do{
		cout<<"请输入需要添加成绩学生的编号：";
		cin>>answer;
		char temp_num[20];			//将学生人数(int)转化为(string)的NO_Len
		sprintf_s(temp_num,"%d",students.size());
		NO_len=temp_num;
		if( ! (answer>="1" && answer<= NO_len ) )		
		{
			cout<<"请检查你的输入！"<<endl;
			system("pause");
			flag=0;
		}else flag=1;
	}while(flag==0);
	int index1= atoi(answer.c_str()) -1;		//编号-1=所在位置
	
	if(students[index1]->courses.size()<=0)
	{
		cout<<students[index1]->getName()<<"没有参加任何课程！无法添加成绩。"<<endl;
		system("pause");
		return false;
	}

	cout<<setw(6)<<"编号"<<setw(12)<<"课程编号"<<setw(15)<<"课程名称"<<endl;
	students[index1]->showAllCourses();			//打印index1号学生的所有课程
	flag=true;			//初始化flag
	do{
		cout<<"请输入"<<students[index1]->getName()<<"需要添加成绩的课程编号：";
		cin>>answer;
		char temp_num[20];
		sprintf_s(temp_num,"%d",students[index1]->getClassSum());
		NO_len=temp_num;
		if(!(answer>="1"&&answer<=NO_len))		//+1+'0'使编号从数字转为字符串，和answer进行比较
		{
			cout<<"请检查你的输入！"<<endl;
			system("pause");
			flag=0;
		}else flag=1;
	}while(flag==0);

	int index2=atoi(answer.c_str())-1;			//老师包含学生 学生包含课程 index1为学生下标  index2为课程下标
	if(students[index1]->courses[index2].getCheckNum()<=0)			
	{
		cout<<students[index1]->getName()<<"学生在"<<students[index1]->courses[index2].getName()<<"课中没有考核项目！"
			<<"无法添加成绩。"<<endl;
		system("pause");
		return false;
	}
	
	students[index1]->courses[index2].showAllScore();
	flag=true;			//初始化flag
	do{
		cout<<"请输入"<<students[index1]->getName()<<"需要添加"
			<<students[index1]->courses[index2].getName()<<"成绩的项目编号：";
		cin>>answer;
		char temp_num[20];
		sprintf_s(temp_num,"%d",students[index1]->courses[index2].getCheckNum());
		NO_len=temp_num;
		if(!(answer>="1"&&answer<=NO_len))		//+1+'0'使编号从数字转为字符串，和answer进行比较
		{
			cout<<"请检查你的输入！"<<endl;
			system("pasue");
			flag=0;
		}else flag=1;
	}while(flag==0);
	int index3= atoi(answer.c_str()) -1;		//index为某学生某门课下的第 index3 个考核项目

	double inScore;
	while(1)
	{
		cout<<"请输入你的成绩：";
		cin>>inScore;
		if(inScore<=100&&inScore>=0) break;
		else
		{
			cout<<"请检查你的输入。按任意键后，重新输入你的成绩"<<endl;
			system("pause");
		}
	}
	students[index1]->courses[index2].enrollScore(index3,inScore);
	cout<<"——成绩录入成功——"<<endl;
	students[index1]->courses[index2].showAllScore();
	system("pause");
	return true;
}

bool Teacher::is_IDPass(string password)							//密码是否验证通过
{
	if(this->password==password) return true;
	else return false;
}
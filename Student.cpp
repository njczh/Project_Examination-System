#include "Student.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Student::Student(string name,string sex,string stuNum,string stuInstitude,string stuMajor,
	string stuClass,string password):Person(name,sex)
{
	this->stuNum=stuNum;
	this->stuInstitude=stuInstitude;
	this->stuMajor=stuMajor;
	this->stuClass=stuClass;
	this->classSum=0;
	this->password=password;
}

/*获取属性信息*/
string Student::getStuNum()
{
	return this->stuNum;
}
int Student::getClassSum()
{
	return this->classSum;
}
string Student::getPassword()
{
	return this->password;
}
string Student::getStuInstitude()
{
	return this->stuInstitude;
}
string Student::getStuMajor()
{
	return this->stuMajor;
}
string Student::getStuClass()
{
	return this->stuClass;
}

/*设置属性信息*/
void Student::setStuNum(string newNum)
{
	this->stuNum=newNum;
}
void Student::setClassSum(int newNum)
{
	this->classSum=newNum;
}
void Student::setPassword(string newPassword)
{
	this->password=newPassword;
}
void Student::setStuInstitude(string newInstitude)
{
	this->stuInstitude=newInstitude;
}
void Student::setStuMajor(string newMajor)
{
	this->stuMajor=newMajor;
}
void Student::setStuClass(string newClass)
{
	this->stuClass=newClass;
}
void Student::setAllData(string name,string sex,string stuNum,string stuInstitude,string stuMajor,string stuClass,string password)
{
	this->name=name;
	this->sex=sex;
	this->stuNum=stuNum;
	this->stuInstitude=stuInstitude;
	this->stuMajor=stuMajor;
	this->stuClass=stuClass;
	this->password=password;
	this->classSum=0;
}

/*成员函数*/
void Student::showStuInfo()			//输出学生个人信息（学号、姓名、性别、学院、专业、班级）
{
	cout<<setw(10)<<this->stuNum<<setw(8)<<this->name<<setw(6)<<this->sex<<setw(14)<<this->stuInstitude
		<<setw(12)<<this->stuMajor<<setw(12)<<this->stuClass<<endl;
}
void Student::showAllCourses()				//按行输出每门课程的课程编号和课程名称
{
	for(int i=0;i<this->classSum;i++)
	{
		cout<<setw(5)<<i+1<<"."<<setw(12)<<this->courses[i].getNumber()<<setw(15)<<this->courses[i].getName()<<endl;
	}
	cout<<endl;
}
void Student::addCourse(Course &c)						//添加课程
{
	this->courses.push_back(c);
	this->classSum++;
}
void Student::deleCourse(Course &c)					//删除课程
{
	int loc;
	if(this->is_ExistCourse(c,loc))			//判断该学生是否存在这门课程，loc记录这门课程在vector中的位置，不存在则loc=-1;
	{
		vector<Course>::iterator it=courses.begin()+loc;
		courses.erase(it);
		this->classSum--;
	}else
	{
		cout<<this->name<<"没有<"<<c.getName()<<">这门课程"<<endl;
	}
}
bool Student::is_ExistCourse(Course &c,int &index)				//判断该学生是否有这门课;存在，则index记录其位置，不存在，index=-1
{
	for(index=0;index<this->classSum;index++)
	{
		if(courses[index].getNumber()==c.getNumber())	return true;		// if课程编号匹配
	}
	index=-1;
	return false;
}
bool Student::is_ExistCourse(Course &c)				//判断该学生是否有这门课
{
	for(int i=0;i<this->classSum;i++)
	{
		if(courses[i].getNumber()==c.getNumber())	return true;		// if课程编号匹配
	}
	return false;
}
bool Student::is_IDPass(string password)					//密码是否验证通过
{
	if(this->password==password) return true;
	else return false;
}

/****************************CZH添****************************/
void Student::showAllCoursesScore()
{
	if (classSum == 0) {cout << "暂无课程" << endl; return;}
	cout << setw(6) << "序号" << setw(12) << "课程编号" << setw(15) << "课程名称" << setw(6) << "得分" << endl
		<< "----------------------------------------------------------" << endl;
	for (int i = 0; i < this->classSum; i++)
	{
		cout << setw(5) << i + 1 << "." << setw(12) << this->courses[i].getNumber() << setw(15) << this->courses[i].getName() <<setw(6)<<courses[i].getScore()<< endl;
	}
	cout << "----------------------------------------------------------" << endl;
}
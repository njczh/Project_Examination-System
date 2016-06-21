#pragma once
#include <iostream>
#include "Person.h"
#include "Course.h"
#include <vector>
using namespace std;

class Student: public Person		//继承拥有name、sex属性
{
private:
	string stuNum;							//学号
	int classSum;							//课程总数
	string stuInstitude;					//学院
	string stuMajor;						//专业
	string stuClass;							//班级
	string password;						//登录密码

	
public:
	vector<Course> courses;			//学生需要上的课程
	/*构造函数*/
	Student(string name="Unknown",string sex="Sex",string stuNum="150101",string stuInstitude="Unknown",string stuMajor="Unknown",
		string stuClass="Unknown",string password="150000");
	//~Student();

	/*获取属性信息*/
	string getStuNum();
	int getClassSum();
	string getPassword();
	string getStuInstitude();
	string getStuMajor();
	string getStuClass();

	/*设置属性信息*/
	void setStuNum(string newNum);
	void setClassSum(int newNum);
	void setPassword(string newPassword);
	void setStuInstitude(string newInstitude);
	void setStuMajor(string newMajor);
	void setStuClass(string newClass);
	void setAllData(string name,string sex,string stuNum,string stuInstitude,string stuMajor,string stuClass,string password);
	
	/*成员函数*/
	void showStuInfo();									//输出学生个人信息（学号、姓名、性别、学院、专业、班级）
	void showAllCourses();								//输出所有课程名称

	bool is_ExistCourse(Course &c,int& index);	//判断该学生是否有这门课; 若存在，则index记录其位置，不存在则index=-1	
	bool is_ExistCourse(Course &c);					//判断该学生是否有这门课（不记录课程位置）
	bool is_IDPass(string password);				//密码是否验证通过
	void addCourse(Course &c);						//添加课程
	void deleCourse(Course &c);						//删除课程

	void deleCourse(int i)
	{
		deleCourse(courses[i]);
	}

	bool is_CourseEmpty()
	{
		if (courses.empty()) return true;
		else return false;
	}

	void showAllCoursesScore();
};
#pragma once
#include <iostream>
#include "Person.h"
#include "Student.h"
#include "Course.h"
#include <vector>
using namespace std;

class Teacher: public Person			//继承拥有name、sex属性
{
private:
	string workNum;									//工号
	int classSum;										//课程数量
	int stuSum;											//学生数量
	string password;									//登录密码
	vector<Course> courses;						//课程数组
	vector<Student*> students;					//学生数组
public:

	/*构造函数*/
	Teacher(string name="Unknown",string sex="Unknown",string workNum="100100",string password="000000");
	~Teacher();
	
	/*成员属性获取*/
	string getWorkNum();
	string getPassword();
	int getClassSum();
	string getCourseName(int index);				//获取教师所教第index个课程的科目名称
	string getCourseClassNum(int index);		//获取教师所教第index个课程的班级名称

	/*成员属性修改*/
	void setWorkNum(string workNum);
	void setPassword(string password);
	void setClassSum(int sum);
	void setAllData(string name,string sex,string workNum,int classSum,string password);		//重置教师所有基本信息

	/*成员函数*/
	void showTeacherInfo();										//打印教师基本信息（工号、姓名、性别、所教科目）
	void showTeacherAllCourses();								//打印教师下所有的课程名称（遍历课程vector，调用课程的print函数）
	void showScore();													//打印某门课下的所有学生分数
	
	void addCourse(Course &c);									//增加课程
	void deleteCourse(Course &c);								//删除某一门课程
	bool is_ExistCourse(Course &c,int &index);			//判断是否存在课程c，若存在，则index记录该位置，若不存在则index=-1;
	bool is_ExistCourse(Course &c);							//判断是否存在课程c（不记录课程位置）

	void addStudent(Student &s);								//增加一名学生
	void deleStudent(Student &s);								//删除一名学生
	bool is_ExistStudent(Student &s);							//判断是否存在学生s（不记录课程位置）
	bool is_ExistStudent(Student &s,int &index);			//判断是否存在学生s，若存在，则index记录该位置，若不存在则index=-1;

	bool addStuMark();												//添加某个学生的某门课程下的某项成绩，找不到学生、课程、考核项目时，输出提示信息，并返回false

	bool is_IDPass(string password);							//密码是否验证通过
	
	//void showCourseOfStudents();							//打印某门课下的所有学生
	/*
	void amendCheck();												//修改考核标准
	void copy(Teacher &t);											//深层拷贝（备用）
	*/

	//********************************************CZH改

	bool is_CourseEmpty()
	{
		if (courses.empty()) return true;
		else return false;
	}

	void showCourseInfo(int n)
	{
		courses[n - 1].showInfo();
	}

	void createCheck(int n,string nm)
	{
		courses[n - 1].createCheck(nm);
	}

	void delCheck(int n, int index)
	{
		courses[n - 1].deleteCheck(index);
	}

	void resetScoreRate(int n)
	{
		courses[n - 1].resetScoreRate();
	}

};
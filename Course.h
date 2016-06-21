#ifndef COURSE_H_
#define COURES_H_
#pragma once
#include <iostream>
#include <string>
#include "Check.h"

class Course {
private:
	// number是该门课的编号，共9位，前三位是科目编号，后6位是任课教师编号
	std::string number;
	std::string name;
	Check check;
	int time;
	std::string classID, teacherID;
public:
	// courseID是科目编号，teacherID是教师编号
	Course();
	Course(std::string nm, int t, std::string courseID, std::string teacherID);
	~Course() {}

	// 创建一种考核
	void createCheck(std::string nm);
	// 删除一种考核
	void deleteCheck(int index);
	// 记录成绩
	void enrollScore(int index, double sc);
	// 删除成绩（该项成绩将会被设置为0）
	void deleteScore(int index, int n);
	// 重置成绩
	void resetScore(int index, int n, double sc);
	// 重置各考核所占总分比例
	void resetScoreRate();
	// 显示一种考核情况
	void showCheck(int index);
	// 显示该课程的分数详情
	void showAllScore();
	// 获得该课程的总分
	double getScore();
	// 显示该门课的基本信息
	void showInfo();

	std::string getName();
	void setName(std::string nm);
	int getTime();
	void setTime(int t);
	std::string getNumber();
	void setNumber(std::string courseID, std::string teacherID);
	int getCheckNum();
	std::string getTeacherID();
	std::string getClassID();
	std::string getCheckName(int index);
	double getCheckRate(int index);
	void initialCheck(std::string name[], double rate[], int size);
	double getOneScore(int index, int cindex);
	int getOneScoreNum(int index);
	void insertScore(int index, double sc);
};

#endif // COURSE_H_

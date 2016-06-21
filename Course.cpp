#include "Course.h"

Course::Course()
{
	name = "Unknown";
	time = 0;
	number = "000000000";
	classID = "000";
	teacherID = "000000";
}

Course::Course(std::string nm = "<unknown>", int t = 0, std::string courseID = "000", std::string teacherID = "000000")
{
	name = nm;
	time = t;
	number = courseID + teacherID;
	classID = courseID;
	this->teacherID = teacherID;
}

void Course::createCheck(std::string nm)
{
	check.createCheck(nm);
}

void Course::deleteCheck(int index)
{
	check.deleteCheck(index);
}

void Course::enrollScore(int index, double sc)
{
	check.enrollScore(index, sc);
}

void Course::deleteScore(int index, int n)
{
	check.deleteScore(index, n);
}

void Course::resetScore(int index, int n, double sc)
{
	check.resetScore(index, n, sc);
}

void Course::resetScoreRate()
{
	check.resetRate();
}

void Course::showCheck(int index)
{
	check.showCheck(index);
}

void Course::showAllScore()
{
	check.showTable();
}

double Course::getScore()
{
	return check.getAllScore();
}

void Course::showInfo()
{
	std::cout << "------------------------------------------------\n";
	std::cout << "课程名称:" << name << " 课程编号:" << number << " 课时:" << time << std::endl;
	std::cout << "------------------------------------------------\n";
	std::cout << "                评分标准\n";
	std::cout << "------------------------------------------------\n";
	std::cout << std::left << std::setw(4) << "序号" << std::setw(15) << "名称" << std::right << std::endl;
	std::cout << "------------------------------------------------\n";
	check.showTableInfo();
	std::cout << "------------------------------------------------\n";
}

std::string Course::getName()
{
	return name;
}

void Course::setName(std::string nm)
{
	name = nm;
}

int Course::getTime()
{
	return time;
}

void Course::setTime(int t)
{
	time = t;
}

std::string Course::getNumber()
{
	return number;
}

void Course::setNumber(std::string courseID, std::string teacherID)
{
	number = courseID + teacherID;
	classID = courseID;
	this->teacherID = teacherID;
}

int Course::getCheckNum()
{
	return this->check.getCheckNum();
}

std::string Course::getTeacherID()
{
	return teacherID;
}

std::string Course::getClassID()
{
	return classID;
}

std::string Course::getCheckName(int index)
{
	return check.getCheckName(index);
}

double Course::getCheckRate(int index)
{
	return check.getCheckRate(index);
}

void Course::initialCheck(std::string name[], double rate[], int size)
{
	check.initialCheck(name, rate, size);
}

double Course::getOneScore(int index, int cindex)
{
	return check.getScore(index, cindex);
}

int Course::getOneScoreNum(int index)
{
	return check.getScoreNum(index);
}

void Course::insertScore(int index, double sc)
{
	check.insertScore(index, sc);
}


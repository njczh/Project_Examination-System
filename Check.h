#ifndef CHECK_H_
#define CHECK_H_

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Check {
private:
	struct type {
		std::string name;
		double rate;
		std::vector<double> score;
	};
	std::vector<type> table;
public:
	Check() {}
	~Check() {}
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
	void resetRate();
	// 显示一种考核情况
	void showCheck(int index);
	// 显示考核基本信息
	void showTableInfo();
	// 显示所有考核的情况
	void showTable();
	// 获得总分
	double getAllScore();
	int getCheckNum();		//获取考核项目的数量
private:
	bool checkRate(std::vector<double> temp);
	void operateScore(int index, int n, double sc = 0);
	bool findIndexPos(int index, std::vector<type>::iterator &it);
	void printCheck(std::vector<type>::iterator it);
};

#endif // CHECK_H_

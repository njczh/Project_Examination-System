#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
	string name;
	string sex;
public:
	/*构造函数*/
	Person(string name="Unknown",string sex="Unknown");
	
	/*获取成员属性*/
	string getName();
	string getSex();

	/*修改成员属性*/
	void setName(string newName);
	void setSex(string newSex);
};
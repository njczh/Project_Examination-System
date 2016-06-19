#include "Person.h"
#include <string>

/*构造函数*/
Person::Person(string name,string sex)
{
	this->name=name;
	this->sex=sex;
}

/*获取属性信息*/
string Person::getName()
{
	return name;
}
string Person::getSex()
{
	return sex;
}

/*设置属性信息*/
void Person::setName(string newName)
{
	this->name=newName;
}
void Person::setSex(string newSex)
{
	this->sex=newSex;
}
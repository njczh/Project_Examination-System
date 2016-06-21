#include "Check.h"
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include "printMenu.h"
#include <fstream>
#include <string>
#include <vector>

vector<Course> myCourses;
vector<Student> myStudents;
vector<Teacher> myTeachers;

void GoToXY(int x, int y)
{
	COORD pos = { x,y };                 //设置光标位置        
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);    // 获取标准输出设备句柄       
	SetConsoleCursorPosition(hOut, pos);      //两个参数分别是指定哪个窗体，什么位置？ 
}

void courseManagementMenu_1()/*课程信息管理——1.添加课程*/
{		
	/*
		【沐】改：（整体思路）先输入老师编号，然后验证老师存在性，不存在，则不可添加，退出；
		存在，则继续输入课程信息。
		而不是所有信息输入后，才被告知没有老师的存在，
		原代码这里的输入顺序更像是创建一个没有关联到老师的课程单体
	*/
	system("cls");
	cout << "正在进行【添加课程】，请按照提示操作。" << endl;

	Course newCourse;
	string newName;
	string newCourseID, newTeacherID;
	int newTime;
	bool flag = false;

	cout << "请输入需要添加课程的教师的工号：";
	cin >> newTeacherID;
	for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
	{
		if (iter->getWorkNum() == newTeacherID)
		{
			iter->addCourse(newCourse);
			flag = true;
		}
	}
	if (!flag) 
	{ 
		cout << endl<<"添加失败！ Error:没有该工号的教师！" << endl<<endl; 
		return; 
	}
	cout << "请输入课程名：";
	cin >> newName;
	newCourse.setName(newName);

	cout << "请输入3位'课程'编号：";
	cin >> newCourseID;
	
	newCourse.setNumber(newCourseID, newTeacherID);

	cout << "请输入课时数：";
	cin >> newTime;

	newCourse.setTime(newTime);

	cout << "添加完成！" << endl;
	myCourses.push_back(newCourse);
}
void courseManagementMenu_2()/*课程信息管理——2.删除课程*/
{
	std::system("cls");
	if (!myCourses.empty()) {
		std::cout << "正在进行【删除课程】，请按照提示操作。" << endl;
		for (auto iter = myCourses.begin(); iter != myCourses.end(); ++iter)
			(*iter).showInfo();
	}
	else {
		std::cout << "抱歉！暂无可操作的课程！" << endl; return;
	}

	string delNumber;
	std::cout << "请输入课程编号：" ;
	std::cin >> delNumber;
	bool flag = false;
	for (auto iter = myCourses.begin(); iter != myCourses.end(); ++iter)
	{
		if (delNumber == (*iter).getNumber())
		{
			std::system("cls");
			flag = true;
			(*iter).showInfo();
			while(1)
			{
				bool pd=false;			//判断修改操作是否合法
				char confirm;
				std::cout << "是否确认删除？"<<endl<<"  0.No"<<endl<<"  1.Yes " << endl;
				std::cin >> confirm;
				std::cin.ignore(1024,'\n');
				switch(confirm)
				{
				case '1':
					{
						for (auto iter2 = myTeachers.begin(); iter2 != myTeachers.end(); ++iter2)
						{
							if (iter2->getWorkNum() == iter->getNumber().substr(6)) {
								iter2->deleteCourse(*iter);//删除老师某一门课
								break;
							}
						}
						for (auto iter2 = myStudents.begin(); iter2 != myStudents.end(); iter2++)
						{ // 逐个学生进行遍历
							for (auto iter3 = iter2->courses.begin(); iter3 != iter2->courses.end(); iter3++)
							{
								if (iter3->getNumber() == iter->getNumber()) 
								{
									iter2->courses.erase(iter3); // 删除学生某一门课
									break;
								}
							}
						}
						myCourses.erase(iter);
						std::cout << "删除成功！" << endl<<endl;
						pd=1;
						break;
					}
				case '0':
					{
						std::cout << "已取消操作！" << endl<<endl;
						pd=1;
						break;
					}
				default:
					{
						std::cout<<"您的输入不合法！请重新确认！"<<endl<<endl;
						break;
					}
				}
				if(pd) break;			//修改操作合法，跳出while循环
				
			}
			break;		//在遍历中找到了这门唯一的课，进行一系列操作，操作完后就跳出
		}
	}
	if (!flag) std::cout << "没有该课程！请确认课程编号!" << endl;
}
void courseManagementMenu_3()
{
	system("cls");
	if (!myCourses.empty())
	{
		cout << "正在进行【修改课程信息】，请按照提示操作。" << endl;
		for (auto iter = myCourses.begin(); iter != myCourses.end(); ++iter)
		{
			(*iter).showInfo();
		}
	}
	else {
		cout << "抱歉！暂无课程！" << endl; 
		return;
	}
	string number;
	int choice_2;
	cout << "请输入想要修改课程信息的编号(9位)：";
	cin >> number;
	auto iter = myCourses.begin();
	while (iter != myCourses.end())
	{
		if ((*iter).getNumber() == number)
		{
			system("cls");
			cout << "正在修改《" << (*iter).getName() << "》，编号：" << iter->getNumber() << endl
				<< "1.修改课程名称" << endl
				<< "2.修改课程课时" << endl
				<< "3.修改课程编号" << endl
				<< "4.取消修改" << endl
				<< "请输入修改项目序号：";
			cin >> choice_2;
			switch (choice_2)
			{
			case 1:
			{
				string newName;
				cout << "请输入新名称：";
				cin >> newName;
				(*iter).setName(newName);
				cout << endl<<"修改成功！新名称为 " << (*iter).getName() << endl<<endl;
				break;
			}
			case 2:
			{
				int newTime;
				cout << "请输入新课时数：";
				cin >> newTime;
				(*iter).setTime(newTime);
				cout <<endl<< "修改成功！新课时数为 " << (*iter).getTime() << endl<<endl;
				break;
			}
			case 3:
			{
				string newCN;
				cout << "请输入3位课程编号：";
				cin >> newCN;

				string newTN;
				cout << "请输入6位教师编号：";
				cin >> newTN;

				iter->setNumber(newCN, newTN);
				cout << endl<<"修改成功！新编号为 " << (*iter).getNumber() << endl<<endl;
				break;
			}
			case 4:
				cout<<endl<<"已取消修改！"<<endl<<endl;
				break;
			}
			break;
		}
		++iter;
	}
	if (iter == myCourses.end()) cout << "————没有该课程！请确认课程编号!————" << endl<<endl;
}
void courseManagementMenu_4()
{
	if (!myCourses.empty())
		for (auto iter = myCourses.begin(); iter != myCourses.end(); ++iter)
			(*iter).showInfo();
	else cout << "抱歉！暂无课程！" << endl;
}
void courseManagementMenu()
{
	char choice;
	printCourseManagementMenu();
	do
	{
		cin >> choice;
		cin.ignore(1024, '\n');
		switch (choice)
		{
		case '1'://添加课程
			courseManagementMenu_1();
			break;
		case '2'://删除课程
			courseManagementMenu_2();
			break;
		case '3'://修改课程信息
			courseManagementMenu_3();
		    break;
		case '4'://列出课程信息
			courseManagementMenu_4();
		    break;
		case '5'://返回上级菜单
			continue;
		default:
			cout << "输入有误，请重新输入（1/2/3/4/5）: ";
			continue;
		}
		std::system("pause");
		printCourseManagementMenu();
	} while (choice != '5');
}

void teacherCourseChoose(int i, int &n)
{
	myTeachers[i].showTeacherAllCourses();
	cout << "请输入课程序号：";
	cin >> n;
}
void teacherModifyCourseCheck(int i)
{
	char choice;
	printTeacherModifyCourseCheck();
	do
	{
		cin >> choice;
		cin.ignore(1024, '\n');
		switch (choice)
		{
		case '1':
			myTeachers[i].showTeacherAllCourses();
			break;
		case '2':
		{
			myTeachers[i].showTeacherAllCourses();
			cout << "请选择课程（方括号内的序号）：";
			int No_;
			cin >> No_;
			if (myTeachers[i].ofr(No_)) break;
			cout << "\n正在进行【增加考核项目】，请按提示进行操作！" << endl;
			myTeachers[i].showCourseInfo(No_);
			cout << "请输入新考核项目的名字：";
			string nm;
			cin >> nm;
			myTeachers[i].createCheck(No_, nm);
			cout << "增加完成！" << endl;
			break;
		}
		case '3':
		{
			myTeachers[i].showTeacherAllCourses();
			cout << "请输入课程编号：";
			int No_;
			cin >> No_;
			if (myTeachers[i].ofr(No_)) break;
			cout << "\n正在进行【删除考核项目】，请按提示进行操作！" << endl;
			myTeachers[i].showCourseInfo(No_);
			cout << "请输入想删除考核项目的序号：";
			int index;
			cin >> index;
			myTeachers[i].delCheck(No_, index - 1);
			break;
		}
		case '4':
		{
			myTeachers[i].showTeacherAllCourses();
			cout << "请输入课程编号：";
			int No_;
			cin >> No_;
			if (myTeachers[i].ofr(No_)) break;
			cout << "\n正在进行【修改考核比例】，请按提示进行操作！" << endl;
			myTeachers[i].showCourseInfo(No_);
			myTeachers[i].resetScoreRate(No_);
			break;
		}
		case '5':
			break;
		default:
			cout << "输入有误，请重新输入（1/2/3/4/5）: ";
			continue;
		}
		if (choice != '5') std::system("pause");
		printTeacherModifyCourseCheck();
	} while (choice != '5');
}
void teacherManagementMenu_1()
{
	system("cls");
	cout << "正在进行【添加教师】，请按照提示操作。" << endl;

	Teacher newTeacher;
	string newName;
	string newSex;
	string newTeacherID;

	cout << "请输入教师工号：";
	cin >> newTeacherID;

	cout << "请输入教师姓名：";
	cin >> newName;

	do{
		cout << "请输入性别（男/女）：";
		cin >> newSex;
		if (!(newSex == "男" || newSex == "女")) cout << "输入有误，请重新输入！" << endl;
	} while (!(newSex == "男" || newSex == "女"));

	newTeacher.setAllData(newName, newSex, newTeacherID, 0, "000000");
	cout << "添加完成！初始密码为“000000”" << endl;
	myTeachers.push_back(newTeacher);

}
void teacherManagementMenu_2()
{
	system("cls");
	if (!myTeachers.empty()) {
		cout << "正在进行【删除教师】，请按照提示操作。" << endl;
		for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
			(*iter).showTeacherInfo();
	}
	else {
		cout << endl<<"抱歉！暂无可操作的教师！" << endl<<endl; return;
	}

	string delNumber;
	cout << "请输入教师编号：" << endl;
	cin >> delNumber;
	bool flag = false;
	for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
		if (delNumber == (*iter).getWorkNum())
		{
			flag = true;
			(*iter).showTeacherInfo();
			bool confirm;
			cout << "确认删除？（ 0.No/1.Yes ）" << endl;
			cin >> confirm;
			if (confirm) {
				myTeachers.erase(iter);
				cout << "删除成功！" << endl;
				break;
			}
			else cout << "已取消操作！" << endl;
			break;
		}
	if (!flag) cout << "没有该教师！请确认教师工号!" << endl;
}
void teacherManagementMenu_3()
{
	system("cls");
	if (!myTeachers.empty())
	{
		cout << "正在进行【查找教师】，请按照提示操作。" << endl;

		char choice2;
		cout << "\t1.根据教师工号" << endl
			<< "\t2.根据教师姓名" << endl
			<< "请输入你的选择：";
		cin >> choice2;
		cin.ignore(1024, '\n');
		switch (choice2)
		{
		case '1':
		{
			string findNum;
			cout << "请输入教师工号：";
			cin >> findNum;
			bool flag = false;
			for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
			{

				if (iter->getWorkNum() == findNum) {
					iter->showTeacherInfo();
					flag = true;
					break;
				}
			}
			if (!flag) cout << "查无此人！请确认教师工号！" << endl;
			break;
		}

		case '2':
		{
			string findName;
			bool flag = false;//查无此人
			cout << "请输入教师姓名：";
			cin >> findName;
			for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
			{
				if (iter->getName() == findName) {
					iter->showTeacherInfo();
					flag = true;
					break;
				}
			}
			if (!flag) cout << "查无此人！请确认教师姓名！" << endl;
		}
		break;
		default: cout << "输入有误！请确认你的选择！" << endl;
		}
	}
	else cout << "抱歉！暂无教师！" << endl;

}
void teacherManagementMenu_4()
{
	system("cls");
	if (!myTeachers.empty()) {
		cout << "------------------------------------------------------------------" << endl
			<< setw(8) << "工号" << setw(8) << "姓名" << setw(6) << "性别" << "   授课科目" << endl
			<< "------------------------------------------------------------------" << endl;
		for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
			(*iter).showTeacherInfo();
		cout << "------------------------------------------------------------------" << endl;
	}
	else {
		cout << "抱歉！暂无教师！" << endl; return;
	}
	string number;
	int choice_2;
	cout << "请输入想要修改教师信息的编号：";
	cin >> number;
	auto iter = myTeachers.begin();
	while (iter != myTeachers.end())
	{
		if ((*iter).getWorkNum() == number)
		{
			cout << "正在修改\"" << (*iter).getName() << "\"，编号：" << iter->getWorkNum() << endl
				<< "\t1.修改名字" << endl
				<< "\t2.修改性别" << endl
				<< "\t3.修改工号" << endl
				<< "\t4.修改授课科目" << endl
				<< "\t5.修改考核" << endl
				<< "\t5.修改密码" << endl
				<< "\t6.取消" << endl
				<< "请输入修改项目序号：";
			cin >> choice_2;
			switch (choice_2)
			{
			case 1:
			{
				string newName;
				cout << "请输入新名字：";
				cin >> newName;
				(*iter).setName(newName);
				cout << "修改成功！新名称为 " << (*iter).getName() << endl;
				break;
			}
			case 2:
			{
				string newSex;
				do
				{
					cout << "请输入性别（男/女）：";
					cin >> newSex;
					if (!(newSex == "男" || newSex == "女")) cout << "输入有误，请重新输入！" << endl;
				} while (!(newSex == "男" || newSex == "女"));
				(*iter).setSex(newSex);
				cout << "修改成功！";
				break;
			}
			case 3:
			{
				string newNum;
				cout << "请输入新工号：";
				cin >> newNum;
				iter->setWorkNum(newNum);
				cout << "修改成功！当前工号为 " << (*iter).getWorkNum() << endl;
				break;
			}
			case 4:
			{
				int choice_3;
				cout << endl
					<< "=====已选择【修改授课科目】=====" << endl
					<< "1.增加课程" << endl
					<< "2.删除课程" << endl
					<< "3.取消" << endl
					<< "请输入你的选择：";
				cin >> choice_3;
				switch (choice_3)
				{
				case 1:
				{
					string newCourse;
					cout << "请输入欲添加课程的编号：";
					cin >> newCourse;
					auto i = myCourses.begin();
					for (i; i != myCourses.end(); ++i)
					{
						if (i->getNumber() == newCourse) (*iter).addCourse((*i));
						cout << "添加成功！" << endl;
						break;
					}
					if (i == myCourses.end()) cout << "未找到该课程！请确认课程编号！" << endl;
					break;
				}
				case 2:
				{
					iter->showTeacherAllCourses();
					string delCourse;
					cout << "请输入欲删除课程的编号：";
					cin >> delCourse;
					auto i = myCourses.begin();
					for (i; i != myCourses.end(); ++i)
					{
						if (i->getNumber() == delCourse) (*iter).deleteCourse((*i));
						cout << "删除成功！" << endl;
						break;
					}
					if (i == myCourses.end()) cout << "未找到该课程！请确认课程编号！" << endl;
					break;
				}
				case 3:
					break;
				default:
					cout << "输入有误！请确认你的选择！" << endl;
					break;
				}
				break;
			}

			case 5:
				teacherModifyCourseCheck(iter - myTeachers.begin());

			case 6:
			{
				string newPW;
				string newPW2;
				cout << "请输入新密码：";
				cin >> newPW;
				cout << "请再次输入密码：";
				cin >> newPW2;
				if (newPW == newPW2)
				{
					iter->setPassword(newPW);
					cout << "修改成功！" << endl;
				}
				else cout << "修改失败！两次密码不匹配，请重试！" << endl;
				break;
			}
			case 7:
				cout << "已取消！" << endl;
				break;
			}
			break;
		}
		++iter;
	}
	if (iter == myTeachers.end()) cout << "没有该教师！请确认教师工号!" << endl;

}
void teacherManagementMenu_5()
{
	if (!myTeachers.empty())
	{
		cout << "------------------------------------------------------------------" << endl
			<< setw(8) << "工号" << setw(8) << "姓名" << setw(6) << "性别" << "   授课科目" << endl
			<< "------------------------------------------------------------------" << endl;
		for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
			(*iter).showTeacherInfo();
		cout << "------------------------------------------------------------------" << endl;
	}
	else cout << "抱歉！暂无教师！" << endl;
}
void teacherManagementMenu()
{
	char choice;
	printTeacherManagementMenu();
	do
	{
		cin >> choice;
		cin.ignore(1024, '\n');
		switch (choice)
		{
		case '1':
			teacherManagementMenu_1();
			break;
		case '2':
			teacherManagementMenu_2();
			break;
		case '3':
			teacherManagementMenu_3();
			break;
		case '4':
			teacherManagementMenu_4();
			break;
		case '5':
			teacherManagementMenu_5();
			break;
		case '6':
			continue;
		}
		std::system("pause");
		printTeacherManagementMenu();
	} while (choice != '6');
}
void teacherMenu(int i)
{
	char choice;
	printTeacherMenu(i);
	do
	{
		cin >> choice;
		cin.ignore(1024, '\n');
		switch (choice)
		{
		case '1':
			myTeachers[i].addStuMark();
			break;
		/*
		{
			
			if (myTeachers[i].students.empty()) {cout << "没有学生！" << endl; break;}
			if (myTeachers[i].is_CourseEmpty()) { cout << "暂无课程！"<<endl; break; }
			int No_ = 1;
			teacherCourseChoose(i, n);
			for(auto iter=myTeachers[i].students.begin();iter!= myTeachers[i].students.end();++iter,++No_)
				cout <<No_+1<<"\t"<< iter->getName() << endl;
			cout << "请输入学生序号：";
			cin >> No_;
			int temp = myTeachers[i].students[No_ - 1].is_ExistCourse(myTeachers[i].courses[n - 1]);
			myTeachers[i].students[No_ - 1].courses[temp].showAllScore();//显示老师对象下该学生的所有考核及成绩
			string na;
			double score;
			cout << "请输入考核项目名：";
			cin >> na;
			cout << "请输入分数：";
			cin >> score;
			myTeachers[i].students[No_ - 1].courses[temp].enrollScore(na,score);//只是更改老师对象下的该学生信息，还需要将此信息拷贝给这个学生本人！
			for (auto stu : myStudents)
				if (stu.getStuNum() == myTeachers[i].students[No_ - 1].getStuNum())
				{
					stu = myTeachers[i].students[No_ - 1];
					break;
				}

			break;
		}
			*/
		
		case '2':
			if (myTeachers[i].is_CourseEmpty()) { cout << "暂无课程！"; break; }
			teacherModifyCourseCheck(i);
			//std::system("pause");
			break;

		case '3':
			if (myTeachers[i].is_CourseEmpty()) { cout << "暂无课程！"; break; }
			myTeachers[i].showTeacherAllCourses();
			std::system("pause");
			break;

		case '4':
		{
			string newPW;
			string newPW2;
			cout << "请输入新密码：";
			cin >> newPW;
			cout << "请再次输入密码：";
			cin >> newPW2;
			if (newPW == newPW2)
			{
				myTeachers[i].setPassword(newPW);
				cout << "修改成功！" << endl;
			}
			else cout << "修改失败！两次密码不匹配，请重试！" << endl;
			std::system("pause");
			break;
		}
		case '5':
			continue;

		default:
			cout << "输入有误，请重新输入（1/2/3/4/5）: ";
			continue;
		}
		printTeacherMenu(i);
	} while (choice != '5');
}
void teacherLogin()
{
	string username;
	string password;
	int i, total = myTeachers.size();

	if (total == 0) { cout << "暂无教师数据！请先录入！" << endl;	system("pause"); return; }
	GoToXY(13, 7);
	cin >> username;
	for (i = 0; i < total; ++i)
		if (username == myTeachers[i].getWorkNum())
		{
			GoToXY(13, 10);
			cin >> password;
			if (password == myTeachers[i].getPassword())
			{
				GoToXY(1, 8);
				cout << "┌───────────────┐" << endl;
				GoToXY(1, 9);
				cout << "│     身份已认证！正在登录！   │" << endl;
				GoToXY(1, 10);
				cout << "└───────────────┘" << endl;
				Sleep(2000);
				teacherMenu(i);
			}
			else
			{
				GoToXY(0,19);
				cout << "密码错误！" << endl;
				system("pause");
			}
			break;
		}
	if (total == i) {
		GoToXY(0, 19);
		cout << "查无此人！请确认教师ID！" << endl; system("pause");
	}
}

void printStudentInfo()
{
	cout << left
		<< "------------------------------------------------------------------" << endl
		<< "序号\t" << setw(10) << "学号" << setw(8) << "姓名" << setw(6) << "性别" << setw(14) << "学院" << setw(12) << "专业" << setw(12) << "班级" << endl
		<< "------------------------------------------------------------------" << endl;
	int i=1;
	for (auto iter = myStudents.begin(); iter != myStudents.end(); ++iter, ++i)
	{
		cout << i << '\t'; (*iter).showStuInfo();
	}
	cout << "------------------------------------------------------------------" << endl
		<< right;
}
void studentManagementMenu_1()
{
	system("cls");
	cout << "正在进行【添加学生】，请按照提示操作。" << endl;

	Student newStudent;
	string newName;
	string newSex;
	string newNum;
	string newIns;
	string newMajor;
	string newClass;

	cout << "请输入学生名：";
	cin >> newName;
	do 
	{
		cout << "请输入性别（男/女）：";
		cin >> newSex;
		if (!(newSex == "男" || newSex == "女")) cout << "输入有误，请重新输入！" << endl;
	} while (!(newSex == "男" || newSex == "女"));
	
	cout << "请输入学号：";
	cin >> newNum;
	cout << "请输入学院：";
	cin >> newIns;
	cout << "请输入专业：";
	cin >> newMajor;
	cout << "请输入班级名：";
	cin >> newClass;

	newStudent.setAllData(newName, newSex, newNum, newIns, newMajor, newClass, "000000");
	cout << "添加完成！初始密码为“000000”" << endl;
	myStudents.push_back(newStudent);
}
void studentManagementMenu_2()
{
	system("cls");
	if (!myStudents.empty()) {
		cout << "正在进行【删除学生】，请按照提示操作。" << endl;
		for (auto iter = myStudents.begin(); iter != myStudents.end(); ++iter)
			(*iter).showStuInfo();
	}
	else {
		cout << "抱歉！暂无学生！" << endl; return;
	}

	string delNumber;
	cout << "请输入学生编号：" << endl;
	cin >> delNumber;
	bool flag = false;
	for (auto iter = myStudents.begin(); iter != myStudents.end(); ++iter)
		if (delNumber == (*iter).getStuNum())
		{
			flag = true;
			(*iter).showStuInfo();
			bool confirm;
			cout << "确认删除？（ 0.No/1.Yes ）" << endl;
			cin >> confirm;
			if (confirm) {
				myStudents.erase(iter);
				cout << "删除成功！" << endl;
				break;
			}
			else cout << "已取消操作！" << endl;
			break;
		}
	if (!flag) cout << "没有该学生！请确认学生学号!" << endl;
}
void studentManagementMenu_3()
{
	system("cls");
	if (!myStudents.empty())
	{
		cout << "正在进行【查找学生】，请按照提示操作。" << endl;

		char choice2;
		cout << "\t1.根据学生学号" << endl
			<< "\t2.根据学生姓名" << endl
			<< "请输入你的选择：";
		cin >> choice2;
		cin.ignore(1024, '\n');
		switch (choice2)
		{
		case '1':
		{
			string findNum;
			bool flag = false;//查无此人
			cout << "请输入学生学号：";
			cin >> findNum;
			for (auto iter = myStudents.begin(); iter != myStudents.end(); ++iter)
			{
				if (iter->getStuNum() == findNum) {
					cout << "已找到！该学生信息如下：" << endl
						<< left
						<< "------------------------------------------------------------------" << endl
						<< setw(10) << "学号" << setw(8) << "姓名" << setw(6) << "性别" << setw(14) << "学院" << setw(12) << "专业" << setw(12) << "班级" << endl
						<< "------------------------------------------------------------------" << endl;
					(*iter).showStuInfo();
					cout << "------------------------------------------------------------------" << endl
						<< right;
					flag = true;
					break;
				}
			}
			if (!flag) cout << "查无此人！请确认学生学号！" << endl;
		}
		break;

		case '2':
		{
			string findName;
			bool flag = false;//查无此人
			cout << "请输入学生姓名：";
			cin >> findName;
			for (auto iter = myStudents.begin(); iter != myStudents.end(); ++iter)
			{
				if (iter->getName() == findName) {
					cout << "已找到！该学生信息如下：" << endl
						<< left
						<< "------------------------------------------------------------------" << endl
						<< setw(10) << "学号" << setw(8) << "姓名" << setw(6) << "性别" << setw(14) << "学院" << setw(12) << "专业" << setw(12) << "班级" << endl
						<< "------------------------------------------------------------------" << endl;
					(*iter).showStuInfo();
					cout << "------------------------------------------------------------------" << endl
						<< right;
					flag = true;
					break;
				}
			}
			if (!flag) cout << "查无此人！请确认学生姓名！" << endl;
		}
		break;

		default: 
			cout << "请确认你的选择！" << endl;
		}
	}
	else cout << "抱歉！暂无学生！" << endl;

}
void studentManagementMenu_4()
{
	system("cls");
	if (!myStudents.empty()) {
		cout << "正在进行【修改学生信息】，请按照提示操作。" << endl;
		printStudentInfo();
	}
	else {
		cout << "抱歉！暂无学生！" << endl; return;
	}
	string number;
	int choice_2;
	cout << "请输入想要修改学生信息的学号：";
	cin >> number;
	auto iter = myStudents.begin();
	while (iter != myStudents.end())
	{
		if ((*iter).getStuNum() == number)
		{
			cout << "正在修改\"" << (*iter).getName() << "\"，编号：" << iter->getStuNum() << endl
				<< "\t1.修改名字" 
				<< "\t2.修改性别" << endl
				<< "\t3.修改学号" 
				<< "\t4.修改学院" << endl
				<< "\t5.修改专业"
				<< "\t6.修改班级" << endl
				<< "\t7.增加课程" 
				<< "\t8.删除课程" << endl
				<< "\t9.修改密码" 
				<< "\t0.取消" << endl
				<< "请输入修改项目序号：";
			cin >> choice_2;
			switch (choice_2)
			{
			case 1:
			{
				string newName;
				cout << "请输入新名字：";
				cin >> newName;
				(*iter).setName(newName);
				cout << "修改成功！新名称为 " << (*iter).getName() << endl;
				break;
			}
			case 2:
			{
				string newSex;
				do
				{
					cout << "请输入性别（男/女）：";
					cin >> newSex;
					if (!(newSex == "男" || newSex == "女")) cout << "输入有误，请重新输入！" << endl;
				} while (!(newSex == "男" || newSex == "女"));
				(*iter).setSex(newSex);
				cout << "修改成功！";
				break;
			}
			case 3:
			{
				string newNum;
				cout << "请输入新学号：";
				cin >> newNum;
				iter->setStuNum(newNum);
				cout << "修改成功！当前学号为 " << (*iter).getStuNum() << endl;
				break;
			}
			case 4:
			{
				string newIns;
				cout << "请输入学院名：";
				cin >> newIns;
				iter->setStuInstitude(newIns);
				cout << "修改成功！当前学院为 " << (*iter).getStuInstitude() << endl;
				break;
			}
			case 5:
			{
				string newMajor;
				cout << "请输入专业名：";
				cin >> newMajor;
				iter->setStuMajor(newMajor);
				cout << "修改成功！当前专业为 " << (*iter).getStuMajor() << endl;
				break;
			}
			case 6:
			{
				string newClass;
				cout << "请输入班级名：";
				cin >> newClass;
				iter->setStuClass(newClass);
				cout << "修改成功！当前班级为 " << (*iter).getStuClass() << endl;
				break;
			}
			case 7:
			{
				if (!myCourses.empty())
				{
					int No_ = 1;
					for (auto iter_2 = myCourses.begin(); iter_2 != myCourses.end(); ++iter_2, ++No_)
					{
						cout << No_ << endl;
						iter_2->showInfo();
					}
					cout << "请选择想要添加课程的序号：";
					cin >> No_;
					iter->addCourse(myCourses[No_ - 1]);
					//学生选择一门课程，将该学生添加到教这门课的老师的student下
					for (auto iter_3 = myTeachers.begin(); iter_3 != myTeachers.end(); ++iter_3)
						if (iter_3->is_ExistCourse(myCourses[No_ - 1]) > -1)
							iter_3->addStudent(*iter);
						else break;
					cout << "添加成功！" << endl;
				}
				else
				{
					cout << "抱歉！暂无课程！" << endl;
				}
				break;
			}
			case 8:
			{
				if (!iter->is_CourseEmpty())
				{
					int No_ = 1;
					cout << "------------------------------------------" << endl
						<< setw(5) << "序号" << setw(12) << "课程编号" << setw(15) << "课程名称" << endl
						<< "-------------------------------------------" << endl;
					iter->showAllCourses();
					cout << "------------------------------------------" << endl;
					cout << "请选择想要删除课程的序号：";
					cin >> No_;
					if (No_ - 1 >= iter->getClassSum()) {
						cout << "输入有误！请确认序号！" << endl;
						break;
					}
					iter->deleCourse(No_ - 1);
					for (auto iter_3 = myTeachers.begin(); iter_3 != myTeachers.end(); ++iter_3)
						if (iter_3->is_ExistCourse(myCourses[No_ - 1]) > -1)
						{
							iter_3->deleStudent(*iter); break;
						}
					cout << "删除成功！" << endl;
				}
				else
					cout << "抱歉！暂无课程！" << endl;
				break;

			}
			case 9:
			{
				string newPW;
				string newPW2;
				cout << "请输入新密码：";
				cin >> newPW;
				cout << "请再次输入密码：";
				cin >> newPW2;
				if (newPW == newPW2)
				{
					iter->setPassword(newPW);
					cout << "修改成功！" << endl;
				}
				else cout << "修改失败！两次密码不匹配，请重试！" << endl;
				break;
			}	
			
			default:
				break;
			}
			break;
		}
		++iter;
	}
	if (iter == myStudents.end()) cout << "没有该学生！请确认学生学号!" << endl;
}
void studentManagementMenu_5()
{
	if (!myStudents.empty())
		printStudentInfo();
	else cout << "抱歉！暂无学生！" << endl;
}
void studentManagementMenu()
{
	char choice;
	printStudentManagementMenu();
	do
	{
		cin >> choice;
		cin.ignore(1024, '\n');
		switch (choice)
		{
		case '1':
			studentManagementMenu_1();
			break;
		case '2':
			studentManagementMenu_2();
			break;
		case '3':
			studentManagementMenu_3();
			break;
		case '4':
			studentManagementMenu_4();
			break;
		case '5':
			studentManagementMenu_5();
			break;
		case '6':
			continue;
		}
		std::system("pause");
		printStudentManagementMenu();
	} while (choice != '6');
}
void studentLogin()
{
	string username;
	string password;
	int i,total= myStudents.size();

	if (total == 0) { cout << "暂无学生数据！请先录入！" << endl;	std::system("pause");	return; }
	GoToXY(13, 7);
	cin >> username;
	for ( i = 0; i < total; ++i)
		if (username == myStudents[i].getName())
		{
			GoToXY(13, 10);
			cin >> password;
			if (myStudents[i].is_IDPass(password))
			{
				GoToXY(0, 19);
				cout << "登录成功!";
				Sleep(2000);
				printStudentInfo(myStudents[i]);
				std::system("pause");//防止显示学生成绩单时一闪而过
			}
			else
			{
				GoToXY(0, 19);
				cout << "密码错误！" << endl;
				std::system("pause");		
			}	
			break;
		}
	if (total == i) {
		GoToXY(0, 19);
		cout << "查无此人！请确认学生ID！" << endl; 
		system("pause");
	}
}

void adminMenu()
{
	char choice;
	printAdminMenu();
	do
	{
		cin >> choice;
		cin.ignore(1024, '\n');
		switch (choice)
		{
		case '1':
			courseManagementMenu();
			break;

		case '2':
			teacherManagementMenu();
			break;

		case '3':
			studentManagementMenu();
			break;

		case '4':
			break;

		default:
			cout << "输入有误，请重新输入（1/2/3/4）: ";
			continue;
		}
		printAdminMenu();
	} while (choice != '4');
}
void adminLogin()
{
	//调试阶段暂不登录
	string username;
	string password;
	GoToXY(13, 7);
	cin >> username;
	for (int i = 0; i < 1; ++i)
		if (username == "admin")
		{
			GoToXY(13, 10);
			cin >> password;
			if (password == "admin")
			{
				GoToXY(1, 8);
				cout << "┌───────────────┐" << endl;
				GoToXY(1, 9);
				cout << "│     身份已认证！正在登录！   │" << endl;
				GoToXY(1, 10);
				cout << "└───────────────┘" << endl;
				Sleep(2000);
					/*
					<< "┌───────────────┐" << endl
					<< "│     正    在    载    入     │" << endl
					<< "└───────────────┘" << endl;
				for (int i = 2; i < 31; i+=2)
				{
					GoToXY(i, 21);
					cout << "■" ;
					Sleep(200);
				}
				*/
				adminMenu();
			}
			else
			{
				GoToXY(0, 19);
				cout <<endl<< "————密码错误！请检查输入————" << endl<<endl;		//美化
				std::system("pause");
			}
			break;
		}else
		{
			GoToXY(0, 19);
			cout<<endl<<"————您的账号不存在！请检查输入。————"<<endl<<endl;		//分支判断
			std::system("pause");
		}
}

void loadFile()
{

	cout<< "┌──────────────┐" << endl
		<< "│正在载入…                  │" << endl
		<< "├──────────────┤" << endl
		<< "│                            │" << endl
		<< "│                            │" << endl
		<< "│                            │" << endl
		<< "│                            │" << endl
		<< "│                            │" << endl
		<< "└──────────────┘" << endl;
	Teacher newTeacher;
	string newName;
	string newSex;
	string newTeacherID;
	ifstream inTeacher("teachersData.dat");
	if (!inTeacher)
	{
		cerr << "Can not open teacherData.dat !";
		exit(1);
	}
	while (!inTeacher.eof())
	{
		inTeacher >> newName >> newSex >> newTeacherID;
		newTeacher.setAllData(newName, newSex, newTeacherID, 0, "000000");
		myTeachers.push_back(newTeacher);
	}
	inTeacher.close();
	GoToXY(2, 4);
	cout << "1.教师信息…………………100%" << endl;

	Course newCourse;
	string newCourseID;
	int newTime;
	ifstream inCourse("coursesData.dat");
	if (!inCourse)
	{
		cerr << "Can not open coursesData.dat !";
		exit(1);
	}
	while (!inCourse.eof())
	{
		inCourse >> newName >> newCourseID >> newTeacherID >> newTime;
		newCourse.setName(newName);
		newCourse.setNumber(newCourseID, newTeacherID);
		newCourse.setTime(newTime);
		for (auto iter = myTeachers.begin(); iter != myTeachers.end(); ++iter)
			if (iter->getWorkNum() == newTeacherID)
				iter->addCourse(newCourse);
		myCourses.push_back(newCourse);
	}
	inCourse.close();
	GoToXY(2, 5);
	cout << "2.课程信息…………………100%" << endl;

	Student newStudent;
	string newNum;
	string newIns;
	string newMajor;
	string newClass;
	ifstream inStudent("studentsData.dat");
	if (!inStudent)
	{
		cerr << "Can not open studentsData.dat !";
		exit(1);
	}
	while (!inStudent.eof())
	{
		inStudent >> newName >> newSex >> newNum >> newIns >> newMajor >> newClass;
		newStudent.setAllData(newName, newSex, newNum, newIns, newMajor, newClass, "000000");
		myStudents.push_back(newStudent);
	}
	inStudent.close();
	GoToXY(2, 6);
	cout << "3.学生信息…………………100%" << endl;
	GoToXY(0, 9);
}

int main()
{
	loadFile();
	system("pause");
	extern vector<Course> myCourses;
	char choice;
	
	while (1)
	{
		printMainMenu();				//刷新屏幕
		cin >> choice;
		cin.ignore(1024, '\n');
		switch (choice)
		{
		case '1':
			adminLogin();    
			break;
		case '2':
			teacherLogin();
			break;

		case '3':
			studentLogin();
			break;

		case '4':
			printExit();
			return 0;

		default:
			GoToXY(0, 18);
			cout << "输入有误！请重新输入 !                   "<<endl;	//清理屏幕
			system("pause");
			continue;
		}
	}
	return 0;
}
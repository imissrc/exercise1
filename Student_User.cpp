#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include"User.h"
#include"Manage.h"
#include"message.h"

void Manage::Student_User(Manage & user)//////////////////////////////////////////////////////已经将添加选修课和删除选修课做了
{
	string id, password;
	Menu_Stu(id, password);
	int pos = 0, choice = 0, TuiChu = 1;
	pos = Find_Student(id);
	if (pos != -1 && password == students[pos].Get_UserPassword())
	{
		Student newStu;
		newStu = students[pos];
		Stu_Options(newStu);
		cin >> choice;
		while (choice != 6)
		{
			switch (choice)
			{
			case 1://选课
			{
				newStu.Print_JoinEle(user, 0);
				newStu.Select_EleCourse(user, newStu);
				break;
			case 2://退课
				//这里应该还有一个成绩提交了后不能退课的处理、、、、、、、、、、、、、、、、、、、、、、、、、
				newStu.Print_JoinEle(user, 0);
				newStu.Delete_JoinEleCous(user, newStu);
				break;
			case 3://查看自己的所有课程
				newStu.Print_JoinRe(user, 0);
				newStu.Print_JoinEle(user, 0);
				break;
			case 4://查看开的所有课程
				user.Print_All_Re();
				user.Print_All_Ele();
				break;
			case 5://查看课程成绩和绩点 ///////////////////////////////////////////////////这里应该当老师把课程提交后使用。
				newStu.Print_JoinRe(user, 1);
				newStu.Print_JoinEle(user, 1);
				break;
			case 6:
				break;
			}
			}
			Stu_Options(newStu);
			cin >> choice;
		}
	}
	else
	{
		cout << "用户账号或密码错误！请重新输入" << endl << endl;
	}
}
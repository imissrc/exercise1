#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include"User.h"
#include"Manage.h"
#include"message.h"
void Manage::Teacher_User(Manage & user)
{

	string id, password;
	Menu_Teacher(id, password);
	int pos = 0, choice = 0;
	pos = Find_Teacher(id);
	if (pos != -1 && password == teachers[pos].Get_UserPassword())
	{
		Teacher newTeach;
		newTeach = teachers[pos];
		while (choice != 6)
		{
			Teach_Options(newTeach);
			cin >> choice;
			switch (choice)
			{
			case 1://录入课程成绩
			{
				newTeach.Register_Score(user);
				break;
			case 2://修改课程成绩
				   //这里应该还有一个成绩提交了后不能退课的处理、、、、、、、、、、、、、、、、、、、、、、、、、
				newTeach.Modify_Score(user);
				break;
			case 3://提交课程成绩
				newTeach.Submit_Score(user);
				break;
			case 4://查看自己教授的所有课程
				newTeach.Print_JoinRe(user, 0);
				newTeach.Print_JoinEle(user, 0);
				break;
			case 5://查看开的所有课程 ///////////////////////////////////////////////////这里应该当老师把课程提交后使用。
				user.Print_All_Re();
				user.Print_All_Ele();
				break;
			case 6:
				break;
			}
			}
		}
	}
	else
	{
		cout << "用户账号或密码错误！请重新输入" << endl << endl;
	}
}
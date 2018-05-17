#include<iostream>
using namespace std;
#include"Manage.h"
#include"message.h"
//程序改进思路，将各个类再进行嵌套，数据和操作分开

int main()
{
	Print_Function_Choice();
	int choice;
	Manage user;
	user.Initial_All_Info();
	//cin >> choice;
	choice = 2;
	while (choice != 3)
	{
		switch (choice)
		{
		case 1:
			user.Student_User(user);//用学号和密码登录。
			break;
		case 2:
			user.Teacher_User(user);	break;
		case 3:
			exit(0); 	break;
		default:
			cout << "没有该选项，请重新选择" << endl;	break;
		}
		Print_Function_Choice();
		cin >> choice;
	}
}




#include<iostream>
using namespace std;
#include"Manage.h"
#include"message.h"
//����Ľ�˼·�����������ٽ���Ƕ�ף����ݺͲ����ֿ�

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
			user.Student_User(user);//��ѧ�ź������¼��
			break;
		case 2:
			user.Teacher_User(user);	break;
		case 3:
			exit(0); 	break;
		default:
			cout << "û�и�ѡ�������ѡ��" << endl;	break;
		}
		Print_Function_Choice();
		cin >> choice;
	}
}




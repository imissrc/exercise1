#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include"User.h"
#include"Manage.h"
#include"message.h"

void Manage::Student_User(Manage & user)//////////////////////////////////////////////////////�Ѿ������ѡ�޿κ�ɾ��ѡ�޿�����
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
			case 1://ѡ��
			{
				newStu.Print_JoinEle(user, 0);
				newStu.Select_EleCourse(user, newStu);
				break;
			case 2://�˿�
				//����Ӧ�û���һ���ɼ��ύ�˺����˿εĴ���������������������������������������������������
				newStu.Print_JoinEle(user, 0);
				newStu.Delete_JoinEleCous(user, newStu);
				break;
			case 3://�鿴�Լ������пγ�
				newStu.Print_JoinRe(user, 0);
				newStu.Print_JoinEle(user, 0);
				break;
			case 4://�鿴�������пγ�
				user.Print_All_Re();
				user.Print_All_Ele();
				break;
			case 5://�鿴�γ̳ɼ��ͼ��� ///////////////////////////////////////////////////����Ӧ�õ���ʦ�ѿγ��ύ��ʹ�á�
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
		cout << "�û��˺Ż������������������" << endl << endl;
	}
}
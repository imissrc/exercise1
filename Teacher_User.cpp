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
			case 1://¼��γ̳ɼ�
			{
				newTeach.Register_Score(user);
				break;
			case 2://�޸Ŀγ̳ɼ�
				   //����Ӧ�û���һ���ɼ��ύ�˺����˿εĴ���������������������������������������������������
				newTeach.Modify_Score(user);
				break;
			case 3://�ύ�γ̳ɼ�
				newTeach.Submit_Score(user);
				break;
			case 4://�鿴�Լ����ڵ����пγ�
				newTeach.Print_JoinRe(user, 0);
				newTeach.Print_JoinEle(user, 0);
				break;
			case 5://�鿴�������пγ� ///////////////////////////////////////////////////����Ӧ�õ���ʦ�ѿγ��ύ��ʹ�á�
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
		cout << "�û��˺Ż������������������" << endl << endl;
	}
}
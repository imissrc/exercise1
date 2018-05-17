#include<iostream>
#include<string>
#include<vector>
using namespace std;
#include"User.h"
#include"Course.h"
#include"Manage.h"
#include"message.h"

Student::Student()
{

}
void Student::Init_Student(const string & name, const string & id, const string & academy, const string & password, const string & stuclass, vector<string> & join_re_cous_id, vector<string> & join_ele_cous_id)
{
	User::Init_User(name, id, academy, password, join_re_cous_id);
	vector<string>::iterator cous;
	Join_EleCous_Id.clear();
	for (cous = join_ele_cous_id.begin(); cous != join_ele_cous_id.end(); cous++)
	{
		Join_EleCous_Id.push_back(*cous);
	}
	Student_Class = stuclass;
}
/*vector<string>::iterator Student::GetFirst_CousId()
{
return Join_EleCous_Id.begin();
}*/
void Student::Select_EleCourse(Manage & stu, Student & man)////////////////////////����Ӧ�����һ���жϸ�ѧ���Ƿ�ѡ���ÿγ̣����Ѿ�ѡ�������
{
	string cours_id;
	int cous_pos, flag_ack = 0, ele_num, i = 0;
	char ack;
	bool judge;
	cout << "����Ϊ���е�ѡ�޿���Ϣ" << endl;
	stu.Print_All_Ele();
	int has_join_class = GetJoinEleNum();
	////////////////////////////////////////////////////��������һ���ж���ѡ�Ŀγ���Ŀ�����Ѵ����ޣ����������ѡ��
	cout << "��������Ҫѡ��Ŀγ����������μ�" << MAX_ELECOUSE << "��ѡ�޿Σ������ڻ�����ѡ��" << MAX_ELECOUSE - has_join_class << "�ſγ�)" << endl;
	cin >> ele_num;
	if (ele_num != 0)
	{
		while (ele_num > MAX_ELECOUSE - has_join_class || ele_num < 0)
		{
			cout << "������벻�Ϸ������������룡" << endl;
			cin >> ele_num;
		}
		while (i < ele_num)
		{
			cout << "������Ҫѡ���ѡ�޿εĿγ̱�ţ�" << endl;
			cin >> cours_id;
			try
			{
				judge = Judge_Join_Ele(cours_id);
				cous_pos = stu.Find_Elective(cours_id);
				if (cous_pos != -1)
				{
					flag_ack = 0;
					cout << "��ȷ��Ҫ�μӡ�" << stu.GetElective_Courses()[cous_pos].Get_CourseName() << "����?" << '\t' << "Y/y���ǣ�" << '\t' << "N/n(��" << endl;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							Join_EleCous_Id.push_back(cours_id);

							stu.GetElective_Courses()[cous_pos].Add_Student(man.Get_UserId());
							cout << "�ɹ�����ÿγ̣�" << endl;
							flag_ack = 1;
							i++;	//�γ���Ŀ+1
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "����ѡ��" << endl;
							flag_ack = 1;
						}
						else
						{
							cout << "��������������������룡" << endl;
						}
					}
				}
				else
				{
					cout << "�����ڴ˿γ�Ŷ��������������Ҫѡ��Ŀγ̱�š�" << endl;
				}
			}
			catch (string s)
			{
				cout << s << endl;
			}
		}
	}
}
void Student::Delete_JoinEleCous(Manage & stu, Student & man)
{
	string cours_id, cours_name;
	char ack;
	int del_num, i = 0, flag_ack = 0, pos;
	cout << "��������Ҫ�˳���ѡ�޿������������Ŀ���ܳ�����" << this->GetJoinEleNum() << "��)��" << endl;
	cin >> del_num;
	if (del_num != 0)
	{
		while (del_num > this->GetJoinEleNum() || del_num < 0)
		{
			cout << "��������������������룡" << endl;
			cin >> del_num;
		}
		while (i < del_num)
		{
			flag_ack = 0;
			cout << "��������Ҫ�˳��Ŀγ̱�ţ�";
			cin >> cours_id;
			vector<string>::iterator id_pos = find(Join_EleCous_Id.begin(), Join_EleCous_Id.end(), cours_id);
			if (id_pos != Join_EleCous_Id.end())
			{
				pos = stu.Find_Elective(cours_id);
				cours_name = stu.GetElective_Courses()[pos].Get_CourseName();
				if (!stu.GetElective_Courses()[pos].Judge_Submit_Score())
				{
					cout << "��ȷ��Ҫ�˳���" << cours_name << "����?" << '\t' << "Y/y���ǣ�" << '\t' << "N/n(��" << endl;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							id_pos = Join_EleCous_Id.erase(id_pos);

							stu.GetElective_Courses()[pos].Delete_Student(man.Get_UserId());
							cout << "�ɹ��˳��ÿγ̣�" << endl;
							flag_ack = 1;
							i++;	//�γ���Ŀ+1
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "����ѡ��" << endl;
							flag_ack = 1;
							i++;//////////��Ȼ����ѡ���ˣ�����Ӧ���Լ�1
						}
						else
						{
							cout << "��������������������룡" << endl;
						}
					}
				}
				else
				{
					cout << cours_name << "�Ѿ����ο���ʦ�ύ����ǰ�����˳��ÿγ�" << endl;
				}
			}
			else
			{
				cout << "û�в��ҵ��ÿγ���Ϣ��������ѡ����Ҫ�˳��Ŀγ�" << endl;
			}
		}
	}
}
/*vector<string> Student::GetJoinEleId()
{
return Join_EleCous_Id;
}*/
int Student::GetJoinEleNum()
{
	return Join_EleCous_Id.size();
}
void Student::Print_JoinEle(Manage & stu, const int score_flag)
{
	vector<string>::iterator ele_id;
	int pos, teach_pos;
	Elective_Course *ele_cos = nullptr;
	string tea_id;
	double score, gpa;
	cout << "���Ѿ��μӵ�ѡ�޿���:" << endl;
	cout << "�γ̱��    "<< "�γ�����" << '\t' << "�ο���ʦ�����ţ�" << "\t" << "�γ�ѧ��";
	if (score_flag == 1)
		cout << '\t' << "�ɼ�  " << "����";
	cout << endl;
	for (ele_id = Join_EleCous_Id.begin(); ele_id != Join_EleCous_Id.end(); ele_id++)
	{
		pos = stu.Find_Elective(*ele_id);
		if (pos != -1)
			ele_cos = &stu.GetElective_Courses()[pos];///�����ķ���ֵ���ڳ�ʼ���ڵ��ú���ʱ��������ʱ��������������Ͳ������ã��ڵ��ú����ĵط��Ὣ��������ֵ��ֵ����ʱ����
		else
			cout << "��д���ѡ�޿���Ϣ����" << endl;
		tea_id = ele_cos->Get_CourseTeacherId();
		teach_pos = stu.Find_Teacher(tea_id);
		if (teach_pos != -1)
			cout << *ele_id << '\t' << ele_cos->Get_CourseName() << '\t' << stu.GetTeachers()[teach_pos].Get_UserName() << "(" << tea_id << ")" << '\t' << ele_cos->Get_CourseCredit();
		else
			cout << "��д���ѡ�޿���ʦ��Ϣ����" << endl;
		if (score_flag == 1)
		{
			try
			{
				score = ele_cos->Find_Score(Get_UserId());
				gpa = ele_cos->Course_GPA(score);
				cout << '\t' << score;
				cout << "  " << gpa;
			}
			catch (string s)
			{
				cout << "  " << s;
			}
		}
		cout << endl;
	}
	cout << endl;
	ele_cos = nullptr;
}
void Student::Print_JoinRe(Manage & stu, const int score_flag)
{
	int pos, teach_pos, k;
	string tea_id;
	Required_Course * re_cos = nullptr;//Ϊʲô����Ҫ��ָ��
	string join_cous_id;
	double score, gpa;
	cout << "��μӵı��޿���:" << endl;
	cout << "�γ̱��" << '\t' << "�γ�����" << '\t' << "�ο���ʦ�����ţ�" << "\t" << "�γ�ѧ��";
	if (score_flag == 1)
		cout << '\t' << "�ɼ�  "  << "����";
	cout << endl;
	for (k = 0; k<Get_JoinReNum(); k++)
	{
		join_cous_id = Get_Join_Re_Id()[k];
		pos = stu.Find_Required(join_cous_id);
		if (pos != -1)
			re_cos = &stu.GetRequired_Courses()[pos];
		else
			cout << "��д��ı��޿���Ϣ����!" << endl;
		tea_id = re_cos->Get_CourseTeacherId();
		teach_pos = stu.Find_Teacher(tea_id);
		if (teach_pos != -1)
			cout << join_cous_id << '\t' << re_cos->Get_CourseName() << '\t' << stu.GetTeachers()[teach_pos].Get_UserName() << "(" << tea_id << ")" << '\t' << re_cos->Get_CourseCredit();
		else
			cout << "��д��ı��޿���ʦ��Ϣ����!" << endl;
		if (score_flag == 1)
		{
			try
			{
				score = re_cos->Find_Score(Get_UserId());
				gpa = re_cos->Course_GPA(score);
				cout << '\t' << score;
				cout << "  " << gpa;
			}
			catch (string s)
			{
				cout << "  " << s;
			}
		}
		cout << endl;
	}
	cout << endl;
	re_cos = nullptr;
}
bool Student::Judge_Join_Ele(string cours_id)
{
	vector<string>::iterator cour_pos = find(Join_EleCous_Id.begin(), Join_EleCous_Id.end(), cours_id);
	string s = "���Ѿ�����ÿγ��ˣ������ظ�����";
	if (cour_pos != Join_EleCous_Id.end())
	{
		throw s;
	}
	else
		return false;
}
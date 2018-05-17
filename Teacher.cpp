#include<iostream>
#include<string>
#include<vector>
using namespace std;
#include"User.h"
#include"Course.h"
#include"Manage.h"
#include"message.h"
Teacher::Teacher()
{

}
void Teacher::Init_Teacher(const string & name, const string & id, const string & academy, const string & password, vector<string> & teach_re_cous_id, vector<string> & teach_ele_cous_id)
{
	User::Init_User(name, id, academy, password, teach_re_cous_id);
	vector<string>::iterator cous;
	Teach_EleCous_Id.clear();
	for (cous = teach_ele_cous_id.begin(); cous != teach_ele_cous_id.end(); cous++)
	{
		Teach_EleCous_Id.push_back(*cous);
	}
}
void Teacher::Print_JoinRe(Manage & teach, const int print_stu_flag)
{
	int pos, i = 0, k;
	string join_cous_id;
	Required_Course * re_cos = nullptr;
	cout << "����ڵı��޿���:" << endl;
	cout << "�γ̱��" << '\t' << "�γ�����" << '\t' << "�γ�ѧ��" << endl;
	for (k = 0; k < Get_JoinReNum(); k++)
	{
		join_cous_id = Get_Join_Re_Id()[k];
		pos = teach.Find_Required(join_cous_id);
		if (pos != -1)
			re_cos = &teach.GetRequired_Courses()[pos];
		else
			cout << "��д��ı��޿���Ϣ����" << endl;
		cout << join_cous_id << '\t' << re_cos->Get_CourseName() << '\t' << re_cos->Get_CourseCredit() << endl;
	}
	cout << endl;
	re_cos = nullptr;
}
void Teacher::Print_JoinEle(Manage & teach, const int print_stu_flag)
{
	vector<string>::iterator ele_id;
	int pos;
	Elective_Course *ele_cos = nullptr;
	cout << "����ڵ�ѡ�޿���:" << endl;
	cout << "�γ̱��" << '\t' << "�γ�����" << '\t' << "�γ�ѧ��" << endl;
	for (ele_id = Teach_EleCous_Id.begin(); ele_id != Teach_EleCous_Id.end(); ele_id++)
	{
		pos = teach.Find_Elective(*ele_id);
		if (pos != -1)
			ele_cos = &teach.GetElective_Courses()[pos];///�����ķ���ֵ���ڳ�ʼ���ڵ��ú���ʱ��������ʱ��������������Ͳ������ã��ڵ��ú����ĵط��Ὣ��������ֵ��ֵ����ʱ����
		else
			cout << "��д���ѡ�޿���Ϣ����" << endl;
		cout << *ele_id << '\t' << ele_cos->Get_CourseName() << '\t' << ele_cos->Get_CourseCredit();
		cout << endl;
	}
	cout << endl;
	ele_cos = nullptr;
}
void Teacher::Register_Score(Manage & teacher)
{
	int i = 0, cous_pos, stu_pos, k, choice;
	double student_score;
	string course_id, stu_id;
	int num, cous_stu_num;
	vector<string>::iterator Pcous;
	cout << "��������Ҫ¼��ɼ��Ŀγ�����" << endl;
	cin >> num;
	//num = 1;
	for (i = 0; i < num; i++)
	{
		cout << "��ѡ����Ҫ¼��Ŀγ����ͣ�1�����޿�    2��ѡ�޿Σ�" << endl;
		cin >> choice;
		//choice = 1;
		while (choice != 1 && choice != 2)
		{
			cout << "û�и�ѡ�������ѡ��!" << endl;
			cout << "��ѡ����Ҫ¼��Ŀγ����ͣ�1�����޿�    2��ѡ�޿Σ�" << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			this->Print_TeachNoSubmit_ReScore(teacher);
			cout << "��ѡ����Ҫ¼��Ŀγ̺�:";
			//cin >> course_id;
			course_id = "00000002";
			while (this->Judge_Join_Re(course_id)==0)
			{
				cout << "��Ŀγ���û�иñ��޿ε���Ϣ�����������룡" << endl;
				cout << "��ѡ����Ҫ¼��Ŀγ̺�:";
				cin >> course_id;
			}
			cout << "���������ѧ���ɼ�����¼��" << endl;
			cout << "ѧ��" << '\t' << '\t' << "����" << '\t' << "�ɼ�" << endl;
			cous_pos = teacher.Find_Required(course_id);
			teacher.GetRequired_Courses()[cous_pos].Get_Course_Student();
			cous_stu_num = teacher.GetRequired_Courses()[cous_pos].Get_CourseStu_Num();
			for (k = 0; k < cous_stu_num; k++)
			{
				stu_id = teacher.GetRequired_Courses()[cous_pos].Get_Course_Student()[k];
				stu_pos = teacher.Find_Student(stu_id);
				cout << stu_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << ":  ";
				cin >> student_score;
				teacher.GetRequired_Courses()[cous_pos].Initial_Score(stu_id, student_score);
			}
		}
		if (choice == 2)
		{
			this->Print_TeachNoSubmit_EleScore(teacher);
			cout << "��ѡ����Ҫ¼��Ŀγ̺�:";
			//cin >> course_id;
			//course_id = "10000006";
			Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
			while (Pcous == Teach_EleCous_Id.end())
			{
				cout << "��Ŀγ���û�и�ѡ�޿ε���Ϣ�����������룡" << endl;
				cout << "��ѡ����Ҫ¼��Ŀγ̺�:";
				cin >> course_id;
				Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
			}
			cous_pos = teacher.Find_Elective(course_id);
			cous_stu_num = teacher.GetElective_Courses().at(cous_pos).Get_CourseStu_Num();
			for (k = 0; k < cous_stu_num; k++)
			{
				stu_id = teacher.GetElective_Courses()[cous_pos].Get_Course_Student()[k];
				stu_pos = teacher.Find_Student(stu_id);
				cout << stu_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << ":";
				cin >> student_score;
				teacher.GetElective_Courses()[cous_pos].Initial_Score(stu_id, student_score);
			}
		}

	}

}
void Teacher::Modify_Score(Manage & teacher)
{
	int stu_num, i, choice, cous_pos, new_score, stu_pos, uns;
	string course_id, student_id;
	double score;
	vector<string>::iterator Pcous;
	
	uns = Print_TeachNoSubmit_ReScore(teacher);
	uns = Print_TeachNoSubmit_EleScore(teacher);
	cout << "��������Ҫ�޸ĳɼ���ѧ��������";
	//cin >> stu_num;
	stu_num = 3;

	for (i = 0; i < stu_num; i++)
	{
		cout << "������Ҫ�޸ĳɼ���ѧ�����ڵĿγ����ͣ�1�����޿�    2��ѡ�޿Σ�" << endl;
		cin >> choice;
		while (choice != 1 && choice != 2)
		{
			cout << "û�и�ѡ�������ѡ��!" << endl;
			cout << "�����뵱ǰѧ�����ڵĿγ����ͣ�1�����޿�    2��ѡ�޿Σ�" << endl;
			cin >> choice;
		}
		cout << "��������Ҫ�޸ĳɼ���ѧ�����ڵĿγ̺ţ�";
		cin >> course_id;
		if (choice == 1)
		{
			while (this->Judge_Join_Re(course_id) == 0)
			{
				cout << "��Ŀγ���û�иñ��޿ε���Ϣ�����������룡" << endl;
				cout << "��ѡ����Ҫѡ��Ŀγ̺�:";
				cin >> course_id;
			}
			cous_pos = teacher.Find_Required(course_id);
			if (cous_pos != -1)
			{
				if (teacher.GetRequired_Courses()[cous_pos].Judge_Submit_Score() == 0)
				{
					cout << "��������Ҫ�޸ĳɼ���ѧ��ѧ�ţ�";
					cin >> student_id;
					if (teacher.GetRequired_Courses()[cous_pos].Judge_Course_Student(student_id))
					{
						stu_pos = teacher.Find_Student(student_id);
						while (stu_pos == -1)
						{
							cout << "��Ŀγ���û�и�ѧ����Ϣ��������������Ҫ�޸ĵ�ѧ��ѧ�ţ�" << endl;
							cin >> student_id;
							stu_pos = teacher.Find_Student(student_id);
						}
						cout << "��ѧ������ǰ�ĳɼ�Ϊ��" << endl;
						cout << "ѧ��    " << "����" << '\t' << "�ɼ�" << endl;
						try
						{
							score = teacher.GetRequired_Courses()[cous_pos].Find_Score(student_id);
							cout << student_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << '\t' << score << endl;
							cout << "�������ѧ�����º�ĳɼ���";
							cin >> new_score;
							teacher.GetRequired_Courses()[cous_pos].Initial_Score(student_id, new_score);
							cout << "��ѧ�����º�ĳɼ�Ϊ��" << endl;
							cout << "ѧ��" << '\t' << "����" << '\t' << "�ɼ�" << endl;
							score = teacher.GetRequired_Courses()[cous_pos].Find_Score(student_id);
							cout << student_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << '\t' << score << endl;
						}
						catch (string s)
						{
							cout << s << endl;
						}
					}
					else
					{
						cout << "��ѧ������û��ѡ��ÿγ̣��㲻�ܻ�ȡ���޸����ĳɼ���" << endl;
					}
				}
				else
				{
					cout << "�ÿγ̵ĳɼ��Ѿ��ύ����ǰ�����޸ĸÿγ̵�ѧ���ɼ�" << endl;
				}
			}
			else
			{
				cout << "�����������û���ҵ��ÿγ̵���Ϣ��" << endl;
			}
		}
		else//choice==2
		{
			Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
			while (Pcous == Teach_EleCous_Id.end())
			{
				cout << "��Ŀγ���û�и�ѡ�޿ε���Ϣ�����������룡" << endl;
				cout << "��ѡ����Ҫѡ��Ŀγ̺�:";
				cin >> course_id;
				Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
			}
			cous_pos = teacher.Find_Elective(course_id);
			if (cous_pos != -1)
			{
				if (teacher.GetElective_Courses()[cous_pos].Judge_Submit_Score() == 0)
				{
					cout << "��������Ҫ�޸ĳɼ���ѧ��ѧ�ţ�" << endl;
					cin >> student_id;
					if (teacher.GetElective_Courses()[cous_pos].Judge_Course_Student(student_id))
					{
						stu_pos = teacher.Find_Student(student_id);
						while (stu_pos == -1)
						{
							cout << "��Ŀγ���û�и�ѧ����Ϣ��������������Ҫ�޸ĵ�ѧ��ѧ�ţ�" << endl;
							cin >> student_id;
							stu_pos = teacher.Find_Student(student_id);
						}
						cout << "��ѧ������ǰ�ĳɼ�Ϊ��" << endl;
						cout << "ѧ��" << '\t' << "����" << '\t' << "�ɼ�" << endl;
						try
						{
							score = teacher.GetElective_Courses()[cous_pos].Find_Score(student_id);
							cout << student_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << '\t' << score << endl;
							cout << "�������ѧ�����º�ĳɼ���";
							cin >> new_score;
							teacher.GetRequired_Courses()[cous_pos].Initial_Score(student_id, new_score);
							cout << "��ѧ�����º�ĳɼ�Ϊ��" << endl;
							cout << "ѧ��" << '\t' << "����" << '\t' << "�ɼ�" << endl;
							score = teacher.GetElective_Courses()[cous_pos].Find_Score(student_id);
							cout << student_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << '\t' << score << endl;
						}
						catch (string s)
						{
							cout << s << endl;
						}
					}
					else
					{
						cout << "��ѧ������û��ѡ��ÿγ̣��㲻�ܻ�ȡ���޸����ĳɼ���" << endl;
					}
				}
				else
				{
					cout << "�ÿγ̵ĳɼ��Ѿ��ύ����ǰ�����޸ĸÿγ̵�ѧ���ɼ�" << endl;
				}
			}
			else
			{
				cout << "�����������û���ҵ��ÿγ̵���Ϣ��" << endl;
			}
		}
		cin.clear();//���������
		cin.ignore(1024, '\n');
	}
}
void Teacher::Submit_Score(Manage & teacher)
{
	int num, no_submit_Renum, i = 0, choice, cous_pos, flag_ack = 0, no_submit_Elenum;
	string course_id;
	char ack;
	vector<string>::iterator Pcous;
	cout << "�㵱ǰδ�ύ�ɼ��Ŀγ�Ϊ��" << endl;
	no_submit_Renum = Print_TeachNoSubmit_ReScore(teacher);
	no_submit_Elenum = Print_TeachNoSubmit_EleScore(teacher);
	if ((no_submit_Renum != 0)&& (no_submit_Elenum != 0))
	{
		cout << "��ѡ����Ҫ�ύ�ɼ��Ŀγ����ͣ�1�����޿�    2��ѡ�޿Σ�" << endl;
		cin >> choice;
		while (choice != 1 && choice != 2)
		{
			cout << "û�и�ѡ�������ѡ��!" << endl;
			cout << "��ѡ����Ҫ�ύ�ɼ��Ŀγ����ͣ�1�����޿�    2��ѡ�޿Σ�" << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			cout << "�����������ύ�ɼ��ı��޿�������";
			cin >> num;
			while (num > no_submit_Renum || num <= 0)
			{
				cout << "������볬����Χ������������" << endl;
				cout << "�����������ύ�ɼ��ı��޿�������";
				cin >> num;
			}
			for (i = 0; i < num; i++)
			{
				cout << "��������Ҫ�ύ�ɼ��ı��޿ογ̺ţ�";
				cin >> course_id;
				//course_id = "00000002";     ///��ɾ
			//	cout << endl;                ///��ɾ
				while (this->Judge_Join_Re(course_id) == 0)
				{
					cout << "��Ŀγ���û�иñ��޿ε���Ϣ�����������룡" << endl;
					cout << "��ѡ����Ҫ�ύ�ɼ��Ŀγ̺�:";
					cin >> course_id;
				}
				cous_pos = teacher.Find_Required(course_id);
				if (teacher.GetRequired_Courses()[cous_pos].Judge_Submit_Score() == 1)
					cout << "�ÿγ̳ɼ��Ѿ����ύ���ˣ������ٴα��ύ" << endl;
				else
				{
					cout << "��ȷ��Ҫ�ύ" << teacher.GetRequired_Courses()[cous_pos].Get_CourseName() << "��    " << "Y/y���ǣ�" << '\t' << "N/n(��" << endl;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							teacher.GetRequired_Courses()[cous_pos].Submit_Course_Score();
							cout << "�ɹ��ύ�ÿγ̳ɼ���" << endl;
							flag_ack = 1;
							i++;
							no_submit_Renum--;
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "�����ύ�ÿγ̳ɼ���" << endl;
							flag_ack = 1;
							i++;  //����ȫ��������֮����ѭ��
						}
						else
						{
							cout << "��������������������룡" << endl;
						}
					}
				}
			}
		}
		else//�ύѡ�޿γɼ�
		{
			cout << "�����������ύ�ɼ���ѡ�޿�������";
			cin >> num;
			while (num > no_submit_Elenum || num <= 0)
			{
				cout << "������볬����Χ������������" << endl;
				cout << "�����������ύ�ɼ���ѡ�޿�������";
				cin >> num;
			}
			for (i = 0; i < no_submit_Elenum; i++)
			{
				cout << "��������Ҫ�ύ�ɼ���ѡ�޿ογ̺ţ�";
				//cin >> course_id;
				//course_id = "10000006";     ///��ɾ
				//cout << endl;                ///��ɾ
				Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
				while (Pcous == Teach_EleCous_Id.end())
				{
					cout << "��Ŀγ���û�и�ѡ�޿ε���Ϣ�����������룡" << endl;
					cout << "��ѡ����Ҫѡ����ύ�ɼ���ѡ�޿ογ̺�:";
					cin >> course_id;
					Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
				}
				cous_pos = teacher.Find_Elective(course_id);
				if (teacher.GetElective_Courses()[cous_pos].Judge_Submit_Score() == 1)
				{
					cout << "�ÿγ̳ɼ��Ѿ����ύ���ˣ������ٴα��ύ" << endl;
				}
				else
				{
					cout << "��ȷ��Ҫ�ύ" << teacher.GetElective_Courses()[cous_pos].Get_CourseName() << "��    " << "Y/y���ǣ�" << '\t' << "N/n(��" << endl;
					flag_ack = 0;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							teacher.GetElective_Courses()[cous_pos].Submit_Course_Score();
							cout << "�ɹ��ύ�ÿγ̳ɼ���" << endl;
							flag_ack = 1;
							no_submit_Elenum--;
							i++;
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "�����ύ�ÿγ̳ɼ���" << endl;
							flag_ack = 1;
							i++;  //����ȫ��������֮����ѭ��
						}
						else
						{
							cout << "��������������������룡" << endl;
						}
					}
				}
			}
		}
	}
}
/*int Teacher::Print_TeachNoSubmitScore(Manage & teacher)
{
	int i, cours_pos, output_flag = 0, num, no_submit_num = 0;
	string teach_cous_id;
	num = Get_JoinReNum();
	for (i = 0; i < num; i++)
	{
		teach_cous_id = Get_Join_Re_Id()[i];
		cours_pos = teacher.Find_Required(teach_cous_id);
		if (teacher.GetRequired_Courses()[cours_pos].Judge_Submit_Score() == 0)
		{
			no_submit_num++;
			if (output_flag == 0)
			{
				cout << "�㵱ǰδ�ύ�ɼ��ı��޿��У�" << endl;
				cout << "�γ̺�" << '\t' << "�γ���" << endl;
			}
			cout << teach_cous_id << '\t' << teacher.GetRequired_Courses()[cours_pos].Get_CourseName() << endl;
		}
	}
	cout << endl;
	output_flag = 0;
	num = Teach_EleCous_Id.size();
	for (i = 0; i < num; i++)
	{
		teach_cous_id = Teach_EleCous_Id[i];
		cours_pos = teacher.Find_Elective(teach_cous_id);
		if (teacher.GetElective_Courses()[cours_pos].Judge_Submit_Score() == 0)
		{
			no_submit_num++;
			if (output_flag == 0)
			{
				cout << "�㵱ǰδ�ύ�ɼ���ѡ�޿��У�" << endl;
				cout << "�γ̺�" << '\t' << "�γ���" << endl;
			}
			cout << teach_cous_id << '\t' << teacher.GetElective_Courses()[cours_pos].Get_CourseName() << endl;
		}
	}
	if (no_submit_num == 0)
		cout << "��Ŀǰû�д��ύ�ɼ��Ŀγ�" << endl;
	return no_submit_num;
}*/
int Teacher::Print_TeachNoSubmit_ReScore(Manage & teacher)
{
	int i, cours_pos, output_flag = 0, num, no_submit_num = 0;
	string teach_cous_id;
	num = Get_JoinReNum();
	for (i = 0; i < num; i++)
	{
		teach_cous_id = Get_Join_Re_Id()[i];
		cours_pos = teacher.Find_Required(teach_cous_id);
		if (teacher.GetRequired_Courses()[cours_pos].Judge_Submit_Score() == 0)
		{
			no_submit_num++;
			if (output_flag == 0)
			{
				cout << "�㵱ǰδ�ύ�ɼ��ı��޿��У�" << endl;
				cout << "�γ̺�" << '\t' << "�γ���" << endl;
				output_flag = 1;
			}
			cout << teach_cous_id << '\t' << teacher.GetRequired_Courses()[cours_pos].Get_CourseName() << endl;
		}
	}
	if (no_submit_num == 0)
		cout << "��Ŀǰû�д��ύ�ɼ��ı��޿�" << endl;
	cout << endl;
	return no_submit_num;
}
int Teacher::Print_TeachNoSubmit_EleScore(Manage & teacher)
{
	int i, cours_pos, output_flag = 0, num, no_submit_num = 0;
	string teach_cous_id;
	num = Teach_EleCous_Id.size();
	for (i = 0; i < num; i++)
	{
		teach_cous_id = Teach_EleCous_Id[i];
		cours_pos = teacher.Find_Elective(teach_cous_id);
		if (teacher.GetElective_Courses()[cours_pos].Judge_Submit_Score() == 0)
		{
			no_submit_num++;
			if (output_flag == 0)
			{
				cout << "�㵱ǰδ�ύ�ɼ���ѡ�޿��У�" << endl;
				cout << "�γ̺�" << '\t' << "�γ���" << endl;
				output_flag = 1;
			}
			cout << teach_cous_id << '\t' << teacher.GetElective_Courses()[cours_pos].Get_CourseName() << endl;
		}
	}
	if (no_submit_num == 0)
		cout << "��Ŀǰû�д��ύ�ɼ���ѡ�޿�" << endl;
	cout << endl;
	return no_submit_num;
}
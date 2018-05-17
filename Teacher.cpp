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
	cout << "你教授的必修课有:" << endl;
	cout << "课程编号" << '\t' << "课程名称" << '\t' << "课程学分" << endl;
	for (k = 0; k < Get_JoinReNum(); k++)
	{
		join_cous_id = Get_Join_Re_Id()[k];
		pos = teach.Find_Required(join_cous_id);
		if (pos != -1)
			re_cos = &teach.GetRequired_Courses()[pos];
		else
			cout << "你写入的必修课信息有误" << endl;
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
	cout << "你教授的选修课有:" << endl;
	cout << "课程编号" << '\t' << "课程名称" << '\t' << "课程学分" << endl;
	for (ele_id = Teach_EleCous_Id.begin(); ele_id != Teach_EleCous_Id.end(); ele_id++)
	{
		pos = teach.Find_Elective(*ele_id);
		if (pos != -1)
			ele_cos = &teach.GetElective_Courses()[pos];///函数的返回值用于初始化在调用函数时创建的临时对象，如果返回类型不是引用，在调用函数的地方会将函数返回值赋值给临时对象
		else
			cout << "你写入的选修课信息有误" << endl;
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
	cout << "请输入你要录入成绩的课程数量" << endl;
	cin >> num;
	//num = 1;
	for (i = 0; i < num; i++)
	{
		cout << "请选择你要录入的课程类型（1、必修课    2、选修课）" << endl;
		cin >> choice;
		//choice = 1;
		while (choice != 1 && choice != 2)
		{
			cout << "没有该选项，请重新选择!" << endl;
			cout << "请选择你要录入的课程类型（1、必修课    2、选修课）" << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			this->Print_TeachNoSubmit_ReScore(teacher);
			cout << "请选择你要录入的课程号:";
			//cin >> course_id;
			course_id = "00000002";
			while (this->Judge_Join_Re(course_id)==0)
			{
				cout << "你的课程里没有该必修课的信息，请重新输入！" << endl;
				cout << "请选择你要录入的课程号:";
				cin >> course_id;
			}
			cout << "请你逐个对学生成绩进行录入" << endl;
			cout << "学号" << '\t' << '\t' << "姓名" << '\t' << "成绩" << endl;
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
			cout << "请选择你要录入的课程号:";
			//cin >> course_id;
			//course_id = "10000006";
			Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
			while (Pcous == Teach_EleCous_Id.end())
			{
				cout << "你的课程里没有该选修课的信息，请重新输入！" << endl;
				cout << "请选择你要录入的课程号:";
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
	cout << "请输入你要修改成绩的学生数量：";
	//cin >> stu_num;
	stu_num = 3;

	for (i = 0; i < stu_num; i++)
	{
		cout << "请输入要修改成绩的学生所在的课程类型（1、必修课    2、选修课）" << endl;
		cin >> choice;
		while (choice != 1 && choice != 2)
		{
			cout << "没有该选项，请重新选择!" << endl;
			cout << "请输入当前学生所在的课程类型（1、必修课    2、选修课）" << endl;
			cin >> choice;
		}
		cout << "请输入你要修改成绩的学生所在的课程号：";
		cin >> course_id;
		if (choice == 1)
		{
			while (this->Judge_Join_Re(course_id) == 0)
			{
				cout << "你的课程里没有该必修课的信息，请重新输入！" << endl;
				cout << "请选择你要选择的课程号:";
				cin >> course_id;
			}
			cous_pos = teacher.Find_Required(course_id);
			if (cous_pos != -1)
			{
				if (teacher.GetRequired_Courses()[cous_pos].Judge_Submit_Score() == 0)
				{
					cout << "请输入你要修改成绩的学生学号：";
					cin >> student_id;
					if (teacher.GetRequired_Courses()[cous_pos].Judge_Course_Student(student_id))
					{
						stu_pos = teacher.Find_Student(student_id);
						while (stu_pos == -1)
						{
							cout << "你的课程里没有该学生信息，请重新输入你要修改的学生学号！" << endl;
							cin >> student_id;
							stu_pos = teacher.Find_Student(student_id);
						}
						cout << "该学生更新前的成绩为：" << endl;
						cout << "学号    " << "姓名" << '\t' << "成绩" << endl;
						try
						{
							score = teacher.GetRequired_Courses()[cous_pos].Find_Score(student_id);
							cout << student_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << '\t' << score << endl;
							cout << "请输入该学生更新后的成绩：";
							cin >> new_score;
							teacher.GetRequired_Courses()[cous_pos].Initial_Score(student_id, new_score);
							cout << "该学生更新后的成绩为：" << endl;
							cout << "学号" << '\t' << "姓名" << '\t' << "成绩" << endl;
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
						cout << "该学生不在没有选择该课程，你不能获取并修改他的成绩！" << endl;
					}
				}
				else
				{
					cout << "该课程的成绩已经提交，当前不可修改该课程的学生成绩" << endl;
				}
			}
			else
			{
				cout << "你的输入有误，没有找到该课程的信息！" << endl;
			}
		}
		else//choice==2
		{
			Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
			while (Pcous == Teach_EleCous_Id.end())
			{
				cout << "你的课程里没有该选修课的信息，请重新输入！" << endl;
				cout << "请选择你要选择的课程号:";
				cin >> course_id;
				Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
			}
			cous_pos = teacher.Find_Elective(course_id);
			if (cous_pos != -1)
			{
				if (teacher.GetElective_Courses()[cous_pos].Judge_Submit_Score() == 0)
				{
					cout << "请输入你要修改成绩的学生学号：" << endl;
					cin >> student_id;
					if (teacher.GetElective_Courses()[cous_pos].Judge_Course_Student(student_id))
					{
						stu_pos = teacher.Find_Student(student_id);
						while (stu_pos == -1)
						{
							cout << "你的课程里没有该学生信息，请重新输入你要修改的学生学号！" << endl;
							cin >> student_id;
							stu_pos = teacher.Find_Student(student_id);
						}
						cout << "该学生更新前的成绩为：" << endl;
						cout << "学号" << '\t' << "姓名" << '\t' << "成绩" << endl;
						try
						{
							score = teacher.GetElective_Courses()[cous_pos].Find_Score(student_id);
							cout << student_id << '\t' << teacher.GetStudents()[stu_pos].Get_UserName() << '\t' << score << endl;
							cout << "请输入该学生更新后的成绩：";
							cin >> new_score;
							teacher.GetRequired_Courses()[cous_pos].Initial_Score(student_id, new_score);
							cout << "该学生更新后的成绩为：" << endl;
							cout << "学号" << '\t' << "姓名" << '\t' << "成绩" << endl;
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
						cout << "该学生不在没有选择该课程，你不能获取并修改他的成绩！" << endl;
					}
				}
				else
				{
					cout << "该课程的成绩已经提交，当前不可修改该课程的学生成绩" << endl;
				}
			}
			else
			{
				cout << "你的输入有误，没有找到该课程的信息！" << endl;
			}
		}
		cin.clear();//清空输入流
		cin.ignore(1024, '\n');
	}
}
void Teacher::Submit_Score(Manage & teacher)
{
	int num, no_submit_Renum, i = 0, choice, cous_pos, flag_ack = 0, no_submit_Elenum;
	string course_id;
	char ack;
	vector<string>::iterator Pcous;
	cout << "你当前未提交成绩的课程为：" << endl;
	no_submit_Renum = Print_TeachNoSubmit_ReScore(teacher);
	no_submit_Elenum = Print_TeachNoSubmit_EleScore(teacher);
	if ((no_submit_Renum != 0)&& (no_submit_Elenum != 0))
	{
		cout << "请选择你要提交成绩的课程类型（1、必修课    2、选修课）" << endl;
		cin >> choice;
		while (choice != 1 && choice != 2)
		{
			cout << "没有该选项，请重新选择!" << endl;
			cout << "请选择你要提交成绩的课程类型（1、必修课    2、选修课）" << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			cout << "请输入你想提交成绩的必修课数量：";
			cin >> num;
			while (num > no_submit_Renum || num <= 0)
			{
				cout << "你的输入超出范围，请重新输入" << endl;
				cout << "请输入你想提交成绩的必修课数量：";
				cin >> num;
			}
			for (i = 0; i < num; i++)
			{
				cout << "请输入你要提交成绩的必修课课程号：";
				cin >> course_id;
				//course_id = "00000002";     ///待删
			//	cout << endl;                ///待删
				while (this->Judge_Join_Re(course_id) == 0)
				{
					cout << "你的课程里没有该必修课的信息，请重新输入！" << endl;
					cout << "请选择你要提交成绩的课程号:";
					cin >> course_id;
				}
				cous_pos = teacher.Find_Required(course_id);
				if (teacher.GetRequired_Courses()[cous_pos].Judge_Submit_Score() == 1)
					cout << "该课程成绩已经被提交过了，不可再次被提交" << endl;
				else
				{
					cout << "你确认要提交" << teacher.GetRequired_Courses()[cous_pos].Get_CourseName() << "吗？    " << "Y/y（是）" << '\t' << "N/n(否）" << endl;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							teacher.GetRequired_Courses()[cous_pos].Submit_Course_Score();
							cout << "成功提交该课程成绩！" << endl;
							flag_ack = 1;
							i++;
							no_submit_Renum--;
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "放弃提交该课程成绩！" << endl;
							flag_ack = 1;
							i++;  //避免全部放弃了之后，死循环
						}
						else
						{
							cout << "你的输入有误，请重新输入！" << endl;
						}
					}
				}
			}
		}
		else//提交选修课成绩
		{
			cout << "请输入你想提交成绩的选修课数量：";
			cin >> num;
			while (num > no_submit_Elenum || num <= 0)
			{
				cout << "你的输入超出范围，请重新输入" << endl;
				cout << "请输入你想提交成绩的选修课数量：";
				cin >> num;
			}
			for (i = 0; i < no_submit_Elenum; i++)
			{
				cout << "请输入你要提交成绩的选修课课程号：";
				//cin >> course_id;
				//course_id = "10000006";     ///待删
				//cout << endl;                ///待删
				Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
				while (Pcous == Teach_EleCous_Id.end())
				{
					cout << "你的课程里没有该选修课的信息，请重新输入！" << endl;
					cout << "请选择你要选择的提交成绩的选修课课程号:";
					cin >> course_id;
					Pcous = find(Teach_EleCous_Id.begin(), Teach_EleCous_Id.end(), course_id);
				}
				cous_pos = teacher.Find_Elective(course_id);
				if (teacher.GetElective_Courses()[cous_pos].Judge_Submit_Score() == 1)
				{
					cout << "该课程成绩已经被提交过了，不可再次被提交" << endl;
				}
				else
				{
					cout << "你确认要提交" << teacher.GetElective_Courses()[cous_pos].Get_CourseName() << "吗？    " << "Y/y（是）" << '\t' << "N/n(否）" << endl;
					flag_ack = 0;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							teacher.GetElective_Courses()[cous_pos].Submit_Course_Score();
							cout << "成功提交该课程成绩！" << endl;
							flag_ack = 1;
							no_submit_Elenum--;
							i++;
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "放弃提交该课程成绩！" << endl;
							flag_ack = 1;
							i++;  //避免全部放弃了之后，死循环
						}
						else
						{
							cout << "你的输入有误，请重新输入！" << endl;
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
				cout << "你当前未提交成绩的必修课有：" << endl;
				cout << "课程号" << '\t' << "课程名" << endl;
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
				cout << "你当前未提交成绩的选修课有：" << endl;
				cout << "课程号" << '\t' << "课程名" << endl;
			}
			cout << teach_cous_id << '\t' << teacher.GetElective_Courses()[cours_pos].Get_CourseName() << endl;
		}
	}
	if (no_submit_num == 0)
		cout << "你目前没有待提交成绩的课程" << endl;
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
				cout << "你当前未提交成绩的必修课有：" << endl;
				cout << "课程号" << '\t' << "课程名" << endl;
				output_flag = 1;
			}
			cout << teach_cous_id << '\t' << teacher.GetRequired_Courses()[cours_pos].Get_CourseName() << endl;
		}
	}
	if (no_submit_num == 0)
		cout << "你目前没有待提交成绩的必修课" << endl;
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
				cout << "你当前未提交成绩的选修课有：" << endl;
				cout << "课程号" << '\t' << "课程名" << endl;
				output_flag = 1;
			}
			cout << teach_cous_id << '\t' << teacher.GetElective_Courses()[cours_pos].Get_CourseName() << endl;
		}
	}
	if (no_submit_num == 0)
		cout << "你目前没有待提交成绩的选修课" << endl;
	cout << endl;
	return no_submit_num;
}
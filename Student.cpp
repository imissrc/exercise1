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
void Student::Select_EleCourse(Manage & stu, Student & man)////////////////////////这里应该添加一个判断该学生是否选过该课程，若已经选过则不添加
{
	string cours_id;
	int cous_pos, flag_ack = 0, ele_num, i = 0;
	char ack;
	bool judge;
	cout << "下面为所有的选修课信息" << endl;
	stu.Print_All_Ele();
	int has_join_class = GetJoinEleNum();
	////////////////////////////////////////////////////这里增加一个判断已选的课程数目，若已达上限，则不允许继续选课
	cout << "请输入你要选择的课程数量（最多参加" << MAX_ELECOUSE << "门选修课，你现在还可以选择" << MAX_ELECOUSE - has_join_class << "门课程)" << endl;
	cin >> ele_num;
	if (ele_num != 0)
	{
		while (ele_num > MAX_ELECOUSE - has_join_class || ele_num < 0)
		{
			cout << "你的输入不合法。请重新输入！" << endl;
			cin >> ele_num;
		}
		while (i < ele_num)
		{
			cout << "请输入要选择的选修课的课程编号：" << endl;
			cin >> cours_id;
			try
			{
				judge = Judge_Join_Ele(cours_id);
				cous_pos = stu.Find_Elective(cours_id);
				if (cous_pos != -1)
				{
					flag_ack = 0;
					cout << "你确定要参加“" << stu.GetElective_Courses()[cous_pos].Get_CourseName() << "”吗?" << '\t' << "Y/y（是）" << '\t' << "N/n(否）" << endl;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							Join_EleCous_Id.push_back(cours_id);

							stu.GetElective_Courses()[cous_pos].Add_Student(man.Get_UserId());
							cout << "成功加入该课程！" << endl;
							flag_ack = 1;
							i++;	//课程数目+1
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "放弃选择！" << endl;
							flag_ack = 1;
						}
						else
						{
							cout << "你的输入有误，请重新输入！" << endl;
						}
					}
				}
				else
				{
					cout << "不存在此课程哦！请重新输入你要选择的课程编号。" << endl;
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
	cout << "请输入你要退出的选修课数量（最大数目不能超过：" << this->GetJoinEleNum() << "个)：" << endl;
	cin >> del_num;
	if (del_num != 0)
	{
		while (del_num > this->GetJoinEleNum() || del_num < 0)
		{
			cout << "你的输入有误，请重新输入！" << endl;
			cin >> del_num;
		}
		while (i < del_num)
		{
			flag_ack = 0;
			cout << "请输入你要退出的课程编号：";
			cin >> cours_id;
			vector<string>::iterator id_pos = find(Join_EleCous_Id.begin(), Join_EleCous_Id.end(), cours_id);
			if (id_pos != Join_EleCous_Id.end())
			{
				pos = stu.Find_Elective(cours_id);
				cours_name = stu.GetElective_Courses()[pos].Get_CourseName();
				if (!stu.GetElective_Courses()[pos].Judge_Submit_Score())
				{
					cout << "你确定要退出“" << cours_name << "”吗?" << '\t' << "Y/y（是）" << '\t' << "N/n(否）" << endl;
					while (flag_ack == 0)
					{
						cin >> ack;
						if (ack == 'Y' || ack == 'y')
						{
							id_pos = Join_EleCous_Id.erase(id_pos);

							stu.GetElective_Courses()[pos].Delete_Student(man.Get_UserId());
							cout << "成功退出该课程！" << endl;
							flag_ack = 1;
							i++;	//课程数目+1
						}
						else if (ack == 'N' || ack == 'n')
						{
							cout << "放弃选择！" << endl;
							flag_ack = 1;
							i++;//////////虽然放弃选择了，但是应该仍加1
						}
						else
						{
							cout << "你的输入有误，请重新输入！" << endl;
						}
					}
				}
				else
				{
					cout << cours_name << "已经被任课老师提交，当前不能退出该课程" << endl;
				}
			}
			else
			{
				cout << "没有查找到该课程信息，请重新选择你要退出的课程" << endl;
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
	cout << "你已经参加的选修课有:" << endl;
	cout << "课程编号    "<< "课程名称" << '\t' << "任课老师（工号）" << "\t" << "课程学分";
	if (score_flag == 1)
		cout << '\t' << "成绩  " << "绩点";
	cout << endl;
	for (ele_id = Join_EleCous_Id.begin(); ele_id != Join_EleCous_Id.end(); ele_id++)
	{
		pos = stu.Find_Elective(*ele_id);
		if (pos != -1)
			ele_cos = &stu.GetElective_Courses()[pos];///函数的返回值用于初始化在调用函数时创建的临时对象，如果返回类型不是引用，在调用函数的地方会将函数返回值赋值给临时对象
		else
			cout << "你写入的选修课信息有误" << endl;
		tea_id = ele_cos->Get_CourseTeacherId();
		teach_pos = stu.Find_Teacher(tea_id);
		if (teach_pos != -1)
			cout << *ele_id << '\t' << ele_cos->Get_CourseName() << '\t' << stu.GetTeachers()[teach_pos].Get_UserName() << "(" << tea_id << ")" << '\t' << ele_cos->Get_CourseCredit();
		else
			cout << "你写入的选修课老师信息有误" << endl;
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
	Required_Course * re_cos = nullptr;//为什么必须要用指针
	string join_cous_id;
	double score, gpa;
	cout << "你参加的必修课有:" << endl;
	cout << "课程编号" << '\t' << "课程名称" << '\t' << "任课老师（工号）" << "\t" << "课程学分";
	if (score_flag == 1)
		cout << '\t' << "成绩  "  << "绩点";
	cout << endl;
	for (k = 0; k<Get_JoinReNum(); k++)
	{
		join_cous_id = Get_Join_Re_Id()[k];
		pos = stu.Find_Required(join_cous_id);
		if (pos != -1)
			re_cos = &stu.GetRequired_Courses()[pos];
		else
			cout << "你写入的必修课信息有误!" << endl;
		tea_id = re_cos->Get_CourseTeacherId();
		teach_pos = stu.Find_Teacher(tea_id);
		if (teach_pos != -1)
			cout << join_cous_id << '\t' << re_cos->Get_CourseName() << '\t' << stu.GetTeachers()[teach_pos].Get_UserName() << "(" << tea_id << ")" << '\t' << re_cos->Get_CourseCredit();
		else
			cout << "你写入的必修课老师信息有误!" << endl;
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
	string s = "你已经加入该课程了，不能重复加入";
	if (cour_pos != Join_EleCous_Id.end())
	{
		throw s;
	}
	else
		return false;
}
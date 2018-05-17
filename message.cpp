#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;
#include"User.h"
#include"message.h"

const int MAX_ELECOUSE = 3;
//bool TEACHER_SUBMIT_SCORE = 0;

void split(vector<string> & READ, string info)
{
	stringstream is;
	is.clear();
	is << info;
	while (is >> info)
	{
		READ.push_back(info);
	}
	is.str("");
}
double str_to_f(string & s)
{
	int len = s.length(), i = 0, sum_int = 0;
	double sum_xiao = 0, sum;

	while (s[i] != '.'&& i < len)
	{
		sum_int = sum_int * 10 + s[i] - '0';
		i++;
	}
	if (s[i] == '.')
	{
		i++;
		while (i < len)
		{
			i++;
			sum_xiao = sum_xiao + (s[i] - '0') * 0.1;
		}
	}
	sum = sum_int + sum_xiao;
	return sum;
}

void Menu_Stu(string & id, string & password)
{
	cout << "学号：";
	//cin >> id;
	id = "20160003";
	cout << "登录密码：";
	//cin >> password;
	password = "11111111";
}
void Menu_Teacher(string & id, string & password)
{
	cout << "工号：";
	//cin >> id;
	id = "20000001";
	cout << "登录密码：";
	//cin >> password;
	password = "11111111";
}
void Stu_Options(Student & newStu)
{
	cout << "请输入你要进行的操作：" << endl;
	cout << "1:选课" << endl;
	cout << "2:退课" << endl;
	cout << "3:查看自己的所有课程" << endl;
	cout << "4:查看开的所有课程" << endl;
	cout << "5：查看课程成绩和绩点" << endl;
	cout << "6:退出程序" << endl;
}
void Teach_Options(Teacher & newTeach)
{
	cout << "请输入你要进行的操作：" << endl;
	cout << "1:录入课程成绩" << endl;
	cout << "2:修改课程成绩" << endl;
	cout << "3:提交课程成绩" << endl;
	cout << "4:查看自己教授的所有课程" << endl;
	cout << "5:查看开的所有课程" << endl;
	cout << "6:退出程序" << endl;
}
void Print_Function_Choice()
{
	cout << "请输入你要进行的操作" << endl;
	cout << "1:学生登录" << endl;
	cout << "2:教师登录" << endl;
	cout << "3:退出该系统" << endl;
}
/*CException::CException(const string s)
{
	msg = s;
}
void CException::Init(const string s)
{
	msg = s;
}*/
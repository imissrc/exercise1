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
	cout << "ѧ�ţ�";
	//cin >> id;
	id = "20160003";
	cout << "��¼���룺";
	//cin >> password;
	password = "11111111";
}
void Menu_Teacher(string & id, string & password)
{
	cout << "���ţ�";
	//cin >> id;
	id = "20000001";
	cout << "��¼���룺";
	//cin >> password;
	password = "11111111";
}
void Stu_Options(Student & newStu)
{
	cout << "��������Ҫ���еĲ�����" << endl;
	cout << "1:ѡ��" << endl;
	cout << "2:�˿�" << endl;
	cout << "3:�鿴�Լ������пγ�" << endl;
	cout << "4:�鿴�������пγ�" << endl;
	cout << "5���鿴�γ̳ɼ��ͼ���" << endl;
	cout << "6:�˳�����" << endl;
}
void Teach_Options(Teacher & newTeach)
{
	cout << "��������Ҫ���еĲ�����" << endl;
	cout << "1:¼��γ̳ɼ�" << endl;
	cout << "2:�޸Ŀγ̳ɼ�" << endl;
	cout << "3:�ύ�γ̳ɼ�" << endl;
	cout << "4:�鿴�Լ����ڵ����пγ�" << endl;
	cout << "5:�鿴�������пγ�" << endl;
	cout << "6:�˳�����" << endl;
}
void Print_Function_Choice()
{
	cout << "��������Ҫ���еĲ���" << endl;
	cout << "1:ѧ����¼" << endl;
	cout << "2:��ʦ��¼" << endl;
	cout << "3:�˳���ϵͳ" << endl;
}
/*CException::CException(const string s)
{
	msg = s;
}
void CException::Init(const string s)
{
	msg = s;
}*/
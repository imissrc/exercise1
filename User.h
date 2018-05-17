#pragma once
#include<vector>
//using namespace std;
extern class Manage* stu;//////////声明，防止重复定义
class User
{
private:
	string User_Name;
	string User_Id;
	string User_Academy;
	string User_Password;
	double score;
	vector<string>Req_Courses_Id;
public:
	User();
	void Init_User(const string & name, const string & id, const string & academy, const string & password, vector<string> & join_cous_id);
	string Get_UserName();
	string Get_UserId();
	string Get_UserAcademy();
	string Get_UserPassword();
	vector<string>&Get_Join_Re_Id();
	int Get_JoinReNum();
	bool Judge_Join_Re(const string re_id);
};

class Student :public User
{
private:
	string Student_Class;
	vector<string>Join_EleCous_Id;
public:
	Student();
	void Init_Student(const string & name, const string & id, const string & academy, const string & password, const string & stuclass, vector<string> & join_re_cous_id, vector<string> & join_ele_cous_id);
	void Select_EleCourse(Manage & stu, Student & man);
	void Delete_JoinEleCous(Manage & stu, Student & man);
	//vector<string> GetJoinEleId();
	//void JoinELE_Info(vector<string> & id, vector<string> & name,vector<string> & )
	int GetJoinEleNum();
	//<string>::iterator GetFirst_CousId();
	void Print_JoinEle(Manage & stu, const int score_flag);
	void Print_JoinRe(Manage & stu, const int score_flag);
	bool Judge_Join_Ele(string cours_id);
};

class Teacher :public User
{
private:
	vector<string>Teach_EleCous_Id;
public:
	Teacher();
	void Init_Teacher(const string & name, const string & id, const string & academy, const string & password, vector<string> & teach_re_cous_id, vector<string> & teach_ele_cous_id);
	void Print_JoinRe(Manage & teach, const int print_stu_flag);
	void Print_JoinEle(Manage & stu, const int print_stu_flag);
	void Register_Score(Manage & teacher);
	void Modify_Score(Manage & teacher);
	void Submit_Score(Manage & teacher);
	//int Print_TeachNoSubmitScore(Manage & teacher);//打印未提交成绩的课程信息顺便返回数量
	int Print_TeachNoSubmit_ReScore(Manage & teacher);
	int Print_TeachNoSubmit_EleScore(Manage & teacher);
};

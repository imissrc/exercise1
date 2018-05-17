#pragma once
#include"User.h"
#include"Course.h"
//#include<vector>
//#include<iostream>
//using namespace std;
class Manage
{
private:
	vector<Required_Course>required_courses;
	vector<Elective_Course>elective_courses;
	vector<Student>students;
	vector<Teacher>teachers;
public:
	vector<Required_Course> & GetRequired_Courses();
	vector<Elective_Course> & GetElective_Courses();
	vector<Student> & GetStudents();
	vector<Teacher> & GetTeachers();

	Manage();
	void Student_User(Manage & user);
	void Teacher_User(Manage & user);

	void Stu_Initial();
	void Teach_Initial();
	void ReqCou_Initial();
	void EleCou_Initial();
	//void Course_Initial(const string & File_Name);
	void Initial_All_Info();

	int Find_Student(const string stu_id);
	int Find_Teacher(const string teacher_id);
	int Find_Required(const string re_id);
	int Find_Elective(const string ele_id);

	int GetStudentNum();
	int GetTeacherNum();
	int GetReNum();
	int GetEleNum();

	void Print_All_Re();
	void Print_All_Ele();
	void Print_Info();

};
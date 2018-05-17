#pragma once
extern const int MAX_ELECOUSE;
//extern bool TEACHER_SUBMIT_SCORE;
/*class Course;
class Required_Course;
class Elective_Course;
class User;
class Student;
class Teacher;
extern Manage user;*/

extern void split(vector<string> & READ, string info);
extern double str_to_f(string & s);
extern void Menu_Stu(string & id, string & password);
extern void Menu_Teacher(string & id, string & password);
extern void Stu_Options(Student & newStu);
extern void Teach_Options(Teacher & newTeach);
extern void Print_Function_Choice();

/*class CException
{
public:
	string msg;
	CException(const string s);
	void Init(const string s);
}cexception;*/
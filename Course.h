#pragma once
#include<map>
class Course
{
private:
	string Course_Id;
	string Course_Name;
	double Course_Credit;
	string Course_Teacher_Id;    //教授课程的老师（没有变化）
	map<string, double>Course_Student;//学号，分数
	bool TEACHER_SUBMIT_SCORE;
	//int Course_Student_Num;
public:
	Course();
	//void Init_Course(const string & id, const string & name, const double & credit, const string & teacher_id, vector<string> & student_id, const int course_student_num);
	void Init_Course(const string & id, const string & name, const double & credit, const string & teacher_id, vector<string> & student_id);
	void Init_Stu(const string id, const double score);	//添加学生
	virtual double Course_GPA(const double Student_Score) = 0;
	string Get_CourseId();
	string Get_CourseName();
	double Get_CourseCredit();
	string Get_CourseTeacherId();
	//vector<string> & GetCourse_Student();
	map<string, double> & GetCourse_Student();
	int Get_CourseStu_Num();
	double Get_All_StuScore();
	void Delete_Student(const string & stu_id);
	vector<string> & Get_Course_Student();
	void Initial_Score(const string stu_id, const double score);
	double Find_Score(string stu_id);
	void Submit_Course_Score();
	bool Judge_Submit_Score();
	bool Judge_Course_Student(const string stu_id);
};

class Required_Course :public Course
{
	//绩点计算方式
//private:
//	vector<string>Required_Students_Id;  //参加课程的学生（学生没有变化）
public:
	//void Init_Required(const string & id, const string & name, const double & credit, const string & teacher_id, vector<string> & student_id);
	virtual double Course_GPA(const double Student_Score);
	Required_Course();
};

class Elective_Course :public Course
{
//private:
//	map<string, bool>TEACHER_SUBMIT_SCORE;
	//vector<string>Elective_Students_Id;  //参加课程的学生(可能会有变化）
//	vector<double>score;
public:
	Elective_Course();//这里的Init_Elective相较于Required多了一个初始化TEACHER_SUBMIT_SCORE
	//void Init_Elective(const string & id, const string & name, const double & credit, const string & teacher, vector<string> & students_id);
	virtual double Course_GPA(const double Student_Score);
	void Add_Student(const string & stu_id);
};
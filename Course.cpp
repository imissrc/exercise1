#include<string>
#include<vector>
#include<cmath>
//#include<iostream>
using namespace std;
#include"Course.h"
Course::Course()
{

}
void Course::Init_Course(const string & id, const string & name, const double & credit, const string & teacher_id, vector<string> & student_id)
{
	Course_Id = id;
	Course_Name = name;
	Course_Credit = credit;
	Course_Teacher_Id = teacher_id;
	TEACHER_SUBMIT_SCORE = 0;
	vector<string>::iterator stu;
	Course_Student.clear();
	for (stu = student_id.begin(); stu != student_id.end(); stu++)
	{
		//Required_Students_Id.push_back(*stu);
		Init_Stu(*stu, 0);
		//cout << *stu << '\t';
	}
}
string Course::Get_CourseId()
{
	return Course_Id;
}
string Course::Get_CourseName()
{
	return Course_Name;
}
double Course::Get_CourseCredit()
{
	return Course_Credit;
}
string Course::Get_CourseTeacherId()
{
	return Course_Teacher_Id;
}
void Course::Init_Stu(const string id, const double score)
{
	Course_Student.insert(make_pair(id, score));
}
map<string, double> & Course::GetCourse_Student()
{
	return Course_Student;
}
vector<string>  & Course::Get_Course_Student()
{
	map<string, double>::iterator stu_pos;
	static vector<string>Cou_student;
	string stu_id;
//	cout << "课程学生为：" << endl;
	for (stu_pos = Course_Student.begin(); stu_pos != Course_Student.end(); stu_pos++)
	{
		stu_id = stu_pos->first;
	//	cout << stu_pos->first << endl;
		Cou_student.push_back(stu_id);
	}
	return Cou_student;
}
int Course::Get_CourseStu_Num()
{
	//cout << "课程学生数量为:" << Course_Student_Num << endl;
//	cout << "课程学生数量为:" << Course_Student.size() << endl;
	//return Course_Student_Num;
	return Course_Student.size();
}
double Course::Get_All_StuScore()
{
	map<string, double>::iterator Cours_Stu;
	double all_score = 0;
	for (Cours_Stu = Course_Student.begin(); Cours_Stu != Course_Student.end(); Cours_Stu++)
	{
		all_score += Cours_Stu->second;
	}
	return all_score;
}
double Course::Find_Score(string stu_id)//这里使用map的迭代器里面的find,参数类型必须不能是const类型的
{
	
	map<string, double>::iterator Cours_Stu = Course_Student.find(stu_id);	
	string s = "没有找到你的成绩信息";
	if (Cours_Stu == Course_Student.end())
		throw s;
	else
		return Cours_Stu->second;
}
/*vector<string> & Get_Course_Student()
{
	
}*/
void Course::Initial_Score(const string stu_id, const double score)
{
	Course_Student[stu_id] = score;
}
void Course::Delete_Student(const string & stu_id)
{
	map<string, double>::iterator Cours_Stu=Course_Student.find(stu_id);
	if (Cours_Stu != Course_Student.end())
		Course_Student.erase(Cours_Stu++);
}
bool Course::Judge_Submit_Score()
{
	if (TEACHER_SUBMIT_SCORE == 0)
		return false;
	else
		return true;
}
void Course::Submit_Course_Score()
{
	TEACHER_SUBMIT_SCORE = 1;
}
bool Course::Judge_Course_Student(const string stu_id)
{
	map<string, double>::iterator Cours_Stu = Course_Student.find(stu_id);
	if (Cours_Stu != Course_Student.end())
		return true;
	else
		return false;
}
Required_Course::Required_Course()
{

}
/*void Required_Course::Init_Required(const string & id, const string & name, const double & credit, const string & teacher_id, vector<string> & student_id)
{
	Course::Init_Course(id, name, credit, teacher_id);
	vector<string>::iterator stu;
	for (stu = student_id.begin(); stu != student_id.end(); stu++)
	{
		//Required_Students_Id.push_back(*stu);
		Init_Stu(*stu, 0);
		cout << *stu << '\t';
	}
	cout << endl;
}
*/
double Required_Course::Course_GPA(const double Student_Score)
{
	double gpa;
	double course_credit = Get_CourseCredit();
	double all_score = Get_All_StuScore();
	string s = "任课老师还提交该课程的成绩,现在不能查看你的成绩和绩点！";
	if (Judge_Submit_Score() == false)
	{
		throw s;
	}
	else if(all_score == 0 || Student_Score == 0)
	{
		return 0;
	}
	else
	{
		gpa = (Student_Score / all_score)* course_credit;
		return gpa;
	}
}

Elective_Course::Elective_Course()
{

}
/*void Elective_Course::Init_Elective(const string & id, const string & name, const double & credit, const string & teacher, vector<string> & students_id)
{
	Init_Course(id, name, credit, teacher);
	vector<string>::iterator stu;
	for (stu = students_id.begin(); stu != students_id.end(); stu++)
	{
		//Elective_Students_Id.push_back(*stu);
		Init_Stu(*stu, 0);
	}
}*/
double Elective_Course::Course_GPA(const double Student_Score)
{
	double gpa;
	double course_credit = Get_CourseCredit();
	string s = "任课老师还提交该课程的成绩,现在不能查看你的成绩和绩点！";
	if (Judge_Submit_Score() == false)
	{
		throw s;
	}
	else
	{
		gpa = (sqrt(Student_Score) / 10) * course_credit;
		if (Student_Score == 0)
			return 0;
		else
			return gpa;
	}
}
void Elective_Course::Add_Student(const string & stu_id)
{
	Init_Stu(stu_id, 0); 
}

/*void Elective_Course::Delete_Student(const string & stu_id)
{
	map<string, double>::iterator Cours_Stu = Course_Student.find(stu_id);
	Course_Student.erase(Cours_Stu);
//	Delete_Ele_Student(stu_id);
}*/
/*vector<string>Elective_Course::Get_EleStuId()
{
return Elective_Students_Id;
}*/
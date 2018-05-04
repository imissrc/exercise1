#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
//程序改进思路，将各个类再进行嵌套，数据和操作分开
using namespace std;
class Course;
class Required_Course;
class Elective_Course;
class User_Course;
class Student;
class Teacher;
int GetVecNum(vector<string> & a);
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
class Course
{
private:
	string Course_Id;
	string Course_Name;
	double Course_Credit;
	string Course_Teacher_Id;    //教授课程的老师（没有变化）
	double score;
public:
	Course();
	void Init_Course(const string & id, const string & name, const double & credit, const string & teacher_id);
	virtual double Course_GPA(double Course_Credit, double Student_Score, double All_Score) = 0;
	string Get_CourseId();
	string Get_CourseName();
	double Get_CourseCredit();
	string Get_CourseTeacherId();
};
Course::Course()
{

}
void Course::Init_Course(const string & id, const string & name, const double & credit, const string & teacher_id)
{
	Course_Id = id;
	Course_Name = name;
	Course_Credit = credit;
	Course_Teacher_Id = teacher_id;
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

class Required_Course :public Course
{
	//绩点计算方式
private:
	vector<string>Required_Students_Id;  //参加课程的学生（学生没有变化）
public:
	void Init_Required(const string & id, const string & name, const double & credit, const string & teacher_id, vector<string> & student_id);
	virtual double Course_GPA(double Course_Credit, double Student_Score, double All_Score);
	Required_Course();
	/*string Get_CourseId()
	{
	return Course::Get_CourseId();
	}*/
};
Required_Course::Required_Course()
{

}
void Required_Course::Init_Required(const string & id, const string & name, const double & credit, const string & teacher_id, vector<string> & student_id)
{
	Course::Init_Course(id, name, credit, teacher_id);
	vector<string>::iterator stu;
	for (stu = student_id.begin(); stu != student_id.end(); stu++)
	{
		Required_Students_Id.push_back(*stu);
	}

}
double Required_Course::Course_GPA(double Course_Credit, double Student_Score, double All_Score)
{
	double gpa;
	gpa = Student_Score / All_Score*Course_Credit;
	return gpa;
}

class Elective_Course :public Course
{
private:
	vector<string>Elective_Students_Id;  //参加课程的学生(可能会有变化）
public:
	Elective_Course();
	void Init_Elective(const string & id, const string & name, const double & credit, const string & teacher, vector<string> & students_id);
	virtual double Course_GPA(double Course_Credit, double Student_Score, double All_Score);
	/*string Get_CourseId()
	{
	return Course::Get_CourseId();
	}*/
};
Elective_Course::Elective_Course()
{

}
void Elective_Course::Init_Elective(const string & id, const string & name, const double & credit, const string & teacher, vector<string> & students_id)
{
	Init_Course(id, name, credit, teacher);
	vector<string>::iterator stu;
	for (stu = students_id.begin(); stu != students_id.end(); stu++)
	{
		Elective_Students_Id.push_back(*stu);
	}
}
double Elective_Course::Course_GPA(double Course_Credit, double Student_Score, double All_Score)
{
	double gpa;
	gpa = sqrt(Student_Score) / 10 * Course_Credit;
	return gpa;
}

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

	virtual void Menu() = 0;
};
User::User()
{

}
void User::Init_User(const string & name, const string & id, const string & academy, const string & password, vector<string> & join_cous_id)
{
	User_Name = name;
	User_Id = id;
	User_Academy = academy;
	User_Password = password;
	vector<string>::iterator cous;
	for (cous = join_cous_id.begin(); cous != join_cous_id.end(); cous++)
	{
		Req_Courses_Id.push_back(*cous);
	}
}
string User::Get_UserName()
{
	return User_Name;
}
string User::Get_UserId()
{
	return User_Id;
}
string User::Get_UserAcademy()
{
	return User_Academy;
}

class Student :public User
{
private:
	string Student_Class;
	vector<string>Join_EleCous_Id;
public:
	Student();
	void Menu();
	void Init_Student(const string & name, const string & id, const string & academy, const string & password, const string & stuclass, vector<string> & join_re_cous_id, vector<string> & join_ele_cous_id);
	/*string Get_UserId()
	{
	return User::Get_UserId();
	}*/
	//void Init_JoinEleCous(vector<Elective_Course>join_cours);   //选修课可修改
	//	void Change_JoinEleCous(vector<Elective_Course>join_cous, string cous_id);(还没实现）
};
Student::Student()
{

}
void Student::Menu()
{
	string id;
	string password;
	cout << "学号：";
	cin >> id;
	cout << "登录密码：";
	cin >> password;

}
void Student::Init_Student(const string & name, const string & id, const string & academy, const string & password, const string & stuclass, vector<string> & join_re_cous_id, vector<string> & join_ele_cous_id)
{
	User::Init_User(name, id, academy, password, join_re_cous_id);
	vector<string>::iterator cous;
	for (cous = join_ele_cous_id.begin(); cous != join_ele_cous_id.end(); cous++)
	{
		Join_EleCous_Id.push_back(*cous);
	}
	Student_Class = stuclass;
}
/*void Student::Init_JoinEleCous(vector<Elective_Course>join_cous)
{
vector<Elective_Course>::iterator cous;
for (cous = join_cous.begin(); cous != join_cous.end(); cous++)
{
Join_EleCous.push_back(*cous);
}
}*/

class Teacher :public User
{
	vector<string>Teach_EleCous_Id;
public:
	Teacher();
	void Menu();
	void Init_Teacher(const string & name, const string & id, const string & academy, const string & password, vector<string> & teach_re_cous_id, vector<string> & join_ele_cous_id);
	/*string Get_UserId()
	{
	return User::Get_UserId();
	}*/
};
Teacher::Teacher()
{

}
void Teacher::Menu()
{
	string id;
	string password;
	cout << "工号：";
	cin >> id;
	cout << "登录密码：";
	cin >> password;

}
void Teacher::Init_Teacher(const string & name, const string & id, const string & academy, const string & password, vector<string> & teach_re_cous_id, vector<string> & join_ele_cous_id)
{
	User::Init_User(name, id, academy, password, teach_re_cous_id);
}

class Manage
{
private:
	vector<Required_Course>required_courses;
	vector<Elective_Course>elective_courses;
	vector<Student>students;
	vector<Teacher>teachers;
public:
	void Stu_Initial();
	void Teach_Initial();
	void ReqCou_Initial();
	void EleCou_Initial();
	vector<Required_Course> GetRequired_Courses();
	vector<Elective_Course> GetElective_Courses();
	vector<Student> GetStudents();
	vector<Teacher> GetTeachers();
	void Student_User();
	void Teacher_User();

	int Find_Student(string stu_id);
	int Find_Teacher(string teacher_id);
	int Find_Required(string re_id);
	int Find_Elective(string ele_id);

	int GetStudentNum();
	int GetTeacherNum();
	int GetReNum();
	int GetEleNum();

	void Print_Info();

};

void Manage::Print_Info()
{
	vector<Student>::iterator stu;
	for (stu = students.begin(); stu != students.end(); stu++)
	{
		cout << stu->Get_UserId() << '\t' << stu->Get_UserName() << '\t' << stu->Get_UserAcademy() << endl;;
	}
}
vector<Required_Course> Manage::GetRequired_Courses()
{
	return required_courses;
}
vector<Elective_Course> Manage::GetElective_Courses()
{
	return elective_courses;
}
vector<Student> Manage::GetStudents()
{
	return students;
}
vector<Teacher> Manage::GetTeachers()
{
	return teachers;
}
void Manage::Teacher_User()
{
	//查看自己的课程（必修课、选修课）、查看所有选课学生的名单，以及查看指定选课学生的学生信息
	//录入自己所带课程的成绩，可以修改指定选课学生的课程成绩。成绩在提交后不可更改，成绩在提交后可被学生看到
}

void Menu(string id, string password)
{
	cout << "学号：";
	cin >> id;
	cout << "登录密码：";
	cin >> password;
}

void Manage::Student_User()
{
	Stu_Initial();
	Teach_Initial();
	ReqCou_Initial();
	EleCou_Initial();

	string id, password;
	Student newStu;
	Menu(id, password);
	/*vector<Student>::iterator findStu = find(students.begin(),students.end(),id);/////这里考虑是否能进一步优化，只比较里面的id号
	if (findStu != students.end())
	{
	newStu = *findStu;
	}*/

	//查看自己的课程（必修课、选修课）、选课、退课、提交自己的选择、查看所有课程
	//查看自己每门课程的成绩和绩点
}


void Manage::Stu_Initial()
{
	ifstream ReadFile;

	Student stu;

	string name, id, stuclass, academy, password;
	string info_re_id, info_ele_id, stu_info;
	string unnecessary;
	vector<string>RE_ID_READ, ELE_ID_READ, STU_INFO;

	ReadFile.open("Student_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Student_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, stu_info))
	{
		split(STU_INFO, stu_info);
		id = STU_INFO[0];
		name = STU_INFO[1];
		stuclass = STU_INFO[2];
		academy = STU_INFO[3];
		password = STU_INFO[4];

		getline(ReadFile, info_re_id);
		split(RE_ID_READ, info_re_id);
		getline(ReadFile, info_ele_id);
		split(ELE_ID_READ, info_ele_id);
		
		stu.Init_Student(name, id, academy, password, stuclass, RE_ID_READ, ELE_ID_READ);
		students.push_back(stu);
		getline(ReadFile, unnecessary);

		STU_INFO.clear();
		RE_ID_READ.clear();
		ELE_ID_READ.clear();
	}
	Print_Info();
	ReadFile.close();

}


void Manage::Teach_Initial()
{
	ifstream ReadFile;

	Teacher teach;
	string name, id, academy, password;
	string info_re_id, info_ele_id, teacher_info;
	string unnecessary;
	int i;
	vector<string>RE_ID_READ, ELE_ID_READ, TEACHER_INFO;

	ReadFile.open("Teacher_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Teacher_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, teacher_info))
	{
		split(TEACHER_INFO, teacher_info);

		id = TEACHER_INFO[0];
		name = TEACHER_INFO[1];
		academy = TEACHER_INFO[2];
		password = TEACHER_INFO[3];

		getline(ReadFile, info_re_id);
		split(RE_ID_READ, info_re_id);
		getline(ReadFile, info_ele_id);
		split(ELE_ID_READ, info_ele_id);

		teach.Init_Teacher(name, id, academy, password, RE_ID_READ, ELE_ID_READ);
		teachers.push_back(teach);
		getline(ReadFile, unnecessary);

		TEACHER_INFO.clear();
		RE_ID_READ.clear();
		ELE_ID_READ.clear();
	}
	ReadFile.close();
}

void Manage::ReqCou_Initial()
{
	ifstream ReadFile;

	Required_Course req_cou;
	string name, class_id, academy, teacher_id;
	double credit;
	string info_stu_id, course_info;
	string unnecessary;
	int i;
	vector<string>STU_ID_READ, COURSE_INFO;
	ReadFile.open("Required_Course_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Required_Course_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, course_info))
	{
		split(COURSE_INFO, course_info);

		class_id = COURSE_INFO[0];
		name = COURSE_INFO[1];
		credit = str_to_f(COURSE_INFO[2]);
		teacher_id = COURSE_INFO[3];

		getline(ReadFile, info_stu_id);
		split(STU_ID_READ, info_stu_id);
	
		req_cou.Init_Required(class_id, name, credit, teacher_id, STU_ID_READ);
		required_courses.push_back(req_cou);
		getline(ReadFile, unnecessary);

		COURSE_INFO.clear();
		STU_ID_READ.clear();
	}
	ReadFile.close();

}
void Manage::EleCou_Initial()
{
	ifstream ReadFile;

	Elective_Course ele_cou;
	string name, class_id, academy, teacher_id;
	double credit;
	string info_stu_id, course_info;
	string unnecessary;
	int i;

	vector<string>STU_ID_READ, COURSE_INFO;

	ReadFile.open("Elective_Course_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Elective_Course_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, course_info))
	{
		split(COURSE_INFO, course_info);

		class_id = COURSE_INFO[0];
		name = COURSE_INFO[1];
		credit = stof(COURSE_INFO[2]);
		teacher_id = COURSE_INFO[3];

		getline(ReadFile, info_stu_id);
		split(STU_ID_READ, info_stu_id);
	
		ele_cou.Init_Elective(class_id, name, credit, teacher_id, STU_ID_READ);
		elective_courses.push_back(ele_cou);
		getline(ReadFile, unnecessary);

		COURSE_INFO.clear();
		STU_ID_READ.clear();
	}
	ReadFile.close();
}
int Manage::Find_Student(string stu_id)
{
	int flag = 0, i;
	for (i = 0; flag == 0 && i < GetStudentNum(); i++)
	{
		if (stu_id == students[i].Get_UserId())
			flag = 1;
	}
	if (flag == 1)
		return i;
	else
		return -1;
}
int Manage::Find_Teacher(string teacher_id)
{
	int flag = 0, i;
	for (i = 0; flag == 0 && i < GetTeacherNum(); i++)
	{
		if (teacher_id == teachers[i].Get_UserId())
			flag = 1;
	}
	if (flag == 1)
		return i;
	else
		return -1;
}
int Manage::Find_Required(string re_id)
{
	int flag = 0, i;
	for (i = 0; flag == 0 && i < GetReNum(); i++)
	{
		if (re_id == required_courses[i].Get_CourseId())
			flag = 1;
	}
	if (flag == 1)
		return i;
	else
		return -1;
}
int Manage::Find_Elective(string ele_id)
{
	int flag = 0, i;
	for (i = 0; flag == 0 && i < GetEleNum(); i++)
	{
		if (ele_id == elective_courses[i].Get_CourseId())
			flag = 1;
	}
	if (flag == 1)
		return i;
	else
		return -1;
}

int Manage::GetStudentNum()
{
	return students.size();
}
int Manage::GetTeacherNum()
{
	return teachers.size();
}
int Manage::GetReNum()
{
	return required_courses.size();
}
int Manage::GetEleNum()
{
	return elective_courses.size();
}
int main()
{
	cout << "Please choose your user account type:	1:Student	2:Teacher\n";
	int choice;
	Manage user;
	cin >> choice;
	if (choice == 1)
	{
		user.Student_User();//用学号和密码登录。
		user.Print_Info();
	}
	else if (choice == 2)
	{
		user.Teacher_User();
	}
}
int GetVecNum(vector<string> & a)
{
	return a.size();
}
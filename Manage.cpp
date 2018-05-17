#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
#include"Manage.h"
#include"message.h"
Manage::Manage()
{

}
void Manage::Print_Info()
{
	/*vector<Teacher>::iterator teach;
	for (teach = teachers.begin(); teach != teachers.end(); teach++)
	{
		cout << teach->Get_JoinReNum() << '\t' << teach->Get_UserName() << '\t' << endl;
	}*/
	vector<Teacher>::iterator stu;
	for (stu = teachers.begin(); stu != teachers.end(); stu++)
	{
		cout << stu->Get_UserId() << '\t' << stu->Get_UserName() << '\t' << stu->Get_UserAcademy() << endl;;
	}
}
vector<Required_Course> & Manage ::GetRequired_Courses()
{
	return required_courses;
}
vector<Elective_Course> & Manage::GetElective_Courses()
{
	return elective_courses;
}
vector<Student> & Manage::GetStudents()
{
	return students;
}
vector<Teacher> & Manage::GetTeachers()
{
	return teachers;
}
void Manage::Initial_All_Info()
{
	Stu_Initial();
	Teach_Initial();
//	Print_Info();
	ReqCou_Initial();
	//Course_Initial("Required_Course_Info.txt");
//	Print_All_Re();
	//Print_Info();
	EleCou_Initial();
}
void Manage::Stu_Initial()
{
	ifstream ReadFile;

	Student stu;

	string name, id, stuclass, academy, password;
	string info_re_id, info_ele_id, stu_info;
	string unnecessary;
	int re_num = 0, ele_num = 0, unnes = 0;
	ReadFile.open("Student_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Student_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, stu_info))
	{
		vector<string>RE_ID_READ, ELE_ID_READ, STU_INFO;
		split(STU_INFO, stu_info);
		id = STU_INFO[0];
		name = STU_INFO[1];
		stuclass = STU_INFO[2];
		academy = STU_INFO[3];
		password = STU_INFO[4];

		if (getline(ReadFile, info_re_id))
			if (info_re_id != "")
				split(RE_ID_READ, info_re_id);
		if (getline(ReadFile, info_ele_id))
			if (info_ele_id != "")
				split(ELE_ID_READ, info_ele_id);

		stu.Init_Student(name, id, academy, password, stuclass, RE_ID_READ, ELE_ID_READ);
		students.push_back(stu);
		getline(ReadFile, unnecessary);

		STU_INFO.clear();
		RE_ID_READ.clear();
		ELE_ID_READ.clear();
		vector<string>().swap(RE_ID_READ);
		vector<string>().swap(ELE_ID_READ);
		vector<string>().swap(STU_INFO);
	}
	//Print_Info()
	ReadFile.close();

}
void Manage::Teach_Initial()
{
	ifstream ReadFile;

	Teacher teach;
	string name, id, academy, password;
	string info_re_id, info_ele_id, teacher_info;
	string unnecessary;
	//int re_num = 0, ele_num = 0, unnes = 0;
	ReadFile.open("Teacher_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Teacher_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, teacher_info))
	{
		vector<string>RE_ID_READ, ELE_ID_READ, TEACHER_INFO;
		split(TEACHER_INFO, teacher_info);

		id = TEACHER_INFO[0];
		name = TEACHER_INFO[1];
		academy = TEACHER_INFO[2];
		password = TEACHER_INFO[3];

		if (getline(ReadFile, info_re_id))/////////////////////////////////////////增加了读取空串的判断
			if (info_re_id != "")
				split(RE_ID_READ, info_re_id);//////////////////////////////////////////////////////////////////////////////////这里出bug了
		if (getline(ReadFile, info_ele_id))
			if (info_ele_id != "")
				split(ELE_ID_READ, info_ele_id);


		teach.Init_Teacher(name, id, academy, password, RE_ID_READ, ELE_ID_READ);
		teachers.push_back(teach);
		getline(ReadFile, unnecessary);

		TEACHER_INFO.clear();
		RE_ID_READ.clear();
		ELE_ID_READ.clear();
		vector<string>().swap(RE_ID_READ);
		vector<string>().swap(ELE_ID_READ);
		vector<string>().swap(TEACHER_INFO);
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
	vector<string>STU_ID_READ, COURSE_INFO;
	//int ifo_count = 0, stu_count = 0;
	ReadFile.open("Required_Course_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Course_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, course_info))
	{
		//stu_count = 0;
		split(COURSE_INFO, course_info);

		class_id = COURSE_INFO[0];
		name = COURSE_INFO[1];
		credit = str_to_f(COURSE_INFO[2]);
		teacher_id = COURSE_INFO[3];

		if (getline(ReadFile, info_stu_id))
			if (info_stu_id != "")
				split(STU_ID_READ, info_stu_id);
		
		req_cou.Init_Course(class_id, name, credit, teacher_id, STU_ID_READ);
		required_courses.push_back(req_cou);
		getline(ReadFile, unnecessary);

		COURSE_INFO.clear();
		STU_ID_READ.clear();
		vector<string>().swap(COURSE_INFO);
		vector<string>().swap(STU_ID_READ);
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


	ReadFile.open("Elective_Course_Info.txt", ios::in);
	if (!ReadFile)
	{
		cout << "Initial_Elective_Course_File open error!" << endl;
	}

	getline(ReadFile, unnecessary);
	while (getline(ReadFile, course_info))
	{
		vector<string>STU_ID_READ, COURSE_INFO;
		split(COURSE_INFO, course_info);

		class_id = COURSE_INFO[0];
		name = COURSE_INFO[1];
		credit = stof(COURSE_INFO[2]);
		teacher_id = COURSE_INFO[3];

		if (getline(ReadFile, info_stu_id))
			if (info_stu_id != "")
				split(STU_ID_READ, info_stu_id);

		ele_cou.Init_Course(class_id, name, credit, teacher_id, STU_ID_READ);
		elective_courses.push_back(ele_cou);
		getline(ReadFile, unnecessary);

		COURSE_INFO.clear();
		STU_ID_READ.clear();
		vector<string>().swap(COURSE_INFO);
		vector<string>().swap(STU_ID_READ);
	}
	ReadFile.close();
}
int Manage::Find_Student(const string stu_id)
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
int Manage::Find_Teacher(const string teacher_id)
{
	int flag = 0, i;
	for (i = 0; flag == 0 && i < GetTeacherNum(); i++)
	{
		if (teacher_id == teachers[i].Get_UserId())
			flag = 1;
	}
	if (flag == 1)
		return i - 1;
	else
		return -1;
}
int Manage::Find_Required(const string re_id)
{
	int flag = 0, i;
	for (i = 0; flag == 0 && i < GetReNum(); i++)
	{
		if (re_id == required_courses[i].Get_CourseId())
			flag = 1;
	}
	if (flag == 1)
		return i - 1;
	else
		return -1;
}
int Manage::Find_Elective(const string ele_id)
{
	int flag = 0, i;
	for (i = 0; flag == 0 && i < GetEleNum(); i++)
	{
		if (ele_id == elective_courses[i].Get_CourseId())
			flag = 1;
	}
	if (flag == 1)
		return i - 1;
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

void Manage::Print_All_Ele()
{
	cout << "所有的选修课为:" << endl;
	cout << "课程编号" << '\t' << "课程名称" << '\t' << "课程学分" << '\t' << "任课老师（工号）" << endl;
	int i;
	int pos;///////////////////////////////////////////////////////////////////////这里用指针是不是能减少行数
	for (i = 0; i < GetEleNum(); i++)
	{
		cout << elective_courses[i].Get_CourseId() << '\t';
		cout << elective_courses[i].Get_CourseName() << '\t';
		cout << elective_courses[i].Get_CourseCredit() << '\t';
		pos = Find_Teacher(elective_courses[i].Get_CourseTeacherId());
		if (pos != -1)///////////////////////////////////////////////////////////这里考虑要不要写if判断（可用来判断文件写入是否有错）
			cout << teachers[pos].Get_UserName() << "(" << teachers[pos].Get_UserId() << ")" << endl;
		else
			cout << "你写入的老师信息有误" << endl;
	}
	cout << endl;
}
void Manage::Print_All_Re()
{
	cout << "所有的选修课为:" << endl;
	cout << "课程编号" << '\t' << "课程名称" << '\t' << "课程学分" << '\t' << "任课老师（工号）" << endl;
	int i;				///////////////////////////////////////////////////////////////////////这里用指针是不是能减少行数
	int pos;
	for (i = 0; i < GetReNum(); i++)
	{
		cout << required_courses[i].Get_CourseId() << '\t';
		cout << required_courses[i].Get_CourseName() << '\t';
		cout << required_courses[i].Get_CourseCredit() << '\t';
	//	cout << required_courses[i].Get_CourseStu_Num() << '\t';
		pos = Find_Teacher(required_courses[i].Get_CourseTeacherId());
		if (pos != -1)///////////////////////////////////////////////////////////这里考虑要不要写if判断（可用来判断文件写入是否有错）
			cout << teachers[pos].Get_UserName() << "(" << teachers[pos].Get_UserId() << ")" << endl;
		else
			cout << "你写入的老师信息有误" << endl;
	
	}
	cout << endl;
}
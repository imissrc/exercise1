#include<iostream>
#include<vector>
#include<string>
using namespace std;
#include"User.h"
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
	Req_Courses_Id.clear();
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
string User::Get_UserPassword()
{
	return User_Password;
}
vector<string>& User::Get_Join_Re_Id()
{
	return Req_Courses_Id;
}
int User::Get_JoinReNum()
{
	return Req_Courses_Id.size();
	/*vector<string>::iterator re_pos;
	int count = 0;
	for (re_pos = Req_Courses_Id.begin(); re_pos != Req_Courses_Id.end(); re_pos++)
	{
		count++;
	}
	return count;*/
}
bool User::Judge_Join_Re(const string re_id)
{
	vector<string>::iterator re_pos = find(Req_Courses_Id.begin(), Req_Courses_Id.end(), re_id);
	if (re_pos != Req_Courses_Id.end())
		return true;
	else
		return false;
}
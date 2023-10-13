#pragma once
#include <string>
using namespace std;
struct Client
{
	Client(string p_name, int p_age, string p_login,string p_pass,int p_id=0,string status="user")
	{
		id = p_id;
		name = p_name;
		age = p_age;
		login = p_login;
		pass = p_pass;
		role = status;
	}
public:
	string name,login,pass, role;
	int age,id;
};
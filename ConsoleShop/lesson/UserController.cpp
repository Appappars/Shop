#include <iostream>
#include <string>
#include "Client.h"
#include "mysql.h"
#include "AdminController.h"
using namespace std;
Client* Register()
{
	string name, login, pass;
	int age;
	cout << "Enter  your name: " << endl;
	cin >> name;
	cout << "Enter  your login: " << endl;
	cin >> login;
	cout << "Enter  your password: " << endl;
	cin >> pass;
	cout << "Enter  your age: " << endl;
	cin >> age;
	Client* c = new Client(name, age, login, pass);//переменна€ указатель "c" хранит адрес созданного клиента
	insert_client_db(*c);//передаем значение по адресу указател€ т.е сам экземпл€р структуры 
	c = get_client_db(login, pass);
	return c;//возвращаем адрес объекта структуры
}

int Authorize()
{

	while (true)
	{
		string  login, pass;
		cout << "Enter  your login: " << endl;
		cin >> login;
		cout << "Enter  your password: " << endl;
		cin >> pass;
		auto client = get_client_db(login, pass);
		if (not client)
		{
			cout << "Do sign up now" << endl;
			client = Register();
		}
		cout << "Sign in is succesfully completed!" << endl;
		if (client->role == "admin")
		{
			show_actions();
			system("cls");
		    continue;
		}
		else return client->id;
	}
}
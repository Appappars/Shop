#pragma once
#include <string>
using namespace std;
struct Item
{
    Item(string _name, int _balance, int _id = 0)
    {
        id = _id;
        name = _name;
        balance = _balance;
    }
public:
    int id;
    string name;
    int balance;
};

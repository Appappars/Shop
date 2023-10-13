
#include <iostream>
#include "mysql.h"
#include <vector>
#include "ItemController.h"

vector<Item> items;
void show_items()
{
    items = get_items_db("items");
	int n = 0;
	for (auto item : items)
	{	
		if (item.balance > 0)
		{
			cout << n + 1 << ")" << item.name << "-" << item.balance << endl;
			n++;
		}
	}

}
vector<Item> get_items() { return items; }

void add_item()
{
	int balance;
	string name;
	cout << "Enter name for item:";
	cin >> name;
	cout << "Enter balance for item:";
	cin >> balance;
	if (insert_item_db(Item(name, balance)))
	{
	
		items.push_back(Item(name, balance));
		cout << "Item added" << endl;
	}
	else
	{
		cout << "Item not added" << endl;
	}
}

void remove_item()
{
	int id_rem;
	cout << "Enter id of item to remove:";
	cin >> id_rem;

	if (id_rem>0 and id_rem<size(items))
	{
		if (delete_item_db(items[id_rem - 1].id))
		{
			cout << "Item removed" << endl;
		}
	}
	else
	{
		cout << "Item not removed" << endl;
	}
}
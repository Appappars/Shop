#include <iostream>
#include "mysql.h"
#include "ItemController.h"


void show_panel()
{
	system("cls");
	cout << "1. Add the item" << endl;
	cout << "2. Remove the item" << endl;
	cout << "3. Show the item" << endl;
	cout << "4. Clear screen" << endl;
	cout << "0. Exit" << endl;
}


void show_actions()
{
	int choice = -1;
	show_panel();
	while (choice!=0)
	{
		cin >> choice;
		switch (choice)
		{
		case 0:
			cout << "Exit" << endl;
			break;
		case 1:
			add_item();
			break;
		case 2:
			remove_item();
			break;
		case 3:
			show_items();
			break;
		case 4:
			show_panel();
			break;
		default:
			cout << "Action incorrect. Repoat try" << endl;

		}
	}

}

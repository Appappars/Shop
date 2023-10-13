#include <iostream>
#include "mysql.h"
#include "Item.h"
#include "ItemController.h"
#include "UserController.h"

void pay() {
	connection_to_db();

	auto client_id = Authorize();
	cout << "Какой вы хотите купить товар?" << endl;
	int choice = -1;
	auto order = Order(client_id);
	show_items();
	auto items = get_items();
	while (choice != 0)
	{
		cin >> choice;
		if (choice == 0) break;
		//вектор с товарами определяется в ItemController
		items[choice - 1].balance--;
		order.items.push_back(items[choice - 1]);
		cout << "Choice is selected.Add something else to your order or press zero!" << endl;
	}

	if (insert_order_db(order))
	{
		if (update_item_db(order.items))
			cout << "Our order is completed. Thank u for trusting us" << endl;

	}
	else cout << "Something went wrong. Try again" << endl;
}
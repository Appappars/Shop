#pragma once
#include "Item.h"
#include <vector>
#include "Client.h"
#include "Order.h"
void connection_to_db();
vector<Item> get_items_db(string table);
bool insert_item_db(Item item);
bool delete_item_db(int id);
bool insert_client_db(Client client);
Client* get_client_db(string login, string password);
bool insert_order_db(Order order);
Item get_item_db(int id);
vector <Item>get_items_by_order_db(int order_id);
bool update_item_db(vector<Item> items);

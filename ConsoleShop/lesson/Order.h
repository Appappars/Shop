#pragma once
#include "Item.h"
#include <vector>
struct Order
{
	Order(int p_client_id)
	{
		client_id = p_client_id;
	}
public:
	int client_id;
	vector<Item> items;
};
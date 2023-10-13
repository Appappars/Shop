
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <vector>
#include "Item.h"
#include "config.h"
#include "mysql.h"
using namespace std;
using namespace sql;
//for demonstration only. never save your password in the code!
Driver* driver;
Connection* con;
Statement* stmt;
PreparedStatement* pstmt;
ResultSet* result;
void connection_to_db()
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
        con->setSchema(db_name);
        stmt = con->createStatement();
    }
    catch (SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
    }
}
vector<Item> get_items_db(string table)
{
    vector<Item> items;
    pstmt = con->prepareStatement("SELECT * FROM "+ table);
    result = pstmt->executeQuery();
    while (result->next())
    {
        items.push_back(Item( result->getString(2).c_str(), result->getInt(3),result->getInt(1)));
    }
    return items;
}
bool insert_item_db(Item item)
{
    pstmt = con->prepareStatement("INSERT INTO items(name,balance) values(?,?)");
    pstmt->setString(1,item.name);
    pstmt->setInt(2, item.balance);
    return not pstmt->execute();
}
bool delete_item_db(int id)
{
    pstmt = con->prepareStatement("Delete from items where id=?");
    pstmt->setInt(1, id);
    pstmt->execute();
}
bool insert_order_db(Order order)
{
    pstmt = con->prepareStatement("INSERT INTO orders(client_id) values(?)");
    pstmt->setInt(1,order.client_id);
    auto b=pstmt->executeQuery();
   
    cout << b->getInt("id")<< endl;;
    return b;
    //возможно возвратить id, нужно протестить
   /* int order_id=result->getInt(1);
    for (auto item:order.items)
    {
        pstmt = con->prepareStatement("INSERT INTO orders_and_Items(order_id,item_id) values(?,?)");
        pstmt->setInt(1, order_id);
        pstmt->setInt(2, item.id);
        pstmt->execute();
    }*/
}
Item get_item_db(int item_id)
{
    pstmt = con->prepareStatement("Select * from Items where id=? limit 1");
    pstmt->setInt(1,item_id);
    result = pstmt->executeQuery();
    return Item (result->getString(2).c_str(), result->getInt(3), (result->getInt(1)));
}
bool insert_client_db(Client client)
{
    pstmt = con->prepareStatement("INSERT INTO clients (name,age,password,login) values(?,?,?,?)");
    pstmt->setString(1, client.name);
    pstmt->setInt(2, client.age);
    pstmt->setString(3, client.pass);
    pstmt->setString(4, client.login);

    return not pstmt->execute();
}
Client* get_client_db(string login,string password)
{
    Client* selected_client;
    pstmt = con->prepareStatement("Select * from clients where login=? and password=?");
	pstmt->setString(1, login);
	pstmt->setString(2, password);
    result=pstmt->executeQuery();
	if (not result->first()) return nullptr;
    selected_client = new Client(
        result->getString(2).c_str(),//имя
        result->getInt(5),//возраст
        result->getString(3).c_str(),//логин
        result->getString(4).c_str(),//пароль
        result->getInt(1),//id
        result->getString(6).c_str()
    );

        return selected_client;
}
vector<Item>get_items_by_order_db(int order_id)
{
    vector<Item> items;
    pstmt = con->prepareStatement("SELECT * FROM orders_and_items WHERE =" + to_string(order_id));
    result = pstmt->executeQuery();
   while (result->next())
    {
        items.push_back(get_item_db(result->getInt(2)));
    }
    return items;
}
bool update_item_db(vector<Item> items)
{
    pstmt = con->prepareStatement("UPDATE items SET balance=? WHERE name=?");
    bool problema=false;
	for (auto item : items)
	{
		pstmt->setInt(1, item.balance);
		pstmt->setString(2, item.name);
		problema= not pstmt->execute();
        if (problema == false)
        {
			cout << "Error" << endl;
			return problema;
        }
	}
	return problema;
}
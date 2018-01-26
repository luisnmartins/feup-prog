#include <iostream>
#include <string>
#include <vector>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"
#include "Error.h"
using namespace std;


int main() {

	unsigned int return_menu = 0;
	string shop, clients_file, products_file, transactions_file;
	int flag = 0;
    

	// asks the name of the store

	do
	{

		cout << "Shop's name: ";
		getline(cin, shop);

	} while (file_valid(shop) == false);

	clearScreen();




	// client products and transactions information

	do {
		flag = 0;
		do
        {   cin.clear();
			cout << "Name of the clients file (press 0 if dont want to work with any existing files): ";
			getline(cin, clients_file);
            if(clients_file == "0")
            {
                
            }
			clients_file += ".txt";
		} while (file_valid(clients_file) == false);

		do
		{
            cin.clear();
            cout << "Name of the products file (press 0 if dont want to work with any existing files): ";
			getline(cin, products_file);
			products_file += ".txt";
		} while (file_valid(products_file) == false);

		do
		{
            cin.clear();
            cout << "Name of the transactions file (press 0 if dont want to work with any existing files): ";
			getline(cin, transactions_file);
			transactions_file += ".txt";
		} while (file_valid(transactions_file) == false);

		if (!initialInfo(shop, clients_file, products_file, transactions_file))
		{
			flag = 1;
		}
	} while (flag == 1);

	// creates the store
	SupermarketPlusPlus supermarket(shop, clients_file, products_file, transactions_file);

	initialOptions(supermarket);

	getchar();
	return 0;
	

}
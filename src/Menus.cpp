#include "Menus.h"
#include <fstream>



bool initialInfo(string & shop, string & clients_file, string & products_file, string & transactions_file){

	int flag = 0; 
	ifstream myfile_client(clients_file);
	ifstream myfile_trans(transactions_file);
	ifstream myfile_products(products_file);
	if(clients_file !="0.txt")
    {
        if (!myfile_client.is_open() || myfile_client.peek() == std::ifstream::traits_type::eof())
        {
            cout << "Can't find the clients file or the file is empty!" << endl;
            flag = 1;
        }
    }
	if (!myfile_products.is_open() || myfile_products.peek() == std::ifstream::traits_type::eof())
	{
		cout << "Can't find the products file or the file is empty!" << endl;
		flag = 1;
	}
    if(transactions_file !="0.txt")
    {
        if (!myfile_trans.is_open() || myfile_trans.peek() == std::ifstream::traits_type::eof())
        {
            cout << "Can't find the transactions file or the file is empty!" << endl;
            flag = 1;
        }
    }
	if (flag == 1)
		return false;
	else
		return true;
}

/******************************************
 * Client Management
 ******************************************/
unsigned short int clientManagementMenu(){
  unsigned short int choice;
  do
  {
	  clearScreen();
	  cout << TAB_BIG << "Clients' Management Menu" << endl;
	  cout << endl;

	  cout << TAB << "1 - List Clients" << endl;
	  cout << TAB << "2 - Show Client Information" << endl;
	  cout << TAB << "3 - Add a new client" << endl;
	  cout << TAB << "4 - Edit a client" << endl;
	  cout << TAB << "5 - Remove a client" << endl;
	  cout << TAB << "6 - Go back to the main menu" << endl << endl;
	  cout << TAB << "Choice: ";
	  choice = leUnsignedShortInt(1, 6);
  } while (choice == 0);
	  if (choice == 6)
		  return 0;

	  else 
  return choice;
}


void clientManagementoptions(SupermarketPlusPlus & supermarket){
  unsigned int choice, id,flag=0, return_menu=0;
  string name, id_string;

  while((choice = clientManagementMenu()))
    switch (choice){
            
        case 1:
            supermarket.showallclients();
            press_any_key();
                break;
        case 2:
            do{
                cout << "What is the client's ID: ";
                getline(cin, id_string);
            }
                while(num_valid(id_string, return_menu) == false);
            if(return_menu!=1)
            {
                
                supermarket.showClientInformation(stoi(id_string));
                press_any_key();
            }
                break;
        case 3:
			do
			{   
                do{
                    
                cout << "What is the name of the client: ";
				getline(cin, name);
                }while(string_valid(name, return_menu) == false);
                
                if(return_menu==1)
                    break;
                
                    if (supermarket.existclientname(name))
                    {
                        
                        flag = 1;
                    }
				
				else
				{
					supermarket.addclient(name);
					
					flag = 0;
				}
                    
			} while (flag == 1);
			getchar();
      break;
	case 4:
            do{
        cout << "Client's ID: ";
		getline(cin, id_string);
            }
		while(num_valid(id_string, return_menu) == false);
            if(return_menu==1)
                break;
            do{
                cout << "New Client's Name: ";
                getline(cin, name);
                id = stoi(id_string);
            }while(string_valid(name, return_menu)== false || supermarket.existclientname(name) == true);
            if(return_menu==1)
                break;
		supermarket.changeclient(id, name);
		getchar();
      break;
	case 5:
            do{
            cout << "Client's ID: ";
                getline(cin,id_string);
            }while(num_valid(id_string, return_menu)==false);
            if(return_menu==1)
                break;
            id = stoi(id_string);
            supermarket.removeclient(id);
			getchar();
            break;
		
		
	}
}



/******************************************
 * Transaction Management
 ******************************************/
unsigned short int trasactionsManagementMenu(){
	unsigned short int choice;
	do
	{
		clearScreen();
		cout << TAB_BIG << "Transactions Menu" << endl;
		cout << endl;

		cout << TAB << "1 - List transactions" << endl;
		cout << TAB << "2 - Add transaction" << endl;
		cout << TAB << "3 - Go back to main menu" << endl;
		cout << TAB << "Choice: ";
		choice = leUnsignedShortInt(1, 3);
	} while (choice == 0);
	if (choice == 3)
		return 0;
	else return choice;
}

void transactionsManagementOptions(SupermarketPlusPlus & supermarket){
    unsigned int choice=0, return_menu=0;
  int flag = 0;
  string id_string,product, name;
  vector<string> transaction_products;

  while((choice = trasactionsManagementMenu()))
    switch (choice){
            
        case 1:
            TransactionsSubMenu_options(supermarket);
            
            break;
    case 2:
                do{
                cout << "Please insert the id of the client you wish to add a transaction to: ";
                getline(cin, id_string);
                }while(num_valid(id_string, return_menu)==false);
            
                if(return_menu==1)
                    break;
                else
                {
                    if (supermarket.existclientIdx(stoi(id_string)))
                    {
                        cout << "Please insert one by one the products bought, any unvalid products will be ignored(submit STOP to stop operation)\n";
                        do{
                            return_menu=0;
                            do{
                                product.clear();
                                cout << "Product: ";
                                getline(cin, product);
							
                            }while(string_valid(product, return_menu)==false);
                            
                            if(return_menu==1)
                                break;
                            else
                            {
								if (product == "0")
								{
									
									break;
								}
								else if (supermarket.existproductIdx(product))
                                {
                                    transaction_products.push_back(product);
                                    flag = 0;
                                }

                                else
                                {
                                    cerr << "Invalid product, please try again!\n";
                                    flag = 0;
                                }
                            }
                        } while (flag == 0);
                        supermarket.addtransaction(stoi(id_string), transaction_products);
						getchar();
                        break;
                    }
                    else
                    {  cerr << "Careful! There is no client with that id! " << endl;
					getchar();
                        break;
                    }
                }
            break;
    }
}


unsigned short int submenuTransactions(){
    unsigned short int choice;
    do
    {
        clearScreen();
        cout << TAB_BIG << "Transactions SubMenu" << endl;
        cout << endl;
        cout << TAB << "1 - List all transactions" << endl;
        cout << TAB << "2 - List transactions between dates" << endl;
        cout << TAB << "3 - List transactions of a client" << endl;
        cout << TAB << "4 - List transactions from a day" << endl;
        cout << TAB << "5 - Go back to previous menu" << endl;
        cout << TAB << "Choice: ";
        choice = leUnsignedShortInt(1, 5);
    } while (choice == 0);
    if (choice == 5)
        return 0;
    else return choice;
}



void TransactionsSubMenu_options(SupermarketPlusPlus & supermarket){
    unsigned int choice=0, return_menu;
    int flag = 0;
    string id_string,product, name;
    vector<string> transaction_products;
    
    while((choice = submenuTransactions()))
        switch (choice){
                
            case 1:
                supermarket.printall_trans();
				press_any_key();
                break;
            case 2:
            {
                Date new_date1, new_date2;
                do{
                    flag=0;
                    
                    string day, mon, year;
                    cout<<"Please insert the first date:"<<endl;
                    do
                    {
                        cout<<"Day: ";
                        getline(cin, day);
                        
                    }while(num_valid(day, return_menu) == false);
                    if(return_menu==1)
                        break;
                    new_date1.setDay(stoi(day));
                    do
                    {
                        cout<<"Month: ";
                        getline(cin, mon);
                 
                    }while(num_valid(mon, return_menu) == false);
                    if(return_menu==1)
                        break;
                    new_date1.setMonth(stoi(mon));
                    do
                    {
                        cout<<"Year: ";
                        getline(cin, year);
  
                        
                    }while(num_valid(year, return_menu) == false);
                    if(return_menu==1)
                        break;
                    new_date1.setYear(stoi(year));
                    if(!new_date1.verify_date())
                    {
                        flag=1;
                        cerr<<"Date new valid. Please insert a valid date"<<endl;
                    }
                }while(flag==1);
                do{
                    flag=0;
                    
                    string day, mon, year;
                    cout<<"Please insert the second date:"<<endl;
                    do
                    {
                        cout<<"Day: ";
                        getline(cin, day);

                    }while(num_valid(day, return_menu) == false);
                    if(return_menu==1)
                        break;
                     new_date2.setDay(stoi(day));
                    do
                    {
                        cout<<"Month: ";
                        getline(cin, mon);

                    }while(num_valid(mon, return_menu) == false);
                    if(return_menu==1)
                        break;
                    new_date2.setMonth(stoi(mon));
                    do
                    {
                        cout<<"Year: ";
                        getline(cin, year);

                    }while(num_valid(year, return_menu) == false);
                    if(return_menu==1)
                        break;
                    new_date2.setYear(stoi(year));
                    if(!new_date2.verify_date())
                    {
                        flag=1;
                        cerr<<"Date new valid. Please insert a valid date"<<endl;
                    }
                }while(flag==1);
                supermarket.print_trans_between_dates(new_date1, new_date2);
				press_any_key();
            }
                break;
            case 3:
                do{
                    cout << "Please insert the name of the client: ";
                    getline(cin, name);
                }while(string_valid(name, return_menu) == false);
                if(return_menu!=1)
                {
                supermarket.clients_transactions(name);
				press_any_key();
                }
                break;
            
            case 4:
            {
            do{
                flag=0;
                Date new_date;
                string day, mon, year;
                do
                {
                    cout<<"Day: ";
                    getline(cin, day);

                }while(num_valid(day, return_menu) == false);
                if(return_menu==1)
                    break;
                new_date.setDay(stoi(day));
                do
                {
                    cout<<"Month: ";
                    getline(cin, mon);

                }while(num_valid(mon, return_menu) == false);
                if(return_menu==1)
                    break;
                new_date.setMonth(stoi(mon));
                do
                {
                    cout<<"Year: ";
                    getline(cin, year);

                }while(num_valid(year, return_menu) == false);
                if(return_menu==1)
                    break;
                new_date.setYear(stoi(year));
                if(!new_date.verify_date())
                {
                    flag=1;
                    cerr<<"Date new valid. Please insert a valid date"<<endl;
                }
				else
				{
					supermarket.print_trans_oneday(new_date);
					press_any_key();
				}
        }while(flag==1);
        }
    break;
        }
}




/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int recomendationMenu(){
    unsigned short int choice;
    do
    {
		clearScreen();
    cout << TAB_BIG << "Recomendation Menu" << endl;
    cout << endl;
    cout << TAB << "1 - Bottom 10 client" << endl;
    cout << TAB << "2 - Recomendation for one client" << endl;
    cout << TAB << "3 - Go back to previous menu" << endl;
    cout << TAB << "Choice: ";
    choice = leUnsignedShortInt(1, 3);
    } while (choice == 0);
    if (choice == 3)
        return 0;
    else
        return choice;

}

void recomendationOptions(SupermarketPlusPlus & supermarket){
  unsigned int choice, return_menu;
    string id_string;
    
  while((choice = recomendationMenu()))
    switch (choice){
        case 1: supermarket.bottom10();
            press_any_key();
      break;
    case 2:
            do
            {
            cout << "Please insert the id of the client you wish to get recomendation: ";
            getline(cin, id_string);
            }
            while(num_valid(id_string, return_menu)==false);
            if(return_menu==1)
                break;
            if (supermarket.existclientIdx(stoi(id_string)))
            {
                unsigned int id= stoi(id_string);
                supermarket.recomendation(id);
            }
            else
            {  cerr << "Careful! There is no client with that id! " << endl;
                break;
            }
            press_any_key();
            break;

            
    }

}


/******************************************
 * Main Menu
 ******************************************/
unsigned short int MainMenu(){
  unsigned short int choice;

  do {
	  cin.clear();
	  clearScreen();
	  cout << TAB_BIG << "Main Menu" << endl;
	  cout << endl;
	  cout << TAB << "1 - Clients' Management" << endl;
	  cout << TAB << "2 - List available products" << endl;
	  cout << TAB << "3 - Transactions' Management" << endl;
	  cout << TAB << "4 - Recomendations" << endl;
	  cout << TAB << "5 - Exit and save" << endl << endl;
	  cout << TAB << "Choice: ";
	  choice = leUnsignedShortInt(1, 5);
  } while (choice == 0);


  return choice;
}

void initialOptions(SupermarketPlusPlus & supermarket)
{
  unsigned int choice;


  while((choice = MainMenu()))
    switch (choice){
    case 1: clientManagementoptions(supermarket);
      break;
    case 2:
            supermarket.listProducts();
			press_any_key();
      break;
    case 3: transactionsManagementOptions(supermarket);
      break;
    case 4: recomendationOptions(supermarket);
            break;
	case 5: supermarket.saveChanges();
		exit(0);
		break;
    }
}


#pragma warning(disable : 4996)
#include "Vende++.h"
#include <algorithm>
#include <ctime>
#include <iterator>


/*********************************
 *           Get files           *
 ********************************/



//**********supermarket constructor*******************//


SupermarketPlusPlus::SupermarketPlusPlus(string shop, string clients_file, string products_file, string transactions_file){
    
    
    string lixo;
    SupermarketPlusPlus::shop = shop;
    SupermarketPlusPlus::clients_file = clients_file;
    SupermarketPlusPlus::products_file = products_file;
    SupermarketPlusPlus::transactions_file = transactions_file;
    
    
    /************************************
    //Push clients to the clients' map//
     ***********************************/
    
    
    
    id_next = 0;
    
	if (clients_file != "0.txt")    //if there is no clients file to use
	{


		ifstream clients_stream(clients_file);
		getline(clients_stream, lixo);

		changedClients = false;
		changedTransactions = false;




		for (int i = 0; i < stoi(lixo); i++)
		{
			Client clients_2(clients_stream);
			clientIdx.insert(make_pair(clients_2.getId(), clients_2));   //fill clients' map<id, client>
			if (clients_2.getId() >= id_next)
			{
				id_next = clients_2.getId() + 1;
			}

		}

		clients_stream.close();
		cout << "Clients' file got with success!" << endl << endl;
	
    }
    else
    {
        id_next = 1;
    }
    
    /*********************************
    //Push products to products' map//
     *******************************/
    
    

    
        ifstream products_stream(products_file);
        getline(products_stream, lixo);

    
        changedClients = false;
        changedTransactions = false;
        productIdx.clear();
        for (int i = 0; i < stoi(lixo); i++)
        {
            Product product(products_stream);
            productIdx.insert(make_pair(product.getName(), product));    //fill products' map <product's name, product>
        }
        products_stream.close();
		cout << "Products' file got with success!" << endl << endl;
    
   
    
    
    /*****************************************
    //Push transactions to transactions' map//
     ****************************************/
    
    
    if(transactions_file != "0.txt")                 //if there is no transactions file to use
    {
    
        ifstream transactions_stream(transactions_file);
    
        getline(transactions_stream, lixo);
    
        changedClients = false;
        changedTransactions = false;
    
        for (int i = 0; i < stoi(lixo); i++)
        {
            Transaction trans(transactions_stream);
            transactionIdx.insert(make_pair(trans.getclientID(), trans));    //fill transactions' multimap<client's ID, transactions of this client>
    
        
        }
        transactions_stream.close();
		cout << "Transactions' file got with success!" << endl;
		getchar();
        }
    
    }







/*********************************
 *     Clients' management       *
 ********************************/



/**************************************
//add a new client to the clients' map//
 *************************************/

void SupermarketPlusPlus::addclient(string name)
{
    
    time_t tt = time(0);   // get time now
    struct tm * now = localtime(&tt);
    ostringstream oss;
    if ((now->tm_mon + 1) > 9) // Adds a zero before the month if month < 9
    {
        oss << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
    }
    else
    {
        oss << now->tm_mday << "/0" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
    };
    
    
    
    Date date(oss.str());           //use the date constructor to separate the date string
    
    Client new_client;            //create a new client with client class
    new_client.setName(name);
    new_client.setId(id_next);     //id is the major id that exists + 1
    id_next++;                      //inc id_next to the next client
    new_client.setdate(date);
    new_client.setPurchases(0.00);
    
    clientIdx.insert(make_pair(new_client.getId(), new_client));   //insert the new client to the clients' map
    
    changedClients = true;
    cout<<endl<<"Client added with success"<<endl;
    
}


/*************************************************
//verify if a product exists to use on transactions//
 **************************************************/


bool SupermarketPlusPlus::existproductIdx(string produto)
{
	
	if(productIdx.find(produto) != productIdx.end())
        return true;
    else
        return false;
}



/********************************
//verify if a client's ID exists //
 *******************************/

bool SupermarketPlusPlus::existclientIdx(unsigned int id)
{
    if(clientIdx.find(id) != clientIdx.end())
        return true;
    else
        return false;
    
}

/**********************************
//verify if a client's Name exists//
**********************************/

bool SupermarketPlusPlus::existclientname (string name)
{
    for(auto iterator=clientIdx.begin(); iterator!=clientIdx.end(); iterator++)
    {
        if(iterator->second.getname() == name)
        {
            cout << "That name already exist, please choose a different name!\n";
            return true;
        }
    }
    
    return false;
}


/**************************************
 //add a new transaction to the transactions' multimap//
 *************************************/

void SupermarketPlusPlus::addtransaction(unsigned int id, vector<string> products) {
    
    
    time_t tt = time(0);   // get time now
    struct tm * now = localtime(&tt);
    ostringstream oss;
    if ((now->tm_mon + 1) > 9) // Adds a zero before the month if month < 9
    {
        oss << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
    }
    else
    {
        oss << now->tm_mday << "/0" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900);
    };
    
    
    
    
    
    Date date(oss.str());
    Transaction new_transaction;    //create a new transaction and set the elements
    new_transaction.setId(id);
    new_transaction.setDate(date);
    new_transaction.setProducts(products);
    
    transactionIdx.insert(make_pair(new_transaction.getclientID(), new_transaction));  //push the new transactions to the transactions' multimap
    vector<string> products_2 = new_transaction.getproducts();
    unsigned int id1 = new_transaction.getclientID();
    set_clients_purchase_value(products_2, id1);                              //update the client's value adding the total value of the transaction
    
    changedTransactions = true;
    changedClients = true;
    
	cout << "Transaction added sucessfuly!\n";
    
    
}


/*****************************************************************
//update the client's amount - to use when a transaction is added //
*******************************************************************/

void SupermarketPlusPlus::set_clients_purchase_value(vector<string> &products_2, unsigned int &id)
{
    for(int i=0; i<products_2.size(); i++)
    {
        float purchase;
        purchase = clientIdx.at(id).getpurchases();           //get the actual amount of the client
        purchase += productIdx.at(products_2[i]).getValue();    //add to the actual amount the price each element of products_2
        clientIdx.at(id).setPurchases(purchase);                //update the client's amount
        
        
    }
    
}

/******************************
//change the name of a client //
 *****************************/

void SupermarketPlusPlus::changeclient(unsigned int id, string new_name)
{
    
    if(existclientIdx(id)) //verify if the client's id introduced exists
    {
        clientIdx.at(id).setName(new_name);                 //change the client's name
		cout << "The client was changed sucessfully!\n\n";
		
    }
    else
    {
        
        cout <<endl<< "This client doesn't exist."<<endl;
        
    }
    changedClients = true;
}


/******************
 //remove a client //
 ******************/


void SupermarketPlusPlus::removeclient(int id)
{
    
    if (existclientIdx(id))
    {
        clientIdx.erase(id);                                  //delete client
		cout << "The client was removed sucessfully!\n\n";
		
    }
    else
    {
        
        cout << endl << "This client doesn't exist." << endl;
        getchar();
    }
    changedClients=true;
    
    
}

/***********************************
 //List clients by alphabetic order//
 ***********************************/



void SupermarketPlusPlus::listClientsOrderAlpha(map<unsigned int, Client> &map_print ){
                                                    /*map<client's ID, client>*/
    
    
    map<string, Client> map_client_name;   //map<client's name, client>
    
    for (auto iterator = map_print.begin(); iterator != map_print.end(); iterator++)
    {
        map_client_name.insert(make_pair(iterator->second.getname(), iterator->second)); //set client_name with the clients that exists in map_print
        
    }
   
    if(!map_client_name.empty())
    {
        cout << right << setw(3) << " CLIENT ID " << "            " << left << setw(25) << "     NAME     " << "      " << "  DATE  " <<"     " << right << setw(15) << "  VALUE  " << endl;
        cout << right << setw(3) << "___________" << "            " << left << setw(25) << "______________" << "      " << "________" << "     " << right << setw(15) << "_________" << endl;
        cout << endl;
    
        
    
    
    for (auto iterator = map_client_name.begin(); iterator != map_client_name.end(); iterator++)
    {
		cout << map_client_name.at(iterator->first);   //cout clients by alphabetic order using clients operator <<
    
    }
        
    }
    else
    {
        cerr<<"No clients to show!! Please insert a client first"<<endl;
        getchar();
    }
    
}

/**************************************
 //List all clients by alphabetic order//
 *************************************/

void SupermarketPlusPlus::showallclients()
{
    listClientsOrderAlpha(clientIdx);
}


/**************************************
 //List one client information//
 *************************************/

void SupermarketPlusPlus::showClientInformation(unsigned int id){
    
    map<unsigned int, Client> client_map;
    Client client;
    if (existclientIdx(id))
    {
        
        client_map.insert(make_pair(id, clientIdx.at(id)));
        listClientsOrderAlpha(client_map);
    }
    
    
    else
    {
        
        cout << endl << "This client doesn't exist." << endl;
        getchar();
    }
    
    
    
    
}

/*******************************************************************
//Sort a vector<string> by the number of times that a string appear//
 ******************************************************************/

void SupermarketPlusPlus::sorting_nmb_occurrence (vector<string> &vec)
{
    multimap<unsigned int, string> map_to_order;   //map<number of occurrences of a string, string>
    
    for(int i=0; i<vec.size(); i++)
    {
        map_to_order.insert(make_pair(count(vec.begin(), vec.end(), vec[i]), vec[i]));   //set map_to-order with the strings of the vec
    }
    vec.clear();
    
    for(auto iterator_t=map_to_order.begin(); iterator_t!=map_to_order.end(); iterator_t++)  //run the map
    {
        
        //get the strings for each number of occurence and put it on the vector by the same order

        
        std::pair <std::multimap<unsigned int,string>::iterator, std::multimap<unsigned int,string>::iterator> ret;
        ret = map_to_order.equal_range(iterator_t->first);
        
        for (std::multimap<unsigned int, string>::iterator it=ret.first; it!=ret.second; ++it)
        {
            vec.push_back(it->second);
        }
        
    }
    
    
    
}


/************************
 //Bottom 10 suggestion//
 ***********************/

void SupermarketPlusPlus::bottom10()
{
    map<unsigned int, unsigned int> client_index;
    unsigned int nothing=0;
    vector<unsigned int> ids;
    if(clientIdx.size() <= 10)
    {
        cout << "There is not enough clients to do this operation" << endl;
    }
    else
    {
        multimap<float, Client> map_clients_values;   //map< purchase value, client>
        
        
        for (auto iterator = clientIdx.begin(); iterator != clientIdx.end(); iterator++)
        {
           
            map_clients_values.insert(make_pair((*iterator).second.getpurchases(), (*iterator).second));   //set map_clients_values
        }
        
        
        
        

        
        vector<unsigned int> id_bottom10;   //vector<bottom10 id's>
        
        vector<string> all_products_bottom10;   //vector<bottom10 products>
        
        map<unsigned int, Client> clients_to_matrix;   //map<client's id, client>   to use as clientIdx
        
        multimap<unsigned int, Transaction> trans_to_matrix;  //map<client's id, transactions> to use as transactionIdx
        
        vector<unsigned int> id_to_matrix;    //id's not bottom 10
        
        map<unsigned int, Transaction> trans_bt10; //map<bt10 id, transactions>  to use as map of bottom10 transactions
        
        map<float, Client>::reverse_iterator it2;   //iterator to delete clients not bottom10
        
        
        auto nmb_not_bt10 = map_clients_values.size()-10;   //get the number of clients that are not bottom 10
        
        for(it2 = map_clients_values.rbegin(); nmb_not_bt10 > 0; nmb_not_bt10--)
        {
        
            clients_to_matrix.insert(make_pair(it2->second.getId(), it2->second));   //insert other clients (not Bottom 10)
            
            id_to_matrix.push_back(it2->second.getId());        //get not bottom 10 id's
           
            map_clients_values.erase(std::next(it2).base());   //delete the client(s) with the most purchase value
            

            
            
        }
        
        //set id_bottom 10 with bottom 10 id's
        
        for(auto iterator = map_clients_values.begin(); iterator!=map_clients_values.end(); iterator++)
        {
            id_bottom10.push_back(iterator->second.getId());
        }
        
        
        //set trans_to_matrix the transactions that are not from bottom 10 clients && set products_bottom10 with transactions
        
        for( auto iterator_t = transactionIdx.begin(); iterator_t != transactionIdx.end(); iterator_t++)
        {
            if(find(id_bottom10.begin(), id_bottom10.end(), iterator_t->first) == id_bottom10.end())
            {
                
                //push all the transactions from not bottom 10 to trans_to_matrix
                
                std::pair <std::multimap<unsigned int,Transaction>::iterator, std::multimap<unsigned,Transaction>::iterator> ret;
                ret = transactionIdx.equal_range(iterator_t->first);
            
                for (std::multimap<unsigned int, Transaction>::iterator it=ret.first; it!=ret.second; ++it)
                {
                    trans_to_matrix.insert(make_pair(iterator_t->first, it->second));
                
                }
            }
            else
            {
                //set products_bottom10 with transactions
                
                std::pair <std::multimap<unsigned int,Transaction>::iterator, std::multimap<unsigned,Transaction>::iterator> ret;
                ret = transactionIdx.equal_range(iterator_t->first);
                
                for (std::multimap<unsigned int, Transaction>::iterator it=ret.first; it!=ret.second; ++it)
                {
                    for(int i=0; i<it->second.getproducts().size(); i++)
                    {

                            all_products_bottom10.push_back(it->second.getproducts()[i]);
                    }
                }
            }
        }
        
        map<string, unsigned int> products_index; //map<products name, matrix posotion>
        
        auto products_index_counter=0;
        
        for(auto iterator = productIdx.begin(); iterator!=productIdx.end(); iterator++)
        {
            products_index.insert(make_pair(iterator->first, products_index_counter));
            products_index_counter++;
        }
        
        
        
        vector<vector<unsigned int>> common_prod_ids_bt10(productIdx.size()); // vector<product, ids of the clients with the product>
        
        //set common_prod_ids_bt10 with the bottom10 clients' id in each product
        
        for(int i=0; i<id_bottom10.size(); i++)
        {
            pair<multimap<unsigned int, Transaction>::iterator, multimap<unsigned int, Transaction>::iterator> ret;
            ret=transactionIdx.equal_range(id_bottom10[i]);
            
            for(multimap<unsigned int, Transaction>::iterator it=ret.first; it!=ret.second; ++it)
            {
                for(auto a=0; a<it->second.getproducts().size(); a++)
                {
                    vector<unsigned int> clients_with_prod_a = common_prod_ids_bt10[products_index[it->second.getproducts()[a]]];
                    
                    if(find(clients_with_prod_a.begin(), clients_with_prod_a.end(), it->first) == clients_with_prod_a.end())
                    {
                        common_prod_ids_bt10[products_index[it->second.getproducts()[a]]].push_back(it->first);
                    }
                }
            }
            
            
        }
        
        
        
        map<unsigned int, string> products_index_inverse;  // map to change products_index map order
        
        for (auto iterator = products_index.begin(); iterator != products_index.end(); iterator++)
        {
            
          products_index_inverse.insert(make_pair(iterator->second, iterator->first));        //invert the products_index map
            // map<matrix position, product name>
        }

        
        
        vector<string> products_common_bt10;    //vector<name of the common products bottom10>
        
       size_t counter_common_prod=0;
        
        //run the common_prod_ids_bt10 to get the products with that the major part of the bt10 bought
        
        for(int i=0; i<common_prod_ids_bt10.size(); i++)
        {
            if(common_prod_ids_bt10[i].size() > counter_common_prod)
            {
                counter_common_prod = common_prod_ids_bt10[i].size();
                products_common_bt10.clear();
                products_common_bt10.push_back(products_index_inverse[i]);
            }
            else if(common_prod_ids_bt10[i].size() == counter_common_prod)
            {
                products_common_bt10.push_back(products_index_inverse[i]);
            }
            
        }
        
        
        //crate a new client and Transaction with the bottom10 products to fill the matrix
        Transaction new_trans_bt10;
        new_trans_bt10.setId(0);
        Date new_date("01/01/2015");
        new_trans_bt10.setDate(new_date);
        new_trans_bt10.setProducts(products_common_bt10);
        Client new_client;
        new_client.setId(0);
        new_client.setdate(new_date);
        new_client.setName("Bottom10");
        new_client.setPurchases(10);
        trans_to_matrix.insert(make_pair(new_trans_bt10.getclientID(), new_trans_bt10));
        clients_to_matrix.insert(make_pair(new_client.getId(), new_client));
        
        //call the matrix function
        
        unsigned int index_id=0, id=0;
        vector<vector<bool>> matrix_bottom10 = recomendation_bool_vector(index_id, id, products_index, client_index, trans_to_matrix, clients_to_matrix);
        vector<bool> target_client = matrix_bottom10[index_id];  //bottom 10 line on the matrix
        
        vector<string> interesting_clients_products;
        unsigned int counter_client_added=0;
        
        //fill the interesting_clients_products vector with the products that the other clients bought and are not bt10 common products
        
        for(int i=0; i<matrix_bottom10.size(); i++)
        {
            counter_client_added=0;
            for(int a=0; a<matrix_bottom10[i].size(); a++)
            {
                if(target_client[a] != matrix_bottom10[i][a])
                {
                    if(matrix_bottom10[i][a] == true)
                    {
                        interesting_clients_products.push_back(products_index_inverse[a]);
                        counter_client_added++;
                    }
                    else
                    {
                        if(counter_client_added!=0)
                        {
                            //if the client didn't bought all bt10 common products erase the products that was added to the vector from this client
                            interesting_clients_products.erase(interesting_clients_products.end()-counter_client_added, interesting_clients_products.end());
                        }
                        break;
                    }
                }
            }

        }
        
        
        //sort the vector<string> using sorting_nmb_occurence
        
        sorting_nmb_occurrence(interesting_clients_products);
        
        sorting_nmb_occurrence(all_products_bottom10);
        
        string product_to_suggest;

        vector<unsigned int> position_bottom10_prod_interesting;
        
        
        for(int i=0; i<interesting_clients_products.size(); i++)
        {
            if(find(all_products_bottom10.begin(), all_products_bottom10.end(), interesting_clients_products[i]) == all_products_bottom10.end())
            {
                product_to_suggest = interesting_clients_products[i];
                break;
            }
            else
            {
                for(int a=0; a<all_products_bottom10.size(); a++)
                {
                    if(all_products_bottom10[a] == interesting_clients_products[i])
                    {
                        position_bottom10_prod_interesting.push_back(a);
                    }
                }
            }

        }
        
        unsigned int less_freq_bottom10=0;
        
        for(int i=0; i<position_bottom10_prod_interesting.size(); i++)
        {
            if(less_freq_bottom10 < position_bottom10_prod_interesting[i])
            {
                less_freq_bottom10 = position_bottom10_prod_interesting[i];
                product_to_suggest = products_index_inverse[i];
            }
        }
            
        

        cout<<"The Bottom10 clients should buy: "<<product_to_suggest<<endl;
        
        }

        
}

//creates a vector of booleans 
vector<vector<bool>> SupermarketPlusPlus::recomendation_bool_vector(unsigned int &index_id, unsigned int &id, map<string, unsigned int> &products_index, map<unsigned int, unsigned int> &client_index, multimap<unsigned int, Transaction> &transaction, map<unsigned int, Client> &client)
{
    
	
	
    
    vector<unsigned int> ids;
    unsigned int i=0;
    for (auto iterator = transaction.begin(); iterator != transaction.end(); iterator++)   //fill client_index
    {
		
        unsigned int id_s = iterator->first;     //
        if(find(ids.begin(), ids.end(),id_s) == ids.end())
        {
            ids.push_back(id_s);
        }
        i++;

    }
    for (auto iterator = client.begin(); iterator != client.end(); iterator++)
    {
        unsigned int id_s = iterator->first;
        if(find(ids.begin(), ids.end(),id_s) == ids.end())
        {
            ids.push_back(id_s);
        }
    }
    for(int a=0; a<ids.size(); a++)
    {
        client_index.insert(make_pair(a, ids[a]));
        if (ids[a] == id)
            index_id = a;
    }
    i=0;

    for (auto iterator = productIdx.begin(); iterator != productIdx.end(); iterator++)
    {
        products_index.insert(make_pair(iterator->first, i));    //map<product's name, position matrix>
        i++;
    }
    vector<vector<bool>> products_vec(client_index.size(),vector<bool>(products_index.size(), false));
    
    
    for(int a=0; a<client_index.size(); a++)
    {
        
        
        vector<vector<string>> all_products_trans;    // matrix(clients, clients' products)
        for (auto iterator = transaction.begin(); iterator != transaction.end(); iterator++)
        {
            
            if((*iterator).first == client_index.at(a))
            {
                all_products_trans.push_back(iterator->second.getproducts());
                
            }
            
        }

        
        for(int c=0; c<all_products_trans.size(); c++)
        {
            for(int d=0; d<all_products_trans[c].size(); d++)
            {
                products_vec[a][products_index[all_products_trans[c][d]]] = true;
            }
        }
        

        
        
    }

    return products_vec;

}

void SupermarketPlusPlus::recomendation(unsigned int &id)
{
	
    
    unsigned int index_id=0;
    map<string, unsigned int> products_index;       //map<product name, matrix position>
    map<unsigned int, unsigned int> client_index;   // map<matrix position, id>
    
    vector<vector<bool>> products_vec = recomendation_bool_vector(index_id, id, products_index,client_index, transactionIdx, clientIdx);  //set products_vec values
    vector<bool> target_client = products_vec[index_id];//set target_client with the matriz line
    get_most_product(products_vec, target_client, products_index, index_id);

    
}
    
    
    
    
void SupermarketPlusPlus::get_most_product(vector<vector<bool>> &matrix, vector<bool> &target_client, map<string, unsigned int> &products_index, unsigned int &index_id)
{
	
    
    
    
    map<unsigned int, string> products_index_inverse;  // map to change products_index map order
    
    for (auto iterator = products_index.begin(); iterator != products_index.end(); iterator++)
    {
        
       
        
        products_index_inverse.insert(make_pair(iterator->second, iterator->first));        //invert the products_index map
        // map<matrix position, product name>
    }

    
    struct client_special
    {
        
        vector<unsigned int> products;
        unsigned int max=0;
    };
    unsigned int counter_max=0;
    vector<client_special> clients_prob_suggest;
    
    for(int i=0; i<matrix.size(); i++)   //run the matrix by clients
    {
        client_special client_temp;
        for(int a=0; a<matrix[i].size(); a++)
        {
            if(target_client[a] == matrix[i][a])
            {
                if(target_client[a]==true)
                {
                    client_temp.max++;
                }
            }
            else if(matrix[i][a] == true)
            {
                client_temp.products.push_back(a);
            }

        }
        if(!client_temp.products.empty())
        {
            clients_prob_suggest.push_back(client_temp);
            if(client_temp.max>counter_max)
            {
                counter_max = client_temp.max;
            }
        }
    }
    vector<unsigned int> products_to_suggest;
    
    for(int i=0; i<clients_prob_suggest.size(); i++)
    {
        if(clients_prob_suggest[i].max == counter_max)
        {
            products_to_suggest.insert(products_to_suggest.end(), clients_prob_suggest[i].products.begin(), clients_prob_suggest[i].products.end());
        }
    }
    unsigned int counter_plus_product=0;
    size_t counter_plus_temp=0;
    vector<unsigned int> posicao;
    
    for(int i=0; i<products_to_suggest.size(); i++)
    {
        counter_plus_temp = count(products_to_suggest.begin(), products_to_suggest.end(), products_to_suggest[i]);
        if(counter_plus_temp> counter_plus_product)
        {
            counter_plus_product=counter_plus_temp;
            posicao.clear();
            posicao.push_back(products_to_suggest[i]);
        }
        else if(counter_plus_temp == counter_plus_product)
        {
            if(find(posicao.begin(), posicao.end(), products_to_suggest[i]) == posicao.end())
            {
                posicao.push_back(products_to_suggest[i]);
            }
        }
    }
    cout<<endl<<"This client should buy: ";
    for(int i=0; i<posicao.size(); i++)
    {
        
        if(i==posicao.size()-1)
        cout<<products_index_inverse[posicao[i]]<<endl;
        else
        cout<<products_index_inverse[posicao[i]]<<", ";
    }
    
}
   

/*********************************
 * Products Management
 ********************************/

// list the products by alphabetical order
void SupermarketPlusPlus::listProducts() const{
    
    
    if(!productIdx.empty())
    {
        cout << right << setw(25) << "  PRODUCT  " << "       " << right << setw(4) << " PRICE " << endl;
        cout << right << setw(25) << "___________" << "       " << right << setw(4) << "_______" << endl;
        cout << endl;
        
        for (auto iterator = productIdx.begin(); iterator != productIdx.end(); iterator++)
        {
			cout << productIdx.at(iterator->first);
           // cout << right << setw(25)<<productIdx.at(iterator->first).getName()<< "       " << left <<productIdx.at(iterator->first).getValue()<<endl;
        }
    }
    else
    {
        cerr<<"No products to show. Please a product first"<< endl;
        getchar();
    }
    
        
}
//lists a multimap of transactions by chornological order
void SupermarketPlusPlus::chronological_order_transactions(const multimap<unsigned int, Transaction> &multimap_print)
{
    
    
    
    multimap<Date, Transaction> trans_temp;
    for (auto iterator = multimap_print.begin(); iterator != multimap_print.end(); iterator++)
    {
        trans_temp.insert(make_pair(iterator->second.getdate(), iterator->second));
    }
    
    
    if(!trans_temp.empty())
    {
        cout << right << setw(2) << "CLIENT ID" << "     " << left << setw(10) << "   DATE   " << "     " << right << setw(15) << "     PRODUCTS       " << endl;
        cout << right << setw(2) << "_________" << "     " << left << setw(10) << "__________" << "     " << right << setw(15) << "__________________" << endl;
        cout << endl;
        
        for (auto iterator = trans_temp.begin(); iterator != trans_temp.end(); iterator++)
        {
        
            cout << (*iterator).second;
        }
    }
    else{
        cerr<< "No Transactions to show" << endl;
    }
    cout << endl;
}

//lists all transactions of a client in chronological order
void SupermarketPlusPlus::clients_transactions(string name)
{
    map<string, Client> map_client_temp;
    for (auto iterator = clientIdx.begin(); iterator != clientIdx.end(); iterator++)
    {
        map_client_temp.insert(make_pair((iterator->second).getname(), iterator->second));
    }
    multimap<unsigned int, Transaction> to_print;
    unsigned int id= map_client_temp[name].getId();
    for (auto iterator = transactionIdx.begin(); iterator != transactionIdx.end(); iterator++)
    {
        if((*iterator).first == id)
        {
            to_print.insert(make_pair(id, iterator->second));
        }
    }
    SupermarketPlusPlus::chronological_order_transactions(to_print);
}

//prints all transactions
void SupermarketPlusPlus::printall_trans()
{
    chronological_order_transactions(transactionIdx);
}

//prints all transactions from a specific day
void SupermarketPlusPlus::print_trans_oneday(Date &date)
{
    multimap<unsigned int, Transaction> map_print;
    for (auto iterator = transactionIdx.begin(); iterator != transactionIdx.end(); iterator++)
    {
        if((*iterator).second.getdate().getDay() == date.getDay() && (*iterator).second.getdate().getMonth() == date.getMonth() && (*iterator).second.getdate().getYear() == date.getYear())
        {
            map_print.insert(make_pair((*iterator).first, (*iterator).second));
        }
    }
    SupermarketPlusPlus::chronological_order_transactions(map_print);
}

//prints all transactions that are set between two dates
void SupermarketPlusPlus::print_trans_between_dates(Date &date1, Date &date2)
{
    
    
    if(date2<=date1)
    {
        cerr<<"The order of the dates you provided is invalid!!"<<endl;
        getchar();
    }
    else
    {
        multimap<unsigned int, Transaction> map_print;
        for (auto iterator = transactionIdx.begin(); iterator != transactionIdx.end(); iterator++)
        {
            if((*iterator).second.getdate()<= date2 && date1<= (*iterator).second.getdate())
            {
                map_print.insert(make_pair((*iterator).first, (*iterator).second));
            }
        }
        SupermarketPlusPlus::chronological_order_transactions(map_print);
    }
    
}

/*********************************
 * Save changes 
 ********************************/

// save the clients information and/or the transactions information
void SupermarketPlusPlus::saveChanges() const
{
	unsigned int return_menu = 0;
	string file;

    if(changedClients == true)
    {
		if (SupermarketPlusPlus::clients_file == "0.txt")
		{
			
			do {
				cout << "What is the name of the clients file you wish to save whitout extension: ";
				getline(cin, file);
			} while (!string_valid(file, return_menu));
			if (return_menu != 1)
			{
				file += ".txt";
				ofstream cl_files(file);

				cl_files << clientIdx.size() << endl;
				for (auto iterator = clientIdx.begin(); iterator != clientIdx.end(); iterator++)
				{
					clientIdx.at(iterator->first).save_client(cl_files);
				}
			}
		}
		else
		{
			ofstream cl_files(SupermarketPlusPlus::clients_file);

			cl_files << clientIdx.size() << endl;
			for (auto iterator = clientIdx.begin(); iterator != clientIdx.end(); iterator++)
			{
				clientIdx.at(iterator->first).save_client(cl_files);
			}
		}

        

    }
	if(changedTransactions== true)
    {
		unsigned int return_menu = 0;
		string file;
		if (SupermarketPlusPlus::transactions_file == "0.txt")
		{
			do {
				cout << "What is the name of the transactions file you wish to save whitout extension: ";
				getline(cin, file);
			} while (!string_valid(file, return_menu));
			if (return_menu != 1)
			{
				file += ".txt";
				ofstream tr_files(file);
				tr_files << transactionIdx.size() << endl;
				for (auto iterator = transactionIdx.begin(); iterator != transactionIdx.end(); iterator++)
				{
					(*iterator).second.save(tr_files);
				}
			}
			else {
				ofstream tr_files(SupermarketPlusPlus::transactions_file);
				tr_files << transactionIdx.size() << endl;

				for (auto iterator = transactionIdx.begin(); iterator != transactionIdx.end(); iterator++)
				{
					(*iterator).second.save(tr_files);
				}
			}
		}
        
    }
    
}

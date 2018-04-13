#pragma once

#include <iostream>
#include <string>
#include <map>
#include <ctime> 
#include <cwchar>
#include <iomanip>
#include <vector>
#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"
#include <stdexcept>


using namespace std;

class SupermarketPlusPlus{
 
	
private:
  string shop; // shop's name
  string clients_file, products_file, transactions_file; // name of the clients, transactions and products files
  bool changedTransactions=false; // flag que fica a true se for preciso guardar no final as transacoes
  bool changedClients=false; // flag que fica a true se for preciso guardar no final os clienets
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identiicador
  map<unsigned int, Client> clientIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
  map<string,Product> productIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  multimap<unsigned int, Transaction> transactionIdx; // multimap para "traduzir" o identificador do cliente nos indices das suas transacoes no vetor de transacoes
  unsigned int id_next;

 public:
    SupermarketPlusPlus(){};
  SupermarketPlusPlus(string shop, string clients_file, string products_file, string transactions_file);
  void listClientsOrderAlpha(map<unsigned int, Client> &map_print);
  void showallclients();
    void bottom10();
    void sorting_nmb_occurrence (vector<string> &vec);
    vector<vector<bool>> recomendation_bool_vector(unsigned int &index_id, unsigned int &id, map<string, unsigned int> &products_index, map<unsigned int, unsigned int> &client_index, multimap<unsigned int, Transaction> &transaction, map<unsigned int, Client> &client);
    void get_most_product(vector<vector<bool>> &matrix, vector<bool> &target_client, map<string, unsigned int> &products_index, unsigned int &index_id);
    void recomendation(unsigned int &id);
  void listProducts() const;
  void showClientInformation(unsigned int id);
  void saveChanges() const;
  void addclient(string name);
  bool existproductIdx(string product);
  bool existclientIdx(unsigned int id);
    bool existclientname (string name);
  void addtransaction(unsigned int id, vector<string> products);
  void set_clients_purchase_value(vector<string> &products_2, unsigned int &id);
  void changeclient(unsigned int id, string new_name);
  void removeclient(int id);
  void chronological_order_transactions(const multimap<unsigned int, Transaction> &multimap_print);
    void clients_transactions(string name);
    void printall_trans();
    void print_trans_oneday(Date &date);
    void print_trans_between_dates(Date &date1, Date &date2);
};


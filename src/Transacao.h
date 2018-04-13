#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Data.h"
#include "utils.h"



using namespace std;


class Transaction {
 private:
  unsigned int clientID;
  Date date; // type DD/MM/AAAAA
  vector<string> products_bought;

 public:
	Transaction() {};
  Transaction(ifstream & in); // transacion like clientID;date; products
  unsigned int getclientID() const;
    Date getdate() const;
    vector<string> getproducts() const;
  void setId(unsigned int id);
  void setDate(Date date);
  void setProducts(vector<string> products);
  void save(ofstream & out) const; // saves transaction
  inline string getid0();
  friend ostream& operator<<(ostream& out,Transaction & trans); // shows transaction
};




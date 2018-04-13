#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "utils.h"
#include "Data.h"

using namespace std;


class Client {
 private:
  unsigned int id;
  string name;
  Date date;
  float purchases;

 public:
	Client() {};
  Client (ifstream & in);
  void setName(string name);
  void setId(unsigned int id);
  void setPurchases(float purchases);
  void setdate(Date date_date);
  void eraseclient(map<unsigned int, Client> &map_client,unsigned int &id);
  string getname() const;
  unsigned int getId() const;
  float getpurchases() const;
  Date getDate() const;
  inline string getid0();
  //Cliente getclient(vector<Cliente> &vec_client, unsigned int id);
  void save_client(ofstream & out) const;
  friend ostream& operator<<(ostream& out,Client & cli);  // mostra informacao do cliente no ecra
};


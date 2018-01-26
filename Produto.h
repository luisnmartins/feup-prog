#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "utils.h"


using namespace std;



class Product {
 private:
  string name;
  float value;


 public:
    Product(){};
  Product(ifstream & in);
  string getName() const;
  float getValue() const;
  int productind(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos
  friend ostream& operator<<(ostream& out, const Product & prod); // ostra umproduto
};



#include "Produto.h"


Product::Product(ifstream & in){ // nome ; custo
	
	string product;
	if (in.is_open())
	{
		

		{
			getline(in, product);
			istringstream is;
			is.str(product);
			getline(is, name, ';');
            del_whitespace(name);
			is >> value;
		}
	}
}

string Product::getName() const {
  return name;
}

float Product::getValue() const {
  return value;
}

ostream& operator<<(ostream& out, const Product & prod){

	out << right << setw(25) << prod.getName() << "       " << left << prod.getValue() << endl;
	return out;


}



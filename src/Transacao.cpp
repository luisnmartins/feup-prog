#include "Transacao.h"



unsigned int Transaction::getclientID() const{
  return clientID;
}

Date Transaction::getdate() const
{
    return date;
}

vector<string> Transaction::getproducts() const
{
    return products_bought;
}



Transaction::Transaction(ifstream & in)
{ 
	char ch;
	string transaction, products, string_date;
	if (in.is_open())
	{
		if (in.peek() == std::ifstream::traits_type::eof())
		{

		}
		else
		{
			getline(in, transaction);
			istringstream is;
			is.str(transaction);


			is >> clientID >> ch;
			getline(is, string_date, ';');
			Date new_date(string_date);
			this->date = new_date;


			getline(is, products);
			
			string eachproduct;
			istringstream as;
			as.str(products);
			int howmany = 0;
			for (int i = 0; i < products.size(); i++)
			{
				if (products[i] == ',') howmany++;
			}
			for (int a = 0; a <= howmany; a++)
			{
				if (a != howmany)
                {
					getline(as, eachproduct, ',');
                    del_whitespace(eachproduct);
                }
				else
                {
                    getline(as, eachproduct);
                    del_whitespace(eachproduct);
                }
				products_bought.push_back(eachproduct);
			}



		}
	}
	
}
void Transaction::setId(unsigned int id) {
	Transaction::clientID = id;
}
void Transaction::setDate(Date date) {
	Transaction::date = date;
}

void Transaction::setProducts(vector<string> products) {
	Transaction::products_bought = products;
}

void Transaction::save(ofstream & out) const{ // saving transaction like id;date;products
  
	out << clientID << " ; ";
	date.save(out);
	out << " ; ";
	for (int i = 0; i < products_bought.size(); i++)
	{
		if (i != products_bought.size() - 1)
		{
			out << products_bought[i] << ", ";

		}
		else out << products_bought[i];

	}
	out << endl;

}
inline string Transaction::getid0() //puts when printed a zero before the number of a date in case it has only one digit ex 10/03/2011 or 03/03/2052
{
	string print;
	unsigned int id = Transaction::clientID;
	if (id < 10)
	{
		print = "0";
		print.append(to_string(id));
		return print;
	}
	else
		return to_string(id);
}

// prints the transaction
ostream& operator<<(ostream& out,Transaction & trans){
	
	out << right << setw(2) << trans.getid0() << "     " << right <<  "       " << trans.getdate() << "     " << left << setw(7);
	for (int a = 0; a< trans.getproducts().size(); a++)
	{
		if (a == (trans.getproducts().size() - 1))
		{
			out << (trans.getproducts()[a]);
		}
		else
			out << trans.getproducts()[a] << " , ";
	}
	out << endl;

	return out;
}

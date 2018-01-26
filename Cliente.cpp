#include "Cliente.h"




Client::Client(ifstream & in)
{
	char ch;
	string client;
	string date;
	if (in.is_open())
	{

			getline(in, client);
			istringstream is;
			is.str(client);
			is >> id >> ch;
			getline(is, name, ';');
			getline(is, date, ';');
			is >> purchases;
			del_whitespace(name);
            del_whitespace(date);
			Date new_date(date);
			Client::date = new_date;

		}
	}




void Client::setdate(Date date_date) {
	Client::date = date_date;
}

void Client::setId(unsigned int id)
{
	Client::id = id;
}

void Client::setName(string name)
{
	Client::name = name;
}

void Client::setPurchases(float purchases)
{
	Client::purchases = purchases;
}

string Client::getname() const{
  return name;
}

unsigned int Client::getId() const{
  
    
    return id;
}

float Client::getpurchases() const{
  return purchases;
}

Date Client::getDate() const {
	return date;
}


void Client::eraseclient(map<unsigned int, Client> &map_client, unsigned int &id)
{
	map_client.erase(id);
	
}

/*Cliente Client::getclient(vector<Cliente> &vec_client, unsigned int id)
{

}*/

void Client::save_client(ofstream & out) const{

  out << id << " ; ";
  out << name << " ; ";
  date.save(out);
  out << " ; ";
  out << purchases << endl;

}

inline string Client::getid0()
{
	string print;
	unsigned int id = Client::id;
	if (id < 10)
	{
		print = "0";
		print.append(to_string(id));
		return print;
	}
	else
		return to_string(id);
}

ostream& operator<<(ostream& out,Client &cli){
	out << right << setw(3) << cli.getid0() << "     " << setw(10) << "               " << left << setw(20) << cli.getname() << "           " << left << cli.getDate() << "     " << right << setw(13) << cli.getpurchases() << endl;
	
	return out;
}

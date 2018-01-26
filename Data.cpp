#include "Data.h"
#include <sstream>

Date::Date(string string_date) // date like DD/MM/AAA
{ 
	char ch1, ch2;
	istringstream is;
	is.str(string_date);
	is >> day >> ch1 >> month >> ch2 >> year;
}

int Date::getDay() const{
  return day;
}

int Date::getMonth() const{
  return month;
}

int Date::getYear() const{
  return year;
}

void Date::setDay(int day){
	Date::day = day;
}

void Date::setMonth(int month){
	Date::month = month;
}

void Date::setYear(int year){
	Date::year = year;
}

void Date::save(ofstream & out) const
{
  
	out << day << "/";
	out << month << "/";
	out << year;
}

ostream& operator<<(ostream& out, const Date & date){
    if(date.getDay()<10)
    out <<"0"<< date.getDay() << "/";
    else
        out << date.getDay() << "/";
    if(date.getMonth()<10)
    out <<"0"<< date.getMonth() << "/";
    else
        out << date.getMonth() << "/";
    out << date.getYear();
    return out;
}
bool operator<=(const Date &date1, const Date & date2)
{
	return (10000 * date1.getYear()) + (date1.getMonth() * 100) + date1.getDay() <= (10000 * date2.getYear()) + (date2.getMonth() * 100) + date2.getDay();

}
bool operator<(const Date &date1, const Date & date2)
{
	return (10000 * date1.getYear()) + (date1.getMonth() * 100) + date1.getDay() < (10000 * date2.getYear()) + (date2.getMonth() * 100) + date2.getDay();

}
bool Date::verify_date()
{
	
    int day, month, year;
    day = Date::getDay();
    month = Date::getMonth();
    year = Date::getYear();
    if (month == 2)
	{

		//leap year
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 4 == 0 && year % 400 == 0))
		{
			if (day <= 29 && day>0)
				return true;
			else

				return false;

		}
		else
		{
			if (day <= 28 && day>0)
				return true;
			else
				return false;
		}
	}
	//month has 31 days
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day <= 31 && day>0)
			return true;
		else
			return false;
	}
	//month is not valid
	else if (month > 12 || month <0)
	{
		return false;

	}
	//month has 30 days
	else
	{
		if (day <= 30 && day>0)
			return true;
		else
			return false;
	}
}

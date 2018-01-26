# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Date {
 private:
  int day;
  int month;
  int year;

 public:
  Date(){};
	Date(string string_date); // date type DD/MM/AAA
  int getDay() const;
  int getMonth() const;
  int getYear() const;
  void setDay(int day);
  void setMonth(int month);
  void setYear(int year);
  void save(ofstream & out) const;
  friend ostream& operator<<(ostream& out, const Date & date);
  friend bool operator<=(const Date &date2, const Date & date1);
  friend bool operator<(const Date &date2, const Date & date1);
  bool verify_date();
};



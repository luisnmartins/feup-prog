#include "Error.h"
#include "utils.h"
#include "Vende++.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstddef>
#include <algorithm>
#include <array>


using namespace std;



	
	


bool num_valid(string num, unsigned int &return_menu)    //verify if a string is a number
{
    return_menu=0;
    SupermarketPlusPlus new_super;
    int choice, choice2, flag=0, flag2=0, final=1;

	if (cin.fail() == true || !(std::all_of(num.begin(), num.end(), :: isdigit)) || num == "")  //if fail or it's not all digits or it's an empty string
	{
		if (cin.eof() == true)   //end of file
		{
			cin.clear();
			do 
			{
				flag = 0;
				cout << "\nAre you sure you want to quit:\n1 - No, Try Again\n2 - Return to Menu\n3 - Exit Program\nChoice:";
				cin >> choice;
				if (cin.fail() == false)
				{

					switch (choice)
					{
					case 1:
						cin.clear();
						cin.ignore();
						final=0;
						break;
					case 2:
                            cin.ignore(1000, '\n');
                            return_menu=1;
						break;
					case 3:
						do
						{
							flag2 = 0;
							cout << "Are you sure you want to quit?\n1 - Yes, save and quit\n2 - Yes, quit without saving\n3 - No, return back\nChoice: ";
							cin >> choice2;
							if (cin.fail() == false)
							{
								switch (choice2)
								{
								case 1:
                                    
                                    new_super.saveChanges();
									exit(0);
									break;
								case 2:
									exit(0);
									break;
								case 3:
                                    cin.ignore(100000, '\n');
                                        return_menu=1;
									break;
								default:
									cout << "\nInvalid choice!! Please try again\n" << endl;
									flag = 1;
									cin.clear();
									break;
								}
							}
							else
							{
								cout << "\nInvalid choice!!Please try again\n" << endl;
								flag2 = 1;
								cin.clear();
								cin.ignore(100000, '\n');
							}

						} 
						while (flag2 == 1);
						break;
					default:
						cout << "\nInvalid choice!! Please try again\n" << endl;
						flag = 1;
						cin.clear();
						break;

					}
				}
				else
				{
					cout << "\nInvalid choice!! Please try again\n" << endl;
					flag = 1;
					cin.clear();
					cin.ignore(100000, '\n');
				}
			} while (flag == 1);
		}
		else 
		{
			cerr << endl << "ERROR!! Please try again!!" << endl << endl;
			cin.clear();
            final=0;
		}
	}
	else
	
        final = 1;
    
    if(final==1)
    {
        return true;
    }
    else
        return false;
	
    
}

bool string_valid(string palavra, unsigned int &return_menu)
{
    return_menu=0;
    SupermarketPlusPlus new_super;
    int choice, flag = 0, final=1;

	if (cin.fail() == true || (!isalpha(palavra[0]) && palavra != "0"))
	{
		if (cin.eof())
			
		{
			cin.clear();
			do {
				flag = 0;
				cout << "\nAre you sure you want to quit:\n1 - No, Try Again\n2 - Return to Menu\n3 - Exit Program\nChoice:";
				cin >> choice;
				if (!cin.fail())
				{
					switch (choice)
					{
					case 1:
						cin.clear();
						cin.ignore();
                        final=0;
						break;
					case 2:
                            cin.ignore(100000, '\n');
                            return_menu=1;
						break;
					case 3:
						do {
							flag = 0;
							cout << "Are you sure you want to quit?\n1 - Yes, save and quit\n2 - Yes, quit without saving\n3 - No, return back\nChoice: ";
							cin >> choice;
							if (!cin.fail())
							{
								switch (choice) {
								case 1:
                                    
                                    new_super.saveChanges();
									exit(0);
									break;
								case 2:
									exit(0);
									break;
								case 3:
                                    cin.ignore(100000, '\n');
                                        return_menu=1;
									break;
								default:
									cout << "Invalid choice!! Please try again\n" << endl;
									flag = 1;
									cin.clear();
									break;
								}
							}
							else
							{
								cout << "\nInvalid choice!! Please try again\n" << endl;
								flag = 1;
								cin.clear();
								cin.ignore(100000, '\n');
							}

						} while (flag == 1);
						break;
					default:
						cout << "\nInvalid choice!! Please try again\n" << endl;
						flag = 1;
						cin.clear();
						break;
					}
				}
				else
				{
					cout << "\nInvalid choice!! Please try again\n" << endl;
					flag = 1;
					cin.clear();
					cin.ignore(100000, '\n');
				}
			} while (flag == 1);
		}
		else

		{
			cerr << endl << "ERROR!! Please try again!!" << endl << endl;
			cin.clear();
			cin.ignore(1000, '\n');
            final=0;
		}
	}
	else
        final=1;
    
    
    if(final==1)
    {
        return true;
    }
    else
        return false;
}

bool file_valid(string name)
{
	SupermarketPlusPlus new_super;
    int flag = 0, choice, final=1;

	if(cin.fail()== true)
	{
		if (cin.eof())

		{
			cin.clear();
			do {
				
				flag = 0;
				cout << "\nAre you sure you want to quit:\n1 - No, Try Again\n2 - Exit Program\nChoice:";
				cin >> choice;
				if (!cin.fail())
				{
					switch (choice)
					{
					case 1:
						cin.clear();
						cin.ignore();
                            final=0;
						break;
					case 2:
						do {
							
							flag = 0;
							cout << "Are you sure you want to quit?\n1 - Yes, save and quit\n2 - Yes, quit without saving\n3 - No, return back\nChoice: ";
							cin >> choice;
							if (!cin.fail())
							{
								switch (choice) {
								case 1:
                                        
                                        new_super.saveChanges();
									exit(0);
									break;
								case 2:
									exit(0);
									break;
								case 3:
                                        cin.ignore(100000, '\n');
                                        final=0;
									break;
								default:
									cout << "Invalid choice!! Please try again\n" << endl;
									flag = 1;
									cin.clear();
									break;
								}
							}
							else
							{
								cout << "\nInvalid choice!! Please try again\n" << endl;
								flag = 1;
								cin.clear();
								cin.ignore(100000, '\n');
							}

						} while (flag == 1);
						break;
					default:
						cout << "\nInvalid choice!! Please try again\n" << endl;
						flag = 1;
						cin.clear();
						break;
					}
				}
				else
				{
					cout << "\nInvalid choice!! Please try again\n" << endl;
					flag = 1;
					cin.clear();
					cin.ignore(100000, '\n');
				}
			} while (flag == 1);
		}
		else
            final=1;
	}
    
    if(final==1)
    {
        return true;
    }
    else
        return false;
}
#include "utils.h"
#include <string>






void clearScreen()
{
	COORD upperLeftCorner = { 0,0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}



unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max)
{

	int num;
	string num_s;
	unsigned int return_menu = 0;
	getline(cin, num_s);
	if (num_valid(num_s,return_menu) == true)
	{
		if(return_menu!=1)
        {
            num = stoi(num_s);
            if (num >= min && num <= max)
            {
                return num;
            }
            else
            {
			
                press_any_key();
                return 0;
            }
        }
	}
	else
	{
        press_any_key();
		return 0;
	}
}



int leInteiro(int min, int max){

	unsigned int return_menu = 0;
	int num;
	cin >> num;
	if (num_valid(to_string(num),return_menu) == true)
	{
		if (num >= min && num <= max)
		{
			return num;
		}
		else
		{
			cout << "Option not Valid!!";
			return 0;
		}
	}
	else
	{
		cout << "Option not Valid!!";
		return 0;
	}



}



void del_whitespace(string &line)
{

	
	//Delete whitespace characters in the beginning
	while (line.at(0) == ' ')
		line.erase(0, 1);
	//Delete whitespace characters in the end
	int lastindex = line.size() - 1;
	while (line.at(lastindex) == ' ' || line.at(lastindex) == '\r')
	{
		line.erase(lastindex, 1);
		lastindex--;
	}
	for (int a = 0; a < line.size(); a++)
	{


		if (isspace(line[a]) && !isalpha(line.at(a + 1)))
		{
			line.erase(a, 1);
			a--;
		}
	}
}


		





void press_any_key() {
	
	cout << endl << endl << "Press any key to continue..." << endl;
	getchar();
}
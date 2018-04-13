#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include<windows.h>
#include "defs.h"
#include "Error.h"

using namespace std;


void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);
int leInteiro(int min, int max);
void press_any_key();
void del_whitespace(string &line);

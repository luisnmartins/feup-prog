#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Error.h"
#include "defs.h"
#include "utils.h"
#include "Vende++.h"

using namespace std;

bool initialInfo(string & shop, string & clients_file, string & products_file, string & transactions_file);

unsigned short int MainMenu();

void initialOptions(SupermarketPlusPlus & supermarket);

void clientManagementoptions(SupermarketPlusPlus & supermarket);
void TransactionsSubMenu_options(SupermarketPlusPlus & supermarket);




/*void listClientsOrderAlpha(SupermarketPlusPlus & supermercado);

void listProducts(SupermarketPlusPlus & supermercado);

void opcoesGestaoTransacoes(SupermarketPlusPlus & supermercado);

void opcoesRecomendacao(SupermarketPlusPlus & supermercado);
*/
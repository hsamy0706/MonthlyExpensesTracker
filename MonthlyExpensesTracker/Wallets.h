#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include"Datafiles.h"

using namespace std;

class Wallets
{
private:
	unordered_map<string, pair<double, bool>>myWallets;

	double total = 0;
	const string filename = "Wallets.csv";
	Datafiles data;

public:

	Wallets();
	bool addWallet(string name, double amount);
	bool changeBalance(string name, double amount, bool isIncome);
	bool checkExistence(string name);
	void viewRemainingMoney();
	bool displayWallets();
	~Wallets();

};


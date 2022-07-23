#include "Wallets.h"
#include<iostream>

using namespace std;

Wallets::Wallets()
{
	data.readWallets(filename, myWallets);
}

bool Wallets::addWallet(string name, double amount)
{
	if (!myWallets[name].second && data.addWallet(filename, name, amount))
	{
		myWallets[name].first = amount;
		myWallets[name].second = true;

		return true;
	}
	else
	{
		cout << "This wallet already exists...\n" << endl;
		return false;
	}
}

bool Wallets::changeBalance(string name, double amount, bool isIncome)//isIncome is passed from home
{
	if (isIncome == true)
	{
		if (myWallets[name].second)
		{
			myWallets[name].first += amount;
			return true;
		}
	}

	else if (isIncome == false)
	{
		if (myWallets[name].second && myWallets[name].first >= amount)
		{
			myWallets[name].first -= amount;
			return true;
		}
		else if (myWallets[name].second && myWallets[name].first < amount)
		{
			return false;
		}
	}
}

bool Wallets::checkExistence(string name)
{
	if (myWallets[name].second == 0)
	{
		cout << "This wallet doesn't exist...\n";
		return false;
	}
	else {
		cout << "This wallet already exists...\n" << endl;
		return true;
	}
}

bool Wallets::displayWallets()
{
	unordered_map<string, pair<double, bool>>::iterator it;
	if (myWallets.empty())
	{
		cout << "There is no wallets \n";
		return false;
	}
	else
	{
		cout << "\nYour Wallets:\n";
		for (it = myWallets.begin(); it != myWallets.end(); it++)
		{
			cout << it->first << endl;
		}
		return true;
	}
}

void Wallets::viewRemainingMoney()
{
	cout << "The remaining money in your: " << endl;

	unordered_map<string, pair<double, bool>>::iterator it;
	if (myWallets.empty())
	{
		cout << "There is no wallets \n";
	}
	else {
		for (it = myWallets.begin(); it != myWallets.end(); it++)
		{
			cout << it->first << ":" << it->second.first << endl;
			total += it->second.first;
		}
		cout << "Total money: " << total << endl;
	}
}

Wallets::~Wallets()
{
	data.updateWallets(filename, myWallets);
	cout << "sucesss" << endl;
}
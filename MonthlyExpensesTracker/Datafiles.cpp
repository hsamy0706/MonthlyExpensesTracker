#include "Datafiles.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>


using namespace std;
Datafiles::Datafiles()
{

}

bool Datafiles::readWallets(string fileName, unordered_map<string, pair<double, bool>>& records)// double ll amount , bool: to check existance of the wallets
{
	inputFile.open(fileName);
	if (inputFile.is_open())
	{
		int i = 0;

		while (!inputFile.eof())
		{
			string name = "   ", str;

			getline(inputFile, name, ',');
			getline(inputFile, str, '\n');
			if (name != "")
			{
				double balance;
				stringstream line(str);
				line >> balance;
				records[name].first = balance;
				records[name].second = true;
			}
			i++;
		}
	}
	else
	{
		cout << "fail to open the file" << endl;
		return false;
	}
	inputFile.close();
	return true;
}

bool Datafiles::read_IEfiles(string fileName, map<pair<string, string>, vector<Money>>& records)
{
	inputFile.open(fileName);
	if (inputFile.is_open())
	{
		int i = 0;
		string line;
		while (getline(inputFile, line))//true if line!=" " else false
		{
			Money money;
			pair<string, string>yearAndMonth;
			string s,dd;
			stringstream record(line);
			getline(record, money.date, ',');
			stringstream date(money.date);
			getline(date,dd , '/');
			getline(date, yearAndMonth.second, '/');
			getline(date, yearAndMonth.first);
			getline(record, s, ',');
			stringstream amount(s);
			amount >> money.amount;
			getline(record, money.note, ',');
			getline(record, money.category, ',');
			getline(record, money.walletName);
			if (i != 0)
			{
				records[yearAndMonth].push_back(money);
			}
			i++;
		}
	}
	else
	{
		cout << "failed to open file" << endl;
		return false;
	}
	inputFile.close();
	return true;
}

bool Datafiles::writeRecord_IEfile(string fileName, Money  money)
{
	outputFile.open(fileName, ios::app);// to append file
	if (outputFile.is_open())
	{
		outputFile << money.date << "," << money.amount << "," << money.note << "," << money.category << "," << money.walletName << endl;
	}
	else {
		cout << "failed to open the file" << endl;
		return false;
	}
	outputFile.close();
	return true;
}

bool Datafiles::addWallet(string fileName, string walletName, double walletAmount)
{
	outputFile.open(fileName, ios::app);
	if (outputFile.is_open())
	{
		outputFile << walletName << "," << walletAmount << endl;
	}
	else
	{
		cout << "failed to open the file" << endl;
		return false;
	}
	outputFile.close();
	return true;
}

void Datafiles::updateWallets(string fileName, unordered_map<string, pair<double, bool>>& records)
{

	outputFile.open(fileName);

	unordered_map<string, pair<double, bool>>::iterator it;
	if (outputFile.is_open())
	{
		for (it = records.begin(); it != records.end(); it++)
		{
			outputFile << it->first << "," << it->second.first << endl;//walletName, walletAmount
		}
	}
	else
		cout << "failed to open the file" << endl;
	outputFile.close();
}

Datafiles::~Datafiles()
{
	inputFile.close();
	outputFile.close();
}

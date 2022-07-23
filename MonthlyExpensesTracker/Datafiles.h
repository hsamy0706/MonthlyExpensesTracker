#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include"Structers.h"  
using namespace std;


class Datafiles
{
private:
	ifstream inputFile;
	ofstream outputFile;

public:
	Datafiles();
	bool readWallets(string fileName, unordered_map<string, pair<double, bool>>& records);//amount,flag to know if the wallet exist
	bool read_IEfiles(string fileName, map<pair<string, string>, vector<Money>>& records);//pair.first=year,pair.second=month
	bool writeRecord_IEfile(string fileName, Money money);
	bool addWallet(string fileName, string walletName, double walletAmount);
	void updateWallets(string fileName, unordered_map<string, pair<double, bool>>& records);
	~Datafiles();
};


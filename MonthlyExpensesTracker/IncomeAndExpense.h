#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include<iomanip>
#include<algorithm>
#include <stdio.h>
#include <time.h>
#include <ctime>

#include "Structers.h"
#include "Wallets.h"
#include "Datafiles.h"
#include "Home.h"

using namespace std;

class IncomeAndExpense
{
private:
	map<pair<string, string>, vector<Money>> expensesMoney;
	map<pair<string, string>, vector<Money>> incomesMoney;
	const string incomeFileName = "Incomes.csv";
	const string expenseFileName = "Expenses.csv";
	Wallets wallets;
	Datafiles data;
	Home home;
	int userDay, userMonth, userYear;

public:
	IncomeAndExpense();
	void choiceValidation(int start, int end, int& choice);
	string convertToLowerCase(string str);
	bool isDateBeforeOrEqualToday();
	string enterDate();
	void enterWalletName(Money& money);
	void addData(bool isIncome);
	void saveData(bool isIncome, Money& money);
	int choicesListOfViewExpenses();
	void filterExpensesBy(double& desiredAmount, string& desiredCategory, string& desiredDate, string& desiredWalle);
	void ViewExpenses();
	~IncomeAndExpense();
};


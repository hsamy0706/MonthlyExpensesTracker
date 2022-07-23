#include "Home.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include"Structers.h"
#include"Wallets.h"
#include "IncomeAndExpense.h"

Home::Home()
{
}

void Home::homeMenu()
{
	do {
		cout << "What do you want\n1-Add monthly income\n2-Add new expenses\n3-View your expenses\n4-View Your Remaining Money\n5-Exist \n";
		cin >> choice;
		if (choice == 1)
		{
			IncomeAndExpense monthlyIncome;
			monthlyIncome.addData(1); //pass 1 if the user chose income
		}
		else if (choice == 2)
		{
			IncomeAndExpense monthlyExpenses;
			monthlyExpenses.addData(0); //pass 0 if the user chose expense
		}
		else if (choice == 3)
		{
			IncomeAndExpense Expenses;
			Expenses.ViewExpenses();
		}
		else if (choice == 4) //view exp
		{
			Wallets wallet;
			wallet.viewRemainingMoney();

		}
		else if (choice == 5)
		{
			cout << "Thank You :)\n";
		}
		else
			cout << "invalid choice" << endl;

	} while (choice != 5);

}
Home::~Home(void)
{

}

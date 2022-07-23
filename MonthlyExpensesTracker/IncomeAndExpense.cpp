#include "IncomeAndExpense.h"

IncomeAndExpense::IncomeAndExpense()
{
	data.read_IEfiles(incomeFileName, incomesMoney);
	data.read_IEfiles(expenseFileName, expensesMoney);
}

void IncomeAndExpense::choiceValidation(int start, int end, int& choice)
{
	while (true)
	{
		if (choice < start || choice > end)
		{
			cout << "Invalid choice, please try again\n";
			cout << "Your choice: ";
			cin >> choice;
			continue;
		}
		break;
	}
}

string IncomeAndExpense::convertToLowerCase(string str)
{
	for_each(str.begin(), str.end(), [](char& c) {
		c = ::tolower(c);
		});
	return str;
}

bool IncomeAndExpense::isDateBeforeOrEqualToday()
{

	const time_t t = time(0);
	const tm* ltm = localtime(&t);
	int todayDay, todayMonth, todayYear;
	todayDay = ltm->tm_mday;
	todayMonth = 1 + ltm->tm_mon; 
	todayYear = 1900 + ltm->tm_year;

	if (todayYear > userYear)
		return true;
	else if (todayYear == userYear)
	{
		if (todayMonth > userMonth)
			return true;
		else if (todayMonth == userMonth)
		{
			if (todayDay >= userDay)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

string IncomeAndExpense::enterDate()
{
	bool isValidDate = true;

	do
	{
		cout << "year: "; cin >> userYear;
		cout << "month: "; cin >> userMonth;
		cout << "day: "; cin >> userDay;

		isValidDate = isDateBeforeOrEqualToday();
		if (!isValidDate)
		{
			cout << "Invalid Date\n";
			continue;
		}

		if (userYear > 9999 ||
			userYear < 1800)
			isValidDate = false;
		if (userMonth < 1 || userMonth > 12)
			isValidDate = false;
		if (userDay < 1 || userDay > 31)
			isValidDate = false;
		if (userMonth == 2)
		{
			if (((userYear % 4 == 0) &&
				(userYear % 100 != 0)) ||
				(userYear % 400 == 0))
				isValidDate = (userDay <= 29);
			else
				isValidDate = (userDay <= 28);
		}
		if (userMonth == 4 || userMonth == 6 ||
			userMonth == 9 || userMonth == 11)
			isValidDate = (userDay <= 30);
		if (userMonth == 1 || userMonth == 3 || userMonth == 5 || userMonth == 7 || userMonth == 8 || userMonth == 10 || userMonth == 12)
			isValidDate = (userDay <= 31);

		if (!isValidDate)
			cout << "Invalid Date\n";

	} while (!isValidDate);

	string date = to_string(userDay) + "/" + to_string(userMonth) + "/" + to_string(userYear);
	return date;
}

void IncomeAndExpense::enterWalletName(Money& money)
{
	int choice;
	cout << "1 - Try again\n2 - Return home\nYour choice: ";
	cin >> choice;
	choiceValidation(1, 2, choice);

	if (choice == 2)
	{
		home.homeMenu();
	}
	cout << "Wallet name: ";
	cin.ignore();
	getline(cin, money.walletName);
	money.walletName = convertToLowerCase(money.walletName);

}

void IncomeAndExpense::addData(bool isIncome)
{
	Money money;
	int choice;
	wallets.displayWallets();

	if (isIncome)
	{
		cout << "\n1-Enter wallet name\n2-Add new wallet\nYour choice: ";
		cin >> choice;
		choiceValidation(1, 2, choice);
	}
	else if (!isIncome)
		choice = 1;

	cout << "\nWallet name: ";
	cin.ignore();
	getline(cin, money.walletName);
	money.walletName = convertToLowerCase(money.walletName);

	if (choice == 1)
	{
		bool walletExists;
		do
		{
			walletExists = wallets.checkExistence(money.walletName);
			if (walletExists)
				break;
			enterWalletName(money);

		} while (!walletExists);//break if wallet exists
	}
	else
	{
		bool walletNotExists;
		do
		{
			walletNotExists = wallets.addWallet(money.walletName, money.amount);
			if (walletNotExists)
				break;
			enterWalletName(money);

		} while (!walletNotExists);//break if wallet does not exist
	}

	do
	{
		cout << "amount: "; cin >> money.amount;
		if (wallets.changeBalance(money.walletName, money.amount, isIncome))
			break;
		cout << "This amount is bigger than the balance in this wallet\n";
		cout << "Do you want to:\n" << "1- Add another amount\n2- Return home\n" << "Your choice: ";

		cin >> choice;
		choiceValidation(1, 2, choice);

		if (choice == 2)
			home.homeMenu();

	} while (true);

	cout << "Enter date\n";
	money.date = enterDate();

	cout << "Enter your note: ";
	cin.ignore();
	getline(cin, money.note);
	cout << "Enter category: "; cin >> money.category; cout << endl;
	money.category = convertToLowerCase(money.category);

	saveData(isIncome, money);

}

void IncomeAndExpense::saveData(bool isIncome, Money& money)
{
	pair<string, string>yearAndMonth;
	stringstream date(money.date);
	getline(date, yearAndMonth.first, '/');
	getline(date, yearAndMonth.second, '/');

	if (isIncome)
	{
		incomesMoney[yearAndMonth].push_back(money);
		data.writeRecord_IEfile(incomeFileName, money);
	}

	else if (!isIncome)
	{
		expensesMoney[yearAndMonth].push_back(money);
		data.writeRecord_IEfile(expenseFileName, money);
	}
}

int IncomeAndExpense::choicesListOfViewExpenses()
{
	cout << "1- show all expenses\n";
	cout << "2- filter by amount\n";
	cout << "3- filter by category\n";
	cout << "4- filter by date\n";
	cout << "5- filter by wallet name\n";
	cout << "6- filter by more than one thing(enter numbers from 2:5 that you)\n";
	int choice;
	cin >> choice;
	choiceValidation(1, 6, choice);

	return choice;
}

void IncomeAndExpense::filterExpensesBy(double& desiredAmount, string& desiredCategory, string& desiredDate, string& desiredWallet)
{
	switch (choicesListOfViewExpenses())
	{
	case 1:
		break;
	case 2:
		cout << "Please enter the AMOUNT you want to display: ";
		cin >> desiredAmount;
		break;
	case 3:
		cout << "Please enter the CATEGORY you want to display: ";
		cin.ignore();
		getline(cin, desiredCategory);
		desiredCategory = convertToLowerCase(desiredCategory);
		break;
	case 4:
		cout << "Please enter the DATE that you want to see your expenses start with till the end of its month: \n";
		desiredDate = enterDate();
		break;
	case 5:
		cout << "Please enter the WALLET you want to display: \n";
		cin.ignore();
		getline(cin, desiredWallet);
		desiredWallet = convertToLowerCase(desiredWallet);
		break;
	case 6:
		int continueFilteration = 0;
		do
		{
			cout << "Please enter from 2:5\n";
			int choice;
			cin >> choice;
			choiceValidation(2, 5, choice);
			switch (choice)
			{
			case 2:
				cout << "Please enter the AMOUNT you want to display: ";
				cin >> desiredAmount;
				break;
			case 3:
				cout << "Please enter the CATEGORY you want to display: ";
				cin.ignore();
				getline(cin, desiredCategory);
				desiredCategory = convertToLowerCase(desiredCategory);
				break;
			case 4:
				cout << "Please enter the DATE that you want to see your expenses start with till the end of its month: \n";
				desiredDate = enterDate();
				break;
			case 5:
				cout << "Please enter the WALLET you want to display: \n";
				cin.ignore();
				getline(cin, desiredWallet);
				desiredWallet = convertToLowerCase(desiredWallet);
				break;
			}
			cout << "If you want to choose another filteration, please enter 1\n";
			cout << "If you have finished filteration, please enter 2\n";
			cin >> continueFilteration;

		} while (continueFilteration == 1);
		break;
	}
}

void IncomeAndExpense::ViewExpenses() {

	const int width_str = 20;
	const char  separator = ' ';
	double desiredAmount = -1;
	string desiredCategory = " ", desiredDate = " ", desiredWallet = " ";

	
	filterExpensesBy(desiredAmount, desiredCategory, desiredDate, desiredWallet);

	cout << left << setw(width_str) << setfill(separator) << "Date";
	cout << left << setw(width_str) << setfill(separator) << "Amount" << " ";
	cout << left << setw(width_str) << setfill(separator) << "Note";
	cout << left << setw(width_str) << setfill(separator) << "Category";
	cout << left << setw(width_str) << setfill(separator) << "Wallets";
	cout << "\n";
	cout << "--------------------------------------------------------------------------------------------\n";

	for (map<pair<string, string>, vector<Money>>::iterator it = expensesMoney.begin(); it != expensesMoney.end(); ++it)
	{
		vector<Money>expense = it->second;
		double totalAmount = 0.0;
		bool isexpensesView = 0;
		int  mm = 0, yy = 0;
		yy = stoi(it->first.first);
		mm = stoi(it->first.second);
		if (desiredDate != " ")
		{
			if (userYear != yy)
				continue;
			if (userMonth != mm)
				continue;
		}
		for (int i = 0; i < expense.size(); i++)
		{
			int dd = 0;
		
			for (int j = 0; j < expense[i].date.size(); j++) //take day from date string
			{
				if (expense[i].date[j] == '/')
					break;

				dd = dd * 10 + (expense[i].date[j] - '0');
			}

			if (desiredAmount != -1 && desiredAmount != expense[i].amount)
				continue;
			if (desiredCategory != " " && desiredCategory != expense[i].category)
				continue;
			if (desiredDate != " ")
			{
				
				if (userDay > dd)
					continue;
			}

			if (desiredWallet != " " && desiredWallet != expense[i].walletName)
				continue;

			cout << left << setw(width_str) << setfill(separator) << expense[i].date;
			cout << left << setw(width_str) << setfill(separator) << expense[i].amount; //double 
			cout << left << setw(width_str) << setfill(separator) << expense[i].note;
			cout << left << setw(width_str) << setfill(separator) << expense[i].category;
			cout << left << setw(width_str) << setfill(separator) << expense[i].walletName;
			cout << "\n";
			totalAmount += expense[i].amount;
			isexpensesView = 1;
		}
		if (isexpensesView)
		{
			cout << "--------------------------------------------------------------------------------------------\n";
			cout << left << setw(width_str) << setfill(separator) << "TOTAL AMOUNT = " << totalAmount << '\n';
			cout << "--------------------------------------------------------------------------------------------\n";
		}
	}
	cout << "--------------------------------------------------------------------------------------------\n";
}

IncomeAndExpense::~IncomeAndExpense()
{

}
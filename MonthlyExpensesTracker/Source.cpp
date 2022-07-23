#include<iostream>
#include<fstream>
#include"Home.h"
#include <string>

using namespace std;

int main()
{
	cout << "Welcome To Monthly Expenses" << endl;
	Home home;
	home.homeMenu();
	system("pause");

	return 0;
}
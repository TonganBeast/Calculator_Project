// Created by Leni Halaapiapi on 10/23/18
// CS_480_Lab_3

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {

	// reads string from user
	string str, rpn;
	cout << "Please enter a mathematical expression.\n";
	getline(cin, str);
	
	// checks string for any values not specified
	size_t found = str.find_first_not_of("0123456789.+-/*^()");

	// if a space or invalid character is found, terminates program
	if (found != string::npos)
	{
		cout << "Invalid character or space. Goodbye.\n";
		return 0;
	}

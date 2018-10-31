// Created by Leni Halaapiapi on 10/23/18
// CS_480_Lab_3

#include <iostream>
#include <string>
#include <stack>
using namespace std;

// returns precedence of operators 
int precedence(char c)
{
	if (c == '^')
	{
		return 3;
	}
	else if (c == '*' || c == '/')
	{
		return 2;
	}
	else if (c == '+' || c == '-')
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// main function to convert infix expression to postfix
string infixToPostfix(string s)
{
	stack<char> workingStack;
	workingStack.push('N');
	int l = s.length();
	string reversePolish;

	for (int i = 0; i < l; i++)
	{

		// if the scanned character is an operand, add it to output string
		if ((s[i] >= '0' && s[i] <= '9') || (s[i] == '.'))
		{
			reversePolish += s[i];
		}

		// if the scanned character is a '(', push it to the stack
		else if (s[i] == '(')
		{
			workingStack.push('(');
		}

		// if the scanned character is a ')', pop to output string from the stack until '(' is encountered. 
		else if (s[i] == ')')
		{
			while (workingStack.top() != 'N' && workingStack.top() != '(')
			{
				char c = workingStack.top();
				workingStack.pop();
				reversePolish += c;
			}
			if (workingStack.top() == '(')
			{
				char c = workingStack.top();
				workingStack.pop();
			}
		}

		// if an operator is scanned 
		else
		{
			reversePolish += ",";
			while (workingStack.top() != 'N' && precedence(s[i]) <= precedence(workingStack.top()))
			{
				char c = workingStack.top();
				workingStack.pop();
				reversePolish += c;
			}
			workingStack.push(s[i]);
		}
	}

	// pop all remaining elements from stack 
	while (workingStack.top() != 'N')
	{
		char c = workingStack.top();
		workingStack.pop();
		reversePolish += c;
	}

	size_t find = reversePolish.find_last_of("0123456789");
	reversePolish.insert(find + 1, ",");
	return reversePolish;
}

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
	
	// tests for user trying to multiply without * operator
	for (int i = 0; i < 10; i++)
	{
		string test, test1, test2;
		test = to_string(i);
		test1 = test + '(';
		test2 = ')' + test;

		if (str.find(")(") != string::npos || str.find(test1) != string::npos || str.find(test2) != string::npos)
		{
			cout << "If you wish to multiply, use the * operator. Goodbye.\n";
			return 0;
		}
	}

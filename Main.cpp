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

float postfixToSolution(string rpn)
{

	// values for stack operations
	stack<double> finalStack;
	double a, b, c;
	string temp, perm;

	while (!rpn.empty())
	{
		// finds first occurrence of operators for easy tokenizing
		size_t found = rpn.find_first_of(",^*/+-()");

		// this tokenizes all the operands and pushes them on the stack
		if (rpn[found] == ',')
		{
			temp = rpn.substr(0, found);
			perm = rpn.substr(found + 1, rpn.length() - found);
			if (temp.empty())
			{
				cout << "Invalid character or space. Goodbye.\n";
				_Exit(EXIT_FAILURE);
			}
			a = stod(temp);
			finalStack.push(a);
			a = 0;
			rpn = perm;
		}

		// this does the exponentiation
		else if (rpn[found] == '^')
		{
			perm = rpn.substr(found + 1, rpn.length() - found);
			b = finalStack.top();
			finalStack.pop();
			a = finalStack.top();
			finalStack.pop();
			c = pow(a, b);
			finalStack.push(c);
			rpn = perm;
			a, b, c = 0;
		}

		// multiplication
		else if (rpn[found] == '*')
		{
			perm = rpn.substr(found + 1, rpn.length() - found);
			b = finalStack.top();
			finalStack.pop();
			a = finalStack.top();
			finalStack.pop();
			c = (a * b);
			finalStack.push(c);
			rpn = perm;
			a, b, c = 0;
		}

		// division
		else if (rpn[found] == '/')
		{
			perm = rpn.substr(found + 1, rpn.length() - found);
			b = finalStack.top();
			finalStack.pop();
			a = finalStack.top();
			finalStack.pop();
			if (b == 0) {
				cout << "Invalid input. Division by 0 is forbidden. Goodbye.\n";
				_Exit(EXIT_FAILURE);
			}
			c = (a / b);
			finalStack.push(c);
			rpn = perm;
			a, b, c = 0;
		}

		// addition
		else if (rpn[found] == '+')
		{
			perm = rpn.substr(found + 1, rpn.length() - found);
			b = finalStack.top();
			finalStack.pop();
			a = finalStack.top();
			finalStack.pop();
			c = (a + b);
			finalStack.push(c);
			rpn = perm;
			a, b, c = 0;
		}

		// subtraction
		else if (rpn[found] == '-')
		{
			perm = rpn.substr(found + 1, rpn.length() - found);
			b = finalStack.top();
			finalStack.pop();
			a = finalStack.top();
			finalStack.pop();
			c = (a - b);
			finalStack.push(c);
			rpn = perm;
			a, b, c = 0;
		}
		
		// exits if there are other characters which should not be in the expression
		else
		{
			_Exit(EXIT_FAILURE);
		}
	}
	return finalStack.top();
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

#include <iostream>
#include <conio.h>
#include <string.h>
using namespace std;
char a[10];
int top = -1, i;

void error()
{
	cout << "Syntax Error";
}

void push(char k[]) // Pushes The Set Of Characters on to the Stack
{
	for (i = 0; k[i] != '\0'; i++)
	{
		if (top < 9)
			a[++top] = k[i];
	}
}

char TOS() // Returns TOP of the Stack
{
	return a[top];
}

void pop() // Pops 1 element from the Stack
{
	if (top >= 0)
		a[top--] = '\0';
}

void display() // Displays Elements Of Stack
{
	for (i = 0; i <= top; i++)
		cout << a[i];
}

void display1(char p[], int m) // Displays The Present Input String
{
	int l;
	cout << "\t";
	for (l = m; p[l] != '\0'; l++)
		cout << p[l];
}

char *stack()
{
	return a;
}

int main()
{
	char ip[20], r[20], st, an;
	int ir, ic, j = 0, k;
	char t[5][6][10] = {"$", "$", "TH", "$", "TH", "$",
						"+TH", "$", "e", "e", "$", "e",
						"$", "$", "FU", "$", "FU", "$",
						"e", "*FU", "e", "e", "$", "e",
						"$", "$", "(E)", "$", "i", "$"};
	cout << "Grammar : \n";
	cout << "E -> TH\n";
	cout << "H -> +TH | e\n";
	cout << "T -> FU\n";
	cout << "U -> *FT | e\n";
	cout << "F -> i | (E)\n";
	cout << "\nInput string with $";
	cout << "\nEnter String: ";
	cin >> ip;
	cout << "\nStack\tInput\tOutput\n";
	cout << "=====\t=====\t=====\n";
	push("$E");
	display();
	cout << "\t" << ip << "\n";
	for (j = 0; ip[j] != '\0';)
	{
		if (TOS() == an)
		{
			pop();
			display();
			display1(ip, j + 1);
			cout << "\tPOP\n";
			j++;
		}
		an = ip[j];
		st = TOS();
		if (st == 'E')
			ir = 0;
		else if (st == 'H')
			ir = 1;
		else if (st == 'T')
			ir = 2;
		else if (st == 'U')
			ir = 3;
		else if (st == 'F')
			ir = 4;
		else
		{
			error();
			break;
		}
		if (an == '+')
			ic = 0;
		else if (an == '*')
			ic = 1;
		else if (an == '(')
			ic = 2;
		else if (an == ')')
			ic = 3;
		else if ((an >= 'a' && an <= 'z') || (an >= 'A' && an <= 'Z'))
		{
			ic = 4;
			an = 'i';
		}
		else if (an == '$')
			ic = 5;
		strcpy(r, strrev(t[ir][ic]));
		strrev(t[ir][ic]);
		pop();
		push(r);
		if (TOS() == 'e')
		{
			pop();
			display();
			display1(ip, j);
			cout << "\t" << st << "->e\n";
		}
		else
		{
			display();
			display1(ip, j);
			cout << "\t" << st << "->" << t[ir][ic] << "\n";
		}

		if (TOS() == '$' && an == '$')
			break;

		if (TOS() == '$')
		{
			error();
			break;
		}
	}
	k = strcmp(stack(), "$"); // if(k==0 && i==strlen(ip))
	if (k == 0 && ip[j] == '$')
		cout << "\nstring is accepted";
	else
		cout << "\nGiven String is not accepted";
	return 0;
}

// Top Down
// i*i+i

#include <iostream>
#include <conio.h>
#include <string.h>
#include "stdlib.h"
#include "ctype.h"

using namespace std;
char a[10];
int top = -1, i;
char ip_sym[15], ip_ptr = 0, op[50], tmp[50];
void e_prime();
void e();
void t_prime();
void t();
void f();
void advance();
int n = 0;
void e()
{
    strcpy(op, "TE'");
    printf("E=%-25s", op);
    printf("E->TE'\n");
    t();
    e_prime();
}

void e_prime()
{
    int i, n = 0, l;
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[n++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (n = 0; n < l && op[n] != 'E'; n++)
        ;
    if (ip_sym[ip_ptr] == '+') {
        i = n + 2; 
        do {
            op[i + 2] = op[i];
            i++;
        } while (i <= l);
        op[n++] = '+';
        op[n++] = 'T';
        op[n++] = 'E';
        op[n++] = 39;
        printf("E=%-25s", op);
        printf("E'->+TE'\n");
        advance();
        t();
        e_prime();
    }
    else {
        op[n] = 'e';
        for (i = n + 1; i <= strlen(op); i++)
            op[i] = op[i + 1];
        printf("E=%-25s", op);
        printf("E'->e");
    }
}
void t()
{
    int i, n = 0, l;
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[n++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (n = 0; n < l && op[n] != 'T'; n++)
        ;

    i = n + 1;
    do {
        op[i + 2] = op[i];
        i++;
    } while (i < l);
    op[n++] = 'F';
    op[n++] = 'T';
    op[n++] = 39;
    printf("E=%-25s", op);
    printf("T->FT'\n");
    f();
    t_prime();
}

void t_prime()
{
    int i, n = 0, l;
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[n++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (n = 0; n < l && op[n] != 'T'; n++)
        ;
    if (ip_sym[ip_ptr] == '*') {
        i = n + 2;
        do {
            op[i + 2] = op[i];
            i++;
        } while (i < l);
        op[n++] = '*';
        op[n++] = 'F';
        op[n++] = 'T';
        op[n++] = 39;
        printf("E=%-25s", op);
        printf("T'->*FT'\n");
        advance();
        f();
        t_prime();
    }
    else {
        op[n] = 'e';
        for (i = n + 1; i <= strlen(op); i++)
            op[i] = op[i + 1];
        printf("E=%-25s", op);
        printf("T'->e\n");
    }
}

void f()
{
    int i, n = 0, l;
    for (i = 0; i <= strlen(op); i++)
        if (op[i] != 'e')
            tmp[n++] = op[i];
    strcpy(op, tmp);
    l = strlen(op);
    for (n = 0; n < l && op[n] != 'F'; n++)
        ;
    if ((ip_sym[ip_ptr] == 'i') || (ip_sym[ip_ptr] == 'I')) {
        op[n] = 'i';
        printf("E=%-25s", op);
        printf("F->i\n");
        advance();
    }
    else {
        if (ip_sym[ip_ptr] == '(') {
            advance();
            e();
            if (ip_sym[ip_ptr] == ')') {
                advance();
                i = n + 2;
                do {
                    op[i + 2] = op[i];
                    i++;
                } while (i <= l);
                op[n++] = '(';
                op[n++] = 'E';
                op[n++] = ')';
                printf("E=%-25s", op);
                printf("F->(E)\n");
            }
        }
        else {
            printf("\n\t syntax error");
            getch();
            exit(1);
        }
    }
}

void advance()
{
    ip_ptr++;
}

void error()
{
	cout << "Syntax Error";
}

void push(char k[]) // Pushes The Set Of Characters on to the Stack
{
	for (i = 0; k[i] != '\0'; i++) {
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

int predictive() 
{
    char ip[20], r[20], st, an;
	int ir, ic, j = 0, k;
	char t[5][6][10] = {"$", "$", "TH", "$", "TH", "$",
						"+TH", "$", "e", "e", "$", "e",
						"$", "$", "FU", "$", "FU", "$",
						"e", "*FU", "e", "e", "$", "e",
						"$", "$", "(E)", "$", "i", "$"};

	cout << "\nEnter String: ";
	cin >> ip;
    char tmp[2] = "$";
    strcat(ip, tmp);
	cout << "\nStack\tInput\tOutput\n";
	cout << "-----------------------\n";
	push("$E");
	display();
	cout << "\t" << ip << "\n";
	for (j = 0; ip[j] != '\0';) {
		if (TOS() == an) {
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
		else {
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
		else if ((an >= 'a' && an <= 'z') || (an >= 'A' && an <= 'Z')) {
			ic = 4;
			an = 'i';
		}
		else if (an == '$')
			ic = 5;
		strcpy(r, strrev(t[ir][ic]));
		strrev(t[ir][ic]);
		pop();
		push(r);
		if (TOS() == 'e') {
			pop();
			display();
			display1(ip, j);
			cout << "\t" << st << "->e\n";
		}
		else {
			display();
			display1(ip, j);
			cout << "\t" << st << "->" << t[ir][ic] << "\n";
		}
		if (TOS() == '$' && an == '$')
			break;
		if (TOS() == '$') {
			error();
			break;
		}
	}
	k = strcmp(stack(), "$");
	if (k == 0 && ip[j] == '$')
		cout << "\nString is accepted";
	else
		cout << "\nString is not accepted";
	return 0;
}

int rdp()
{
    int i;
    printf("\nEnter String: ");
    cin >> ip_sym;
    printf("Expressions");
    printf("\tSequence of production rules\n");
    e();
    for (i = 0; i < strlen(ip_sym); i++) {
        if (ip_sym[i] != '+' && ip_sym[i] != '*' && ip_sym[i] != '(' &&
            ip_sym[i] != ')' && ip_sym[i] != 'i' && ip_sym[i] != 'I') {
            printf("\nSyntax error");
            break;
        }
        for (i = 0; i <= strlen(op); i++)
            if (op[i] != 'e')
                tmp[n++] = op[i];
        strcpy(op, tmp);
        printf("\nE=%-25s", op);
    }
    if( !strcmp( op, ip_sym )) {
        printf("\nString is accepted");
    }
    else {
        printf("\nString is not accepted");
    }
    return 0;
}

int main()
{
    cout << "Grammar : \n";
	cout << "E -> TH\n";
	cout << "H -> +TH | e\n";
	cout << "T -> FU\n";
	cout << "U -> *FT | e\n";
	cout << "F -> i | (E)\n";
    int ch;
    char c;
    do {
        cout << "\n1. Predictive\n2. Recursive Descent Parsing\n\n";
        cout << "Enter your choice : ";
        cin >> ch;
        switch (ch) {
            case 1:
                predictive();
                break;
            case 2:
                rdp();
                break;
            default:
                cout << "Invalid Choice." << endl;
        }
        cout << "\n\nDo you want to try again?(y/n) : ";
        cin >> c;
    }
    while (c == 'y' || c == 'Y');
}
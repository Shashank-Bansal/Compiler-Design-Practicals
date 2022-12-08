// Bottom Up
// a+a*a

# include <iostream>
# include <string>
# include <deque>
# include <fstream>
# include <string.h>
using namespace std;
int n, n1, n2;
int z = 0, i = 0, j = 0, c = 0;
int  *ptr = NULL;
char a[16], ac[20], tc[20], fc[20], stk[20], act[10];

int getPosition(string arr[], string q, int size) {
    for (int i = 0; i < size; i++) {
        if (q == arr[i])
            return i;
    }
    return -1;
}

void operatorPrecedence() {
    string prods[10], leads[10], trails[10], nonterms[10], terms[10];
    char op_table[20][20] = {};
    n = 6;
    prods[0] = "E->E+E";
    prods[1] = "E->T";
    prods[2] = "T->T*F";
    prods[3] = "T->F";
    prods[4] = "F->(E)";
    prods[5] = "F->a";
    n2 = 5;
    terms[0] = "+";
    terms[1] = "*";
    terms[2] = "(";
    terms[3] = ")";
    terms[4] = "a";
    terms[n2] = "$";
    n2++;
    n1 = 3;
    nonterms[0] = "E";
    leads[0] = "*+(a";
    trails[0] = "*+)a";
    nonterms[1] = "T";
    leads[1] = "*(a";
    trails[1] = "*)a";
    nonterms[2] = "F";
    leads[2] = "(a";
    trails[2] = ")a";

    string rule = "";    
    ifstream infile;

    infile.open("operatorRules.txt");
    
    while (getline(infile, rule)) {
        if (rule[0] == '1') {
            int row = getPosition(terms, rule.substr(2, 1), n2);
            int column = getPosition(terms, rule.substr(4, 1), n2);
            op_table[row][column] = '=';
        }
        if (rule[0] == '2') {
            int ntp = getPosition(nonterms, rule.substr(4, 1), n1);
            int row = getPosition(terms, rule.substr(2, 1), n2);
            for (int j = 0; j < leads[ntp].size(); j++) {
                int col = getPosition(terms, leads[ntp].substr(j, 1), n2);
                op_table[row][col] = '<';
            }
        }
        if (rule[0] == '3') {
            int col = getPosition(terms, rule.substr(4, 1), n2);
            int ntp = getPosition(nonterms, rule.substr(2, 1), n1);
            for (int j = 0; j < trails[ntp].size(); j++) {
                int row = getPosition(terms, trails[ntp].substr(j, 1), n2);
                op_table[row][col] = '>';
            }
        }
    }
    for (int j = 0; j < leads[0].size(); j++) {
        int col = getPosition(terms, leads[0].substr(j, 1), n2);
        op_table[n2 - 1][col] = '<';
    }
    for (int j = 0; j < trails[0].size(); j++) {
        int row = getPosition(terms, trails[0].substr(j, 1), n2);
        op_table[row][n2 - 1] = '>';
    }
    cout << endl << "Operator Table" << endl << endl;
    for (int j = 0; j < n2; j++)
    cout << "\t" << terms[j];
    cout << endl;
    for (int i = 0; i < n2; i++)
    {
        cout << terms[i] << "\t";
        for (int j = 0; j < n2; j++)
        {
            cout << op_table[i][j] << "\t";
        }
        cout << endl;
    }
    char c;
        string ip;
        deque<string> op_stack;
        op_stack.push_back("$");
        cout << "\nEnter the string to be parsed : ";
        cin >> ip;
        ip.push_back('$');
        cout << "\nStack Implementation:\n";
        cout << "\nStack\t\tRemaining Input\t\tRelation\tAction ";
        cout << "\n-----------------------------------------------------\n";
        // cout << "Stack\t\ti/p Buffer\tRelation\tAction" << endl;
        while (true) {
        for (int i = 0; i < op_stack.size(); i++)
            cout << op_stack[i];
        cout << "\t\t";
        cout << ip << "\t\t";
        int row = getPosition(terms, op_stack.back(), n2);
        int column = getPosition(terms, ip.substr(0, 1), n2);
        if (op_table[row][column] == '<') {
            op_stack.push_back("<");
            op_stack.push_back(ip.substr(0, 1));
            ip = ip.substr(1);
            cout << "\t<\t\tPush";
        }
        else if (op_table[row][column] == '=') {
            op_stack.push_back("=");
            op_stack.push_back(ip.substr(0, 1));
            ip = ip.substr(1);
            cout << "\t=\t\tPush";
        }
        else if (op_table[row][column] == '>') {
            string last;
            do {
                op_stack.pop_back();
                last = op_stack.back();
                op_stack.pop_back();
            } while (last != "<");
            cout << "\t>\t\tPop";
        }
        else {
            if (ip[0] == '$' && op_stack.back() == "$") {
                cout << "\t\t\tAccept\nString Parsed." << endl;
                break;
            }
            else {
                cout << endl
                        << "String cannot be Parsed." << endl;
                break;
            }
        }
        cout << endl;
    }
}

void check()
{
    int m;
    strcpy(ac, "REDUCE TO E -> ");
    strcpy(tc, "REDUCE TO T -> ");
    strcpy(fc, "REDUCE TO F -> ");

    for (z = 0; z < c; z++) {
        if (stk[z] == 'a') {
            printf("%sa", fc);
            stk[z] = 'F';
            printf("\n$%s\t\t%s$\t\t", stk, a);
        }
    }

    for (z = 0; z < c - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' &&
            stk[z + 2] == 'T') {
            printf("%sE+T", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            for (m = z + 3; m < c; m++) {
                stk[z+1] = stk[m];
                z++;
            }
            printf("\n$%s\t\t%s$\t\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++) {
        if (stk[z] == 'T' && stk[z + 1] == '*' &&
            stk[z + 2] == 'F') {
            printf("%sT*F", tc);
            stk[z] = 'T';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            for (m = z + 3; m < c; m++) {
                stk[z+1] = stk[m];
                z++;
            }
            printf("\n$%s\t\t%s$\t\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && 
            stk[z + 2] == ')') {
            printf("%s(E)", fc);
            stk[z] = 'F';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            for (m = z + 3; m < c; m++) {
                stk[z+1] = stk[m];
                z++;
            }
            printf("\n$%s\t\t%s$\t\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c; z++) {
        if (stk[z] == 'T') {
            printf("%sT", ac);
            stk[z] = 'E';
            printf("\n$%s\t\t%s$\t\t", stk, a);
        }
    }
    
    for (z = 0; z < c; z++) {
        if (stk[z] == 'F') {
            printf("%sF", tc);
            stk[z] = 'T';
            printf("\n$%s\t\t%s$\t\t", stk, a);
        }
    }

    for (z = 0; z < c - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && 
            stk[z + 2] == 'E') {
            printf("%sE*E", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            for (m = z + 3; m < c; m++) {
                stk[z+1] = stk[m];
                z++;
            }
            printf("\n$%s\t\t%s$\t\t", stk, a);
            i = i - 2;
        }
    }
}

void shiftReduce()
{
    cout << endl << "Enter the string to be parsed : ";
    cin >> a;
    c = strlen(a);
    strcpy(act, "SHIFT");
    cout << "\nStack Implementation:\n";
    cout << "\nStack\t\tRemaining Input\t\tAction ";
    cout << "\n-----------------------------------------------------\n";
    printf("\n$\t\t%s$\t\t", a);
    for (i = 0; j < c; i++, j++) {
        printf("%s", act);
        stk[i] = a[j];
        stk[i + 1] = '\0';
        a[j] = ' ';
        printf("\n$%s\t\t%s$\t\t", stk, a);
        check();
    }
    check();
    if (stk[0] == 'E' && stk[1] == '\0')
        printf("Accept\n");
    else
        printf("Reject\n");
}

int main()
{
    printf("\nGRAMMAR:\nE->E+T | T \nT->T*F | F \nF->(E) | a\n");
    int ch;
    char c;
    do {
        cout << "\n1. Operator Precedence\n2. Shift Reduce\n\n";
        cout << "Enter your choice : ";
        cin >> ch;
        switch (ch) {
            case 1:
                operatorPrecedence();
                break;
            case 2:
                shiftReduce();
                break;
            default:
                cout << "Invalid Choice." << endl;
        }
        cout << "\n\nDo you want to try again?(y/n) : ";
        cin >> c;
    }
    while (c == 'y' || c == 'Y');
}
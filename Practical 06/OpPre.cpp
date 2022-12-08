#include <iostream>
#include <string>
#include <deque>
#include <fstream>
using namespace std;
int n, n1, n2;
int getPosition(string arr[], string q, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (q == arr[i])
            return i;
    }
    return -1;
}
int main()
{
    string prods[10], leads[10], trails[10], nonterms[10], terms[10];
    char op_table[20][20] = {};
    // cout << "Enter the number of productions : ";
    n = 6;
    // cout << "Enter the productions" << endl;
    prods[0] = "E->E+E";
    prods[1] = "E->T";
    prods[2] = "T->T+F";
    prods[3] = "T->F";
    prods[4] = "F->(E)";
    prods[5] = "F->a";
    // cout << "Enter the number of Terminals : ";
    n2 = 5;
    // cout << "Enter the Terminals" << endl;
    terms[0] = "+";
    terms[1] = "*";
    terms[2] = "(";
    terms[3] = ")";
    terms[4] = "a";
    terms[n2] = "$";
    n2++;
    // cout << "Enter the number of Non-Terminals : ";
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

    // cout << "Enter the Rules (exit to stop)" << endl;
    string rule = "";    
    ifstream infile;

    infile.open("thefile.txt");

    
    while (getline(infile, rule))
    {
        if (rule[0] == '1')
        {
            int row = getPosition(terms, rule.substr(2, 1), n2);
            int column = getPosition(terms, rule.substr(4, 1), n2);
            op_table[row][column] = '=';
        }
        if (rule[0] == '2')
        {
            int ntp = getPosition(nonterms, rule.substr(4, 1), n1);
            int row = getPosition(terms, rule.substr(2, 1), n2);
            for (int j = 0; j < leads[ntp].size(); j++)
            {
                int col = getPosition(terms, leads[ntp].substr(j, 1), n2);
                op_table[row][col] = '<';
            }
        }
        if (rule[0] == '3')
        {
            int col = getPosition(terms, rule.substr(4, 1), n2);
            int ntp = getPosition(nonterms, rule.substr(2, 1), n1);
            for (int j = 0; j < trails[ntp].size(); j++)
            {
                int row = getPosition(terms, trails[ntp].substr(j, 1), n2);
                op_table[row][col] = '>';
            }
        }
    }
    for (int j = 0; j < leads[0].size(); j++)
    {
        int col = getPosition(terms, leads[0].substr(j, 1), n2);
        op_table[n2 - 1][col] = '<';
    }
    for (int j = 0; j < trails[0].size(); j++)
    {
        int row = getPosition(terms, trails[0].substr(j, 1), n2);
        op_table[row][n2 - 1] = '>';
    }
    cout << endl;
    cout << "Grammar" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << prods[i] << endl;
    }
    // Display Table
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
    // Parsing String
    char c;
    do
    {
        string ip;
        deque<string> op_stack;
        op_stack.push_back("$");
        cout << "Enter the string to be parsed : ";
        getline(cin, ip);
        ip.push_back('$');
        cout << "\nStack Implementation:\n";
        cout << "\nStack\t\tRemaining Input\t\tRelation\tAction ";
        cout << "\n-----------------------------------------------------\n";
        // cout << "Stack\t\ti/p Buffer\tRelation\tAction" << endl;
        while (true)
        {
            for (int i = 0; i < op_stack.size(); i++)
                cout << op_stack[i];
            cout << "\t\t";
            cout << ip << "\t\t";
            int row = getPosition(terms, op_stack.back(), n2);
            int column = getPosition(terms, ip.substr(0, 1), n2);
            if (op_table[row][column] == '<')
            {
                op_stack.push_back("<");
                op_stack.push_back(ip.substr(0, 1));
                ip = ip.substr(1);
                cout << "\t<\t\tPush";
            }
            else if (op_table[row][column] == '=')
            {
                op_stack.push_back("=");
                op_stack.push_back(ip.substr(0, 1));
                ip = ip.substr(1);
                cout << "\t=\t\tPush";
            }
            else if (op_table[row][column] == '>')
            {
                string last;
                do
                {
                    op_stack.pop_back();
                    last = op_stack.back();
                    op_stack.pop_back();
                } while (last != "<");
                cout << "\t>\t\tPop";
            }
            else
            {
                if (ip[0] == '$' && op_stack.back() == "$")
                {
                    cout << "\t\t\tAccept\nString Parsed." << endl;
                    break;
                }
                else
                {
                    cout << endl
                         << "String cannot be Parsed." << endl;
                    break;
                }
            }
            cout << endl;
        }
        cout << "Continue?(Y/N) ";
        cin >> c;
        cin.ignore();
    } while (c == 'y' || c == 'Y');
    return 0;
}
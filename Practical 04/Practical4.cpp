#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

bool isOperator(string x) {
    return (x == "+" || x == "-" || x == "*" || x == "/" || x == "%" || x == "++" || x == "--" || x == "==" || x == "!=" || x == ">" || x == "<" || x == ">=" || x == "<=" || x == "&&" || x == "||" || x == "!" || x == "&" || x == "|" || x == "^" || x == "<<" || x == ">>" || x == "=" || x == "+" || x == "+=" || x == "-=" || x == "*=" || x == "/=" || x == "%=" || x == "<<=" || x == ">>=" || x == "&=" || x == "|=" || x == "^=");
}

bool isKeyword(string x) {
    return (x == "asm" || x == "auto" || x == "break" || x == "case" || x == "catch" || x == "char" || x == "class" || x == "const" || x == "continue" || x == "default" || x == "delete" || x == "do" || x == "double" || x == "else" || x == "enum" || x == "explicit" || x == "export" || x == "extern" || x == "false" || x == "float" || x == "for" || x == "friend" || x == "goto" || x == "if" || x == "inline" || x == "int" || x == "long" || x == "mutable" || x == "namespace" || x == "new" || x == "operator" || x == "private" || x == "protected" || x == "protected" || x == "protected" || x == "protected" || x == "protected"|| x == "protected" || x == "public" || x == "register" || x == "return" || x == "short" || x == "signed" || x == "sizeof" || x == "static" || x == "struct"  || x == "switch" || x == "template" || x == "this" || x == "throw" || x == "true" || x == "try" || x == "typedef" || x == "typeid" || x == "typename" || x == "union"  || x == "unsigned"  || x == "using"  || x == "virtual"  || x == "void"  || x == "volatile"  || x == "wchar_t"  || x == "while");
}

int main() {
    char str[5000];

    Start:
    cout << "\n1. Enter the code.\n2. Use input from file.\n";
    int select;
    cin >> select;
    cout << endl;
    
    switch (select) {
        case 1: {
            cin.ignore();
            cin.getline(str, sizeof(str));
            cout << endl;
            break;
        }   
        case 2: {
            ifstream infile("test.cpp");
            char ch;
            unsigned int pos = 0;
            while (infile) {
                infile.get(ch);
                cout<<ch;
                str[pos] = ch;
                pos++;
            }
            cout<<endl;
            break;
        }
       default: {
           cout << "Invalid Input, retry";
           goto Start;
       }
    }
    
    cout<<"Lexemes\t\t\t\tTokens\n";
    cout<<"----------------------------------------------\n";
    
    vector<string> tokenlist;
    vector<string> tokentype;
    
    char delimit[] = "#;)(}{\n\t\f\v\r ";
    char* token = strtok(str, delimit);
    
    while (token != NULL) {
        tokenlist.push_back(token);
        token = strtok(NULL, delimit);
    }
    
    for (int i=0; i < tokenlist.size(); i++) {
        char t = tokenlist[i].at(0);
        int num = (int) t;
        int len = (int) tokenlist[i].length();
        
        if ((num > 47) && (num < 58))
            tokentype.push_back("Constant");
        else if (ispunct(t) && len>1)
            tokentype.push_back("String");
        else if (isOperator(tokenlist[i]))
            tokentype.push_back("Operator");
        else if (isKeyword(tokenlist[i]))
            tokentype.push_back("Keyword");
        else
            tokentype.push_back("Identifier");
    }
    
    for (int i=0; i < tokenlist.size(); i++)
        cout<<tokenlist[i]<<"\t\t\t--\t"<<tokentype[i]<<"\n";

    return 0;
}
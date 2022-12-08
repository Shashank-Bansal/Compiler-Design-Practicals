#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <iomanip>

using namespace std;

int num = 0, len = 0;
char inp[400];

int main() {
    start:

    num = 0;
    len = 0;

    char check[30];
    string input, line, str;
    int choice, i, j = 0, x = 0;
    int single = 0, multi = 0;
    ifstream fin;

    cout << "\nChoose the way you want to enter the code:\n";
    cout << "1. Input at the console\n";
    cout << "2. Input from a file\n";
    cout << "3. Exit\n\n";
    cout << "Enter your option: ";

    cin >> choice;
    switch (choice) {
        case 1: {
            cout << "Enter input:\n";

            do {
                getline(cin, line);
                input += line + " ";
                input += '\n';
            } while (line != "end");

            len = input.length();

            for (int p = 0; p < len; p++)
                inp[p] = input[p];

            break;
        }
        case 2: {
            fin.open("code.txt");
            
            if (!fin.is_open()) {
                cout << "\nError while opening the file\n";
                exit(0);
            }
            do {
                getline(fin, str);
                input += str + " ";
                input += '\n';
            } while (fin);

            len = input.length();

            for (int p = 0; p < len; p++)
                inp[p] = input[p];

            break;
        }
        case 3: {
            cout << "\n";
            exit(0);
            break;
        }
        default:
            cout << "Enter valid option";
            goto start;
    }

    cout << "\n S.No. \t|\tType of Comment\t\t|\t\tComment\n";
    cout << "________|_______________________________|_________________________\n";
    cout << "        |                               | ";

    while (x != len) {
        if (inp[x] == '/') {
            x++;

            if (inp[x] == '/') {
                x++;

                i = 0;
                while (inp[x] != '\n') {
                    check[i] = inp[x];
                    x++;
                    i++;
                }

                cout << "\n " << ++num << "\t|\t" << "Single line Comment" << "\t|\t";
                single++;

                for (int q = 0; q < i; q++)
                    cout << check[q];
            }

            if (inp[x] == '*') {
                cout << "\n " << ++num << "\t|\t" << "Multi line Comment" << "\t|\t";

                multi++;
                x++;
                i = 0;

                while (inp[x] != '*') {
                    if (inp[x] == '\n') {
                        x++;
                        continue;
                    }

                    cout << inp[x];
                    i++;
                    x++;
                }
            }
        }

        x++;
    }

    cout << "\n\nNumber of Single line Comments: " << single;
    cout << "\nNumber of Multi line Comments: " << multi << "\n\n\n";

    fin.close();
    goto start;

    return 0;
}
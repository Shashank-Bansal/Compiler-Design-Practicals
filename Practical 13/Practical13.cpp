#include <iostream>
#include <chrono>
#include "slr.h"
#include "clr.h"
#include "lalr.h"

using namespace std;

void comparison()
{
    std::chrono::steady_clock::time_point clrBegin = std::chrono::steady_clock::now();
    string pa = clrParser();
    std::chrono::steady_clock::time_point clrEnd = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point slrBegin = std::chrono::steady_clock::now();
    string ra = slrParser();
    std::chrono::steady_clock::time_point slrEnd = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point lalrBegin = std::chrono::steady_clock::now();
    string oa = lalrParser();
    std::chrono::steady_clock::time_point lalrEnd = std::chrono::steady_clock::now();

    ifstream file1("clr.h", ios::binary | ios::ate);
    int clrSize = file1.tellg();

    ifstream file2("slr.h", ios::binary | ios::ate);
    int slrSize = file2.tellg();

    ifstream file3("lalr.h", ios::binary | ios::ate);
    int lalrSize = file3.tellg();


    cout << endl
         << endl
         <<
         "_________________________________________________________________________________________________________"
         << endl;
    cout << "|\tParsers \t|\t"
         << "Time Taken\t\t|\t"
         << "Space Used\t|\t"
         << "Accepted\t|" << endl;
    cout << "|_______________________|_______________________________|_______________________|_______________________|" << endl;

    cout << "|\tCLR\t\t|\t" <<  std::chrono::duration_cast<std::chrono::microseconds>(clrEnd - clrBegin).count() / 1000.00 << " milliseconds\t|\t" << clrSize << " bytes\t|\t" << pa << "\t\t|" << endl;

    cout << "|-----------------------|-------------------------------|-----------------------|-----------------------|" << endl;

    cout << "|\tSLR\t\t|\t" <<  std::chrono::duration_cast<std::chrono::microseconds>(slrEnd - slrBegin).count() / 1000.00 << " milliseconds\t|\t" << slrSize << " bytes\t|\t" << ra  << "\t\t|" << endl;

    cout << "|-----------------------|-------------------------------|-----------------------|-----------------------|" << endl;

    cout << "|\tLALR\t\t|\t" <<  std::chrono::duration_cast<std::chrono::microseconds>(lalrEnd - lalrBegin).count() / 1000.00 << " milliseconds\t|\t" << lalrSize << " bytes\t|\t" << oa << "\t\t|" << endl;

    cout << 
    "|_______________________|_______________________________|_______________________|_______________________|" << endl;

}

int main()
{
    int ch;
    char c;
    do
    {
        cout << "\n1. CLR"
             << "\n2. SLR"
             << "\n3. LALR"
             << "\n4. Comparison\n\n";
        cout << "Enter your choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            clrParser();
            break;
        case 2:
            slrParser();
            break;
        case 3:
            lalrParser();
            break;
        case 4:
            comparison();
            break;
        default:
            cout << "Invalid Choice." << endl;
        }
        cout << "\n\nDo you want to try again?(y/n) : ";
        cin >> c;
    } while (c == 'y' || c == 'Y');
}
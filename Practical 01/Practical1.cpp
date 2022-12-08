#include <iostream>
#include <cstring>
using namespace std;

char alphabet[2];   
int transition_table[15][2];

void string_recognize(int transition_table[15][2])
{
    start:
    int length;
    cout << "\nEnter the length of the string\n";
    cin >> length;

    char process[100];
    cout << "\nEnter the string\n";
    cin >> process;

    int size = strlen(process);
    while (size != length) {
        cout << "Enter string again as the length didn't match !\n";
        cin >> process;
        size = strlen(process);
    }
    
    cout << "\nString Processing\n\n";
    cout << "->";

    int present_state = 0;
    for (int i = 0; i < length; i++) {
        if (process[i] == alphabet[0]) {
            cout << "q" << present_state << "-" << process[i] << "->";
            present_state = transition_table[present_state][0];
        }
        else if (process[i] == alphabet[1]) {
            cout << "q" << present_state << "-" << process[i] << "->";
            present_state = transition_table[present_state][1];
        }
        else {
            cout << endl << process[i] << " doesn't match with alphabet, so try again.\n";
            goto start;
        }
    }

    if (present_state == 5) {
        cout << "*q" << present_state;
        cout << "\n\nSTRING IS ACCEPTED !! \n\n";
    } 
    else {
        cout << "q" << present_state;
        cout << "\n\nSTRING IS NOT ACCEPTED !! \n\n";
    }

    int choice, c;
    char cond, f;

    do {
        cout << "Do you want to process string again? (1/0)\n";
        cin >> choice;
        switch (choice)
        {
            case 1:
                string_recognize(transition_table);
                cin >> cond;
                break;
            case 0:
                exit(0);
            default:
                cout << "INVAID OPTION\n";
                cin >> cond;
                break;
        }
    } while (cond == 'y' || cond == 'Y');
}

int main() {
    cout << "\nEnter the input alphabets - \n";
    cin >> alphabet[0] >> alphabet[1];

    int transition_table[6][2] = {{1, 0}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 0}};
    cout << "\n-----------------------------------------";
    cout << "\n\t   Transition Table\t\t|\n";
    cout << "-----------------------------------------\n";
    cout << "States"
         << "\t|\tInput " << alphabet[0] << "\t|\tInput " << alphabet[1] << "\t|"
         << "\n";
    cout << "-----------------------------------------\n";
    cout << "->q0"
         << "\t|\t"; // initial state
    cout << "q" << transition_table[0][0] << "\t|\t";
    cout << "q" << transition_table[0][1] << "\t|\n";

    cout << "q1"
         << "\t|\t";
    cout << "q" << transition_table[1][0] << "\t|\t";
    cout << "q" << transition_table[1][1] << "\t|\n";

    cout << "q2"
         << "\t|\t";
    cout << "q" << transition_table[2][0] << "\t|\t";
    cout << "q" << transition_table[2][1] << "\t|\n";

    cout << "q3"
         << "\t|\t";
    cout << "q" << transition_table[3][0] << "\t|\t";
    cout << "q" << transition_table[3][1] << "\t|\n";
    cout << "q4"
         << "\t|\t";
    cout << "q" << transition_table[4][0] << "\t|\t";
    cout << "q" << transition_table[4][1] << "\t|\n";
    
    cout << "*q5"
         << "\t|\t";
    cout << "q" << transition_table[5][0] << "\t|\t";
    cout << "q" << transition_table[5][1] << "\t|\n";

    cout << "-----------------------------------------\n\n";
    string_recognize(transition_table);
}
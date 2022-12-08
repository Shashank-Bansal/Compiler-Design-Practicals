#include <bits/stdc++.h>
using namespace std;

// functions
void exactly();
void atleast();
void atmost();

// variables
int transition_table[15][2];
char alphabet[2];
char alpha;
int states_count = 0;
int final_state[15];

// function to recognize string
void string_processing(int transition_table[15][2], int final_state[15]) {
    int length, i;
    cout << "\nEnter the length of string you want to process\n";
    cin >> length;
    char process[100];

    cout << "\nEnter the string to check whether it is recognized by finite automata.\n";
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
        if (process[i] == 'a') {
            cout << "q" << present_state << "-" << process[i] << "->";
            present_state = transition_table[present_state][0];
        }
        else {
            cout << "q" << present_state << "-" << process[i] << "->";
            present_state = transition_table[present_state][1];
        }
    }

    bool check = false;

    for (int i = 0; i < states_count - 1; i++) {
        if (present_state == final_state[i]) {
            check = true;
            break;
        }
        else
            check = false;
    }

    if (check == true) {
        cout << "*q" << present_state;
        cout << "\n\nSTRING IS ACCEPTED\n\n";
    }
    else {
        cout << "q" << present_state;
        cout << "\n\nSTRING IS NOT ACCEPTED\n\n";
    }

    int option, c;
    char opt, f;

    do {
        cout << "Do you want to process string again? (1/0)\n";
        cin >> option;

        switch (option) {
            case 1:
                string_processing(transition_table, final_state);
                cin >> opt;
                break;
            case 0:
                exit(0);
            default:
                cout << "INVAID OPTION\n";
                cin >> opt;
                break;
        }
    } while (opt == 'y' || opt == 'Y');
}

// main
int main() {
    cout << "\nEnter alphabets - \n";
    cin >> alphabet[0] >> alphabet[1];
    cout << "\n";
    int option;
    cout << "\n\n-=-=-=-=-=-=-=- Program to check whether a string is recognized by finite automata  -=-=-=-=-=-=-=-=\n\n";
    cout << " Choose your option that you want to perform  \n";
    cout << " 1. Display a DFA having exactly specific symbol\n";
    cout << " 2. Display a DFA having atleast specific symbol\n";
    cout << " 3. Display a DFA having atmost specific symbol\n\n";
    cin >> option;

    switch (option) {
        case 1:
            exactly();
            break;
        case 2:
            atleast();
            break;
        case 3:
            atmost();
            break;
    }

    return 0;
}

// exactly case
void exactly() {
    char alpha;
    cout << "\nEnter alphabet -\n ";
    cin >> alpha;

    cout << "\nChoose your option that you want to run\n ";
    cout << "1. Exactly 1 " << alpha << "\n ";
    cout << "2. Exactly 2 " << alpha << "'s\n ";
    cout << "3. Exactly 3 " << alpha << "'s\n ";

    int size;
    cin >> size;
    states_count = size + 2;
    int transition_table[states_count][2];

    for (int i = 0; i < states_count - 1; i++) {
        if (alpha == 'a') {
            transition_table[i][0] = i + 1;
            transition_table[i][1] = i;
        }
        else {
            transition_table[i][0] = i;
            transition_table[i][1] = i + 1;
        }
    }

    transition_table[states_count - 1][0] = states_count - 1;
    transition_table[states_count - 1][1] = states_count - 1;

    cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-";
    cout << "\n\t   Transition Table\t\t|\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n";
    cout << "States"
         << "\t|   Input " << alphabet[0] << "\t|   Input " << alphabet[1] << "\t|"
         << "\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n";
    cout << "->q0"
         << "\t|\t"; // initial state
    cout << "q" << transition_table[0][0] << "\t|\t";
    cout << "q" << transition_table[0][1] << "\t|\n";

    for (int i = 1; i < states_count - 2; i++) {
        cout << "  q" << i << "\t|\t";
        cout << "q" << transition_table[i][0] << "\t|\t";
        cout << "q" << transition_table[i][1] << "\t|\n";
    }

    cout << " *q" << states_count - 2 << "\t|\t";
    final_state[0] = states_count - 2;
    cout << "q" << transition_table[states_count - 2][0] << "\t|\t";
    cout << "q" << transition_table[states_count - 2][1] << "\t|\n";
    cout << "  q" << states_count - 1 << "\t|\t";
    cout << "q" << transition_table[states_count - 1][0] << "\t|\t";
    cout << "q" << transition_table[states_count - 1][1] << "\t|\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n\n";

    string_processing(transition_table, final_state);
}

// atleast case
void atleast() {
    int size;
    char alpha;
    cout << "\nEnter alphabet -\n ";
    cin >> alpha;

    cout << "\nChoose your option that you want to run-\n ";
    cout << "1. Atleast 1 " << alpha << "\n ";
    cout << "2. Atleast 2 " << alpha << "'s\n ";
    cout << "3. Atleast 3 " << alpha << "'s\n ";

    cin >> size;
    states_count = size + 1;
    int transition_table[states_count][2];

    for (int i = 0; i < states_count - 1; i++) {
        if (alpha == 'a') {
            transition_table[i][0] = i + 1;
            transition_table[i][1] = i;
        }
        else {
            transition_table[i][0] = i;
            transition_table[i][1] = i + 1;
        }
    }
    transition_table[states_count - 1][0] = states_count - 1;
    transition_table[states_count - 1][1] = states_count - 1;

    cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-";
    cout << "\n\t   Transition Table\t\t|\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n";
    cout << "States"
         << "\t|   Input " << alphabet[0] << "\t|   Input " << alphabet[1] << "\t|"
         << "\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n";
    cout << "->q0"
         << "\t|\t"; // initial state
    cout << "q" << transition_table[0][0] << "\t|\t";
    cout << "q" << transition_table[0][1] << "\t|\n";

    for (int i = 1; i < states_count - 1; i++) {
        cout << "  q" << i << "\t|\t";
        cout << "q" << transition_table[i][0] << "\t|\t";
        cout << "q" << transition_table[i][1] << "\t|\n";
    }

    cout << " *q" << states_count - 1 << "\t|\t";
    final_state[0] = states_count - 1;
    cout << "q" << transition_table[states_count - 1][0] << "\t|\t";
    cout << "q" << transition_table[states_count - 1][1] << "\t|\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n\n";

    string_processing(transition_table, final_state);
}

// atmost case
void atmost() {
    int size;
    char alpha;
    cout << "\nEnter alphabet -\n ";
    cin >> alpha;

    cout << "\nWhich case you want to run -\n ";
    cout << "1. Atmost 1 " << alpha << "\n ";
    cout << "2. Atmost 2 " << alpha << "'s\n ";
    cout << "3. Atmost 3 " << alpha << "'s\n ";

    cin >> size;
    states_count = size + 2;
    int transition_table[states_count][2];

    for (int i = 0; i < states_count - 1; i++) {
        if (alpha == 'a') {
            transition_table[i][0] = i + 1;
            transition_table[i][1] = i;
        }
        else {
            transition_table[i][0] = i;
            transition_table[i][1] = i + 1;
        }
    }

    transition_table[states_count - 1][0] = states_count - 1;
    transition_table[states_count - 1][1] = states_count - 1;

    cout << "\n-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-";
    cout << "\n\t   Transition Table\t\t|\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n";
    cout << "States"
         << "\t|   Input " << alphabet[0] << "\t|   Input " << alphabet[1] << "\t|"
         << "\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n";
    cout << "->*q0"
         << "\t|\t"; // initial state
    cout << "q" << transition_table[0][0] << "\t|\t";
    cout << "q" << transition_table[0][1] << "\t|\n";
    final_state[0] = 0;

    for (int i = 1; i < states_count - 1; i++)
    {
        cout << "  *q" << i << "\t|\t";
        cout << "q" << transition_table[i][0] << "\t|\t";
        cout << "q" << transition_table[i][1] << "\t|\n";
        final_state[i] = i;
    }

    cout << "   q" << states_count - 1 << "\t|\t";
    cout << "q" << transition_table[states_count - 1][0] << "\t|\t";
    cout << "q" << transition_table[states_count - 1][1] << "\t|\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-\n\n";
    string_processing(transition_table, final_state);
}

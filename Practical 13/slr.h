// SLR Parser

// 3
// 1
// S
// 2
// a
// b
// S->aS
// S->Sb
// S->ab

#include <bits/stdc++.h>

using namespace std;

char terminalSLR[100] = {};
int noterminalSLR;
char nonterminalSLR[100] = {};
int noNonterminalSLR;
char gotoTable[100][100];
char reduce[20][20];
char followSLR[20][20];
char foCo[20][20];
char firstSLR[20][20];
char a[100] = {};

struct state {
    int prodCount;
    char prod[100][100] = {{}};
};

void addDots(struct state *I) {
    for (int i = 0; i < I->prodCount; i++) {
        for (int j = 99; j > 3; j--)
            I->prod[i][j] = I->prod[i][j - 1];
        I->prod[i][3] = '.';
    }
}

void augument(struct state *S, struct state *I) {
    if (I->prod[0][0] == 'S')
        strcpy(S->prod[0], "Z->.S");
    else {
        strcpy(S->prod[0], "S->.");
        S->prod[0][4] = I->prod[0][0];
    }
    S->prodCount++;
}

void getProdRules(struct state *I) {
    cout << "\n----------------------SLR PARSER----------------------\n\n";
    cout << "Enter the number of productions:\n";
    cin >> I->prodCount;
    cout << "Enter the number of non terminalSLR:" << endl;
    cin >> noNonterminalSLR;
    cout << "Enter the non terminalSLR one by one:" << endl;
    for (int i = 0; i < noNonterminalSLR; i++)
        cin >> nonterminalSLR[i];
    cout << "Enter the number of terminalSLR:" << endl;
    cin >> noterminalSLR;
    cout << "Enter the terminalSLR (single lettered) one by one:" << endl;
    for (int i = 0; i < noterminalSLR; i++)
        cin >> terminalSLR[i];
    cout << "Enter the productions one by one in form (S->ABc):\n";
    for (int i = 0; i < I->prodCount; i++) {
        cin >> I->prod[i];
    }
}

bool isNonTerminal(char a) {
    if (a >= 'A' && a <= 'Z')
        return true;
    else
        return false;
}

bool presentState(struct state *I, char *a) {
    for (int i = 0; i < I->prodCount; i++) {
        if (!strcmp(I->prod[i], a))
            return true;
    }
    return false;
}

char charAfterDot(char a[100]) {
    char b;
    for (int i = 0; i < strlen(a); i++)
        if (a[i] == '.') {
            b = a[i + 1];
            return b;
        }
    return -1;
}

char *moveDot(char b[100], int len) {
    strcpy(a, b);
    for (int i = 0; i < len; i++) {
        if (a[i] == '.') {
            swap(a[i], a[i + 1]);
            break;
        }
    }
    return &a[0];
}

bool sameState(struct state *I0, struct state *I) {
    if (I0->prodCount != I->prodCount)
        return false;
    for (int i = 0; i < I0->prodCount; i++) {
        int flag = 0;
        for (int j = 0; j < I->prodCount; j++)
            if (strcmp(I0->prod[i], I->prod[j]) == 0)
                flag = 1;
        if (flag == 0)
            return false;
    }
    return true;
}

void closure(struct state *I, struct state *I0) {
    char a = {};
    for (int i = 0; i < I0->prodCount; i++) {
        a = charAfterDot(I0->prod[i]);
        if (isNonTerminal(a)) {
            for (int j = 0; j < I->prodCount; j++) {
                if (I->prod[j][0] == a) {
                    if (!presentState(I0, I->prod[j])) {
                        strcpy(I0->prod[I0->prodCount], I->prod[j]);
                        I0->prodCount++;
                    }
                }
            }
        }
    }
}

void gotoState(struct state *I, struct state *S, char a) {
    int time = 1;
    for (int i = 0; i < I->prodCount; i++) {
        if (charAfterDot(I->prod[i]) == a) {
            if (time == 1) {
                time++;
            }
            strcpy(S->prod[S->prodCount], moveDot(I->prod[i], strlen(I->prod[i])));
            S->prodCount++;
        }
    }
}

void printProdRules(struct state *I) {
    for (int i = 0; i < I->prodCount; i++)
        printf("%s\n", I->prod[i]);
    cout << endl;
}

bool presentInArr(char a[20], char b) {
    for (int i = 0; i < strlen(a); i++)
        if (a[i] == b)
            return true;
    return false;
}

char *chars_after_dots(struct state *I) {
    for (int i = 0; i < I->prodCount; i++) {
        if (!presentInArr(a, charAfterDot(I->prod[i]))) {
            a[strlen(a)] = charAfterDot(I->prod[i]);
        }
    }
    return &a[0];
}

void cleanProdRules(struct state *I) {
    char a[100] = {};
    for (int i = 0; i < I->prodCount; i++)
        strcpy(I->prod[i], a);
    I->prodCount = 0;
}

int retIndex(char a) {
    for (int i = 0; i < noterminalSLR; i++)
        if (terminalSLR[i] == a)
            return i;
    for (int i = 0; i < noNonterminalSLR; i++)
        if (nonterminalSLR[i] == a)
            return noterminalSLR + i;
    return -1;
}

void printShiftTable(int state_count) {
    cout << endl
         << "----------------------Shift Actions----------------------" << endl
         << endl;
    cout << "\t";
    for (int i = 0; i < noterminalSLR; i++)
        cout << terminalSLR[i] << "\t";
    for (int i = 0; i < noNonterminalSLR; i++)
        cout << nonterminalSLR[i] << "\t";
    cout << endl;
    for (int i = 0; i < state_count; i++) {
        int arr[noNonterminalSLR + noterminalSLR] = {-1};
        for (int j = 0; j < state_count; j++) {
            if (gotoTable[i][j] != '~') {
                arr[retIndex(gotoTable[i][j])] = j;
            }
        }
        cout << "I" << i << "\t";
        for (int j = 0; j < noNonterminalSLR + noterminalSLR; j++) {
            if (i == 1 && j == noterminalSLR - 1)
                cout << "ACC"
                     << "\t";
            if (arr[j] == -1 || arr[j] == 0)
                cout << "\t";
            else {
                if (j < noterminalSLR)
                    cout << "S" << arr[j] << "\t";
                else
                    cout << arr[j] << "\t";
            }
        }
        cout << "\n";
    }
}

int getIndex(char c, char *a) {
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == c) {
            return i;
        }
    }
    return -1;
}

void addDotEnd(struct state *I) {
    for (int i = 0; i < I->prodCount; i++) {
        strcat(I->prod[i], ".");
    }
}

void addfirstSLR(int n, char b) {
    for (int i = 0; i < strlen(firstSLR[n]); i++)
        if (firstSLR[n][i] == b)
            return;
    firstSLR[n][strlen(firstSLR[n])] = b;
}

void addfirstSLR(int m, int n) {
    for (int i = 0; i < strlen(firstSLR[n]); i++) {
        int flag = 0;
        for (int j = 0; j < strlen(firstSLR[m]); j++) {
            if (firstSLR[n][i] == firstSLR[m][j])
                flag = 1;
        }
        if (flag == 0)
            addfirstSLR(m, firstSLR[n][i]);
    }
}

void addfollowSLR(int n, char b) {
    for (int i = 0; i < strlen(followSLR[n]); i++)
        if (followSLR[n][i] == b)
            return;
    followSLR[n][strlen(followSLR[n])] = b;
}

void addfollowSLR(int m, int n) {
    for (int i = 0; i < strlen(followSLR[n]); i++) {
        int flag = 0;
        for (int j = 0; j < strlen(followSLR[m]); j++) {
            if (followSLR[n][i] == followSLR[m][j])
                flag = 1;
        }
        if (flag == 0)
            addfollowSLR(m, followSLR[n][i]);
    }
}

void addfollowSLRfirstSLR(int m, int n) {
    for (int i = 0; i < strlen(firstSLR[n]); i++) {
        int flag = 0;
        for (int j = 0; j < strlen(followSLR[m]); j++) {
            if (firstSLR[n][i] == followSLR[m][j])
                flag = 1;
        }
        if (flag == 0)
            addfollowSLR(m, firstSLR[n][i]);
    }
}

void calcfirstSLR(struct state *I) {
    for (int i = 0; i < noNonterminalSLR; i++) {
        for (int j = 0; j < I->prodCount; j++) {
            if (I->prod[j][0] == nonterminalSLR[i]) {
                if (!isNonTerminal(I->prod[j][3])) {
                    addfirstSLR(i, I->prod[j][3]);
                }
            }
        }
    }
}

void calcfollowSLR(struct state *I) {
    for (int i = 0; i < noNonterminalSLR; i++) {
        for (int j = 0; j < I->prodCount; j++) {
            for (int k = 3; k < strlen(I->prod[j]); k++) {
                if (I->prod[j][k] == nonterminalSLR[i]) {
                    if (I->prod[j][k + 1] != '\0') {
                        if (!isNonTerminal(I->prod[j][k + 1])) {
                            addfollowSLR(i, I->prod[j][k + 1]);
                        }
                    }
                }
            }
        }
    }
}

int getIndex(int *arr, int n) {
    for (int i = 0; i < noterminalSLR; i++) {
        if (arr[i] == n)
            return i;
    }
    return -1;
}

void printReduceTable(int state_count, int *no_re, struct state *temp1) {
    cout << "----------------------Reduce actions----------------------" << endl
         << endl;
    cout << "\t";
    int arr[temp1->prodCount][noterminalSLR] = {-1};
    for (int i = 0; i < noterminalSLR; i++) {
        cout << terminalSLR[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < temp1->prodCount; i++) {
        int n = no_re[i];
        for (int j = 0; j < strlen(followSLR[retIndex(temp1->prod[i][0]) 
                                    - noterminalSLR]); j++) {
            for (int k = 0; k < noterminalSLR; k++) {
                if (followSLR[retIndex(temp1->prod[i][0]) 
                                    - noterminalSLR][j] == terminalSLR[k])
                    arr[i][k] = i + 1;
            }
        }
        cout << "I" << n << "\t";
        for (int j = 0; j < noterminalSLR; j++) {
            if (arr[i][j] != -1 && arr[i][j] != 0 && arr[i][j] < state_count)
                cout << "R" << arr[i][j] << "\t";
            else
                cout << "\t";
        }
        cout << endl;
    }
}

string slrParser() {
    struct state init;
    struct state temp;
    struct state temp1;
    int state_count = 1;
    getProdRules(&init);
    temp = init;
    temp1 = temp;
    addDots(&init);
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            gotoTable[i][j] = '~';
    struct state I[50];
    augument(&I[0], &init);
    closure(&init, &I[0]);
    cout << "\nI0:\n";
    printProdRules(&I[0]);
    char characters[20] = {};
    for (int i = 0; i < state_count; i++) {
        char characters[20] = {};
        for (int z = 0; z < I[i].prodCount; z++)
            if (!presentInArr(characters, charAfterDot(I[i].prod[z])))
                characters[strlen(characters)] = charAfterDot(I[i].prod[z]);
        for (int j = 0; j < strlen(characters); j++) {
            gotoState(&I[i], &I[state_count], characters[j]);
            closure(&init, &I[state_count]);
            int flag = 0;
            for (int k = 0; k < state_count - 1; k++) {
                if (sameState(&I[k], &I[state_count])) {
                    cleanProdRules(&I[state_count]);
                    flag = 1;
                    cout << "I" << i << " on reading the symbol " 
                    << characters[j] << " goes to I" << k << ".\n";
                    gotoTable[i][k] = characters[j];
                    ;
                    break;
                }
            }
            if (flag == 0) {
                state_count++;
                cout << "I" << i << " on reading the symbol " 
                << characters[j] << " goes to I" 
                << state_count - 1 << ":\n";
                gotoTable[i][state_count - 1] = characters[j];
                printProdRules(&I[state_count - 1]);
            }
        }
    }
    int no_re[temp.prodCount] = {-1};
    terminalSLR[noterminalSLR] = '$';
    noterminalSLR++;
    addDotEnd(&temp1);
    for (int i = 0; i < state_count; i++) {
        for (int j = 0; j < I[i].prodCount; j++)
            for (int k = 0; k < temp1.prodCount; k++)
                if (presentState(&I[i], temp1.prod[k]))
                    no_re[k] = i;
    }
    calcfirstSLR(&temp);
    for (int l = 0; l < noNonterminalSLR; l++) {
        for (int i = 0; i < temp.prodCount; i++) {
            if (isNonTerminal(temp.prod[i][3])) {
                addfirstSLR(retIndex(temp.prod[i][0]) - noterminalSLR, 
                retIndex(temp.prod[i][3]) - noterminalSLR);
            }
        }
    }
    calcfollowSLR(&temp);
    addfollowSLR(0, '$');
    for (int l = 0; l < noNonterminalSLR; l++) {
        for (int i = 0; i < temp.prodCount; i++) {
            for (int k = 3; k < strlen(temp.prod[i]); k++) {
                if (temp.prod[i][k] == nonterminalSLR[l]) {
                    if (isNonTerminal(temp.prod[i][k + 1])) {
                        addfollowSLRfirstSLR(l, retIndex(temp.prod[i][k + 1]) 
                        - noterminalSLR);
                    }
                    if (temp.prod[i][k + 1] == '\0')
                        addfollowSLR(l, retIndex(temp.prod[i][0]) 
                        - noterminalSLR);
                }
            }
        }
    }
    printShiftTable(state_count);
    cout << endl;
    printReduceTable(state_count, &no_re[0], &temp1);
    return "Yes";
}
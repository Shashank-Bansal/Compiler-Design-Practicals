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

char terminals[100] = {};
int noTerminals;
char nonTerminals[100] = {};
int noNonTerminals;
char gotoTable[100][100];
char reduce[20][20];
char follow[20][20];
char foCo[20][20];
char first[20][20];
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
    cout << "Enter the number of non terminals:" << endl;
    cin >> noNonTerminals;
    cout << "Enter the non terminals one by one:" << endl;
    for (int i = 0; i < noNonTerminals; i++)
        cin >> nonTerminals[i];
    cout << "Enter the number of terminals:" << endl;
    cin >> noTerminals;
    cout << "Enter the terminals (single lettered) one by one:" << endl;
    for (int i = 0; i < noTerminals; i++)
        cin >> terminals[i];
    cout << "Enter the productions one by one in form (S->ABc):\n";
    for (int i = 0; i < I->prodCount; i++) 
        cin >> I->prod[i];
}

bool isNonTerminal(char a) {
    return a >= 'A' && a <= 'Z';
}

bool presentState(struct state *I, char *a) {
    for (int i = 0; i < I->prodCount; i++)
        if (!strcmp(I->prod[i], a))
            return true;
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
    for (int i = 0; i < len; i++) 
        if (a[i] == '.') {
            swap(a[i], a[i + 1]);
            break;
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
        if (isNonTerminal(a))
            for (int j = 0; j < I->prodCount; j++) 
                if (I->prod[j][0] == a)
                    if (!presentState(I0, I->prod[j])) {
                        strcpy(I0->prod[I0->prodCount], I->prod[j]);
                        I0->prodCount++;
                    }
    }
}

void gotoState(struct state *I, struct state *S, char a) {
    int time = 1;
    for (int i = 0; i < I->prodCount; i++)
        if (charAfterDot(I->prod[i]) == a) {
            if (time == 1) 
                time++;

            strcpy(S->prod[S->prodCount], moveDot(I->prod[i], strlen(I->prod[i])));
            S->prodCount++;
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
    for (int i = 0; i < I->prodCount; i++) 
        if (!presentInArr(a, charAfterDot(I->prod[i]))) 
            a[strlen(a)] = charAfterDot(I->prod[i]);
    
    return &a[0];
}

void cleanProdRules(struct state *I) {
    char a[100] = {};
    for (int i = 0; i < I->prodCount; i++)
        strcpy(I->prod[i], a);
    I->prodCount = 0;
}

int retIndex(char a) {
    for (int i = 0; i < noTerminals; i++)
        if (terminals[i] == a)
            return i;
    for (int i = 0; i < noNonTerminals; i++)
        if (nonTerminals[i] == a)
            return noTerminals + i;
    return -1;
}

void printShiftTable(int state_count) {
    cout << endl
         << "----------------------Shift Actions----------------------" << endl
         << endl;
    cout << "\t";
    for (int i = 0; i < noTerminals; i++)
        cout << terminals[i] << "\t";
    for (int i = 0; i < noNonTerminals; i++)
        cout << nonTerminals[i] << "\t";
    cout << endl;
    for (int i = 0; i < state_count; i++) {
        int arr[noNonTerminals + noTerminals] = {-1};
        for (int j = 0; j < state_count; j++) 
            if (gotoTable[i][j] != '~') 
                arr[retIndex(gotoTable[i][j])] = j;
        
        cout << "I" << i << "\t";
        for (int j = 0; j < noNonTerminals + noTerminals; j++) {
            if (i == 1 && j == noTerminals - 1)
                cout << "ACC"
                     << "\t";
            if (arr[j] == -1 || arr[j] == 0)
                cout << "\t";
            else {
                if (j < noTerminals)
                    cout << "S" << arr[j] << "\t";
                else
                    cout << arr[j] << "\t";
            }
        }
        cout << "\n";
    }
}

int getIndex(char c, char *a) {
    for (int i = 0; i < strlen(a); i++) 
        if (a[i] == c) 
            return i;
    return -1;
}

void addDotEnd(struct state *I) {
    for (int i = 0; i < I->prodCount; i++)
        strcat(I->prod[i], ".");
}

void addFirst(int n, char b) {
    for (int i = 0; i < strlen(first[n]); i++)
        if (first[n][i] == b)
            return;
    first[n][strlen(first[n])] = b;
}

void addFirst(int m, int n) {
    for (int i = 0; i < strlen(first[n]); i++) {
        int flag = 0;
        for (int j = 0; j < strlen(first[m]); j++) 
            if (first[n][i] == first[m][j])
                flag = 1;
        if (flag == 0)
            addFirst(m, first[n][i]);
    }
}

void addFollow(int n, char b) {
    for (int i = 0; i < strlen(follow[n]); i++)
        if (follow[n][i] == b)
            return;
    follow[n][strlen(follow[n])] = b;
}

void addFollow(int m, int n) {
    for (int i = 0; i < strlen(follow[n]); i++) {
        int flag = 0;
        for (int j = 0; j < strlen(follow[m]); j++) 
            if (follow[n][i] == follow[m][j])
                flag = 1;
        if (flag == 0)
            addFollow(m, follow[n][i]);
    }
}

void addFollowFirst(int m, int n) {
    for (int i = 0; i < strlen(first[n]); i++) {
        int flag = 0;
        for (int j = 0; j < strlen(follow[m]); j++)
            if (first[n][i] == follow[m][j])
                flag = 1;

        if (flag == 0)
            addFollow(m, first[n][i]);
    }
}

void calcFirst(struct state *I) {
    for (int i = 0; i < noNonTerminals; i++) 
        for (int j = 0; j < I->prodCount; j++) 
            if (I->prod[j][0] == nonTerminals[i]) 
                if (!isNonTerminal(I->prod[j][3])) 
                    addFirst(i, I->prod[j][3]);
}

void calcFollow(struct state *I) {
    for (int i = 0; i < noNonTerminals; i++) 
        for (int j = 0; j < I->prodCount; j++) 
            for (int k = 3; k < strlen(I->prod[j]); k++) 
                if (I->prod[j][k] == nonTerminals[i]) 
                    if (I->prod[j][k + 1] != '\0') 
                        if (!isNonTerminal(I->prod[j][k + 1])) 
                            addFollow(i, I->prod[j][k + 1]);
}

int getIndex(int *arr, int n) {
    for (int i = 0; i < noTerminals; i++)
        if (arr[i] == n)
            return i;
    return -1;
}

void printReduceTable(int state_count, int *no_re, struct state *temp1) {
    cout << "----------------------Reduce actions----------------------" << endl << endl;
    cout << "\t";
    int arr[temp1->prodCount][noTerminals] = {-1};
    for (int i = 0; i < noTerminals; i++) 
        cout << terminals[i] << "\t";

    cout << endl;
    for (int i = 0; i < temp1->prodCount; i++) {
        int n = no_re[i];
        for (int j = 0; j < strlen(follow[retIndex(temp1->prod[i][0]) - noTerminals]); j++) 
            for (int k = 0; k < noTerminals; k++) 
                if (follow[retIndex(temp1->prod[i][0]) - noTerminals][j] == terminals[k])
                    arr[i][k] = i + 1;

        cout << "I" << n << "\t";
        for (int j = 0; j < noTerminals; j++) 
            if (arr[i][j] != -1 && arr[i][j] != 0 && arr[i][j] < state_count)
                cout << "R" << arr[i][j] << "\t";
            else
                cout << "\t";

        cout << endl;
    }
}

int main() {
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
    terminals[noTerminals] = '$';
    noTerminals++;
    addDotEnd(&temp1);
    for (int i = 0; i < state_count; i++) {
        for (int j = 0; j < I[i].prodCount; j++)
            for (int k = 0; k < temp1.prodCount; k++)
                if (presentState(&I[i], temp1.prod[k]))
                    no_re[k] = i;
    }
    calcFirst(&temp);
    for (int l = 0; l < noNonTerminals; l++) 
        for (int i = 0; i < temp.prodCount; i++) 
            if (isNonTerminal(temp.prod[i][3])) {
                addFirst(retIndex(temp.prod[i][0]) - noTerminals, 
                retIndex(temp.prod[i][3]) - noTerminals);
            }
        
    calcFollow(&temp);
    addFollow(0, '$');
    for (int l = 0; l < noNonTerminals; l++) 
        for (int i = 0; i < temp.prodCount; i++) 
            for (int k = 3; k < strlen(temp.prod[i]); k++) 
                if (temp.prod[i][k] == nonTerminals[l]) {
                    if (isNonTerminal(temp.prod[i][k + 1])) 
                        addFollowFirst(l, retIndex(temp.prod[i][k + 1]) - noTerminals);
                    if (temp.prod[i][k + 1] == '\0')
                        addFollow(l, retIndex(temp.prod[i][0]) - noTerminals);
                }

    printShiftTable(state_count);
    cout << endl;
    printReduceTable(state_count, &no_re[0], &temp1);
    return 0;
}
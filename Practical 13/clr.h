// CLR Parser
// 
// 3
// S->CC
// S->cC
// C->d

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

char rulesCLR[100][100], terminalCLR[100], nonterminalCLR[100], actionCLR[100][100][100];
int termLenCLR, nontermLenCLR, firstCLR[100][100], followCLR[100][100], hash1CLR[100];
int ruleCountCLR, hash2CLR[100], canonicalCLR[100][20][10][10], canLenCLR, go_to_clr[100][100], clr;

void calcfirstCLR(int k) {
    int j, flag = 0, len, l, m, i;
    if (hash1CLR[k])
        return;
    hash1CLR[k] = 1;
    for (i = 0; i < ruleCountCLR; i++) {
        if (rulesCLR[i][0] == nonterminalCLR[k]) {
            flag = 0;
            len = strlen(rulesCLR[i]);
            for (j = 3; j < len; j++) {
                if (!flag) {
                    if (rulesCLR[i][j] >= 'A' && rulesCLR[i][j] <= 'Z') {
                        for (l = 0; l < nontermLenCLR; l++) {
                            if (nonterminalCLR[l] == rulesCLR[i][j])
                                break;
                        }
                        flag = 1;
                        if (hash1CLR[l]) {
                            for (m = 0; m < termLenCLR; m++) {
                                if (firstCLR[l][m]) {
                                    firstCLR[k][m] = 1;
                                    if (terminalCLR[m] == '^')
                                        flag = 0;
                                }
                            }
                        }
                        else {
                            calcfirstCLR(l);
                            for (m = 0; m < termLenCLR; m++) {
                                if (firstCLR[l][m]) {
                                    firstCLR[k][m] = 1;
                                    if (terminalCLR[m] == '^')
                                        flag = 0;
                                }
                            }
                        }
                    }
                    else if (rulesCLR[i][j] != '|') {
                        for (l = 0; l < termLenCLR; l++) {
                            if (terminalCLR[l] == rulesCLR[i][j])
                                break;
                        }
                        firstCLR[k][l] = 1;
                        flag = 1;
                    }
                }
                else {
                    if (rulesCLR[i][j] == '|')
                        flag = 0;
                }
            }
        }
    }
}

void calcfollowCLR(int k) {
    int i, len, j, l, flag = 0, m;
    if (hash2CLR[k])
        return;
    hash2CLR[k] = 1;
    for (i = 0; i < ruleCountCLR; i++) {
        len = strlen(rulesCLR[i]);
        for (j = 3; j < len; j++) {
            if (flag) {
                if (rulesCLR[i][j] >= 'A' && rulesCLR[i][j] <= 'Z') {
                    flag = 0;
                    for (l = 0; l < nontermLenCLR; l++) {
                        if (nonterminalCLR[l] == rulesCLR[i][j])
                            break;
                    }
                    if (l < nontermLenCLR) {
                        for (m = 0; m < termLenCLR; m++) {
                            if (firstCLR[l][m]) {
                                followCLR[k][m] = 1;
                                if (terminalCLR[m] == '^')
                                    flag = 1;
                            }
                        }
                    }
                }
                else {
                    for (l = 0; l < termLenCLR; l++) {
                        if (terminalCLR[l] == rulesCLR[i][j])
                            break;
                    }
                    if (l < termLenCLR) {
                        followCLR[k][l] = 1;
                    }
                    else {
                        if (rulesCLR[i][j] == '|') {
                            for (l = 0; l < nontermLenCLR; l++) {
                                if (nonterminalCLR[l] == rulesCLR[i][0])
                                    break;
                            }
                            if (l < nontermLenCLR) {
                                calcfollowCLR(l);
                                for (m = 0; m < termLenCLR; m++) {
                                    if (followCLR[l][m])
                                        followCLR[k][m] = 1;
                                }
                            }
                            flag = 0;
                        }
                    }
                    flag = 0;
                }
            }
            if (rulesCLR[i][j] == nonterminalCLR[k]) {
                flag = 1;
            }
        }
        if (flag) {
            for (l = 0; l < nontermLenCLR; l++) {
                if (nonterminalCLR[l] == rulesCLR[i][0])
                    break;
            }
            if (l < nontermLenCLR) {
                calcfollowCLR(l);
                for (m = 0; m < termLenCLR; m++) {
                    if (followCLR[l][m])
                        followCLR[k][m] = 1;
                }
            }
            flag = 0;
        }
    }
}

void printCLR(int in) {
    int i, j, len, k, l, prnt;
    cout << "I" << in << ":\n";
    for (i = 0; i < 10; i++) {
        prnt = 0;
        for (k = 0; k < termLenCLR; k++) {
            if (canonicalCLR[in][ruleCountCLR - 1][i][k]) {
                if (!prnt) {
                    len = strlen(rulesCLR[ruleCountCLR - 1]);
                    for (j = 0; j <= len; j++) {
                        if (j == i)
                            cout << ".";
                        cout << rulesCLR[ruleCountCLR - 1][j];
                    }
                    cout << "," << terminalCLR[k];
                    prnt = 1;
                }
                else
                    cout << "|" << terminalCLR[k];
            }
        }
        if (prnt)
            puts("");
    }
    for (l = 0; l < ruleCountCLR - 1; l++) {
        for (i = 0; i < 10; i++) {
            prnt = 0;
            for (k = 0; k < termLenCLR; k++) {
                if (canonicalCLR[in][l][i][k]) {
                    if (!prnt) {
                        len = strlen(rulesCLR[l]);
                        for (j = 0; j <= len; j++) {
                            if (j == i)
                                cout << ".";
                            cout << rulesCLR[l][j];
                        }
                        cout << "," << terminalCLR[k];
                        prnt = 1;
                    }
                    else
                        cout << "|" << terminalCLR[k];
                }
            }
            if (prnt)
                puts("");
        }
    }
}

void firstCLRCalc(char *str, int *arr) {
    int j, flag = 0, len, l, m, i, k;
    len = strlen(str);
    for (j = 0; j < len; j++) {
        if (!flag) {
            if (str[j] >= 'A' && str[j] <= 'Z') {
                for (l = 0; l < nontermLenCLR; l++) {
                    if (nonterminalCLR[l] == str[j])
                        break;
                }
                flag = 1;
                for (m = 0; m < termLenCLR; m++) {
                    if (firstCLR[l][m]) {
                        arr[m] = 1;
                        if (terminalCLR[m] == '^')
                            flag = 0;
                    }
                }
            }
            else if (str[j] != '|') {
                for (l = 0; l < termLenCLR; l++) {
                    if (terminalCLR[l] == str[j])
                        break;
                }
                arr[l] = 1;
                flag = 1;
            }
        }
        else
            break;
    }
}

void closureCLR(int arr[][10][10]) {
    int i, j, flag = 1, k, l, m, arr1[10], n;
    char c, str[100];
    while (flag) {
        flag = 0;
        for (i = 0; i < ruleCountCLR; i++) {
            for (k = 0; k < 10; k++) {
                for (n = 0; n < 10; n++) {
                    if (arr[i][k][n]) {
                        c = rulesCLR[i][k];
                        for (j = 0; j < ruleCountCLR; j++) {
                            if (rulesCLR[j][0] == c) {
                                for (m = 0; m < 10; m++)
                                    arr1[m] = 0;
                                for (m = k + 1; rulesCLR[i][m] != '\0'; m++) {
                                    str[m - k - 1] = rulesCLR[i][m];
                                }
                                str[m - k - 1] = terminalCLR[n];
                                str[m - k] = '\0';
                                firstCLRCalc(str, arr1);
                                for (m = 0; m < termLenCLR; m++) {
                                    if (arr1[m] && !arr[j][3][m]) {
                                        flag = 1;
                                        arr[j][3][m] = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int GotoCLR(int in, int sym, int nt) {
    int j, ans = 0, arr[100][10][10] = {0}, flg = 0, k, l, len, i, m;
    char c;
    for (i = 0; i < ruleCountCLR; i++) {
        for (j = 0; j < 10; j++) {
            for (k = 0; k < termLenCLR; k++) {
                if (canonicalCLR[in][i][j][k]) {
                    if (nt) {
                        if (rulesCLR[i][j] == nonterminalCLR[sym]) {
                            arr[i][j + 1][k] = 1;
                            flg = 1;
                        }
                    }
                    else if (rulesCLR[i][j] == terminalCLR[sym]) {
                        arr[i][j + 1][k] = 1;
                        flg = 1;
                    }
                }
            }
        }
    }
    if (!flg)
        return 0;
    closureCLR(arr);
    for (j = 0; j < canLenCLR; j++) {
        flg = 0;
        for (k = 0; k < ruleCountCLR; k++) {
            for (l = 0; l < 10; l++) {
                for (i = 0; i < termLenCLR; i++) {
                    if (canonicalCLR[j][k][l][i] != arr[k][l][i]) {
                        flg = 1;
                        break;
                    }
                }
                if (flg)
                    break;
            }
            if (flg)
                break;
        }
        if (!flg) {
            ans = j;
            break;
        }
    }
    if (flg) {
        for (j = 0; j < ruleCountCLR; j++) {
            for (l = 0; l < 10; l++) {
                for (i = 0; i < termLenCLR; i++)
                    canonicalCLR[canLenCLR][j][l][i] = arr[j][l][i];
            }
        }
        ans = canLenCLR;
        canLenCLR++;
    }
    if (nt)
        go_to_clr[in][sym] = ans;
    else {
        if (actionCLR[in][sym][0] == '\0')
            printf(actionCLR[in][sym], "s%d\0", ans);
        else {
            sscanf(actionCLR[in][sym], "s%d", &k);
            if (k != ans) {
                clr = 0;
                len = strlen(actionCLR[in][sym]);
                printf(actionCLR[in][sym] + len, ",s%d", ans);
            }
        }
    }
    if (flg) {
        for (i = 0; i < ruleCountCLR; i++) {
            len = strlen(rulesCLR[i]);
            for (j = 0; j < 10; j++) {
                for (l = 0; l < termLenCLR; l++) {
                    if (arr[i][j][l] && j == len) {
                        if (i == ruleCountCLR - 1)
                            printf(actionCLR[canLenCLR - 1][termLenCLR - 1], "acc\0");
                        else {
                            if (actionCLR[canLenCLR - 1][l][0] == '\0')
                                printf(actionCLR[canLenCLR - 1][l], "r%d\0", i + 1);
                            else {
                                sscanf(actionCLR[canLenCLR - 1][l], "r%d", &k);
                                if (k != i + 1) {
                                    clr = 0;
                                    len = strlen(actionCLR[canLenCLR - 1][l]);
                                    printf(actionCLR[canLenCLR - 1][l] + len, "r%d\0", i + 1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return flg;
}

string clrParser() {
    int i, j, len, k, a, b, t, flag;
    char c, temp[100];
    clr = 1;
    canLenCLR = 0;
    termLenCLR = nontermLenCLR = 0;
    cout << "\n----------------------CLR PARSER----------------------\n";
    cout << "Enter the number of Production rulesCLR = ";
    cin >> ruleCountCLR;
    cout << "\n";
    cout << "Enter the Production rulesCLR in form (S->ABc) = " << endl;
    for (i = 0; i < ruleCountCLR; i++) {
        scanf("%s", rulesCLR[i]);
        cout << rulesCLR[i];
        len = strlen(rulesCLR[i]);
        for (j = 0; j < len; j++) {
            if (rulesCLR[i][j] >= 'A' && rulesCLR[i][j] <= 'Z') {
                for (k = 0; k < nontermLenCLR; k++) {
                    if (nonterminalCLR[k] == rulesCLR[i][j])
                        break;
                }
                if (k == nontermLenCLR) {
                    nonterminalCLR[nontermLenCLR] = rulesCLR[i][j];
                    nontermLenCLR++;
                }
            }
            else if (rulesCLR[i][j] != '-' && rulesCLR[i][j] != '>' && rulesCLR[i][j] != '|') {
                for (k = 0; k < termLenCLR; k++) {
                    if (terminalCLR[k] == rulesCLR[i][j])
                        break;
                }
                if (k == termLenCLR) {
                    terminalCLR[termLenCLR] = rulesCLR[i][j];
                    termLenCLR++;
                }
            }
        }
    }
    cout << "\nSet of Non terminalCLR => ";
    cout << nonterminalCLR[0];
    for (i = 1; i < nontermLenCLR; i++) {
        cout << "," << nonterminalCLR[i];
    }
    puts("");
    cout << "\nSet of terminalCLR => ";
    cout << terminalCLR[0];
    for (i = 1; i < termLenCLR; i++) {
        cout << "," << terminalCLR[i];
    }
    puts("");
    for (i = 0; i < nontermLenCLR; i++) {
        calcfirstCLR(i);
        cout << "\nfirstCLR(" << nonterminalCLR[i] << ") = { ";
        for (j = 0; j < termLenCLR; j++) {
            if (firstCLR[i][j])
                break;
        }
        if (j < termLenCLR) {
            cout << terminalCLR[j];
            j++;
            for (; j < termLenCLR; j++) {
                if (firstCLR[i][j])
                    cout << " ," << terminalCLR[j];
            }
        }
        cout << " }\n";
    }
    terminalCLR[termLenCLR] = '$';
    termLenCLR++;
    followCLR[0][termLenCLR - 1] = 1;
    for (i = 0; i < nontermLenCLR; i++) {
        calcfollowCLR(i);
        cout << "\nfollowCLR(" << nonterminalCLR[i] << ") = { ";
        for (j = 0; j < termLenCLR; j++) {
            if (followCLR[i][j])
                break;
        }
        if (j < termLenCLR) {
            cout << terminalCLR[j];
            j++;
            for (; j < termLenCLR; j++) {
                if (followCLR[i][j])
                    cout << " ," << terminalCLR[j];
            }
        }
        cout << " }\n";
    }
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            printf(actionCLR[i][j], "\0");
            go_to_clr[i][j] = -1;
        }
    }
    printf(rulesCLR[ruleCountCLR], "X->%c\0", rulesCLR[0][0]); // New initial symbol
    ruleCountCLR++;
    cout << "\n-----------------------------------------------\n";
    cout << "\ncanonicalCLR Collection => ";
    canonicalCLR[0][ruleCountCLR - 1][3][termLenCLR - 1] = 1;
    closureCLR(canonicalCLR[0]);
    canLenCLR++;
    puts("");
    printCLR(0);
    flag = 1;
    while (flag) {
        flag = 0;
        for (i = 0; i < canLenCLR; i++) {
            for (j = 0; j < nontermLenCLR; j++) {
                if (GotoCLR(i, j, 1)) {
                    cout << "\nGotoCLR(I" << i << ", " << nonterminalCLR[j] << ") ";
                    printCLR(canLenCLR - 1);
                    flag = 1;
                }
            }
            for (j = 0; j < termLenCLR - 1; j++) {
                if (GotoCLR(i, j, 0)) {
                    cout << "\nGotoCLR(I" << i << ", " << terminalCLR[j] << ") ";
                    printCLR(canLenCLR - 1);
                    flag = 1;
                }
            }
        }
    }
    if (clr) {
        puts("\nGrammar is CLR(1)");
        cout << "\n-----------------------------------------------\n";
        cout << "\nCLR Parsing Table\n\n";
        cout << "State\t|\tactionCLR\t";
        for (i = 0; i < termLenCLR - 2; i++)
            cout << "\t";
        cout << "|\tGotoCLR\n";
        cout << "------------------------------------------------------\n\t|";
        for (i = 0; i < termLenCLR; i++)
        {
            cout << terminalCLR[i] << "\t";
        }
        cout << "|";
        for (i = 0; i < nontermLenCLR; i++)
        {
            cout << nonterminalCLR[i] << "\t";
        }
        cout << "\n------------------------------------------------------\n";
        for (i = 0; i < canLenCLR; i++)
        {
            cout << i << "\t|";
            for (j = 0; j < termLenCLR; j++)
            {
                cout << actionCLR[i][j] << "\t";
            }
            cout << "|";
            for (j = 0; j < nontermLenCLR; j++)
            {
                if (go_to_clr[i][j] != -1)
                    cout << go_to_clr[i][j];
                cout << "\t";
            }
            puts("");
        }
        return "Yes";
    }
    else {
        puts("\nGrammar is not CLR(1)");
        return "No";
    }
}

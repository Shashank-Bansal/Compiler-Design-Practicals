#include <bits/stdc++.h>

using namespace std;

char rulesLALR[100][100], terminalLALR[100], nonterminalLALR[100], actionLALR[100][100][100];
int termLenLALR, nontermLenLALR, firstLALR[100][100], followLALR[100][100], hash1LALR[100];
int ruleCountLALR, hash2LALR[100], canonicalLALR[100][20][10][10], canLenLALR, go_to_lalr[100][100], eqItems[100], lalr;

void calcfirstLALR(int k) {
    int j, flag = 0, len, l, m, i;
    if (hash1LALR[k])
        return;
    hash1LALR[k] = 1;
    for (i = 0; i < ruleCountLALR; i++) {
        if (rulesLALR[i][0] == nonterminalLALR[k]) {
            flag = 0;
            len = strlen(rulesLALR[i]);
            for (j = 3; j < len; j++) {
                if (!flag) {
                    if (rulesLALR[i][j] >= 'A' && rulesLALR[i][j] <= 'Z') {
                        for (l = 0; l < nontermLenLALR; l++) {
                            if (nonterminalLALR[l] == rulesLALR[i][j])
                                break;
                        }
                        flag = 1;
                        if (hash1LALR[l]) {
                            for (m = 0; m < termLenLALR; m++) {
                                if (firstLALR[l][m]) {
                                    firstLALR[k][m] = 1;
                                    if (terminalLALR[m] == '^')
                                        flag = 0;
                                }
                            }
                        }
                        else {
                            calcfirstLALR(l);
                            for (m = 0; m < termLenLALR; m++) {
                                if (firstLALR[l][m]) {
                                    firstLALR[k][m] = 1;
                                    if (terminalLALR[m] == '^')
                                        flag = 0;
                                }
                            }
                        }
                    }
                    else if (rulesLALR[i][j] != '|') {
                        for (l = 0; l < termLenLALR; l++) {
                            if (terminalLALR[l] == rulesLALR[i][j])
                                break;
                        }
                        firstLALR[k][l] = 1;
                        flag = 1;
                    }
                }
                else {
                    if (rulesLALR[i][j] == '|')
                        flag = 0;
                }
            }
        }
    }
}

void calcfollowLALR(int k) {
    int i, len, j, l, flag = 0, m;
    if (hash2LALR[k])
        return;
    hash2LALR[k] = 1;
    for (i = 0; i < ruleCountLALR; i++) {
        len = strlen(rulesLALR[i]);
        for (j = 3; j < len; j++) {
            if (flag) {
                if (rulesLALR[i][j] >= 'A' && rulesLALR[i][j] <= 'Z') {
                    flag = 0;
                    for (l = 0; l < nontermLenLALR; l++) {
                        if (nonterminalLALR[l] == rulesLALR[i][j])
                            break;
                    }
                    if (l < nontermLenLALR) {
                        for (m = 0; m < termLenLALR; m++) {
                            if (firstLALR[l][m]) {
                                followLALR[k][m] = 1;
                                if (terminalLALR[m] == '^')
                                    flag = 1;
                            }
                        }
                    }
                }
                else {
                    for (l = 0; l < termLenLALR; l++) {
                        if (terminalLALR[l] == rulesLALR[i][j])
                            break;
                    }
                    if (l < termLenLALR) {
                        followLALR[k][l] = 1;
                    }
                    else {
                        if (rulesLALR[i][j] == '|') {
                            for (l = 0; l < nontermLenLALR; l++) {
                                if (nonterminalLALR[l] == rulesLALR[i][0])
                                    break;
                            }
                            if (l < nontermLenLALR) {
                                calcfollowLALR(l);
                                for (m = 0; m < termLenLALR; m++)
                                {
                                    if (followLALR[l][m])
                                        followLALR[k][m] = 1;
                                }
                            }
                            flag = 0;
                        }
                    }
                    flag = 0;
                }
            }
            if (rulesLALR[i][j] == nonterminalLALR[k]) {
                flag = 1;
            }
        }
        if (flag) {
            for (l = 0; l < nontermLenLALR; l++) {
                if (nonterminalLALR[l] == rulesLALR[i][0])
                    break;
            }
            if (l < nontermLenLALR) {
                calcfollowLALR(l);
                for (m = 0; m < termLenLALR; m++) {
                    if (followLALR[l][m])
                        followLALR[k][m] = 1;
                }
            }
            flag = 0;
        }
    }
}

void print(int in) {
    int i, j, len, k, l, prnt;
    cout << "I" << in << ":\n";
    for (i = 0; i < 10; i++) {
        prnt = 0;
        for (k = 0; k < termLenLALR; k++) {
            if (canonicalLALR[in][ruleCountLALR - 1][i][k]) {
                if (!prnt) {
                    len = strlen(rulesLALR[ruleCountLALR - 1]);
                    for (j = 0; j <= len; j++) {
                        if (j == i)
                            cout << ".";
                        cout << rulesLALR[ruleCountLALR - 1][j];
                    }
                    cout << "," << terminalLALR[k];
                    prnt = 1;
                }
                else
                    cout << "|" << terminalLALR[k];
            }
        }
        if (prnt)
            puts("");
    }
    for (l = 0; l < ruleCountLALR - 1; l++) {
        for (i = 0; i < 10; i++) {
            prnt = 0;
            for (k = 0; k < termLenLALR; k++) {
                if (canonicalLALR[in][l][i][k]) {
                    if (!prnt) {
                        len = strlen(rulesLALR[l]);
                        for (j = 0; j <= len; j++) {
                            if (j == i)
                                cout << ".";
                            cout << rulesLALR[l][j];
                        }
                        cout << "," << terminalLALR[k];
                        prnt = 1;
                    }
                    else
                        cout << "|" << terminalLALR[k];
                }
            }
            if (prnt)
                puts("");
        }
    }
}

void firstLALRCalc(char *str, int *arr) {
    int j, flag = 0, len, l, m, i, k;
    len = strlen(str);
    for (j = 0; j < len; j++) {
        if (!flag) {
            if (str[j] >= 'A' && str[j] <= 'Z') {
                for (l = 0; l < nontermLenLALR; l++) {
                    if (nonterminalLALR[l] == str[j])
                        break;
                }
                flag = 1;
                for (m = 0; m < termLenLALR; m++) {
                    if (firstLALR[l][m]) {
                        arr[m] = 1;
                        if (terminalLALR[m] == '^')
                            flag = 0;
                    }
                }
            }
            else if (str[j] != '|') {
                for (l = 0; l < termLenLALR; l++) {
                    if (terminalLALR[l] == str[j])
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

void closure(int arr[][10][10]) {
    int i, j, flag = 1, k, l, m, arr1[10], n;
    char c, str[100];
    while (flag) {
        flag = 0;
        for (i = 0; i < ruleCountLALR; i++) {
            for (k = 0; k < 10; k++) {
                for (n = 0; n < 10; n++) {
                    if (arr[i][k][n]) {
                        c = rulesLALR[i][k];
                        for (j = 0; j < ruleCountLALR; j++) {
                            if (rulesLALR[j][0] == c) {
                                for (m = 0; m < 10; m++)
                                    arr1[m] = 0;
                                for (m = k + 1; rulesLALR[i][m] != '\0'; m++) {
                                    str[m - k - 1] = rulesLALR[i][m];
                                }
                                str[m - k - 1] = terminalLALR[n];
                                str[m - k] = '\0';
                                firstLALRCalc(str, arr1);
                                for (m = 0; m < termLenLALR; m++) {
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

int Goto(int in, int sym, int nt) {
    int j, ans = 0, arr[100][10][10] = {0}, flg = 0, k, l, len, i, m;
    char c;
    for (i = 0; i < ruleCountLALR; i++) {
        for (j = 0; j < 10; j++) {
            for (k = 0; k < termLenLALR; k++) {
                if (canonicalLALR[in][i][j][k]) {
                    if (nt) {
                        if (rulesLALR[i][j] == nonterminalLALR[sym]) {
                            arr[i][j + 1][k] = 1;
                            flg = 1;
                        }
                    }
                    else if (rulesLALR[i][j] == terminalLALR[sym]) {
                        arr[i][j + 1][k] = 1;
                        flg = 1;
                    }
                }
            }
        }
    }
    if (!flg)
        return 0;
    closure(arr);
    for (j = 0; j < canLenLALR; j++) {
        flg = 0;
        for (k = 0; k < ruleCountLALR; k++) {
            for (l = 0; l < 10; l++) {
                for (i = 0; i < termLenLALR; i++) {
                    if (canonicalLALR[j][k][l][i] != arr[k][l][i]) {
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
        for (j = 0; j < ruleCountLALR; j++) {
            for (l = 0; l < 10; l++) {
                for (i = 0; i < termLenLALR; i++)
                    canonicalLALR[canLenLALR][j][l][i] = arr[j][l][i];
            }
        }
        ans = canLenLALR;
        canLenLALR++;
    }
    if (nt)
        go_to_lalr[in][sym] = ans;
    else {
        if (actionLALR[in][sym][0] == '\0')
            sprintf(actionLALR[in][sym], "s%d\0", ans);
        else {
            sscanf(actionLALR[in][sym], "s%d", &k);
            if (k != ans) {
                lalr = 0;
                len = strlen(actionLALR[in][sym]);
                sprintf(actionLALR[in][sym] + len, ",s%d", ans);
            }
        }
    }
    if (flg) {
        for (i = 0; i < ruleCountLALR; i++) {
            len = strlen(rulesLALR[i]);
            for (j = 0; j < 10; j++) {
                for (l = 0; l < termLenLALR; l++) {
                    if (arr[i][j][l] && j == len) {
                        if (i == ruleCountLALR - 1)
                            sprintf(actionLALR[canLenLALR - 1][termLenLALR - 1], "acc\0");
                        else {
                            if (actionLALR[canLenLALR - 1][l][0] == '\0')
                                sprintf(actionLALR[canLenLALR - 1][l], "r%d\0", i + 1);
                            else {
                                sscanf(actionLALR[canLenLALR - 1][l], "r%d", &k);
                                if (k != i + 1) {
                                    lalr = 0;
                                    len = strlen(actionLALR[canLenLALR - 1][l]);
                                    sprintf(actionLALR[canLenLALR - 1][l] + len, "r%d\0", i + 1);
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

void printAlt(int in) {
    int i;
    in = eqItems[in];
    for (i = 0; i < canLenLALR; i++) {
        if (eqItems[i] == in)
            cout << i;
    }
}

string lalrParser()
{
    int i, j, len, k, a, b, t, flag, l, m, flg1, flg2;
    char c, temp[100];
    lalr = 1;
    canLenLALR = 0;
    termLenLALR = nontermLenLALR = 0;
    cout << "\n----------------LALR PARSER----------------\n";
    cout << "Enter the number of Production rulesLALR = ";
    cin >> ruleCountLALR;
    cout << "\n";
    cout << "Enter the rulesLALR in form (S->ABc) = " << endl;
    for (i = 0; i < ruleCountLALR; i++) {
        scanf("%s", &rulesLALR[i]);
        len = strlen(rulesLALR[i]);
        for (j = 0; j < len; j++) {
            if (rulesLALR[i][j] >= 'A' && rulesLALR[i][j] <= 'Z') {
                for (k = 0; k < nontermLenLALR; k++) {
                    if (nonterminalLALR[k] == rulesLALR[i][j])
                        break;
                }
                if (k == nontermLenLALR) {
                    nonterminalLALR[nontermLenLALR] = rulesLALR[i][j];
                    nontermLenLALR++;
                }
            }
            else if (rulesLALR[i][j] != '-' && rulesLALR[i][j] != '>' && rulesLALR[i][j] != '|') {
                for (k = 0; k < termLenLALR; k++) {
                    if (terminalLALR[k] == rulesLALR[i][j])
                        break;
                }
                if (k == termLenLALR) {
                    terminalLALR[termLenLALR] = rulesLALR[i][j];
                    termLenLALR++;
                }
            }
        }
    }
    cout << "\nSet of Non terminalLALR => ";
    cout << nonterminalLALR[0];
    for (i = 1; i < nontermLenLALR; i++) {
        cout << "," << nonterminalLALR[i];
    }
    puts("");
    cout << "\nSet of terminalLALR => ";
    cout << terminalLALR[0];
    for (i = 1; i < termLenLALR; i++) {
        cout << "," << terminalLALR[i];
    }
    puts("");
    for (i = 0; i < nontermLenLALR; i++) {
        calcfirstLALR(i);
        cout << "\nfirstLALR(" << nonterminalLALR[i] << ") = { ";
        for (j = 0; j < termLenLALR; j++) {
            if (firstLALR[i][j])
                break;
        }
        if (j < termLenLALR) {
            cout << terminalLALR[j];
            j++;
            for (; j < termLenLALR; j++) {
                if (firstLALR[i][j])
                    cout << " ," << terminalLALR[j];
            }
        }
        cout << " }\n";
    }
    terminalLALR[termLenLALR] = '$';
    termLenLALR++;
    followLALR[0][termLenLALR - 1] = 1;
    for (i = 0; i < nontermLenLALR; i++) {
        calcfollowLALR(i);
        cout << "\nfollowLALR(" << nonterminalLALR[i] << ") = { ";
        for (j = 0; j < termLenLALR; j++) {
            if (followLALR[i][j])
                break;
        }
        if (j < termLenLALR) {
            cout << terminalLALR[j];
            j++;
            for (; j < termLenLALR; j++) {
                if (followLALR[i][j])
                    cout << " ," << terminalLALR[j];
            }
        }
        cout << " }\n";
    }
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            sprintf(actionLALR[i][j], "\0");
            go_to_lalr[i][j] = -1;
        }
    }
    sprintf(rulesLALR[ruleCountLALR], "X->%c\0", rulesLALR[0][0]); //New initial symbol
    ruleCountLALR++;
    cout << "\n-----------------------------------------------\n";
    cout << "\ncanonicalLALR Collection";
    canonicalLALR[0][ruleCountLALR - 1][3][termLenLALR - 1] = 1;
    closure(canonicalLALR[0]);
    canLenLALR++;
    puts("");
    print(0);
    flag = 1;
    while (flag) {
        flag = 0;
        for (i = 0; i < canLenLALR; i++) {
            for (j = 0; j < nontermLenLALR; j++) {
                if (Goto(i, j, 1)) {
                    cout << "\nGOTO(I" << i << ", " << nonterminalLALR[j] << ") ";
                    print(canLenLALR - 1);
                    flag = 1;
                }
            }
            for (j = 0; j < termLenLALR - 1; j++) {
                if (Goto(i, j, 0)) {
                    cout << "\nGOTO(I" << i << ", " << terminalLALR[j] << ") ";
                    print(canLenLALR - 1);
                    flag = 1;
                }
            }
        }
    }
    if (lalr) {
        puts("\nGrammar is LALR(1)");
        cout << "\n-----------------------------------------------\n";
        for (i = 0; i < canLenLALR; i++) {
            if (!eqItems[i]) {
                eqItems[i] = i;
                for (j = i + 1; j < canLenLALR; j++) {
                    flag = 1;
                    for (k = 0; k < ruleCountLALR; k++) {
                        for (l = 0; l < 10; l++) {
                            flg1 = flg2 = 0;
                            for (m = 0; m < termLenLALR; m++) {
                                if (canonicalLALR[i][k][l][m])
                                    flg1 = 1;
                                if (canonicalLALR[j][k][l][m])
                                    flg2 = 1;
                            }
                            if (flg1 != flg2) {
                                flag = 0;
                                break;
                            }
                        }
                        if (!flag)
                            break;
                    }
                    if (flag)
                        eqItems[j] = i;
                }
            }
        }
        printf("\nItems which are found to be same =\n");
        for (i = 0; i < canLenLALR; i++) {
            if (eqItems[i] == i) {
                flag = 0;
                for (j = i + 1; j < canLenLALR; j++) {
                    if (eqItems[j] == i) {
                        if (!flag) {
                            cout << i << "," << j;
                            flag = 1;
                        }
                        else
                            cout << ", " << j;
                    }
                }
                if (flag)
                    puts("");
            }
        }
        cout << "\nSo we combine these items to form single item\n";
        cout << "\n-----------------------------------------------\n";
        cout << "\nLALR Parsing Table\n\n";
        cout << "State\t|\tactionLALR\t";
        for (i = 0; i < termLenLALR - 2; i++)
            printf("\t");
        cout << "|\tGoto\n";
        cout << "------------------------------------------------------\n\t|";
        for (i = 0; i < termLenLALR; i++) {
            cout << terminalLALR[i] << "\t";
        }
        cout << "|";
        for (i = 0; i < nontermLenLALR; i++) {
            cout << nonterminalLALR[i] << "\t";
        }
        cout << "\n------------------------------------------------------\n";
        for (i = 0; i < canLenLALR; i++) {
            if (eqItems[i] == i) {
                printAlt(i);
                cout << "\t|";
                for (j = 0; j < termLenLALR; j++) {
                    if (actionLALR[i][j][0] == 's') {
                        sscanf(actionLALR[i][j], "s%d", &k);
                        cout << "s";
                        printAlt(k);
                        cout << "\t";
                    }
                    else if (actionLALR[i][j][0] == 'r' || actionLALR[i][j][0] == '\0') {
                        flag = 0;
                        k = eqItems[i];
                        for (l = 0; l < canLenLALR; l++) {
                            if (eqItems[l] == k && actionLALR[l][j][0] == 'r') {
                                if (!flag) {
                                    cout << actionLALR[l][j];
                                    flag = 1;
                                }
                                else
                                    cout << actionLALR[l][j] + 1;
                            }
                        }
                        cout << "\t";
                    }
                    else
                        cout << actionLALR[i][j] << "\t";
                }
                cout << "|";
                for (j = 0; j < nontermLenLALR; j++) {
                    if (go_to_lalr[i][j] != -1)
                        cout << go_to_lalr[i][j];
                    cout << "\t";
                }
                puts("");
            }
        }
        return "Yes";
    }
    else {
        puts("\nGrammar is not LALR(1)");
        return "No";
    }
}
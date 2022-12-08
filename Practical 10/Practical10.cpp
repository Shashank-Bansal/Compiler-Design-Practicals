#include <bits/stdc++.h>

using namespace std;

char rules[100][100], terminals[100], nonTerminals[100], action[100][100][100];
int termLen, nonTermLen, first[100][100], follow[100][100], hash1[100];
int ruleCount, hash2[100], canonical[100][20][10][10], canLen, go_to[100][100], eqItems[100], lalr;

void calcFirst(int k) {
    int j, flag = 0, len, l, m, i;
    if (hash1[k])
        return;
    hash1[k] = 1;
    for (i = 0; i < ruleCount; i++) {
        if (rules[i][0] == nonTerminals[k]) {
            flag = 0;
            len = strlen(rules[i]);
            for (j = 3; j < len; j++) {
                if (!flag) {
                    if (rules[i][j] >= 'A' && rules[i][j] <= 'Z') {
                        for (l = 0; l < nonTermLen; l++) {
                            if (nonTerminals[l] == rules[i][j])
                                break;
                        }
                        flag = 1;
                        if (hash1[l]) {
                            for (m = 0; m < termLen; m++) {
                                if (first[l][m]) {
                                    first[k][m] = 1;
                                    if (terminals[m] == '^')
                                        flag = 0;
                                }
                            }
                        }
                        else {
                            calcFirst(l);
                            for (m = 0; m < termLen; m++) {
                                if (first[l][m]) {
                                    first[k][m] = 1;
                                    if (terminals[m] == '^')
                                        flag = 0;
                                }
                            }
                        }
                    }
                    else if (rules[i][j] != '|') {
                        for (l = 0; l < termLen; l++) {
                            if (terminals[l] == rules[i][j])
                                break;
                        }
                        first[k][l] = 1;
                        flag = 1;
                    }
                }
                else {
                    if (rules[i][j] == '|')
                        flag = 0;
                }
            }
        }
    }
}

void calcFollow(int k) {
    int i, len, j, l, flag = 0, m;
    if (hash2[k])
        return;
    hash2[k] = 1;
    for (i = 0; i < ruleCount; i++) {
        len = strlen(rules[i]);
        for (j = 3; j < len; j++) {
            if (flag) {
                if (rules[i][j] >= 'A' && rules[i][j] <= 'Z') {
                    flag = 0;
                    for (l = 0; l < nonTermLen; l++) {
                        if (nonTerminals[l] == rules[i][j])
                            break;
                    }
                    if (l < nonTermLen) {
                        for (m = 0; m < termLen; m++) {
                            if (first[l][m]) {
                                follow[k][m] = 1;
                                if (terminals[m] == '^')
                                    flag = 1;
                            }
                        }
                    }
                }
                else {
                    for (l = 0; l < termLen; l++) {
                        if (terminals[l] == rules[i][j])
                            break;
                    }
                    if (l < termLen) {
                        follow[k][l] = 1;
                    }
                    else {
                        if (rules[i][j] == '|') {
                            for (l = 0; l < nonTermLen; l++) {
                                if (nonTerminals[l] == rules[i][0])
                                    break;
                            }
                            if (l < nonTermLen) {
                                calcFollow(l);
                                for (m = 0; m < termLen; m++)
                                {
                                    if (follow[l][m])
                                        follow[k][m] = 1;
                                }
                            }
                            flag = 0;
                        }
                    }
                    flag = 0;
                }
            }
            if (rules[i][j] == nonTerminals[k]) {
                flag = 1;
            }
        }
        if (flag) {
            for (l = 0; l < nonTermLen; l++) {
                if (nonTerminals[l] == rules[i][0])
                    break;
            }
            if (l < nonTermLen) {
                calcFollow(l);
                for (m = 0; m < termLen; m++) {
                    if (follow[l][m])
                        follow[k][m] = 1;
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
        for (k = 0; k < termLen; k++) {
            if (canonical[in][ruleCount - 1][i][k]) {
                if (!prnt) {
                    len = strlen(rules[ruleCount - 1]);
                    for (j = 0; j <= len; j++) {
                        if (j == i)
                            cout << ".";
                        cout << rules[ruleCount - 1][j];
                    }
                    cout << "," << terminals[k];
                    prnt = 1;
                }
                else
                    cout << "|" << terminals[k];
            }
        }
        if (prnt)
            puts("");
    }
    for (l = 0; l < ruleCount - 1; l++) {
        for (i = 0; i < 10; i++) {
            prnt = 0;
            for (k = 0; k < termLen; k++) {
                if (canonical[in][l][i][k]) {
                    if (!prnt) {
                        len = strlen(rules[l]);
                        for (j = 0; j <= len; j++) {
                            if (j == i)
                                cout << ".";
                            cout << rules[l][j];
                        }
                        cout << "," << terminals[k];
                        prnt = 1;
                    }
                    else
                        cout << "|" << terminals[k];
                }
            }
            if (prnt)
                puts("");
        }
    }
}

void firstCalc(char *str, int *arr) {
    int j, flag = 0, len, l, m, i, k;
    len = strlen(str);
    for (j = 0; j < len; j++) {
        if (!flag) {
            if (str[j] >= 'A' && str[j] <= 'Z') {
                for (l = 0; l < nonTermLen; l++) {
                    if (nonTerminals[l] == str[j])
                        break;
                }
                flag = 1;
                for (m = 0; m < termLen; m++) {
                    if (first[l][m]) {
                        arr[m] = 1;
                        if (terminals[m] == '^')
                            flag = 0;
                    }
                }
            }
            else if (str[j] != '|') {
                for (l = 0; l < termLen; l++) {
                    if (terminals[l] == str[j])
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
        for (i = 0; i < ruleCount; i++) {
            for (k = 0; k < 10; k++) {
                for (n = 0; n < 10; n++) {
                    if (arr[i][k][n]) {
                        c = rules[i][k];
                        for (j = 0; j < ruleCount; j++) {
                            if (rules[j][0] == c) {
                                for (m = 0; m < 10; m++)
                                    arr1[m] = 0;
                                for (m = k + 1; rules[i][m] != '\0'; m++) {
                                    str[m - k - 1] = rules[i][m];
                                }
                                str[m - k - 1] = terminals[n];
                                str[m - k] = '\0';
                                firstCalc(str, arr1);
                                for (m = 0; m < termLen; m++) {
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
    for (i = 0; i < ruleCount; i++) {
        for (j = 0; j < 10; j++) {
            for (k = 0; k < termLen; k++) {
                if (canonical[in][i][j][k]) {
                    if (nt) {
                        if (rules[i][j] == nonTerminals[sym]) {
                            arr[i][j + 1][k] = 1;
                            flg = 1;
                        }
                    }
                    else if (rules[i][j] == terminals[sym]) {
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
    for (j = 0; j < canLen; j++) {
        flg = 0;
        for (k = 0; k < ruleCount; k++) {
            for (l = 0; l < 10; l++) {
                for (i = 0; i < termLen; i++) {
                    if (canonical[j][k][l][i] != arr[k][l][i]) {
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
        for (j = 0; j < ruleCount; j++) {
            for (l = 0; l < 10; l++) {
                for (i = 0; i < termLen; i++)
                    canonical[canLen][j][l][i] = arr[j][l][i];
            }
        }
        ans = canLen;
        canLen++;
    }
    if (nt)
        go_to[in][sym] = ans;
    else {
        if (action[in][sym][0] == '\0')
            sprintf(action[in][sym], "s%d\0", ans);
        else {
            sscanf(action[in][sym], "s%d", &k);
            if (k != ans) {
                lalr = 0;
                len = strlen(action[in][sym]);
                sprintf(action[in][sym] + len, ",s%d", ans);
            }
        }
    }
    if (flg) {
        for (i = 0; i < ruleCount; i++) {
            len = strlen(rules[i]);
            for (j = 0; j < 10; j++) {
                for (l = 0; l < termLen; l++) {
                    if (arr[i][j][l] && j == len) {
                        if (i == ruleCount - 1)
                            sprintf(action[canLen - 1][termLen - 1], "acc\0");
                        else {
                            if (action[canLen - 1][l][0] == '\0')
                                sprintf(action[canLen - 1][l], "r%d\0", i + 1);
                            else {
                                sscanf(action[canLen - 1][l], "r%d", &k);
                                if (k != i + 1) {
                                    lalr = 0;
                                    len = strlen(action[canLen - 1][l]);
                                    sprintf(action[canLen - 1][l] + len, "r%d\0", i + 1);
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
    for (i = 0; i < canLen; i++) {
        if (eqItems[i] == in)
            cout << i;
    }
}

int main()
{
    int i, j, len, k, a, b, t, flag, l, m, flg1, flg2;
    char c, temp[100];
    lalr = 1;
    canLen = 0;
    termLen = nonTermLen = 0;
    cout << "\n----------------LALR PARSER----------------\n";
    cout << "Enter the number of Production Rules = ";
    cin >> ruleCount;
    cout << "\n";
    cout << "Enter the Rules in form (S->ABc) = " << endl;
    for (i = 0; i < ruleCount; i++) {
        scanf("%s", &rules[i]);
        len = strlen(rules[i]);
        for (j = 0; j < len; j++) {
            if (rules[i][j] >= 'A' && rules[i][j] <= 'Z') {
                for (k = 0; k < nonTermLen; k++) {
                    if (nonTerminals[k] == rules[i][j])
                        break;
                }
                if (k == nonTermLen) {
                    nonTerminals[nonTermLen] = rules[i][j];
                    nonTermLen++;
                }
            }
            else if (rules[i][j] != '-' && rules[i][j] != '>' && rules[i][j] != '|') {
                for (k = 0; k < termLen; k++) {
                    if (terminals[k] == rules[i][j])
                        break;
                }
                if (k == termLen) {
                    terminals[termLen] = rules[i][j];
                    termLen++;
                }
            }
        }
    }
    cout << "\nSet of Non terminals => ";
    cout << nonTerminals[0];
    for (i = 1; i < nonTermLen; i++) {
        cout << "," << nonTerminals[i];
    }
    puts("");
    cout << "\nSet of terminals => ";
    cout << terminals[0];
    for (i = 1; i < termLen; i++) {
        cout << "," << terminals[i];
    }
    puts("");
    for (i = 0; i < nonTermLen; i++) {
        calcFirst(i);
        cout << "\nFIRST(" << nonTerminals[i] << ") = { ";
        for (j = 0; j < termLen; j++) {
            if (first[i][j])
                break;
        }
        if (j < termLen) {
            cout << terminals[j];
            j++;
            for (; j < termLen; j++) {
                if (first[i][j])
                    cout << " ," << terminals[j];
            }
        }
        cout << " }\n";
    }
    terminals[termLen] = '$';
    termLen++;
    follow[0][termLen - 1] = 1;
    for (i = 0; i < nonTermLen; i++) {
        calcFollow(i);
        cout << "\nFOLLOW(" << nonTerminals[i] << ") = { ";
        for (j = 0; j < termLen; j++) {
            if (follow[i][j])
                break;
        }
        if (j < termLen) {
            cout << terminals[j];
            j++;
            for (; j < termLen; j++) {
                if (follow[i][j])
                    cout << " ," << terminals[j];
            }
        }
        cout << " }\n";
    }
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            sprintf(action[i][j], "\0");
            go_to[i][j] = -1;
        }
    }
    sprintf(rules[ruleCount], "X->%c\0", rules[0][0]); //New initial symbol
    ruleCount++;
    cout << "\n-----------------------------------------------\n";
    cout << "\nCanonical Collection";
    canonical[0][ruleCount - 1][3][termLen - 1] = 1;
    closure(canonical[0]);
    canLen++;
    puts("");
    print(0);
    flag = 1;
    while (flag) {
        flag = 0;
        for (i = 0; i < canLen; i++) {
            for (j = 0; j < nonTermLen; j++) {
                if (Goto(i, j, 1)) {
                    cout << "\nGOTO(I" << i << ", " << nonTerminals[j] << ") ";
                    print(canLen - 1);
                    flag = 1;
                }
            }
            for (j = 0; j < termLen - 1; j++) {
                if (Goto(i, j, 0)) {
                    cout << "\nGOTO(I" << i << ", " << terminals[j] << ") ";
                    print(canLen - 1);
                    flag = 1;
                }
            }
        }
    }
    if (lalr) {
        puts("\nGrammar is LALR(1)");
        cout << "\n-----------------------------------------------\n";
        for (i = 0; i < canLen; i++) {
            if (!eqItems[i]) {
                eqItems[i] = i;
                for (j = i + 1; j < canLen; j++) {
                    flag = 1;
                    for (k = 0; k < ruleCount; k++) {
                        for (l = 0; l < 10; l++) {
                            flg1 = flg2 = 0;
                            for (m = 0; m < termLen; m++) {
                                if (canonical[i][k][l][m])
                                    flg1 = 1;
                                if (canonical[j][k][l][m])
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
        for (i = 0; i < canLen; i++) {
            if (eqItems[i] == i) {
                flag = 0;
                for (j = i + 1; j < canLen; j++) {
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
        cout << "State\t|\tAction\t";
        for (i = 0; i < termLen - 2; i++)
            printf("\t");
        cout << "|\tGoto\n";
        cout << "------------------------------------------------------\n\t|";
        for (i = 0; i < termLen; i++) {
            cout << terminals[i] << "\t";
        }
        cout << "|";
        for (i = 0; i < nonTermLen; i++) {
            cout << nonTerminals[i] << "\t";
        }
        cout << "\n------------------------------------------------------\n";
        for (i = 0; i < canLen; i++) {
            if (eqItems[i] == i) {
                printAlt(i);
                cout << "\t|";
                for (j = 0; j < termLen; j++) {
                    if (action[i][j][0] == 's') {
                        sscanf(action[i][j], "s%d", &k);
                        cout << "s";
                        printAlt(k);
                        cout << "\t";
                    }
                    else if (action[i][j][0] == 'r' || action[i][j][0] == '\0') {
                        flag = 0;
                        k = eqItems[i];
                        for (l = 0; l < canLen; l++) {
                            if (eqItems[l] == k && action[l][j][0] == 'r') {
                                if (!flag) {
                                    cout << action[l][j];
                                    flag = 1;
                                }
                                else
                                    cout << action[l][j] + 1;
                            }
                        }
                        cout << "\t";
                    }
                    else
                        cout << action[i][j] << "\t";
                }
                cout << "|";
                for (j = 0; j < nonTermLen; j++) {
                    if (go_to[i][j] != -1)
                        cout << go_to[i][j];
                    cout << "\t";
                }
                puts("");
            }
        }
    }
    else {
        puts("\nGrammar is not LALR(1)");
    }
    return 0;
}
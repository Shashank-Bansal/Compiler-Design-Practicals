// 3

// E->aE
// E->Ec
// E->ac

// aaca
// y

// caca
// n

#include <conio.h>
#include <iostream>
#include <string.h>

using namespace std;
struct grammar{
    char p[20];
    char prod[20];
} g[10];

int main() {
    int i, stpos, j, k, l, m, o, p, f, r;
    int np, tspos, cr;
    cout << "---Check whether a given string is parsed by CFG or not---";
    cout << "\nEnter Number of productions:";
    cin >> np;
    char sc, ts[10];
    cout << "\nEnter productions:\n";
    for (i = 0; i < np; i++) {
        cin >> ts;
        strncpy(g[i].p, ts, 1); // lhs
        strcpy(g[i].prod, &ts[3]);
    } // after>
l:
    char ip[10];
    cout << "\nEnter Input:";
    cin >> ip;            // aab
    int lip = strlen(ip); // 3
    char stack[10];
    stpos = 0;
    i = 0;
    // moving input
    sc = ip[i];        // a
    stack[stpos] = sc; // stack[0]=a
    i++;
    stpos++; // 1,
    do {
        r = 1;
        while (r != 0) {
            r = 0;
            // try reducing
            for (k = 0; k < stpos; k++) {
                f = 0;
                for (l = 0; l < 10; l++) // l from 1 to 10
                    ts[l] = '\0';
                tspos = 0;
                for (l = k; l < stpos; l++) {
                    // removing first caharcter//k=0,1,l=0,1
                    ts[tspos] = stack[l]; // ts[01]=aa
                    tspos++;              // 2}
                    // now compare each possibility with production
                    for (m = 0; m < np; m++) 
                        cr = strcmp(ts, g[m].prod); // a,aS
                        // if cr is zero then match is found
                        if (cr == 0) {
                            for (l = k; l < 10; l++)
                            { // removing matched part from stack
                                stack[l] = '\0';
                                stpos--;
                            }
                            stpos = k; // 0
                            // concatinate the string
                            strcat(stack, g[m].p);
                            stpos++;
                            r = 2;
                        }
                }
            }
            // moving input
            sc = ip[i];        // b
            stack[stpos] = sc; // stack[2]=b
            i++;
            stpos++; // 3,3
        }
        // 3,3
    } while (strlen(stack) != 1 && stpos <= lip);

    if (strlen(stack) == 1)
        cout << "\nThe string can be parsed";
    else
        cout << "\nThe string cannot be parsed";
        
    cout << "\n\nWant to check another string for the grammar:(y/n) ";
    char op;
    cin >> op;

    if (op == 'y')
        goto l;

    return 0;
}
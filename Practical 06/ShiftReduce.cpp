// Including Libraries
#include <bits/stdc++.h>
using namespace std;

// Global Variables
int z = 0, i = 0, j = 0, c = 0;

int  *ptr = NULL;

// Modify array size to increase
// length of string to be parsed
char a[16], ac[20], tc[20], fc[20], stk[15], act[10];

// This Function will check whether
// the stack contain a production rule
// which is to be Reduce.
// Rules can be E->2E2 , E->3E3 , E->4
void check()
{
    // Copying string to be printed as action
    strcpy(ac, "REDUCE TO E -> ");
    strcpy(tc, "REDUCE TO T -> ");
    strcpy(fc, "REDUCE TO F -> ");

    // c=length of input string
    for (z = 0; z < c; z++)
    {
        // checking for producing rule E->4
        if (stk[z] == 'a')
        {
            printf("%sa", fc);
            stk[z] = 'F';
            // stk[z + 1] = '\0';

            // printing action
            printf("\n$%s\t\t%s$\t\t", stk, a);
        }
    }

    for (z = 0; z < c - 2; z++)
    {
        // checking for another production
        if (stk[z] == 'E' && stk[z + 1] == '+' &&
            stk[z + 2] == 'T')
        {
            printf("%sE+T", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            for (i = z + 3; i < c; i++)
            {
                stk[z+1] = stk[i];
                z++;
            }
            printf("\n$%s\t\t%s$\t\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++)
    {
        // checking for E->3E3
        if (stk[z] == 'T' && stk[z + 1] == '*' &&
            stk[z + 2] == 'F')
        {
            printf("%sT*F", tc);
            stk[z] = 'T';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            for (i = z + 3; i < c; i++)
            {
                stk[z+1] = stk[i];
                z++;
            }
            printf("\n$%s\t\t%s$\t\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++)
    {
        // checking for E->3E3
        if (stk[z] == '(' && stk[z + 1] == 'E' &&
            stk[z + 2] == ')')
        {
            printf("%s(E)", fc);
            stk[z] = 'F';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            for (i = z + 3; i < c; i++)
            {
                stk[z+1] = stk[i];
                z++;
            }
            printf("\n$%s\t\t%s$\t\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c; z++)
    {
        // checking for producing rule E->4
        if (stk[z] == 'T')
        {
            printf("%sT", ac);
            stk[z] = 'E';
            // stk[z + 1] = '\0';

            // printing action
            printf("\n$%s\t\t%s$\t\t", stk, a);
        }
    }
    
    for (z = 0; z < c; z++)
    {
        // checking for producing rule E->4
        if (stk[z] == 'F')
        {
            printf("%sF", tc);
            stk[z] = 'T';
            // stk[z + 1] = '\0';
            // printing action
            printf("\n$%s\t\t%s$\t\t", stk, a);
        }
    }
    return; // return to main
}

// Driver Function
int main()
{
    printf("GRAMMAR is -\nE->E+T | T \nT->T*F | F \nF->(E) | a\n");

    cout << endl << "Enter the string to be parsed : ";
    cin >> a;

    // a is input string
    // strcpy(a, "(a+a)*a");

    // strlen(a) will return the length of a to c
    c = strlen(a);

    // "SHIFT" is copied to act to be printed
    strcpy(act, "SHIFT");

    // This will print Labels (column name)
    // This will print the initial
    // values of stack and input
    cout << "\nStack Implementation:\n";
    cout << "\nStack\t\tRemaining Input\t\tAction ";
    cout << "\n-----------------------------------------------------\n";
    printf("\n$\t\t%s$\t\t", a);
    // This will Run upto length of input string
    for (i = 0; j < c; i++, j++)
    {
        // Printing action
        printf("%s", act);

        // Pushing into stack
        stk[i] = a[j];
        stk[i + 1] = '\0';

        // Moving the pointer
        a[j] = ' ';

        // Printing action
        printf("\n$%s\t\t%s$\t\t", stk, a);

        // Call check function ..which will
        // check the stack whether its contain
        // any production or not
        check();
    }

    // Rechecking last time if contain
    // any valid production then it will
    // replace otherwise invalid
    check();

    // if top of the stack is E(starting symbol)
    // then it will accept the input
    if (stk[0] == 'E' && stk[1] == '\0')
        printf("Accept\n");
    else // else reject
        printf("Reject\n");
}
// This code is contributed by Shubhamsingh10

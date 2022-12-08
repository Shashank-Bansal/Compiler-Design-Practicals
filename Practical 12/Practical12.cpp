#include <iostream>
// #include <stdio.h>
// #include <conio.h>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

char op[2], arg1[5], arg2[5], result[5];
int main() {
  string input;
  cout << "\nEnter the Code\n";

  FILE *fp1, *fp2;
  fp1 = fopen("input.txt", "r");
  char c;
  c = fgetc(fp1);
  while (c != EOF) {
      printf ("%c", c);
      c = fgetc(fp1);
  }
  fclose(fp1);
  fp1 = fopen("input.txt", "r");
  fp2 = fopen("output.txt", "w");
  while (!feof(fp1)) {
    fscanf(fp1, "%s%s%s%s", op, arg1, arg2, result);
    if (strcmp(op, "+") == 0) {
      fprintf(fp2, "\nMOV R0,%s", arg1);
      fprintf(fp2, "\nADD R0,%s", arg2);
      fprintf(fp2, "\nMOV %s,R0", result);
    }
    if (strcmp(op, "*") == 0) {
      fprintf(fp2, "\nMOV R0,%s", arg1);
      fprintf(fp2, "\nMUL R0,%s", arg2);
      fprintf(fp2, "\nMOV %s,R0", result);
    }
    if (strcmp(op, "-") == 0) {
      fprintf(fp2, "\nMOV R0,%s", arg1);
      fprintf(fp2, "\nSUB R0,%s", arg2);
      fprintf(fp2, "\nMOV %s,R0", result);
    }
    if (strcmp(op, "/") == 0) {
      fprintf(fp2, "\nMOV R0,%s", arg1);
      fprintf(fp2, "\nDIV R0,%s", arg2);
      fprintf(fp2, "\nMOV %s,R0", result);
    }
    if (strcmp(op, "=") == 0) {
      fprintf(fp2, "\nMOV R0,%s", arg1);
      fprintf(fp2, "\nMOV %s,R0", result);
    }
  }
  fclose(fp1);
  cout << "\n\nOutput:" << endl;
  fclose(fp2);
  fp2 = fopen("output.txt", "r");
  c = fgetc(fp2);
  while (c != EOF) {
      printf ("%c", c);
      c = fgetc(fp2);
  }
  fclose(fp2);
  cout << endl << endl;
}
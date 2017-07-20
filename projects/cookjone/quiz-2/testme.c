#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void inputChar(char *character) {
    // selecting random characters from 'Space' to '~' on the ASCII table
    int min = 32; // 'Space'
    int max = 126; // '~'
    int delta = max - min;
    *character = (rand() % (delta + 1)) + min;
}

void inputString(char string[]) {
    // selecting random characters from 'a' to 'z' on the ASCII table
    int min = 97; // 'a'
    int max = 122; // 'z'
    int delta = max - min;
    int i;
    for (i = 0; i < 5; i++) {
        string[i] = (rand() % (delta + 1)) + min;
    }
}

void testme() {
    int tcCount = 0;
    char s[] = "tempy";
    char c;
    char *cPtr = &c;
    int state = 0;
    while (1) {
        tcCount++;
        inputChar(cPtr);
        inputString(s);
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' '&& state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' &&
            s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9) {
            printf("error ");
            exit(200);
        }
    }
}


int main(int argc, char *argv[]) {
    srand(time(NULL));
    testme();
    return 0;
}

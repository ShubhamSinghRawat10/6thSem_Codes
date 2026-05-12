#include <stdio.h>
#include <string.h>

char input[100];
int i = 0;
int level = 0;

void printSpace() {
    for(int j = 0; j < level; j++) {
        printf("  ");
    }
}

void A();

void S() {
    printSpace();
    printf("S\n");
    level++;

    A();

    level--;
}

void A() {
    printSpace();
    printf("A\n");
    level++;

    if(input[i] == 'a') {
        printSpace();
        printf("a\n");
        i++;
        A();
    }
    else if(input[i] == 'b') {
        printSpace();
        printf("b\n");
        i++;
    }
    else {
        printf("Error: Invalid string\n");
    }

    level--;
}

int main() {
    printf("Enter string: ");
    scanf("%s", input);

    printf("\nParse Tree:\n");
    S();

    if(input[i] == '\0')
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}
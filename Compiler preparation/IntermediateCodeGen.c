#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX][MAX];
int top = -1;
int tempCount = 1;

void push(char *str) {
    strcpy(stack[++top], str);
}

char* pop() {
    return stack[top--];
}

void newTemp(char *temp) {
    sprintf(temp, "t%d", tempCount++);
}

int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void generateTAC(char *expr) {
    char opStack[MAX];
    int opTop = -1;

    for(int i = 0; expr[i] != '\0'; i++) {

        if(isalnum(expr[i])) {

            char operand[10];

            operand[0] = expr[i];

            operand[1] = '\0';

            push(operand);
        }

        else if(expr[i] == '(') {

            opStack[++opTop] = expr[i];
        }

        else if(expr[i] == ')') {

            while(opTop >= 0 && opStack[opTop] != '(') {

                char op = opStack[opTop--];

                char *op2 = pop();

                char *op1 = pop();

                char temp[10];

                newTemp(temp);

                printf("%s = %s %c %s\n", temp, op1, op, op2);

                push(temp);
            }

            opTop--;
        }

        else if(isOperator(expr[i])) {

            while(opTop >= 0 && precedence(opStack[opTop]) >= precedence(expr[i])) {

                char op = opStack[opTop--];

                char *op2 = pop();

                char *op1 = pop();

                char temp[10];

                newTemp(temp);

                printf("%s = %s %c %s\n", temp, op1, op, op2);

                push(temp);
            }

            opStack[++opTop] = expr[i];
        }
    }

    while(opTop >= 0) {

        char op = opStack[opTop--];

        char *op2 = pop();

        char *op1 = pop();

        char temp[10];

        newTemp(temp);

        printf("%s = %s %c %s\n", temp, op1, op, op2);

        push(temp);
    }
}

int main() {

    char expr[MAX];

    printf("Enter expression: ");

    scanf("%s", expr);

    printf("\nThree Address Code:\n");

    generateTAC(expr);

    return 0;
}
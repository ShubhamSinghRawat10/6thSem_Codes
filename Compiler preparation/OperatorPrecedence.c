#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char productions[MAX][MAX];
char terminals[MAX][10];
char precedence[MAX][MAX];

char stack[50][10];
int top = -1;

int tcount = 0;

/* Check terminal */
int isTerminal(char *str) {
    int i;
    for (i = 0; i < tcount; i++) {
        if (strcmp(terminals[i], str) == 0)
            return 1;
    }
    return 0;
}

/* Add terminal */
void addTerminal(char *str) {
    if (!isTerminal(str)) {
        strcpy(terminals[tcount], str);
        tcount++;
    }
}

/* Extract terminals */
void extractTerminals(int n) {
    int i, j;
    char temp[10];

    for (i = 0; i < n; i++) {
        for (j = 0; productions[i][j] != '\0'; j++) {

            if (productions[i][j] == 'i' && productions[i][j+1] == 'd') {
                addTerminal("id");
                j++;
            }
            else if (!isupper(productions[i][j]) &&
                     productions[i][j] != '-' &&
                     productions[i][j] != '>' &&
                     productions[i][j] != '|') {

                temp[0] = productions[i][j];
                temp[1] = '\0';
                addTerminal(temp);
            }
        }
    }
    addTerminal("$");
}

/* Get index */
int getIndex(char *str) {
    int i;
    for (i = 0; i < tcount; i++) {
        if (strcmp(terminals[i], str) == 0)
            return i;
    }
    return -1;
}

/* Initialize table */
void initTable() {
    int i, j;
    for (i = 0; i < tcount; i++)
        for (j = 0; j < tcount; j++)
            precedence[i][j] = 'e';
}

/* Build precedence table (fixed for +, *, id) */
void buildTable() {
    int i;

    for (i = 0; i < tcount; i++) {
        int j;
        for (j = 0; j < tcount; j++) {

            if (strcmp(terminals[i], "+") == 0 &&
                strcmp(terminals[j], "+") == 0)
                precedence[i][j] = '>';

            else if (strcmp(terminals[i], "+") == 0 &&
                     strcmp(terminals[j], "*") == 0)
                precedence[i][j] = '<';

            else if (strcmp(terminals[i], "*") == 0 &&
                     strcmp(terminals[j], "+") == 0)
                precedence[i][j] = '>';

            else if (strcmp(terminals[i], "*") == 0 &&
                     strcmp(terminals[j], "*") == 0)
                precedence[i][j] = '>';

            else if (strcmp(terminals[j], "id") == 0)
                precedence[i][j] = '<';

            else if (strcmp(terminals[i], "id") == 0)
                precedence[i][j] = '>';
        }
    }

    /* $ handling */
    for (i = 0; i < tcount; i++) {
        precedence[getIndex("$")][i] = '<';
        precedence[i][getIndex("$")] = '>';
    }
    precedence[getIndex("$")][getIndex("$")] = '=';
}

/* Display table */
void displayTable() {
    int i, j;

    printf("\nPrecedence Table:\n    ");
    for (i = 0; i < tcount; i++)
        printf("%5s", terminals[i]);

    printf("\n");

    for (i = 0; i < tcount; i++) {
        printf("%5s", terminals[i]);
        for (j = 0; j < tcount; j++) {
            printf("%5c", precedence[i][j]);
        }
        printf("\n");
    }
}

/* Stack operations */
void push(char *str) {
    top++;
    strcpy(stack[top], str);
}

void pop() {
    top--;
}

char* getTopTerminal() {
    int i;
    for (i = top; i >= 0; i--) {
        if (isTerminal(stack[i]))
            return stack[i];
    }
    return "$";
}

/* Tokenize input */
int getNextToken(char input[], int *pos, char token[]) {

    if (input[*pos] == '\0')
        return 0;

    if (input[*pos] == 'i' && input[*pos+1] == 'd') {
        strcpy(token, "id");
        *pos += 2;
    } else {
        token[0] = input[*pos];
        token[1] = '\0';
        (*pos)++;
    }
    return 1;
}

/* Reduce */
void reduce() {

    if (strcmp(stack[top], "id") == 0) {
        strcpy(stack[top], "E");
        printf("Reduce: E -> id\n");
    }
    else if (top >= 2 &&
             strcmp(stack[top], "E") == 0 &&
             strcmp(stack[top-1], "+") == 0 &&
             strcmp(stack[top-2], "E") == 0) {

        pop(); pop(); pop();
        push("E");
        printf("Reduce: E -> E+E\n");
    }
    else if (top >= 2 &&
             strcmp(stack[top], "E") == 0 &&
             strcmp(stack[top-1], "*") == 0 &&
             strcmp(stack[top-2], "E") == 0) {

        pop(); pop(); pop();
        push("E");
        printf("Reduce: E -> E*E\n");
    }
}

/* Display stack */
void displayStack() {
    int i;
    for (i = 0; i <= top; i++)
        printf("%s", stack[i]);
}

/* Parsing */
void parse(char input[]) {
    int pos = 0;
    char token[10];
    char *a, *b;

    push("$");
    getNextToken(input, &pos, token);

    printf("\nStack\tInput\tAction\n");

    while (1) {
        displayStack();
        printf("\t%s\t", input + pos);

        a = getTopTerminal();
        b = token;

        if (strcmp(a, "$") == 0 && strcmp(b, "$") == 0) {
            printf("Accept\n");
            break;
        }

        if (precedence[getIndex(a)][getIndex(b)] == '<' ||
            precedence[getIndex(a)][getIndex(b)] == '=') {

            printf("Shift %s\n", b);
            push(b);
            getNextToken(input, &pos, token);
        }
        else if (precedence[getIndex(a)][getIndex(b)] == '>') {
            printf("Reduce\n");
            reduce();
        }
        else {
            printf("Error\n");
            break;
        }
    }
}

int main() {
    int n, i;
    char input[50];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");
    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    extractTerminals(n);
    initTable();
    buildTable();
    displayTable();

    printf("\nEnter input (e.g., id+id*id$): ");
    scanf("%s", input);

    parse(input);

    return 0;
}

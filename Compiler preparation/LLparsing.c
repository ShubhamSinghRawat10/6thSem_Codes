#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char productions[MAX][MAX];
char first[MAX][MAX], follow[MAX][MAX];
int n;

// Check if character exists in set
int contains(char *set, char c) {
    int i;
    for (i = 0; set[i] != '\0'; i++) {
        if (set[i] == c) return 1;
    }
    return 0;
}

// Add character to set
void addToSet(char *set, char c) {
    int len;
    if (!contains(set, c)) {
        len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// FIRST calculation
void findFirst(char c, int index) {
    int i;

    if (!isupper(c)) {
        addToSet(first[index], c);
        return;
    }

    for (i = 0; i < n; i++) {
        if (productions[i][0] == c) {
            if (productions[i][2] == '#') {
                addToSet(first[index], '#'); // epsilon
            } else {
                findFirst(productions[i][2], index);
            }
        }
    }
}

// FOLLOW calculation
void findFollow(char c, int index) {
    int i, j;

    if (productions[0][0] == c) {
        addToSet(follow[index], '$'); // start symbol
    }

    for (i = 0; i < n; i++) {
        for (j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == c) {
                if (productions[i][j + 1] != '\0') {
                    if (!isupper(productions[i][j + 1])) {
                        addToSet(follow[index], productions[i][j + 1]);
                    }
                } else {
                    if (productions[i][0] != c) {
                        findFollow(productions[i][0], index);
                    }
                }
            }
        }
    }
}

// Check LL(1)
void checkLL1() {
    int i, j, k;
    int isLL1 = 1;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (productions[i][0] == productions[j][0]) {

                // FIRST/FIRST conflict
                for (k = 0; first[i][k] != '\0'; k++) {
                    if (first[i][k] != '#' && contains(first[j], first[i][k])) {
                        isLL1 = 0;
                    }
                }

                if (contains(first[i], '#')) {
                    for (k = 0; follow[i][k] != '\0'; k++) {
                        if (contains(first[j], follow[i][k])) {
                            isLL1 = 0;
                        }
                    }
                }
            }
        }
    }

    if (isLL1)
        printf("\nGrammar is LL(1)\n");
    else
        printf("\nGrammar is NOT LL(1)\n");
}

int main() {
    int i;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (format: A=aB or A=# for epsilon):\n");

    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    for (i = 0; i < n; i++) {
        findFirst(productions[i][0], i);
    }

    for (i = 0; i < n; i++) {
        findFollow(productions[i][0], i);
    }

    printf("\nFIRST sets:\n");
    for (i = 0; i < n; i++) {
        printf("FIRST(%c) = { %s }\n", productions[i][0], first[i]);
    }

    printf("\nFOLLOW sets:\n");
    for (i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { %s }\n", productions[i][0], follow[i]);
    }

    checkLL1();

    return 0;
}

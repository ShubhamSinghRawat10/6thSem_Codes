#include<stdio.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char str[]){
    char *keyword[] = {
        "int","float","double","void","char","bool",
        "if","else","for","while","do","switch","case","default"
    };
    int n = sizeof(keyword)/sizeof(keyword[0]);

    for(int i=0;i<n;i++){
        if(strcmp(str,keyword[i])==0){
            return 1;
        }
    }
    return 0;
}

int isOperator(char str[]){
    char *operator[] = {
        "+","-","*","/","%","=","==","!=","<",">","<=",">=",
        "&&","||","!","&","|","^","~"
    };
    int n = sizeof(operator)/sizeof(operator[0]);

    for(int i=0;i<n;i++){
        if(strcmp(str,operator[i])==0){
            return 1;
        }
    }
    return 0;
}

int isParenthesis(char str[]){
    char *parenthesis[] = {"(",")","{","}","[","]"};
    int n = sizeof(parenthesis)/sizeof(parenthesis[0]);

    for(int i=0;i<n;i++){
        if(strcmp(str,parenthesis[i])==0){
            return 1;
        }
    }
    return 0;
}

int isIdentifier(char str[]){
    if(!(isalpha(str[0]) || str[0]=='_')){
        return 0;
    }

    for(int i=1;str[i]!='\0';i++){
        if(!(isalnum(str[i]) || str[i]=='_')){
            return 0;
        }
    }
    return 1;
}

int main(){
    char str[50];

    printf("Enter a string: ");
    scanf("%s",str);

    if(isKeyword(str)){
        printf("%s is a keyword.\n",str);
    }
    else if(isOperator(str)){
        printf("%s is an operator.\n",str);
    }
    else if(isParenthesis(str)){
        printf("%s is a parenthesis.\n",str);
    }
    else if(isIdentifier(str)){
        printf("%s is an identifier.\n",str);
    }
    else{
        printf("%s is not a keyword, operator, parenthesis, or identifier.\n",str);
    }

    return 0;
}
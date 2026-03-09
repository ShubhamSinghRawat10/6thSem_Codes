#include<stdio.h>
#include<string.h>
int main(){
    char str1[100],str2[100];
    int length, result;

    printf("Enter first string: ");
    gets(str2);

    length = strlen(str2);
    printf("Length of the string is: %d\n", length);

    char copy[100];
    strcpy(copy, str2);
    printf("Copied string: %s\n", copy);

    strcat(str1, str2);
    printf("\n Concatenated string : %s\n", str1);

    result = strcmp(str1,str2);
    if(result == 0){
        printf("The strings are equal.\n");
    } else {
        printf("The strings are not equal.\n");
    }
    
    strrev(str2);
    printf("Reversed string: %s\n", str2);

    strupr(str2);
    printf("Uppercase string: %s\n", str2);

    strlwr(str2);
    printf("Lowercase string: %s\n", str2);

    return 0;
    
}
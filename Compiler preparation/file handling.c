#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp1, *fp2;
    char ch;

    // Create and write to file
    fp1 = fopen("file1.txt", "w");
    if (fp1 == NULL)
    {
        printf("File cannot be created");
        return 0;
    }

    printf("Enter text to write into file (Press Ctrl+Z to stop):\n");

    while ((ch = getchar()) != EOF)
    {
        fputc(ch, fp1);
    }

    fclose(fp1);

    // Read file
    fp1 = fopen("file1.txt", "r");
    printf("\nContents of file1.txt:\n");

    while ((ch = fgetc(fp1)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp1);

    // Copy file
    fp1 = fopen("file1.txt", "r");
    fp2 = fopen("file2.txt", "w");

    while ((ch = fgetc(fp1)) != EOF)
    {
        fputc(ch, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    printf("\nFile copied to file2.txt");

    // Delete file
    if (remove("file2.txt") == 0)
        printf("\nfile2.txt deleted successfully");
    else
        printf("\nUnable to delete the file");

    return 0;
}
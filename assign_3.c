// Name: Benjamin Vo
// CWID: 889378170
// Assignment 3
// CPSC 223C, Spring 2023
// Email: bvo@csu.fullerton.edu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100

char *show(char *a[], int size);
void searchChar(char *array[], int size, char *a, int num_lines);

int main(int argc, char *argv[])
{
    char *myArray[MAX_LINES];
    char fileName[100], line[300], search[300];
    int line_number;

    FILE *fpointer;

    int line_count = 0;

    printf("Welcome to Text File Analysis brought to you by Benjamin Vo. \n");
    printf("If you need any help please contact me at bvo@csu.fullerton.edu . \n\n");

    printf("PLease enter the name of the file for analysis: ");
    scanf("%s", fileName);

    fpointer = fopen(fileName, "r");

    if(fpointer == NULL)
    {
        printf("Error: File not found. \n");
        return 1;
    }

    while(fgets(line, sizeof(line), fpointer))
    {
        if(line_count >= MAX_LINES)
        {
            printf("Error: Maximum number of lines exceeded. \n");
            return 1;
        }

        line[strlen(line) - 1] = '\0';
        myArray[line_count] = malloc((strlen(line) + 1) * sizeof(char));
        strcpy(myArray[line_count], line);

        line_count++;
    }

    fclose(fpointer);

    printf("\nThank you. This file contains %d lines of text. \n\n", line_count);
    printf("The file contents were copied to an array. A dedicated funnction will output the array. \n\n");

    printf("%s", show(myArray, line_count));

    char choice;
    do
    {
        printf("\nDo you wish to search for specific characters (y or n)?: ");
        scanf(" %c", &choice);

        if(choice == 'y')
        {
            printf("\nPlease enter the set of characters that you wish to find: ");
            scanf("%s", search);

            printf("\nPlease enter the line number in which to search: ");
            scanf("%d", &line_number);

            searchChar(myArray, line_count, search, line_number);
        }
    } while (choice == 'y');
    
    if(choice == 'n')
    {
            printf("\nHave a nice day. This program will terminate. \n");
    }

    return 0;
}

char *show(char *a[], int size)
{
    if(size < 0)
    {
        printf("Error: Invalid size. \n");
        return NULL;
    }

    for(int i = 0; i < size; i++)
    {
        printf("%s\n", a[i]);
    }

    printf("\n//End of array output. \n\n");

    int num = 0;
    printf("Please enter the number of a line ot view or a negative number to terminate: ");
    scanf("%d", &num);

    while(num >= 0 && num < size)
    {
        printf("%s\n", a[num]);
        printf("Please enter the number of a line ot view or a negative number to terminate: ");
        scanf("%d", &num);
    }

    return "";
}

void searchChar(char *array[], int size, char *a, int num_lines)
{
    if(num_lines < 0 || num_lines >= size)
    {
        printf("\nError: Invalid line number. \n");
        return;
    }

    char *found = strpbrk(array[num_lines], a);

    if(found == NULL)
    {
        printf("\nNo matching characters found in line %d. \n", num_lines);
    }
    else
    {
        printf("\nIn this line matching characters were found at these indices: ");
        while(found != NULL)
        {
            int index = found - array[num_lines];
            printf("%d ", index);
            found = strpbrk(found + 1, a);
        }

        printf("\n");
    }
}

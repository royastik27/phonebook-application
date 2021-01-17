#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000
#define NAME_LIMIT 33
#define NUMBER_LIMIT 20

typedef struct{
    char name[NAME_LIMIT], number[NUMBER_LIMIT];
}Contact;

void getFormat(char str[])
{
    int len = strlen(str);

    str[len] = '\n';
    str[len+1] = '\0';
}

int findMatch(char fileStr[], char name[])
{
    int i, j = 0;

    for(i = 0; fileStr[i] != '\0'; ++i)
    {
        if(fileStr[i] == name[j] || fileStr[i] + 32 == name[j] || fileStr[i] - 32 == name[j])
            ++j;
        else
            j = 0;

        if(name[j] == '\0')
            return 1;
    }

    return 0;
}

void createContact()
{
    system("cls");
    printf("------------------------ Create Contact ------------------------\n\n");

    Contact newContact;

    printf("Enter Name: ");
    gets(newContact.name);
    printf("Enter the number: ");
    gets(newContact.number);

    /* Used append mode */
    FILE * namesFile = fopen("names.txt", "a");
    FILE * numbersFile = fopen("numbers.txt", "a");

    /* File opening error handling */
    if(!namesFile || !numbersFile)
        printf("\nSomething went wrong...\n");
    else
    {
        fprintf(namesFile, "%s\n", newContact.name);
        fprintf(numbersFile, "%s\n", newContact.number);

        printf("\nContact added successfully!");

        fclose(namesFile);
        fclose(numbersFile);
    }

    printf("\nPress any key to go back...");
    getchar();
}

void editContact()
{
    system("cls");
    printf("------------------------ Edit Contact ------------------------\n\n");

    /* Used reading mode */
    FILE * namesFile = fopen("names.txt", "r");
    FILE * numbersFile = fopen("numbers.txt", "r");

    /* File opening error handling */
    if(!namesFile || !numbersFile)
    {
        printf("You haven't created any contacts yet...\n");
    }
    else
    {
        Contact contacts[LIMIT];
        int i, len, toEdit;
        char newName[NAME_LIMIT], newNumber[NUMBER_LIMIT];

        /* Copying contacts from files to array */
        len = 0;
        while(fgets(contacts[len].name, NAME_LIMIT, namesFile))
        {
            fgets(contacts[len].number, NUMBER_LIMIT, numbersFile);
            ++len;
        }

        fclose(namesFile);
        fclose(numbersFile);

        /* Displaying array elements with Serial Number */
        printf("SL No\t\tName and Number\n");
        printf(".......................................\n");
        for(i = 0; i<len; ++i)
        {
            printf("%d\t\t%s\t\t%s\n",  i+1, contacts[i].name, contacts[i].number);
        }

        /* Getting the serial number to edit */
        printf("\nEnter the SL no to Edit: ");
        scanf("%d", &toEdit);
        getchar();

        /* Checking input validity */
        while(toEdit < 1 || toEdit > len){
            printf("Invalid Input!\n");
            printf("\nEnter the SL no to Edit: ");
            scanf("%d", &toEdit);
            getchar();
        }

        /* Getting new name and number */
        system("cls");
        printf("------------------------ Edit Contact ------------------------\n\n");

        /* For zero based index */
        --toEdit;

        printf("%d\t\t%s\t\t%s\n",  toEdit + 1, contacts[toEdit].name, contacts[toEdit].number);

        printf("Enter new name: ");
        gets(newName);
        printf("Enter new number: ");
        gets(newNumber);

        /* Making the input as same format as file data */
        getFormat(newName);
        getFormat(newNumber);

        /* Replacing the contact */
        strcpy(contacts[toEdit].name, newName);
        strcpy(contacts[toEdit].number, newNumber);

        /* Used writing mode */
        namesFile = fopen("names.txt", "w");
        numbersFile = fopen("numbers.txt", "w");

        /* File opening error handling */
        if(!namesFile || !numbersFile)
        {
            printf("Something went wrong...\n");
        }
        else
        {
            /* Copying the contacts from array to file */
            for(i = 0; i<len; ++i)
            {
                fprintf(namesFile, "%s", contacts[i].name);
                fprintf(numbersFile, "%s", contacts[i].number);
            }

            printf("\nContact edited successfully!\n");

            fclose(namesFile);
            fclose(numbersFile);
        }
    }

     printf("Press any key to go back...");
     getchar();
}

void deleteContact()
{
    system("cls");
    printf("------------------------ Delete Contact ------------------------\n\n");

    Contact contacts[LIMIT];
    int len, i, toDelete;

    /* Used reading mode */
    FILE * namesFile = fopen("names.txt", "r");
    FILE * numbersFile = fopen("numbers.txt", "r");

    /* File opening error handling */
    if(!namesFile || !numbersFile)
        printf("\nSomething went wrong...\n");
    else
    {
        /* Copying contacts from files to array */
        len = 0;
        while(fgets(contacts[len].name, NAME_LIMIT, namesFile))
        {
            fgets(contacts[len].number, NUMBER_LIMIT, numbersFile);
            ++len;
        }

        /* Displaying the array */
        printf("SL No\t\tName and Number\n");
        printf(".......................................\n");
        for(i = 0; i<len; ++i)
        {
            printf("%d\t\t%s\t\t%s\n",  i+1, contacts[i].name, contacts[i].number);
        }

        /* Getting the serial number to delete */
        printf("\nEnter the SL no to delete: ");
        scanf("%d", &toDelete);
        getchar();

        /* Checking input validity */
        while(toDelete < 1 || toDelete > len){
            printf("Invalid Input!\n");
            printf("\nEnter the SL no to delete: ");
            scanf("%d", &toDelete);
            getchar();
        }

        fclose(namesFile);
        fclose(numbersFile);

        /* Used writing mode */
        namesFile = fopen("names.txt", "w");
        numbersFile = fopen("numbers.txt", "w");

        /* File opening error handling */
        if(!namesFile || !numbersFile)
            printf("\nSomething went wrong...\n");
        else
        {
            /* For zero based index */
            --toDelete;

            /* Copying array elements to file without the selected one */
            for(i = 0; i<toDelete; ++i)
            {
                fprintf(namesFile, "%s", contacts[i].name);
                fprintf(numbersFile, "%s", contacts[i].number);
            }
            for(i = toDelete+1; i<len; ++i)
            {
                fprintf(namesFile, "%s", contacts[i].name);
                fprintf(numbersFile, "%s", contacts[i].number);
            }

            printf("Deleted successfully!\n");

            fclose(namesFile);
            fclose(numbersFile);
        }
    }

    printf("\nPress any key to go back...");
    getchar();
}

void searchContacts()
{
    system("cls");
    printf("------------------------ Search Contacts ------------------------\n\n");

    Contact contacts[LIMIT];
    char name[NAME_LIMIT];
    int len, res, i;

    printf("Enter name: ");
    gets(name);

    /* Used reading mode */
    FILE * namesFile = fopen("names.txt", "r");
    FILE * numbersFile = fopen("numbers.txt", "r");

    /* File opening error handling */
    if(!namesFile || !numbersFile)
    {
        printf("Something went wrong...\n");
    }
    else
    {
        /* Copying contacts from files to array */
        len = 0;
        while(fgets(contacts[len].name, NAME_LIMIT, namesFile))
        {
            fgets(contacts[len].number, NUMBER_LIMIT, numbersFile);
            ++len;
        }

        /* Checking and printing */
        printf("\n\n---------------- Matched Contacts ----------------\n\n");

        res = 0;
        for(i = 0; i<len; ++i)
        {
            if(findMatch(contacts[i].name, name))
            {
                printf("%s%s\n", contacts[i].name, contacts[i].number);
                ++res;
            }
        }

        if(res)
            printf("Found result: %d\n", res);
        else
            printf("Sorry, no result found!\n");
    }

    printf("Press any key to go back...");
    getchar();
}

void viewAllContacts()
{
    system("cls");
    printf("------------------------ All Contacts ------------------------\n\n");

    /* Used reading mode */
    FILE * namesFile = fopen("names.txt", "r");
    FILE * numbersFile = fopen("numbers.txt", "r");

    /* File opening error handling */
    if(!namesFile || !numbersFile)
        printf("\nSomething went wrong...\n");
    else
    {
        Contact contact;

        /* Getting contact details from file and printing it one by one */
        while(fgets(contact.name, NAME_LIMIT, namesFile) != NULL)
        {
            fgets(contact.number, NUMBER_LIMIT, numbersFile);

            printf("%s%s\n", contact.name, contact.number);
        }

        fclose(namesFile);
        fclose(numbersFile);
    }

    printf("Press any key to go back...");
    getchar();
}

int main()
{
    int option;

    while(1)
    {
        system("cls");

        printf("------------------------ My PhoneBook ------------------------\n\n");
        printf("1. Create a contact\n");
        printf("2. Edit a contact\n");
        printf("3. Delete a contact\n");
        printf("4. Search contacts\n");
        printf("5. View all contacts\n");
        printf("6. Exit\n");

        printf("\nEnter your option: ");
        scanf("%d", &option);
        getchar();

        switch(option)
        {
        case 1:
            createContact();
            break;
        case 2:
            editContact();
            break;
        case 3:
            deleteContact();
            break;
        case 4:
            searchContacts();
            break;
        case 5:
            viewAllContacts();
            break;
        case 6:
            return 0;
        }
    }

    return 0;
}

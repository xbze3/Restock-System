/*
Group Members
    Clarence Lucius - 1046776
    Ezra Minty      - 1048091
    Safrina Ali     - 1041627


Documentation

    show
        Process - The software iterates through the inventory data, printing the item's name, stock amount, and price.
        Output - The software displays a list of every item in the inventory, together with their price and stock amount.

    find
        Process - The software searches the inventory data for the requested item and, if found, prints its name, stock quantity, and price.
        Operation - The software displays the item's details if it is identified. If it is not found, the user is notified that the item is not in the inventory.

    add
        Process - The software determines whether the item already exists in the inventory. If not, the new item is added to the inventory data using the information provided.
        Operation - The software confirms the addition if the item is correctly added or not. It alerts the user and recommends using the "stock" command if the item already exists.

    stock
        Process - The user is prompted by the application to enter the amount by which the stock quantity should be increased or decreased to. The stock quantity is then updated appropriately.
        Operation - The software displays the item's new stock quantity, if operation was successful. If the input is invalid (for example, attempting to reduce stock below zero), it alerts the user.

    help
        Process - To assist the user, the software displays a list of available commands, along with descriptions.
        Operation - The program displays the command selected by user, which is included by the command word (e.g. “stock”)

    commit
        Input - The “commit” command, cannot be called by the user. It is, however, within the written program and could be used in later scenarios.
        Process - This function might serve as a stand-in for later development or additional features. It just ends the program in its current iteration.
        Output - It will display future developments made to the software/program.


Limitations
        ~   In case the user changed the stock amount of an item or added an item, it is necessary to exit
            the display screen and run the software in order to achieve updated input.

        ~   In this situation, the old inventory is deleted, and the user's unchanged sections
            and updates are copied and run into the current inventory.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LSIZ 128
#define RSIZ 10

// Declaration of necessary variables needed for the programs functionality

FILE *fptr = NULL;
FILE *fptw = NULL;
FILE *fptw2 = NULL;

char itemName[10];
int itemAmount;
float itemPrice;

char line[RSIZ][LSIZ];
int i = 0;
int tot = 0;

char currentCommand[10];
char numberAsString[10];

int increaseOrDecrease;
int amountIncDec;
int dest = 0;

int ret;
char filename[] = "database.txt";
char altFilename[] = "database_alt.txt";

// "show" command logic

void show()
{
    printf("\n");
    for(i = 0; i < tot; ++i)
    {

        // Below statement will run on lines where an items name is mentioned

        if((i % 3) == 0)
        {
            printf("Item: %s\n", line[i]);
        }

        // Below statement will run on lines where an item's stock amount is mentioned

        else if((i % 3) == 1)
        {
            printf("In Stock: %s\n", line[i]);
        }

        // Below statement will run on lines where an item's price is mentioned

        else if((i % 3) == 2)
        {
            printf("Price: $%s\n", line[i]);
            printf("\n");
        }
    }
}

// "find" command logic

void find()
{
    int found = 0;
    printf("Item Name: ");
    scanf("%s", itemName);

    /* Below loop is used to find and display information relation to a specific product by
    looping through the list and printing the lines containing the item's information to the terminal */

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(line[i], itemName) == 0)
        {
            printf("\n");
            printf("Item: %s\n", line[i]);
            printf("In Stock: %s\n", line[i + 1]);
            printf("Price: $%s\n", line[i + 2]);
            printf("\n");

            found = 1;
        }
    }

    // Below code will run if the variable found has a value of 0, meaning that the item was not found within the file

    if(found == 0)
    {
        printf("Item Not Found\n");
    }
}

// "add" command logic

void add()
{
    int found = 0;
    printf("Item Name: ");
    scanf("%s", itemName);

    /* Code below will loop through loop through the lines of the file in search of an item which
    shares the same name as the one entered into the find command. If an item is found, then it already exists and
    cannot be re-added and thus, the message "Item Already Exists" will be printed to the terminal */

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(line[i], itemName) == 0)
        {
            found = 1;
            printf("Item Already Exists\n");
            printf("Use 'stock' command to update the amount in stock\n");
        }
    }

    /* If the item does not already exist within the file, the user is the promoted by the following code to enter
    the desired price of the item and the amount of said item which are in stock. This information is then
    added to the database file */

    if(found == 0)
    {
        printf("Amount of Item in stock: ");
        scanf("%d", &itemAmount);

        printf("Item Price: $");
        scanf("%f", &itemPrice);

        fprintf(fptw, "%s", itemName);
        fprintf(fptw, "\n%d", itemAmount);
        fprintf(fptw, "\n%.2f\b\n", itemPrice);

        printf("Success, restart program to see changes\n");
    }
}

// "stock" command logic

int stock()
{
    int valid = 0;
    printf("Item Name: ");
    scanf("%s", itemName);

    /* Below code is responsible for checking whether an item is already apart of the database, and if so then
    either adds to the amount of it which is in stock or subtracts from the amount of it which is in stock.
    This can be used if a certain amount of a product was bought by the user, thus increasing the amount in stock, or
    sold by the user, and decreasing the amount of that item which is in stock */

    for(i = 0; i < tot; ++i)
    {
        if(strcmp(line[i], itemName) == 0)
        {
            printf("Increase in Stock (1) | Decrease in Stock (2): ");
            scanf("%d", &increaseOrDecrease);
            dest = i + 1;
        }

        /* The below portion of code will be executed if the user has chosen to increase the amount of product in stock
        which is mentioned within the database file. It is responsible for asking for the amount by which the stock
        should be incremented and it also outputs the new amount to the screen after the calculation has been done */

        else if((i == dest) && increaseOrDecrease == 1)
        {
            printf("Increase Amount: ");
            scanf("%d", &amountIncDec);

            printf("New Amount: %d\n", atoi(line[i]) + amountIncDec);
            valid = 1;
        }

        /* The below portion of code will be executed if the user has chosen to decrease the amount of product in stock
        which is mentioned within the database file. It is responsible for asking for the amount by which the stock
        should be decremented and it also outputs the new amount to the screen after the calculation has been done.
        It is also responsible for checking whether the amount the stock is to be decremented is greater than the amount
        which is listed within the database */

        else if((i == dest) && increaseOrDecrease == 2)
        {
            printf("Decrease Amount: ");
            scanf("%d", &amountIncDec);

            if(amountIncDec > atoi(line[i]))
            {
                printf("Invalid Amount\n");
            }
            else
            {
                printf("New Amount: %d\n", atoi(line[i]) - amountIncDec);
                valid = 1;
            }
        }
    }

    /* The following code is responsible for converting the both performing the calculations on the stock amount
    listed in the file and also for converting that amount to an integer. It is also responsible for copying
    the contents of the database file into the database_alt file except for the line which mentions the stock amount.
    The new stock amount is then copied to the file at this point, at which point the program then deletes the old database file
    and renames the "database_alt.txt" to "database.txt" and then recreates the database_alt file */

    if(valid == 1)
    {
         for(i = 0; i < tot; ++i)
        {
            if((i == dest) && (increaseOrDecrease == 1))
            {
                sprintf(numberAsString, "%d", atoi(line[i]) + amountIncDec);
                fprintf(fptw2, "%s\n", numberAsString);
            }

            else if((i == dest) && (increaseOrDecrease == 2))
            {
                sprintf(numberAsString, "%d", atoi(line[i]) - amountIncDec);
                fprintf(fptw2, "%s\n", numberAsString);
            }

            else
            {
                fprintf(fptw2, "%s\n", line[i]);
            }
        }
        fclose(fptr);
        fclose(fptw);
        fclose(fptw2);

        /* The "ret" variable will be equal to 0 if both the remove operation and rename operation run, otherwise
        it will have a value other than 0, causing the else portion of the below IF-ELSE structure to run */

        ret = remove(filename) + rename(altFilename, filename);

        /* In the event that the there was an error with the file deletion or renaming the else portion of the below
        IF-ELSE statement will run, indicating to the user that the operation was unsuccessful */

        if(ret == 0)
        {
          printf("Operation Successful\n");
          printf("Restart program to see changes\n");
        }
        else
        {
          printf("Operation Error\n");
        }
    }
}

void help()
{
    printf("\n");
    printf(" ************************Command List*************************\n");
    printf(" * help  - Show this help screen                             *\n");
    printf(" * show  - Show items                                        *\n");
    printf(" * find  - Find a specific item within database              *\n");
    printf(" * add   - Add Item                                          *\n");
    printf(" * stock - Increase or decrease a listed item's stock amount *\n");
    printf(" *************************************************************\n");
    printf("\n");
}

// Main Function

int main()
{

    /* Code portion below is used to open the necessary "database.txt" and "database_alt.txt" files.
    It is also responsible for creating an array called "line" and assigning each line of the file as one of its elements.
    This allows for each line of the file to be accessed in the same way an element within an array could be accessed */

    fptr = fopen("database.txt", "r");
    fptw = fopen("database.txt", "a");
    fptw2 = fopen("database_alt.txt", "w");

    while(fgets(line[i], LSIZ, fptr))
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

    tot = i;

    // Main Loop of Program

    while(1)
    {
        printf("help|show|find|add|stock|exit> ");
        scanf("%s", currentCommand);

        // Code below will run if the "exit" keyword is passed to the program

        if(strcmp(currentCommand, "exit") == 0)
        {
            break;
        }

        // Code below will call the "show()" function is the "show" keyword is passed to the program

        else if(strcmp(currentCommand, "show") == 0)
        {
            show();
        }

        // Code below will call the "find()" function if the "find" keyword is passed to the program

        else if(strcmp(currentCommand, "find") == 0)
        {
            find();
        }

        // Code below will call the "add()" function if the "add" keyword is passed to the program

        else if(strcmp(currentCommand, "add") == 0)
        {
            add();
        }

        // Code below will call the "stock()" function if the "stock" keyword is passed to the program

        else if(strcmp(currentCommand, "stock") == 0)
        {
            stock();
        }

        // Code below will run if the "help()" function if the "help" keyword is passed to the program

        else if(strcmp(currentCommand, "help") == 0)
        {
            help();
        }

        // Code below will run if the "commit" keyword is passed to the program

        else if(strcmp(currentCommand, "commit") == 0)
        {
            // Possible Commit Command
            exit(0);
        }
    }

    printf("\n");
    fclose(fptr);
    fclose(fptw);
    return 0;
}


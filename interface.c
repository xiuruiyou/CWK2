#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "user.h"
#include "generate.h"

int option1()
{
    int option = -1;
    char line[80];
    fgets(line,80,stdin);
    option = (int)atoi(line);
    return option;
}

void user_page(char *userFileName)
{
    char USER[100];
    strcpy(USER, userFileName);
    int option;
    while(1)
    {
        printf("\n Please choose an option:\n 1) New Random Game\n 2) New All Dead Game\n 3) The Last game\n 4) Exit\n   Option: ");
        option = option1();
        //User registration.
        if( option == 1 )
        {
            newRandomGame(USER);
        }
        else if(option == 2)
        {
            newAllDeadGame(USER);
        }
            //A user logs in to the system page of the user.
        else if( option == 3 )
        {
            OldGame(USER);
        }
            //Exit the program.
        else if( option == 4 )
        {
            exit(0);
        }
        else
            printf("\nSorry, the option you entered was invalid, please try again.\n");
    }
}

void interface()
{
    int option;
    FILE *fp;
    linklist head, p2, last;
    head = (linklist) malloc(sizeof(user));
    head->next1 = NULL;
    last = head;
    if((fp = fopen("user.txt", "r")) == NULL)
    {
        fp = fopen("user.txt", "w");
        fclose(fp);
    }
    while (1)
    {
        p2 = (linklist) malloc(sizeof(user));
        fscanf(fp, "%s %s", p2->username, p2->password);
        if(feof(fp))
        {
            break;
        }
        last->next1 = p2;
        last = p2;
    }
    last->next1 = NULL;
    fclose(fp);


    //The system main page is displayed.
    while(1)
    {
        printf("\n Please choose an option:\n 1) Register an account\n 2) Login\n 3) Quit\n   Option: ");
        option = option1();
        //User registration.
        if( option == 1 )
        {
            regi(head);
            output(head, "user.txt");
        }
        //A user logs in to the system page of the user.
        else if( option == 2 )
        {
            login(head);
        }
        //Exit the program.
        else if( option == 3 )
        {
            printf("\nClosing\n");
            exit(0);
        }
        else
            printf("\nSorry, the option you entered was invalid, please try again.\n");
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct contact
{
    char Name[20];
    char LastName[20];
    char Tel[15];
    char Address[40];
    char City[20];
    int SpeedDial;
    struct contact *ptrNext;
};


typedef struct contact Contact;
typedef Contact *ptrContact;


void main_menu();
// 1
void add_contact(ptrContact *ptrListTop, char name[20], char last_name[20],
                 char tel[15], char address[40], char city[20]);
// 2
void add_speed_dial_num(ptrContact ptrListTop, char name[20], char last_name[20], int speed_dial);
// 3
void print_last_contact(ptrContact ptrListTop);
// 4
void del_contact(ptrContact *ptrListTop, char name[20], char last_name[20], int speed_dial);
// 5
void del_contacts(ptrContact *ptrListTop);
// 6
void print_contacts(ptrContact ptrListTop);


int main(int argc, char **argv)
{
    ptrContact ptrTop=NULL;
    int Option;
    char name[20], last_name[20], tel[15], address[40], city[20];
    int speed_dial;

    printf("This program allows you to manage your contacts information.\n\n");
    
    main_menu();
    scanf("%i", &Option);
    system("cls");
    
    while(Option != 7)
    {
        switch(Option)
        {
            case 1:
                printf("Type the information of the new contact:\n\n");
                printf("Name: ");
                fflush(stdin);
                scanf("%20[0-9a-zA-Z .,-]", &name[0]);
                fflush(stdin);

                printf("Last Name: ");
                fflush(stdin);
                scanf("%20[0-9a-zA-Z .,-]", &last_name[0]);
                fflush(stdin);

                printf("Telephone: ");
                fflush(stdin);
                scanf("%15[0-9 +-]", &tel[0]);
                fflush(stdin);

                printf("Address: ");
                fflush(stdin);
                scanf("%40[0-9a-zA-Z .,-#]", &address[0]);
                fflush(stdin);

                printf("City: ");
                fflush(stdin);
                scanf("%20[0-9a-zA-Z .,]", &city[0]);
                fflush(stdin);

                add_contact(&ptrTop, name, last_name, tel, address, city);
                break;

            case 2:
                if(ptrTop!=NULL)
                {
                    printf("Type the information of the contact you want to modify:\n");
                    printf("The Speed Dial number must be an integer greater than 0\n\n");

                    printf("Name: ");
                    fflush(stdin);
                    scanf("%20[0-9a-zA-Z .,-]", &name[0]);
                    fflush(stdin);

                    printf("Last Name: ");
                    fflush(stdin);
                    scanf("%20[0-9a-zA-Z .,-]", &last_name[0]);
                    fflush(stdin);

                    printf("\nNew Speed Dial number:\n");
                    scanf("%i", &speed_dial);

                    printf("\n");
                    add_speed_dial_num(ptrTop, name, last_name, speed_dial);
                    printf("\n");
                }
                else
                {
                    printf("\nContact list empty\n\n");
                }
                break;

            case 3:
                if (ptrTop!=NULL)
                {
                    print_last_contact(ptrTop);
                }
                else
                {
                    printf("\nContact list empty\n\n");
                }
                break;

            case 4:
                if (ptrTop!=NULL)
                {
                    printf("Type the information of the contact you want to delete\n");
                    printf("To find a contact you either need the correct name AND last name\n");
                    printf("OR the correct speed dial number.\n\n");
                    
                    printf("Name: ");
                    fflush(stdin);
                    scanf("%20[0-9a-zA-Z .,-]", &name[0]);
                    fflush(stdin);
                    
                    printf("Last Name: ");
                    fflush(stdin);
                    scanf("%20[0-9a-zA-Z .,-]", &last_name[0]);
                    fflush(stdin);
                    
                    printf("Speed Dial (Type 0 to ignore): ");
                    fflush(stdin);
                    scanf("%i", &speed_dial);

                    del_contact(&ptrTop, name, last_name, speed_dial);
                }
                else
                {
                    printf("\nContact list empty\n\n");
                }
                break;
            
            case 5:
                if (ptrTop!=NULL)
                {
                    del_contacts(&ptrTop);
                }
                else
                {
                    printf("\nContact list empty\n\n");
                }
                break;

            case 6:
                if (ptrTop!=NULL)
                {
                    print_contacts(ptrTop);
                }
                else
                {
                    printf("\nContact list empty\n\n");
                }
                break;

            case 7:
                break;
                
            default:
                printf("\nUnavailable option\n");
                break;
        }
        printf("\n");
        system("pause");
        main_menu();
        scanf("%i", &Option);
        system("cls");
    }
    printf("Program closed.\n");
    printf("\n");
    
	return 0;
}


void main_menu()
{
    system("cls");
    printf("Type an option of the menu:\n\n");
    printf("1. Add new contact\n");
    printf("2. Assign speed dial number to contact\n");
    printf("3. Show the last contact added\n");
    printf("4. Delete contact\n");
    printf("5. Delete all contacts\n");
    printf("6. Show all contacts\n");
    printf("7. Close program\n");
    printf("\n");
}


void add_contact(ptrContact *ptrListTop, char name[20], char last_name[20],
                 char tel[15], char address[40], char city[20])
{
    ptrContact ptrNew;
    ptrNew = (ptrContact)malloc(sizeof(Contact));
    if(ptrNew != NULL)
    {
        strcpy(ptrNew -> Name, name);
        strcpy(ptrNew -> LastName, last_name);
        strcpy(ptrNew -> Tel, tel);
        strcpy(ptrNew -> Address, address);
        strcpy(ptrNew -> City, city);
        ptrNew -> SpeedDial = -1;

        ptrNew -> ptrNext = *ptrListTop;
        *ptrListTop = ptrNew;

        printf("\n\nContact added\n\n");
    }
    else
    {
        printf("It was not possible to assign memory space.");
    }
}


void add_speed_dial_num(ptrContact ptrListTop, char name[20], char last_name[20], int speed_dial)
{
    if(speed_dial<=0)
    {
        printf("The Speed Dial number must be an integer greater than 0\n");
        return;
    }
    ptrContact ptrTemp;
    ptrContact ptrMatch;
    ptrTemp = ptrListTop;
    ptrMatch = NULL;

    while(ptrTemp!=NULL)
    {
        if(ptrTemp->SpeedDial==speed_dial)
        {
            printf("The number %i is already assigned to a contact", speed_dial);
            return;
        }

        if( (strcmp(ptrTemp->Name, name)==0 && strcmp(ptrTemp->LastName, last_name)==0) )
        {
            ptrMatch = ptrTemp;
        }
        ptrTemp=ptrTemp->ptrNext;
    }

    if (ptrMatch != NULL)
    {
        ptrMatch -> SpeedDial = speed_dial;
        printf("Speed Dial number assigned to contact");
    }
    else
    {
        printf("Contact not found");
    }
}


void print_last_contact(ptrContact ptrListTop)
{
    printf("The information of the last contact added is:\n\n");
    printf("Name: %s\n", ptrListTop->Name);
    printf("Last Name: %s\n", ptrListTop->LastName);
    printf("Telephone: %s\n", ptrListTop->Tel);
    printf("Address: %s\n", ptrListTop->Address);
    printf("City: %s\n", ptrListTop->City);
    printf("Speed Dial: ");

    if (ptrListTop->SpeedDial!=-1)
    {
        printf("%i\n", ptrListTop->SpeedDial);
    }
    else
    {
        printf("Unassigned\n");
    }

    printf("\n");
}


void del_contact(ptrContact *ptrListTop, char name[20], char last_name[20], int speed_dial)
{
    ptrContact ptrTemp;
    ptrContact ptrPrev;
    ptrTemp = *ptrListTop;
    ptrPrev = ptrTemp;

    while(ptrTemp!=NULL)
    {
        if( (strcmp(ptrTemp->Name, name)==0 && strcmp(ptrTemp->LastName, last_name)==0 )
             || ptrTemp->SpeedDial == speed_dial)
        {
            if(*ptrListTop==ptrTemp)
            {
                *ptrListTop = (*ptrListTop)->ptrNext;
            }
            else
            {
                ptrPrev->ptrNext = ptrTemp->ptrNext;
            }
            free(ptrTemp);
            printf("\n\nContact deleted\n\n");
            return;
        }

        ptrPrev = ptrTemp;
        ptrTemp=ptrTemp->ptrNext;
    }
    printf("\n\nContact not found\n\n");
}


void del_contacts(ptrContact *ptrListTop)
{
    ptrContact ptrTemp;
    ptrTemp = *ptrListTop;
    while(ptrTemp!=NULL)
    {
        *ptrListTop = (ptrTemp)->ptrNext;
        free(ptrTemp);
        ptrTemp = *ptrListTop;
    }
    printf("\n\nAll contacts deleted\n\n");
}


void print_contacts(ptrContact ptrListTop)
{
    printf("Contacts (Shown from last to first added):\n\n");
    while(ptrListTop!=NULL)
    {
        printf("Name: %s\n", ptrListTop->Name);
        printf("Last Name: %s\n", ptrListTop->LastName);
        printf("Telephone: %s\n", ptrListTop->Tel);
        printf("Address: %s\n", ptrListTop->Address);
        printf("City: %s\n", ptrListTop->City);
        printf("Speed Dial: ");

        if (ptrListTop->SpeedDial!=-1)
        {
            printf("%i\n", ptrListTop->SpeedDial);
        }
        else
        {
            printf("Unassigned\n");
        }
        printf("\n");
        ptrListTop=ptrListTop->ptrNext;
    }
    printf("\n");
}

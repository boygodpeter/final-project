#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>






#define MEMBER 200
#define MEMBER_NAME_MAX 100
#define MEMBER_NUMBER_MAX 20
#define OCCUPATION_NAME 100
#define PASSWORD_MAX 20





struct bankmember{
    char occupation[OCCUPATION_NAME+1];
    char name[MEMBER_NAME_MAX+1];
    char phone[MEMBER_NUMBER_MAX+1];
    char password[PASSWORD_MAX+1];
    int account;
    int money;
    int age;
}member[MEMBER];



int compare1(const void *x_void , const void *y_void)
{
    const struct bankmember *x = x_void;
    const struct bankmember *y = y_void;
    return (x->money - y->money);
}

int compare2(const void *x_void , const void *y_void)
{
    const struct bankmember *x = x_void;
    const struct bankmember *y = y_void;
    return (y->money - x->money);
}

struct node
{
    char text[100];
    struct node *next;
};


struct node *insert(struct node *list, char *word)
{
    int i;
    struct node *new_node;
    new_node = malloc(sizeof(struct node));
    for (i = 0; word[i] != '\0'; i++)
    {
        new_node->text[i] = word[i];
    }
    new_node->text[i] = '\0';
    new_node->next = list;
    return new_node;
}





int main()
{
    char command[100];
    int tmp = 0 , read , number = 411410001 , read2;
    struct node *first = NULL;

    printf("It's a bank database system\n");
    printf("You can enter some instructions to operate this system\n");
    printf("If you have some questions about the system\n");
    printf("You can enter 'help' instruction to find out !\n");
    printf("If this is you first time to use , remember to enter 'open' to open a new account\n");
    printf("\n");


    while(1)
    {
        printf("Enter the command:");
        fgets(command , 100 , stdin);
        command[strcspn(command, "\n")] = '\0';
        switch(command[0])
        {

            //open
            case 'o':
                if(strcmp(command , "open") == 0)
                {
                    printf("Enter your name :");
                    scanf("%s" , member[tmp].name);
                    while (getchar() != '\n');

                    printf("Enter your phone number :");
                    scanf("%s" , member[tmp].phone);
                    while (getchar() != '\n');

                    printf("Enter how much money you want to save :");
                    scanf("%d" , &member[tmp].money);
                    while (getchar() != '\n');

                    printf("Enter your age :");
                    scanf("%d" , &member[tmp].age);
                    while (getchar() != '\n');

                    printf("Enter your occupation :");
                    scanf("%s" , member[tmp].occupation);
                    while (getchar() != '\n');

                    printf("Create your own password :");
                    scanf("%s" , member[tmp].password);
                    while (getchar() != '\n');

                    printf("\n");
                    printf("Opening account successfully !\n");
                    printf("Your bank account is '%d'\n" , number);
                    printf("You can take a piece of papper and write your account and password on it\n");
                    printf("\n");

                    member[tmp].account = number;
                    number++;
                    tmp++;
                    first = insert(first, "Using 'open' to open the account");
                    break;
                }

            case 's':
                //sortH
                if(strcmp(command , "sortH") == 0)
                {
                    qsort(member,tmp,sizeof(struct bankmember),compare2);
                    for(int i=0 ; i<tmp ; i++)
                    {
                        printf("\n");
                        printf("---------------------------------------------------------\n");
                        printf("NO.%d richest person" , i+1);
                        printf("Name : %s\n" , member[i].name);
                        printf("Age : %d\n" , member[i].age);
                        printf("Occupation : %s\n" , member[i].occupation);
                        printf("Deposit : %d\n" , member[i].money);
                        printf("Phone number : %s\n" , member[i].phone);
                        printf("---------------------------------------------------------\n");
                        printf("\n");
                    }
                    first = insert(first, "Using 'sortH' to sort people with most money to least");
                    break;
                }



                //sortL
                else if(strcmp(command , "sortL") == 0)
                {
                     qsort(member,tmp,sizeof(struct bankmember),compare1);
                     for(int i=0 ; i<tmp ; i++)
                     {
                         printf("\n");
                        printf("---------------------------------------------------------\n");
                        printf("NO.%d poorest person" , i+1);
                        printf("Name : %s\n" , member[i].name);
                        printf("Age : %d\n" , member[i].age);
                        printf("Occupation : %s\n" , member[i].occupation);
                        printf("Deposit : %d\n" , member[i].money);
                        printf("Phone number : %s\n" , member[i].phone);
                        printf("---------------------------------------------------------\n");
                        printf("\n");
                     }
                     first = insert(first, "Using 'sortL' to sort people with least money to most");
                     break;
                }



                //save
                else if(strcmp(command , "save") == 0)
                {
                    char pass[21];
                    bool sign = false;


                    printf("Enter your password :");
                    scanf("%s" , pass);
                    while (getchar() != '\n');

                    for(int i=0 ; i<tmp ; i++)
                    {
                        if(strcmp(member[i].password , pass) == 0)
                        {
                            sign = true;
                            read = i;
                            break;
                        }
                    }
                    if(sign)
                    {
                        int num;

                        printf("Enter how much do you want to save :");
                        scanf("%d" , &num);
                        while (getchar() != '\n');

                        member[read].money += num;
                        printf("\n");
                        printf("Save successfully !\n");
                        printf("\n");
                        first = insert(first, "Using 'save' to save money");
                    }
                    else
                    {
                        printf("\n");
                        printf("Sorry this is wrong password , if you want to save money\n");
                        printf("Please enter command 'save', and try again !\n");
                        printf("\n");
                    }
                    break;
                }





            //withdraw
            case 'w':
                if(strcmp(command , "withdraw") == 0)
                {
                    char pass[21];
                    bool sign = false;

                    printf("Enter your password :");
                    scanf("%s" , pass);
                    while (getchar() != '\n');

                    for(int i=0 ; i<tmp ; i++)
                    {
                        if(strcmp(member[i].password , pass) == 0)
                        {
                            sign = true;
                            read = i;
                            break;
                        }
                    }
                    if(sign)
                    {
                        int num , total;

                        printf("Enter how much money do you want to withdraw :");
                        scanf("%d" , &num);
                        while (getchar() != '\n');

                        total = member[read].money-num-0.4;
                        if(total>0)
                        {
                            first = insert(first, "Using 'withdraw' to withdraw money");
                            member[read].money = member[read].money-num-4;
                            printf("\n");
                            printf("Withdraw money successfully !\n");
                            printf("Your deposit now is %d\n" , member[read].money);
                            printf("Remember there will be a $4 handling fee for each withdrawal\n");
                            printf("\n");
                        }
                        else
                        {
                            printf("\n");
                            printf("Due to the insufficient balance , you can not withdraw your money\n");
                            printf("Please save enough money !\n");
                            printf("Reminder! There will be a $4 handling fee for each withdrawal!\n");
                            printf("\n");
                        }
                    }
                    else
                    {
                        printf("\n");
                        printf("Sorry this is wrong password , if you want to withdraw money\n");
                        printf("Please enter command 'withdraw', and try again !\n");
                        printf("\n");
                    }
                    break;
                }





                //exit
            case 'e':
                if(strcmp(command , "exit") == 0)
                {
                    printf("\n");
                    printf("Operation Record\n");
                    //printf("form the newest to the oldest\n");
                    printf("---------------------------------------------------------\n");
                    struct node *ptr2;
                    for(ptr2 = first ; ptr2 != NULL ; ptr2=ptr2->next)
                    {
                        printf("%s\n" , ptr2->text);
                    }
                    printf("---------------------------------------------------------\n");
                    return 0;
                    break;
                }




                //help
            case 'h':
                if(strcmp(command , "help") == 0)
                {
                    printf("\n");
                    printf("---------------------------------------------------------\n");
                    printf("All commands and descriptions\n");
                    printf("1. 'help'       -> Print all the commands.\n");
                    printf("2. 'exit'       -> End the program.\n");
                    printf("3. 'open'       -> If you want to open the new account.\n");
                    printf("4. 'save'       -> If you want to save the money , and you already have a account.\n");
                    printf("5. 'withdraw'   -> To withdraw your money.\n");
                    printf("6. 'sortH'      -> To sort people with most money to least.\n");
                    printf("7. 'sortL'      -> To sort people with least money to most.\n");
                    printf("8. 'check'      -> To check personal information.\n");
                    printf("9. 'fixpassword'-> To change your password.\n");
                    printf("10.'transfer'   -> To transfer from your account to another account.\n");
                    printf("---------------------------------------------------------\n");
                    printf("\n");
                    first = insert(first, "Using 'help' to check the command");
                    break;
                }






                //check
            case 'c':
                if(strcmp(command , "check") == 0)
                {
                    char name[101];
                    bool sign = false;

                    printf("Enter your name :");
                    scanf("%s" , name);
                    while (getchar() != '\n');

                    for(int i=0 ; i<tmp ; i++)
                    {
                        if(strcmp(member[i].name , name) == 0)
                        {
                            read = i;
                            sign = true;
                            break;
                        }
                    }

                    if(sign)
                    {
                        char pass[21];

                        printf("Enter your password :");
                        scanf("%s" , pass);
                        while (getchar() != '\n');

                        if(strcmp(member[read].password , pass) == 0)
                        {
                            printf("\n");
                            printf("Your information:\n");
                            printf("---------------------------------------------------------\n");
                            printf("Name : %s\n" , member[read].name);
                            printf("Phone number : %s\n" , member[read].phone);
                            printf("Age : %d\n" , member[read].age);
                            printf("Deposit : %d\n" , member[read].money);
                            printf("Occupation : %s\n" , member[read].occupation);
                            printf("---------------------------------------------------------\n");
                            printf("\n");
                            first = insert(first, "Using 'check' to check personal information");
                            break;
                        }
                        else
                        {
                            printf("\n");
                            printf("Wrong password!  Please enter the command 'check' again , and try again\n");
                            printf("\n");
                        }
                        break;
                    }
                    else
                    {
                        printf("\n");
                        printf("Wrong name ! Please enter the command 'check' again , and try again\n");
                        printf("Reminder! If this is you first time to use , remember enter 'open' to open a new account\n");
                        printf("\n");
                        break;
                    }
                }





                //fixpassword
            case 'f':
                if(strcmp(command , "fixpassword") == 0)
                {
                    char name[101];
                    bool sign = false;
                    printf("Enter your name :");
                    scanf("%s" , name);
                    while (getchar() != '\n');

                    for(int i=0 ; i<tmp ; i++)
                    {
                        if(strcmp(member[i].name , name) == 0)
                        {
                            read = i;
                            sign = true;
                            break;
                        }
                    }
                    if(sign)
                    {
                        char pass[21];

                        printf("Enter your password :");
                        scanf("%s" , pass);
                        while (getchar() != '\n');

                        if(strcmp(member[read].password , pass) == 0)
                        {
                            printf("\n");
                            printf("Your length of new password can not exceed 20 characters\n");
                            printf("Enter your new password :");
                            scanf("%s" , member[read].password);
                            while (getchar() != '\n');
                            printf("\n");
                            printf("New password save successfully !\n");
                            printf("\n");
                            first = insert(first, "Using 'fixpassword' to fix the password");
                            break;
                        }
                        else
                        {
                            printf("\n");
                            printf("Wrong password ! Please enter the command 'fixpassword' again , and try again\n");
                            printf("Reminder! If this is you first time to use , remember enter 'open' to open a new account\n");
                            printf("\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("\n");
                        printf("Wrong name ! Please enter the command 'fixpassword' again , and try again\n");
                        printf("Reminder! If this is you first time to use , remember enter 'open' to open a new account\n");
                        printf("\n");
                        break;
                    }
                }




                //transfer
            case 't':
                if(strcmp(command , "transfer") == 0)
                {
                    int num1 , num2 , num3;
                    bool sign = false , sign2 = false;
                    char pass[21];
                    printf("Enter want account do you want to transfer money to :");
                    scanf("%d" , &num1);
                    while (getchar() != '\n');

                    for(int i=0 ; i<tmp ; i++)
                    {
                        if(num1 == member[i].account)
                        {
                            read = i;
                            sign = true;
                            break;
                        }
                    }

                    if(sign)
                    {
                        printf("Enter your account : ");
                        scanf("%d" , &num2);
                        while (getchar() != '\n');

                        for(int i=0 ; i<tmp ; i++)
                        {
                            if(num2 == member[i].account)
                            {
                                read2 = i;
                                sign2 = true;
                                break;
                            }
                        }
                        if(sign2)
                        {
                            printf("Enter your password : ");
                            scanf("%s" , pass);
                            while (getchar() != '\n');
                            if(strcmp(pass , member[read2].password) == 0)
                            {
                                printf("How much money do you want to transfer : ");
                                scanf("%d" , &num3);
                                while (getchar() != '\n');

                                if((member[read2].money-num3) >= 0)
                                {
                                    member[read2].money = member[read2].money-num3;
                                    member[read].money = member[read].money+num3;
                                    printf("\n");
                                    printf("Transfer money successfully !\n");
                                    printf("Your balance is %d\n" , member[read2].money);
                                    printf("\n");
                                    first = insert(first, "Using 'transfer' to transfer money");
                                    break;
                                }
                                else
                                {
                                    printf("\n");
                                    printf("Insufficient balance ! If you want to transfer money please enter command 'transfer' again\n");
                                    printf("If you don't know how much money you have , you can enter the command 'check' to check it out\n");
                                    printf("\n");
                                    break;
                                }
                            }
                            else
                            {
                                printf("\n");
                                printf("Wrong password ! Please enter the command 'transfer' again , and try again\n");
                                printf("\n");
                                break;
                            }
                        }
                        else
                        {
                            printf("\n");
                            printf("The account doesn't exist ! Please enter the command 'transfer' again , and try again\n");
                            printf("\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("\n");
                        printf("The account doesn't exist ! Please enter the command 'transfer' again , and try again\n");
                        printf("\n");
                        break;
                    }
                }






            default:
                printf("\n");
                printf("Wrong command , please try again or enter 'help' to check what command you can use\n");
                printf("\n");
        }
    }
}






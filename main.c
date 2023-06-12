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
#define EMPLOYEE_ID_MAX 10





struct bankmember
{
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

struct loan
{
    struct bankmember *user; //提出申請的用戶
    char reason;        //提出申請的理由
    int money;                 //要申請的金額
    char date[11];
    struct loan *next;
};

typedef struct loan Queue_Node;
Queue_Node * front = NULL;
Queue_Node * tail = NULL;
int size=0;

void push(struct bankmember *user,char reason,int money,char* date)
{
    Queue_Node* new_add_node;
    new_add_node = (Queue_Node*)malloc(sizeof(struct loan));

    new_add_node->user = user;
    new_add_node->reason = reason;
    new_add_node->money = money;
    strcpy(new_add_node->date,date);
    new_add_node->next = NULL;

    if(tail==NULL)
    front = new_add_node;
    else
    tail->next=new_add_node;

    tail=new_add_node;
    size++;
}

void *pop()
{
    Queue_Node *pt = front;
    front = front->next;
    free(pt);
    size--;
}

struct loan *getFront()
{
    return front;
}


unsigned int XORbits(unsigned int* A)
{
    unsigned int temp;
    int count =0;
    temp= (*A & 0000011111); //後五碼
    *A = *A >> 5; //前五碼
    temp=*A ^ temp; //前五碼跟後五碼做xor
    for(int i=0;i<5;i++)
    {
        if(temp & 00001)
        {
            count ++; //xor後有幾個1
        }
        temp=temp>>1;
    }

    //is employee:有偶數個1
    if(count/2) return 1;
    //not employee:有奇數個1
    return 0;
}

int main()
{
    char word;
    char identity[15];
    char command[100]={0};
    int tmp = 0 , read = 0 , number = 411410001 , read2 = 0;

    printf("It's a bank database system\n");
    printf("You can enter some instructions to operate this system\n");
    printf("If you have some questions about the system\n");
    printf("You can enter 'help' instruction to find out !\n");
    printf("If this is you first time to use , remember to enter 'open' to open a new account\n");
    printf("\n");
    while(1)
    {
        printf("Please enter your correct identity(employee/bank member):");
        gets(identity);
        if(!strcmp(identity,"employee"))
        {
            unsigned int id=0; //1101011111
            printf("Enter your employee Id:");
            scanf("%x",&id);
            while (getchar() != '\n');

            //not employee
            if(!XORbits(&id))
            {
                printf("ERROR ID!");
            }
            else
            {
                struct node *ope_emp = NULL;
                strcpy(command,"\0");
                while(strcmp(command , "log out") != 0)
                {
                    printf("Enter the command:");
                    fgets(command , 100 , stdin);
                    command[strcspn(command, "\n")] = '\0';
                    switch(command[0])
                    {
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
                                if(!tmp) printf("-----------------------------------No user to sort-------------------------------------\n");
                                ope_emp = insert(ope_emp, "Using 'sortH' to sort people with most money to least");
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
                                if(!tmp) printf("-----------------------------------No user to sort-------------------------------------\n");
                                ope_emp = insert(ope_emp, "Using 'sortL' to sort people with least money to most");
                                break;
                            }

                            else
                            {
                                printf("\n");
                                printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                printf("\n");
                                break;
                            }

                            //loanList & log out
                        case 'l':
                            if(strcmp(command , "loanList") == 0)
                            {
                                if(!size)
                                {
                                    printf("\033[36mThis job has already done!\033[0m\n");
                                    break;
                                }
                                else
                                {
                                    printf("\n");
                                    struct loan *request;
                                    request= front->next;
                                    int a;
                                    printf("We have %d requests\n",size);
                                    while(size)
                                    {
                                        struct loan *temp;
                                        temp=getFront();
                                        printf("The request list is below:\n");
                                        printf("---------------------------------------------------------\n");
                                        printf("Account: %d\n",temp->user->account);
                                        printf("Occupation: %s\n",temp->user->occupation);
                                        printf("Reason: %c\n",temp->reason);
                                        printf("Request money: %d\n",temp->money);
                                        printf("Debt repayment time: %s\n",temp->date);
                                        printf("\n");
                                        printf("Do you allow this request?(Yes: 1 / No: 0): ");
                                        scanf("%d",&a);
                                        while(getchar() != '\n');
                                        if(a==1)
                                        {
                                            temp->user->money += temp->money;  //申請成功者帳戶錢錢++
                                            printf("\033[36mThis request is done\033[0m\n");
                                            printf("---------------------------------------------------------\n");
                                            printf("You have %d request(s) remained\n",size-1);
                                        }
                                        else printf("\033[36mOOPS!We're sorry to hear that!\033[0m\n");
                                        pop();
                                    }
                                    ope_emp = insert(ope_emp, "Using 'loanList' to check who apply for the loan");
                                    printf("---------------------------------------------------------\n");
                                    printf("\033[36mWell done,you handled all the request!\033[0m\n");
                                    printf("\n");
                                    break;
                                }
                            }
                            else if(strcmp(command , "log out") == 0)
                            {
                                printf("\n");
                                printf("Operation Record:\n");
                                //printf("form the newest to the oldest\n");
                                printf("---------------------------------------------------------\n");
                                struct node *ptr2;
                                for(ptr2 = ope_emp ; ptr2 != NULL ; ptr2=ptr2->next)
                                {
                                    printf("%s\n" , ptr2->text);
                                }
                                printf("---------------------------------------------------------\n");
                                break;
                            }
                            else
                            {
                                printf("\n");
                                printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                printf("\n");
                                break;
                            }

                            //exit
                        case 'e':
                            if(strcmp(command , "exit") == 0)
                            {
                                return 0;
                            }


                        //help
                        case 'h':
                            if(strcmp(command , "help") == 0)
                            {
                                printf("\n");
                                printf("All commands and descriptions\n");
                                printf("---------------------------------------------------------\n");
                                printf("\033[32m1. 'help'       -> Print all the commands.\n");
                                printf("2. 'exit'       -> End the program.\n");
                                printf("3. 'sortH'      -> To sort people with most money to least.\n");
                                printf("4. 'sortL'      -> To sort people with least money to most.\n");
                                printf("5. 'loanList'   -> To check the members who want to take out a loan.\n");
                                printf("6. 'log out'    -> Log out.\033[0m\n");
                                printf("---------------------------------------------------------\n");
                                printf("\n");
                                ope_emp = insert(ope_emp, "Using 'help' to check the command");
                                break;
                            }


                        default:
                            printf("\n");
                            printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                            printf("\n");
                    }
                }
            }

        }

        else if (!strcmp(identity,"bank member"))
        {
            strcpy(command,"\0");
            while(strcmp(command , "log out") != 0)
            {
                int log=2;
                printf("For log in, please enter 0 / For create a new account, please enter 1:");
                scanf("%d",&log);
                while (getchar() != '\n');
                if(log == 1)
                {
                    printf("Do you want to input the items from external files?\n");
                    printf("[Y/N]:");
                    scanf("%c" , &word);
                    if(word == 'Y')
                    {
                        char text[100];
                        int count = 0;
                        FILE* fptr;
                        fptr = fopen("D:\\input.txt","r");
                        if(fptr == NULL)
                        {
                            printf("fail to open the file\n");
                        }
                        while(fscanf(fptr , "%s" , text) != EOF)
                        {
                            if(count == 0)
                            {
                                strcpy(member[tmp].name , text);
                                count++;
                            }
                            else if(count == 1)
                            {
                                strcpy(member[tmp].phone , text);
                                count++;
                            }
                            else if(count == 2)
                            {
                                sscanf(text,"%i", &member[tmp].money);
                                count++;
                            }
                            else if(count == 3)
                            {
                                sscanf(text,"%i", &member[tmp].age);
                                count++;
                            }
                            else if(count == 4)
                            {
                                strcpy(member[tmp].occupation , text);
                                count++;
                            }
                            else if(count == 5)
                            {
                                strcpy(member[tmp].password , text);
                            }
                        }
                        fclose(fptr);
                        printf("\n");
                        printf("\033[32;1mOpening account successfully !\033[0m\n");
                        printf("Your bank account is '%d'\n" , number);
                        printf("You can take a piece of paper and write your account and password on it\n");
                        printf("\n");
                        member[tmp].account = number;
                        number++;
                        tmp++;
                        break;
                    }
                    else
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
                        printf("\033[32;1mOpening account successfully !\033[0m\n");
                        printf("Your bank account is '%d'\n" , number);
                        printf("You can take a piece of paper and write your account and password on it\n");
                        printf("\n");

                        member[tmp].account = number;
                        number++;
                        tmp++;
                        break;
                    }
                }

                else if(log == 0)
                {
                    int  num1;
                    bool sign = false , sign2 = false;
                    char pass[21];
                    struct node *ope_mem = NULL;

                    printf("Enter your account : ");
                    scanf("%d" , &num1);
                    while (getchar() != '\n');

                    for(int i=0 ; i<tmp ; i++)
                    {
                        if(num1 == member[i].account)
                        {
                            read2 = i;
                            sign2 = true;
                            break;
                        }
                    }
                    if(sign2)
                    {
                        printf("Enter your password : \033[37m");
                        scanf("%s" , pass);
                        printf("\033[0m");
                        while (getchar() != '\n');
                        if(strcmp(pass , member[read2].password) == 0)
                        {
                            printf("\n");
                            printf("\033[32;1mLog in successful\033[0m\n");
                            strcpy(command,"\0");
                            while(strcmp(command , "log out") != 0)
                            {
                                printf("Enter the command:");
                                fgets(command , 100 , stdin);
                                command[strcspn(command, "\n")] = '\0';
                                switch(command[0])
                                {

                                    //save
                                case 's':
                                    if(strcmp(command , "save") == 0)
                                    {

                                        int num;

                                        printf("Enter how much do you want to save :");
                                        scanf("%d" , &num);
                                        while (getchar() != '\n');

                                        member[read2].money += num;
                                        printf("\n");
                                        printf("\033[32mSave successfully !\033[0m\n");
                                        printf("\n");
                                        ope_mem = insert(ope_mem, "Using 'save' to save money");

                                        break;
                                    }
                                    else
                                    {
                                        printf("\n");
                                        printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                        printf("\n");
                                        break;
                                    }

                                //withdraw
                                case 'w':
                                    if(strcmp(command , "withdraw") == 0)
                                    {

                                        int num , total;

                                        printf("Enter how much money do you want to withdraw :");
                                        scanf("%d" , &num);
                                        while (getchar() != '\n');

                                        total = member[read2].money-num-0.4;
                                        if(total>0)
                                        {
                                            ope_mem = insert(ope_mem, "Using 'withdraw' to withdraw money");
                                            member[read2].money = member[read2].money-num-4;
                                            printf("\n");
                                            printf("\033[32mWithdraw money successfully !\n");
                                            printf("Your deposit now is\033[0m %d\n" , member[read2].money);
                                            printf("\033[32mRemember there will be a $4 handling fee for each withdrawal\033[0m\n");
                                            printf("\n");
                                        }
                                        else
                                        {
                                            printf("\n");
                                            printf("\033[1mDue to the insufficient balance , you can not withdraw your money\n");
                                            printf("Please save enough money !\n");
                                            printf("Reminder! There will be a $4 handling fee for each withdrawal!\033[0m\n");
                                            printf("\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\n");
                                        printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                        printf("\n");
                                    }
                                    break;



                                    //exit
                                case 'e':
                                    if(strcmp(command , "exit") == 0) return 0;

                                    //check
                                case 'c':
                                    if(strcmp(command , "check") == 0)
                                    {
                                        printf("\n");
                                        printf("Your information:\n");
                                        printf("---------------------------------------------------------\n");
                                        printf("Name : %s\n" , member[read2].name);
                                        printf("Phone number : %s\n" , member[read2].phone);
                                        printf("Age : %d\n" , member[read2].age);
                                        printf("Deposit : %d\n" , member[read2].money);
                                        printf("Occupation : %s\n" , member[read2].occupation);
                                        printf("---------------------------------------------------------\n");
                                        printf("\n");
                                        ope_mem = insert(ope_mem, "Using 'check' to check personal information");
                                    }
                                    else
                                    {
                                        printf("\n");
                                        printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                        printf("\n");
                                    }
                                    break;




                                    //fixpassword
                                case 'f':
                                    if(strcmp(command , "fixpassword") == 0)
                                    {
                                        printf("\n");
                                        printf("Your length of new password can not exceed 20 characters\n");
                                        printf("Enter your new password :");
                                        scanf("%s" , member[read2].password);
                                        while (getchar() != '\n');
                                        printf("\n");
                                        printf("\033[32mNew password save successfully !\033[0m\n");
                                        printf("\n");
                                        ope_mem = insert(ope_mem, "Using 'fixpassword' to fix the password");
                                    }
                                    else
                                    {
                                        printf("\n");
                                        printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                        printf("\n");
                                    }
                                    break;




                                    //transfer
                                case 't':
                                    if(strcmp(command , "transfer") == 0)
                                    {
                                        int num2,num3;
                                        printf("Enter what account do you want to transfer money to :");
                                        scanf("%d" , &num3);
                                        while (getchar() != '\n');

                                        for(int i=0 ; i<tmp ; i++)
                                        {
                                            if(num3 == member[i].account)
                                            {
                                                read = i;
                                                sign = true;
                                                break;
                                            }
                                        }
                                        if(sign)
                                        {
                                            printf("How much money do you want to transfer : ");
                                            scanf("%d" , &num2);
                                            while (getchar() != '\n');

                                            if((member[read2].money-num2) >= 0)
                                            {
                                                member[read2].money = member[read2].money-num2;
                                                member[read].money = member[read].money+num2;
                                                printf("\n");
                                                printf("\033[32mTransfer money successfully !\n");
                                                printf("Your balance is \033[0m%d\n" , member[read2].money);
                                                printf("\n");
                                                ope_mem = insert(ope_mem, "Using 'transfer' to transfer money");
                                            }
                                            else
                                            {
                                                printf("\n");
                                                printf("\033[31;1mInsufficient balance ! If you want to transfer money, please enter command 'transfer' again\n");
                                                printf("If you don't know how much money you have , you can enter the command 'check' to check it out\033[0m\n");
                                                printf("\n");
                                            }
                                        }
                                        else
                                        {
                                            printf("\n");
                                            printf("\033[31;1mThe account doesn't exist ! Please enter the command 'transfer' again , and try again\033[0m\n");
                                            printf("\n");
                                            break;
                                        }
                                    }

                                    else
                                    {
                                        printf("\n");
                                        printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                        printf("\n");
                                    }
                                    break;


                                    //loan
                                case 'l':
                                {
                                    if(strcmp(command , "loan") == 0)
                                    {
                                        char reason;
                                        int money;
                                        char date[11];
                                        printf("\n");
                                        printf("user account: %d\n",member[read2].account);
                                        printf("please answer the questions below.\n");
                                        printf("---------------------------------------------------------------------------------------------------------------------------------\n");
                                        printf("Why do you want to apply for this loan?\n");
                                        printf("(personnal factors: p / commercial factors: c / educational factors: e / else: y ):");
                                        scanf("%c",&reason);
                                        while (getchar() != '\n');
                                        printf("How much money do you want to loan:");
                                        scanf("%d",&money);
                                        while (getchar() != '\n');
                                        printf("When will you repay your loan(form:0000/00/00):");
                                        scanf("%s",date);
                                        while (getchar() != '\n');

                                        push((member+read2),reason,money,date);
                                        printf("\n");
                                        printf("\033[32mOk,we have receive your request\n");
                                        printf("Our employees will help you \033[32;1mASAP\033[0m\n");
                                        printf("--------------------------------------------------------------------------------------------------------------------------------\n");
                                        printf("\n");
                                        ope_mem = insert(ope_mem, "Using 'loan' to apply for a loan");
                                    }
                                    //log out
                                    else if(strcmp(command , "log out") == 0)
                                    {
                                        printf("\n");
                                        printf("Operation Record:\n");
                                        //printf("form the newest to the oldest\n");
                                        printf("---------------------------------------------------------\n");
                                        struct node *ptr2;
                                        for(ptr2 = ope_mem ; ptr2 != NULL ; ptr2=ptr2->next)
                                        {
                                            printf("%s\n" , ptr2->text);
                                        }
                                        printf("---------------------------------------------------------\n");
                                        printf("\n");
                                    }
                                    else
                                    {
                                        printf("\n");
                                        printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                        printf("\n");
                                    }
                                    break;
                                }


                                //help
                                case 'h':
                                    if(strcmp(command , "help") == 0)
                                    {
                                        printf("\n");
                                        printf("All commands and descriptions\n");
                                        printf("-----------------------------------------------------------------------------------------\n");
                                        printf("\033[32m1. 'help'       -> Print all the commands.\n");
                                        printf("2. 'exit'       -> End the program.\n");
                                        printf("3. 'open'       -> If you want to open the new account.\n");
                                        printf("4. 'save'       -> If you want to save the money , and you already have a account.\n");
                                        printf("5. 'withdraw'   -> To withdraw your money.\n");
                                        printf("6. 'check'      -> To check personal information.\n");
                                        printf("7. 'fixpassword'-> To change your password.\n");
                                        printf("8. 'transfer'   -> To transfer from your account to another account.\n");
                                        printf("9. 'loan'       -> To apply for a loan request.\n");
                                        printf("10. 'log out'   -> Log out.\033[0m\n");
                                        printf("-----------------------------------------------------------------------------------------\n");
                                        printf("\n");
                                        ope_mem = insert(ope_mem, "Using 'help' to check the command");
                                    }
                                    else
                                    {
                                        printf("\n");
                                        printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                        printf("\n");
                                    }
                                    break;


                                default:
                                    printf("\n");
                                    printf("\033[31;1mThe command is wrong ! Please enter the correct command,or enter 'help' to check what command you can use \033[0m \n");
                                    printf("\n");
                                }
                            }
                        }
                        else
                        {
                            printf("\n");
                            printf("\033[31;1mThe password is wrong ! Please enter the correct password \033[0m \n");
                            printf("\n");
                        }
                    }
                    else
                    {
                        printf("\n");
                        printf("\033[31;1mThe account is wrong! Please enter the correct account \033[0m\n");
                        printf("\n");
                    }
                }
                else printf("\033[31;1mPlease enter the correct command\033[0m\n");
            }
        }
        else
        {
            printf("\033[31;1mWrong identity! \033[0m");
            printf("\n");
        }
    }
    return 0;
}





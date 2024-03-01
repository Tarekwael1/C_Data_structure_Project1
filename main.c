#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
/***********************#includes****************************/
#include "Clinic.c"

/***********************Data Type****************************/
typedef unsigned char      boolean;
typedef unsigned char      uint8  ;
typedef unsigned short     uint16 ;
typedef unsigned int       uint32 ;
typedef unsigned long long uint64 ;
typedef signed char        sint8  ;
typedef signed short       sint16 ;
typedef signed int         sint32 ;
typedef signed long long   sint64 ;
typedef float              float32;
typedef double             float64;

struct Patient
{
    uint32 ID;
    uint8 name[100];
    uint32 time[12];
    uint32 phone_number[15];
};

// Node structure for the linked list
struct Node
{
    struct Patient data;
    struct Node* next;
};

// Queue to hold Patients using linked list
struct Queue
{
    struct Node* Front;
    struct Node* rear;
};


/***********************Prototypes****************************/
void Admen_Mode(void);
void User_Mode(void);
void Enter_Password(void);

// Function to add a new Patient to the queue
void Add_Patient_Record(void);

// Function to edit Patient details in the queue
void Edit_Patient_Record(void);

// Function to delete a Patient from the queue
void Cancel_Reservation(void);

void setColor(uint32 ForgC);

void Clinic_panner(void);

uint32 Get_Length (struct Node *Head_Of_List);

// Function to initialize the Patient queue
void initPatientQueue();


/***********************Variables****************************/
// Global variable for the Patient queue for making it accessible to all the functions defined in that file.
struct Queue Patient_queue;
struct Node ListHead;

uint32 pass_flag = 0;
uint32 Counter = 0;
/***********************Main****************************/
int main()
{
    uint8 Choice1 = 0;
    uint8 Choice2 = 0;
    uint8 Choice3 = 0;
    uint8 name[100];
    // Initialize the student queue
    Patient_queue.Front = NULL;
    Patient_queue.rear = NULL;
    Clinic_panner();
    system("cls");

    uint8 home[] =
        "     ============================\n\
    |  Clinic Management System  |\n\
     ============================\n\
    ";
    while(1)
    {
kk:
        setColor(3);
        printf("\n");
        for(uint32 i=0; home[i]; i++)
        {
            printf("%c", home[i]);
        }
        setColor(15);
        printf("Please choose the number of operation that you want :) \n\n");
        printf("=========================================\n");
        printf("1- Admen mode.\n"
               "2- User mode. \n"
               "3- Exit (Cancel). \n");
        printf("=========================================\n");

        scanf("%i", &Choice1);

        switch(Choice1)
        {
        case 1 :
            system("cls");
            printf("=====> Hello Our Admen <=====\n\n");

            //1)Enter password if true could record Patients
            Enter_Password();
            if(1 == pass_flag)
            {
tt:
                printf("Please choose the number of operation that you want : ");
                printf("\n=========================================\n");
                printf("1- Record Patients.\n"
                       "2- Edit informations. \n"
                       "3- Cancel the record. \n"
                       "4- Exit.\n");
                printf("=========================================\n");
                scanf("%i", &Choice2);

                switch(Choice2)
                {
                case 1://2)Record Patients
                    //get the number of records
                    if(Counter >= 5)
                    {
                        system("cls");
                        setColor(12);
                        printf("Sorry!, Cannot enter anther record \n\n");
                        Sleep(2000);
                        system("cls");
                        setColor(11);
                        goto tt;
                    }
                    else
                    {
                        printf("You Must input sorted IDs \n");
                        Add_Patient_Record();
                        goto tt;
                    }
                    break;
                case 2://3)can edit informations
                    Edit_Patient_Record();
                    goto tt;
                    break;
                case 3://4)can cancel record
                    Cancel_Reservation();
                    goto tt;
                    break;
                case 4:
                    system("cls");
                    goto kk;
                default:
                    printf("Wrong number\n\n");
                }
            }
            break;
        case 2 :
            system("cls");


ss:
            printf("Please choose the number of operation that you want : ");
            printf("\n=========================================\n");
            printf("1- View Patient Record.\n"
                   "2- View Today Reservation . \n"
                   "3- Cancel. \n");
            printf("=========================================\n");
            scanf("%i", &Choice3);
            switch(Choice3)
            {
            case 1:
                View_Patient_Record();
                goto ss;
                break;
            case 2:
                View_Today_Resevation();
                goto ss;
                break;
            case 3:
                goto kk;
                break;
            default:
                printf("Wrong number\n\n");
            }
            break;
        case 3 :
            system("cls");
            exit(1);
            break;
        default :
            printf("Sorry, This choice not available \n");
            return 0;
        }
    }

}

/***********************Definitions****************************/

void View_Patient_Record()
{
    struct Node* current = Patient_queue.Front;
    uint32 PatientID;
    system("cls");
    setColor(9);
    printf("\n    Print Patient :");
    printf("\n    ===============\n\n");
    setColor(11);
    printf("> Enter Patient ID to print: ");
    scanf("%d", &PatientID);


    while (current != NULL)
    {
        if ((current->data.ID) == PatientID)
        {

            system("cls");
            setColor(9);
            printf("   ========== Personal Data ==========\n");
            setColor(15);
            printf("    - Name             : %s\n", current->data.name);
            printf("    - Phone            : %s\n", current->data.phone_number);
            setColor(9);
            printf("   ==========  Record Data   ==========\n");
            setColor(15);
            printf("    - ID               : %d\n",  current->data.ID);
            printf("    - Time             : %s\n",  current->data.time);
            setColor(9);
            printf("   ===================================\n");
            setColor(7);
            Sleep(5000);
            system("cls");
            return;
        }


        current = current->next;

    }
    setColor(12);
    printf(">>> This ID < %d > not found <<< \n", PatientID);

}


// Function to list all Patient in the queue
void View_Today_Resevation()
{
    struct Node* current = Patient_queue.Front;

    if (current == NULL)
    {
        setColor(12);
        printf("\n>>> No Patients Found <<<");
        Sleep(2000);
        system("cls");
        return;
    }
    system("cls");
    setColor(9);
    printf("\n     > List All Patients ");
    printf("\n  ===========================\n");
    setColor(6);
    printf("   =====+======================\n");
    printf("  | ID  |        Name          |\n");
    printf("   =====+======================\n");
    setColor(14);



    while (current != NULL)
    {
        printf("  | %-4d|  %-20s|\n", current->data.ID, current->data.name);
        printf("   -----+----------------------\n");

        current = current->next;
    }
    Sleep(5000);
    system("cls");
}








void Enter_Password(void)
{
    uint32 i = 0;
    uint32 Int_password = 0, password = 1234;
    setColor(11);
    printf("Please enter the password : ");
    for(i = 0; i < 3; i++)
    {
        scanf("%i", &Int_password);
        if(password == Int_password)
        {
            printf("Please wait");
            for(uint32 j = 0; j < 6; j++)
            {
                printf(".");
                Sleep(200);
            }
            pass_flag = 1;
            setColor(10);
            printf("\n\nCorrect password \n");
            Sleep(2000);
            setColor(11);
            system("cls");
            break;
        }
        else
        {
            printf("Please wait");
            for(uint32 j = 0; j < 6; j++)
            {
                printf(".");
                Sleep(200);
            }
            setColor(12);
            printf("\n\n Incorrect Password \n");

            if(2 == i)
            {
                Sleep(2000);
                system("cls");
                break;
            }
            else
            {
                setColor(11);
                pass_flag = 0;
                printf("Please try again : ");
            }
        }
    }
    //3 tries if the 3 are incorrect close the site or return the main padg
}


// Function to add a new Patient to the queue
void Add_Patient_Record(void)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }
    system("cls");
    setColor(9);
    printf("\n    Insert new Patient :");
    printf("\n    ====================\n\n");
    setColor(11);
    printf("Please choose from 1 to 5 (do not repeat it more than one time)\n");
    printf(">> Enter Patient ID :");
    setColor(7);
    scanf("%d", &newNode->data.ID);
    setColor(11);
    printf(">> Enter Patient Name :");
    setColor(7);
    getchar(); // consume the newline character left in the input buffer
    fgets(newNode->data.name, sizeof(newNode->data.name), stdin);
    newNode->data.name[strcspn(newNode->data.name, "\n")] = '\0'; // remove the newline character
    setColor(14);
    printf("\nThere are many slots\n ===>(2 / 2.5  / 3 / 4 / 4.5)<===\n""Please choose one and do not choose it again in the same day\n\n");
    setColor(11);
    printf(">> Enter Date of record (hh:mm): ");
    setColor(7);
    scanf("%s", newNode->data.time);
    setColor(11);
    printf(">> Enter Patient Phone :");
    setColor(7);
    scanf("%s", newNode->data.phone_number);
    setColor(11);
    newNode->next = NULL;

    if (Patient_queue.rear == NULL)
    {
        Patient_queue.Front = newNode;
        Patient_queue.rear = newNode;
    }
    else
    {
        Patient_queue.rear->next = newNode;
        Patient_queue.rear = newNode;
    }

    system("cls");
    setColor(10);
    Counter++;
    printf("\n\n  >>> Patient Recorded successfully <<< \n");
    Sleep(2000);
    system("cls");
    setColor(11);
}


// Function to edit Patient details in the queue
void Edit_Patient_Record(void)
{
    //By Id if it is there access the edit if not print incorrect message
    system("cls");
    uint32 chose;
    uint32 option;
    uint32 x;
    uint32 PatientID;
    struct Node* current = Patient_queue.Front;
    setColor(9);
    printf("\n    Edit Patient :");
    printf("\n    ==============\n\n");
    setColor(11);
    printf("> Enter Patient ID to Edit: ");
    scanf("%d", &PatientID);
    while (current != NULL)
    {
        if (current->data.ID == PatientID)
        {
            system("cls");
            setColor(9);
            printf("\n    Edit Patient :");
            printf("\n    ==============\n\n");
            setColor(7);
            printf("      1 > Update Personal Data.\n");
            printf("      2 > Update Record Data.\n\n");
            setColor(11);
            printf("> Enter a number of operation that needed :");
            setColor(7);
            scanf("%d", &chose);
            setColor(15);
            switch(chose)
            {
            case 1 :
                printf("\n     1 > Edit Phone.\n");
                printf("     2 > Edit Time.\n");
                printf("     2 > Edit Age.\n");
                setColor(11);
                printf("\n > Enter a number of operation that needed : ");
                setColor(7);
                scanf("%d",&option);
                switch(option)
                {
                case 1 :
                    setColor(6);
                    printf("\nCurrent Phone : %s\n", current->data.phone_number);
                    setColor(11);
                    printf("Enter new Phone: ");
                    setColor(7);
                    scanf("%s", current->data.phone_number);
                    break;
                case 2 :
                    setColor(6);
                    printf("Current Name : %s\n", current->data.name);
                    setColor(11);
                    printf("Enter new Name : ");
                    setColor(7);
                    getchar();
                    fgets(current->data.name, sizeof(current->data.name), stdin);
                    current->data.name[strcspn(current->data.name, "\n")] = '\0';
                    break;
                default:
                    setColor(4);
                    printf("\n    Wrong option, Try again!\n");
                    break;
                }
                break;
            case 2:
                printf("\n     1 > Edit Id .\n");
                printf("     2 > Edit Time.\n");
                setColor(11);
                printf("\n > Enter a number of operation that needed : ");
                setColor(7);
                scanf("%d",&x);
                switch(x)
                {
                case 1 :
                    setColor(6);
                    printf("Current ID : %d\n", current->data.ID);
                    setColor(11);
                    printf("Enter ID : ");
                    setColor(7);
                    scanf("%d", &current->data.ID);
                    break;
                case 2 :
                    setColor(6);
                    printf("Current Time : %d\n", current->data.time);
                    setColor(11);
                    printf("Enter Time : ");
                    setColor(7);
                    scanf("%d", &current->data.time);
                    break;
                default:
                    setColor(4);
                    printf("\n    Wrong option, Try again!\n");
                    break;
                }
                break;
            default:
                setColor(4);
                printf("\n    Wrong option, Try again!\n");
                break;
            }
            setColor(10);
            printf(">>> Patient Edited successfully <<<\n");
            Sleep(2000);
            system("cls");
            return;
        }

        current = current->next;
    }
    setColor(12);
    printf("Patient with ID %d not found.\n", PatientID);
}


// Function to delete a Patient from the queue
void Cancel_Reservation(void)
{

    uint32 PatientID;
    uint32 option;
    struct Node* current = Patient_queue.Front;
    struct Node* previous = NULL;
    system("cls");
    setColor(9);
    printf("\n    Delete Patient :");
    printf("\n    ==============\n\n");
    setColor(11);
    printf("> Enter Patient ID to Delete: ");
    scanf("%d", &PatientID);

    while (current != NULL)
    {
        if (current->data.ID == PatientID)
        {
            printf("\n  > Name : %s\n", current->data.name);
            printf("  > ID   : %d\n", current->data.ID);
            setColor(12);
            printf("\n > Are you sure to delete this Patient ?\n");
            setColor(11);
            printf("\n > Press 1 to delete, 0 to discard :");
            setColor(7);
            scanf("%d", &option);
            if(option == 1)
            {
                if (current == Patient_queue.Front)
                {
                    Patient_queue.Front = current->next;
                    free(current);
                }
                else if (current == Patient_queue.rear)
                {
                    Patient_queue.rear = previous;
                    previous->next = NULL;
                    free(current);
                }
                else
                {
                    previous->next = current->next;
                    free(current);
                }
                setColor(10);
                printf(">>> Patient Deleted successfully <<<\n");
                Counter--;
                Sleep(2000);
                system("cls");
                setColor(11);
                return;
            }
            else
                return;
        }

        previous = current;
        current = current->next;
    }
    setColor(12);
    printf(">>> Patient with ID %d not found <<<\n", PatientID);
}

void setColor(uint32 ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
    SetConsoleTextAttribute(hStdOut, wColor);
}

void Clinic_panner(void)
{
    uint8 jumpControlAtBottom = 0;
    uint8 shiftControl = 0;
    uint8 panner[] =
        "                                                                                       \n\
                        EE       EE EEEEE  E       EEEEE     EEEEE       EE   EE    EEEEE       \n\
                        EE   E   EE E      E     EE        EE     EE    EE E E EE   E           \n\
                        EE   E   EE EEEEE  E    EE        EE       EE  EE   E   EE  E EEE       \n\
                         EE E E EE  E      E     EE        EE     EE   EE   E   EE  E           \n\
                          EE   EE   EEEEE  EEEEE   EEEEE     EEEEE     EE       EE  EEEEE       \n\
                                                                                                \n\
                                                                                                \n\
                                           EEEEE     EE   EE  EE EEEE                           \n\
                                         EE     EE   EE   EE  EEE                               \n\
                                        EE       EE  EE   EE  EE                                \n\
                                         EE     EE   EE   EE  EE                                \n\
                                           EEEEE      EEEEE   EE                                \n\
                                                                                                \n\
                           EEEEE    E       E     EE    E     E     EEEEE                       \n\
                          EE        E       E     E E   E     E    EE                           \n\
                         EE         E       E     E  E  E     E   EE                            \n\
                          EE        E       E     E   E E     E    EE                           \n\
                           EEEEE    EEEE    E     E    EE     E     EEEEE                       \n\
                                                                                                \n\
                                                              Author : Eng. Tarek Wael          \n\
";
    for (jumpControlAtBottom = 0; jumpControlAtBottom < 30; ++jumpControlAtBottom)
    {
        printf("\n");
    }
    setColor(9);
    for(uint32 i=0; panner[i]; i++)
    {
        printf("%c", panner[i]);
    }
    printf("\n");
    setColor(7);
    for (shiftControl = 0; shiftControl < 30; shiftControl++)
    {
        Sleep(200);
        printf("\n");
    }
}


/***********************END Project****************************/


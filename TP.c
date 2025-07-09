

/*********************************** NOTE: Pour les booléens ***********************************/
/* Dans ce programme, on définit les booléens comme des entiers auxquels on affecte 1 pour la  */
/* valeur "true" et 0 pour la valeur "false", au lieu d'utiliser la bibliothèque <stdbool.h>   */
/***********************************************************************************************/



/*** Bibliothèques ***/
#include "queue.h"
#include <conio.h>
/*********************/




/********* Constantes et variables *********/

#define KEY_ENTER 13            // Code ASCII de la touche Entrer

time_t t;                       // Variable qui nous permet de récupérer la date d'execution du programme en secondes
struct tm currentDate;          // Variable pour transformer la date d'execution du programme en format calendrier

/*******************************************/



void main() {

    srand(time(0));

    t = time(NULL);
    currentDate = *localtime(&t);

    int choice;
    int exit = 0;
    int exit2 = 0;
    int exit4 = 0;
    int FileGenerated = 0;
    int QueueGenerated = 0;
    int NextDayScheduled = 0;
    int FilesUpdated = 0;

    clearScreen();

    setColor(CYAN); printf("\n\n\t\t\t\t ____________________________________________________\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|"); setColor(WHITE); printf("     Higher National School of Computer Science     "); setColor(CYAN); printf("|\n"); Sleep(50);
    printf("\t\t\t\t|                       - ESI -                      |\n"); Sleep(50);
    printf("\t\t\t\t|____________________________________________________|\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|"); setColor(WHITE); printf("    1st Year Preparatory Class - University Year    "); setColor(CYAN); printf("|\n"); Sleep(50);
    printf("\t\t\t\t|                     2024 / 2025                    |\n"); Sleep(50);
    printf("\t\t\t\t|____________________________________________________|\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|   Directed by :                                    |\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|       >>"); setColor(WHITE); printf(" Rachid Mustapha Amine                     "); setColor(CYAN); printf("|\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|       >>"); setColor(WHITE); printf(" Ait Boussad Ramy Idir                     "); setColor(CYAN); printf("|\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|   Section :"); setColor(WHITE); printf(" C                         "); setColor(CYAN); printf("Group :"); setColor(WHITE); printf(" 12   "); setColor(CYAN); printf("|\n"); Sleep(50);
    printf("\t\t\t\t|____________________________________________________|\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|   TP1 :"); setColor(WHITE); printf(" Linked Lists & Priority Queues             "); setColor(CYAN); printf("|\n"); Sleep(50);
    printf("\t\t\t\t|____________________________________________________|\n"); Sleep(50);
    printf("\t\t\t\t|                                                    |\n"); Sleep(50);
    printf("\t\t\t\t|   Execution Date :"); setColor(WHITE); printf(" %02d/%02d/%04d                      ", currentDate.tm_mday, currentDate.tm_mon+1, currentDate.tm_year + 1900); setColor(CYAN); printf("|\n"); Sleep(50);
    printf("\t\t\t\t|____________________________________________________|\n"); Sleep(50);


    setColor(GRAY);
    printf("\n\n\nPRESS ENTER TO CONTINUE ...");
    while (getch() != KEY_ENTER);

    maillonEmp *Tete = NULL;
    maillon_de_liste *ListeDF = NULL;
    int NumerosDeCons = 0;


    do {

        clearScreen();
        
        setColor(RED); printf("\t    __\n");
        setColor(RED); printf("\t   ||||");        setColor(CYAN); printf("       _ __ ___   ___ _ __  _   _  \n");
        setColor(RED); printf("\t==========");        setColor(CYAN); printf("   | '_ ` _ \\ / _ \\ '_ \\| | | | \n");
        setColor(RED); printf("\t==========");        setColor(CYAN); printf("   | | | | | |  __/ | | | |_| | \n");
        setColor(RED); printf("\t   ||||");        setColor(CYAN); printf("      |_| |_| |_|\\___|_| |_|\\__,_| \n");
        setColor(RED); printf("\t    --\n"); 


        setColor(WHITE);

        printf("\n\n\t1. | Generate a list of employee's medical records\n");
        printf("\t2. | Manage employees' records\n");
        printf("\t3. | Create a priority appointment queue\n");
        printf("\t4. | Manage appointments\n");
        printf("\t5. | Schedule appointments of the next day\n");
        printf("\t6. | Update the records and consultations file\n");
        printf("\t7. | Exit the program\n");
        printf("\nChoose an option : ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {

        case 1:

            if (!FileGenerated) {

                clearScreen();

                int choice1;
                char Gen;
                
                setColor(CYAN);
                printf("\n\n- Generating a list of employee's medical records\n\n");
                setColor(GRAY);
                printf("                      ____________________         ________________         _________________                \n");
                printf("                     |  |    |      |     |       |   |   |        |       |   |   |         |               \n");
                printf("           HEAD--->  |ID|Name|LCDate|.....|------>|   |   |        |------>|   |   |         | -----[ NULL    \n");
                printf("                     |__|____|______|_____|       |___|___|________|       |___|___|_________|               \n\n");
                setColor(WHITE);
                printf("- To generate a list, the program needs an EmpRecords.txt file :\n\n");
                setColor(CYAN);
                printf("\t\t _________________________________________________________________________________________________________ \n");
                printf("\t\t|                                                                                                         |\n");
                printf("\t\t|\t\t\t\t\t\tUsage Guide                                               |\n");
                printf("\t\t|                                                                                                         |\n");
                printf("\t\t|");setColor(WHITE);printf("\t- The file must be placed within the folder of the program.");setColor(CYAN);printf("                                       |\n");
                printf("\t\t|");setColor(WHITE);printf("\t- The file is built as follows :");setColor(CYAN);printf("                                                                  |\n");
                printf("\t\t|                                                                                                         |\n");
                printf("\t\t|");setColor(WHITE);printf("\t\t- Each line represents a medical record with multiple fields, and each field");setColor(CYAN);printf("              |\n");
                printf("\t\t|");setColor(WHITE);printf("\t\t  is delimited by the special character \";\", dates are written following the");setColor(CYAN);printf("              |\n");
                printf("\t\t|");setColor(WHITE);printf("\t\t  DD/MM/YYYY format, if there is no return-to-work date, you can write it as");setColor(CYAN);printf("              |\n");
                printf("\t\t|");setColor(WHITE);printf("\t\t  two delimiters one after the other with no blank space in between, or directly");setColor(CYAN);printf("          |\n");
                printf("\t\t|");setColor(WHITE);printf("\t\t  write the history after the last consultation date delimiter.");setColor(CYAN);printf("                           |\n");
                printf("\t\t|                                                                                                         |\n");
                printf("\t\t|");setColor(GRAY);printf("\t       ....................................................................................");setColor(CYAN);printf("       |\n");
                printf("\t\t|");setColor(GRAY);printf("\t\t34567890;Ahmad Mansour;2;20/02/2025;;Pre-employment,Periodic.");setColor(CYAN);printf("                             |\n");
                printf("\t\t|");setColor(GRAY);printf("\t\t63808066;Fella Benazouz;0;13/10/2024;Pre-employment,Occupational-disease,Periodic.");setColor(CYAN);printf("        |\n");
                printf("\t\t|");setColor(GRAY);printf("\t       ....................................................................................");setColor(CYAN);printf("       |\n");
                printf("\t\t|                                                                                                         |\n");
                printf("\t\t|_________________________________________________________________________________________________________|\n");
                setColor(WHITE);
                printf("\n\n 1. | Generate a random file\n");
                printf(" 2. | Use an existing file\n");
                printf("\nChoose an option : ");

                scanf("%d", &choice1);
                getchar();

                switch (choice1) {

                case 1:
                    
                    setColor(RED);
                    printf("\n\n Generating a random file will overwrite any EmpRecords.txt file - as well as the Consultations.txt\n");
                    printf(" file - that exist within the programs directory. Would you like to proceed ? (y/n) : ");
                    setColor(WHITE);
                    
                    scanf("%c", &Gen);
                    while (getchar() != '\n');

                    if (Gen == 'y' || Gen == 'Y') {

                        int numEmp;
                        printf("\nHow many employees would you like to simulate ? : ");
                        scanf("%d", &numEmp);
                        getchar();
                        generateEmpRecord(numEmp, currentDate, t);
                        GenerateEmpList(&Tete);
                        ResetConsultationsFile();
                        GenerateConsultationsFile(Tete, currentDate);
                        FileGenerated = 1;

                    }

                    setColor(GRAY);
                    printf("\n\nPRESS ENTER TO CONTINUE ...");
                    setColor(WHITE);
                    while (getch() != KEY_ENTER);

                    break;
                
                case 2:
                    
                    FileGenerated = GenerateEmpList(&Tete);
                    if (FileGenerated) GenerateConsultationsFile(Tete, currentDate);
                    
                    setColor(GRAY);
                    printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                    setColor(WHITE);
                    while (getch() != KEY_ENTER);
                    break;
                
                default:

                    setColor(RED);
                    printf("\nInvalid choice.");
                    setColor(WHITE);

                    setColor(GRAY);
                    printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                    setColor(WHITE);
                    while (getch() != KEY_ENTER);
                    
                    break;

                }

            } else {

                setColor(RED);
                printf("\nYou already generated a list of employees' medical records.");

                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            }
            
            break;

        case 2:

            if (FileGenerated) {

                do {

                    clearScreen();

                    int choice2;

                    setColor(CYAN);
                    printf("\n\n- Managing employees' medical records : \n\n");
                    setColor(WHITE);
                    printf("\t1. | Print the records list\n");
                    printf("\t2. | Add a record\n");
                    printf("\t3. | Update a record\n");
                    printf("\t4. | Delete a record\n");
                    printf("\t5. | Exit\n");
                    printf("\nChoose an option : ");

                    scanf("%d", &choice2);
                    getchar();

                    switch (choice2) {

                    case 1:
                        
                        PrintEmpList(Tete);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    case 2:

                        AddToEmpList(Tete, currentDate);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    case 3:

                        UpdateEmpList(Tete, currentDate);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    case 4:

                        DeleteFromEmpList(&Tete);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;
                    
                    case 5:
                        
                        exit2 = 1;

                        break;
                    
                    default:

                        setColor(RED);
                        printf("\nInvalid choice.");
                        setColor(WHITE);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;
                        
                    }

                } while (!exit2);

            } else {

                setColor(RED);
                printf("\nYou must generate a list of employees' records first (Option 1).\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            }

            exit2 = 0;

            break;

        case 3:

            if (FileGenerated && !QueueGenerated) {

                clearScreen();

                setColor(CYAN);
                printf("\n\n- Generating a priority appointment queue\n\n");
                setColor(GRAY);
                printf("                  ____________________         ______________________                         ________________                \n");
                printf("                 |                    |       |                      |                       |                |               \n");
                printf("       HEAD--->  |  1. Work Accident  |------>| 2. Occupat. disease  |------> ....... ------>|  4. Periodic   | -----[ NULL    \n");
                printf("                 |____________________|       |______________________|                       |________________|               \n");
                printf("                           ||                            ||                                          ||                       \n");
                printf("                    _______||________                    NULL                                  _______||_______                \n");
                printf("                   |                 |                                                       |                |               \n");
                printf("      First-IN---> |    Employee 1   |                                                       |   Employee 1   |               \n");
                printf("                   |_________________|                                                       |________________|               \n");
                printf("                           ||                                                                        ||                       \n");
                printf("                           NULL                                                                _______||_______                \n");
                printf("                                                                                             |                |               \n");
                printf("                                                                                             |   Employee 2   |               \n");
                printf("                                                                                             |________________|               \n");
                printf("                                                                                                     ||                       \n");
                printf("                                                                                                     NULL                      \n");

                setColor(WHITE);
                InitialiserFile(&ListeDF);
                CreerFilePrioritaire(&ListeDF, &NumerosDeCons);
                ResetConsultationsFile();
                QueueGenerated = 1;

                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            } else if (QueueGenerated) {

                setColor(RED);
                printf("\nYou already generated a priority queue.\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            } else {

                setColor(RED);
                printf("\nYou must generate a list of employees' medical records first (Option 1).\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            }

            break;

        case 4:

            if (QueueGenerated) {

                do {

                    clearScreen();

                    int choice4;

                    setColor(CYAN);
                    printf("\n\n- Managing appointments : \n\n");
                    setColor(WHITE);
                    printf("\t1. | Display the priority queue\n");
                    printf("\t2. | Add an appointment\n");
                    printf("\t3. | Reschedule an appointment\n");
                    printf("\t4. | Cancel an appointment\n");
                    printf("\t5. | Close an appointment\n");
                    printf("\t6. | Exit\n");
                    printf("\nChoose an option : ");

                    scanf("%d", &choice4);
                    getchar();

                    switch (choice4) {

                    case 1:

                        PrintQueue(ListeDF);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;
                    
                    case 2:
                        
                        AddAppointment(&Tete, &ListeDF, &NumerosDeCons);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    case 3:

                        RescheduleAppointment(&Tete, &ListeDF, &NumerosDeCons);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    case 4:

                        CancelAppointment(&Tete, &ListeDF, &NumerosDeCons);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    case 5:

                        CloseAppointment(Tete, &ListeDF, currentDate);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    case 6:

                        exit4 = 1;

                        break;
                    
                    default:

                        setColor(RED);
                        printf("\nInvalid choice.");
                        setColor(WHITE);

                        setColor(GRAY);
                        printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                        setColor(WHITE);
                        while (getch() != KEY_ENTER);

                        break;

                    }

                } while (!exit4);

            } else {

                setColor(RED);
                printf("\nYou must generate a list of employees' records and create a priority appointment queue first (Option 1 & 3).\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            }

            exit4 = 0;

            break;

        case 5:

            if (QueueGenerated && !NextDayScheduled) {

                char choice5;

                setColor(CYAN);
                printf("\n Usage Guide :");
                setColor(WHITE);
                printf("\n - Before scheduling the appointments of the next-day, you need to make sure you closed all the appointments");
                printf("\n  of the day, or else the data will be lost and the appointments erased. Additionaly, it may cause unwanted lags");
                printf("\n  on the system. Proceed with caution.");

                setColor(RED);
                printf("\n\n Are you sure you want to schedule the next-day appointments ? (y/n) : ");
                setColor(WHITE);

                scanf("%c", &choice5);
                while (getchar() != '\n');

                if (choice5 == 'y' || choice5 == 'Y') {

                    ScheduleNextDayAppointments(Tete, ListeDF, currentDate);
                    NextDayScheduled = 1;

                    setColor(GRAY);
                    printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                    setColor(WHITE);
                    while (getch() != KEY_ENTER);

                }

            } else if (NextDayScheduled) {

                setColor(RED);
                printf("\nYou already scheduled the next day appointments.\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            } else {

                setColor(RED);
                printf("\nYou must generate a list of employees' records and create a priority appointment queue first (Option 1 & 3).\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            }

            break;

        case 6:

            if (NextDayScheduled && !FilesUpdated) {

                UpdateEmpRecordsFile(Tete);
                UpdateConsFile(ListeDF);
                FilesUpdated = 1;

                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            } else if (FilesUpdated) {

                setColor(RED);
                printf("\nYou already updated the files.\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            } else {

                setColor(RED);
                printf("\nYou must first schedule the next-day appointments (Option 5).\n");
                
                setColor(GRAY);
                printf("\n\n\nPRESS ENTER TO CONTINUE ...");
                setColor(WHITE);
                while (getch() != KEY_ENTER);

            }

            break;
            
        case 7:

            char choice7;
            setColor(RED);
            printf("\nAre you sure you want to exit the program ? Any changes to the file not saved will be lost (y/n) : ");
            setColor(WHITE);
            scanf("%c", &choice7);
            while (getchar() != '\n');

            if (choice7 == 'y' || choice7 == 'Y') {
                
                exit = 1;
                LibererListe(Tete);
                LibererLFile(ListeDF);
                printf("\nExiting...\n\n\n");
                Sleep(1000);

            }

            break;
        
        default:

            setColor(RED);
            printf("\nInvalid choice.");

            setColor(GRAY);
            printf("\n\n\nPRESS ENTER TO CONTINUE ...");
            setColor(WHITE);
            while (getch() != KEY_ENTER);

            break;

        }


    } while (!exit);
    
}

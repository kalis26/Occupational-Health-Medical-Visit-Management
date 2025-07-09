

// Bibliothèque regroupant les fonctions qui permettent de manipuler les files prioritaires
// afin d'automatiser les consultations médicales selon le jour à partir du fichier
// Consultations.txt, auxquelles on pourra ajouter, annuler, reprogrammer et fermer des 
// consultations selon les circonstances.



/******* Documentation *******/

// C Documentation : https://devdocs.io/c/
// TutorialsPoint : https://www.tutorialspoint.com/c_standard_library/index.htm
// GeeksForGeeks : https://www.geeksforgeeks.org/c-programming-language/?ref=shm
// BroCode : https://www.youtube.com/@BroCodez

/*****************************/



/************************************** NOTE: Pour les booléens *************************************/
/* Dans cette bibliothèque, on définit les booléens comme des entiers auxquels on affecte 1 pour la */
/* valeur "true" et 0 pour la valeur "false", au lieu d'utiliser la bibliothèque <stdbool.h>        */
/****************************************************************************************************/




/*** Bibliothèques ***/
#include "linkedlist.h"
/*********************/






/******************* Structures de données *******************/

typedef struct Cell {                       // Structure se composant des informations de consultation et d'un champ adresse
                                            // qui pointe vers le maillon suivant

    char ID[MAX_LENGTH_ID];                 // ID
    char Name[MAX_LENGTH_NAME];             // Nom complet
    char ConsReason[MAX_LENGTH_HIST];       // La raison de consultation
    struct Cell *adr;                       // Pointeur qui pointe le maillon suivant de type struct Cell

} maillon_de_file;                          // On définit un type maillon_de_file qu'on chaine pour avoir une liste

typedef struct Qtypecell {                  // Structure se composant de deux pointeurs vers des structures de type maillon_de_file

    maillon_de_file *T;                     // Pointeur vers la tete
    maillon_de_file *Q;                     // Pointeur vers la queue

} File;                                     // On définit un type File qui constituera notre file d'attente

typedef struct Ltypecell {                  // Strucuture se composant de différentes informations et d'un champ adresse qui
                                            // pointe vers le maillon suivant

    int priorite;                           // La priorité du maillon représenté par un entier
    File *File;                             // Pointeur vers une file d'attente
    struct Ltypecell *adr;                  // Pointeur qui pointe le maillon suivant de type struct Ltypecell

} maillon_de_liste;                         // On définit un type maillon_de_liste qu'on chaine pour avoir une liste de files
                                            // qui constituera notre système de file prioritaire

/*************************************************************/






/************************* Machine Abstraite **************************/

void Allouer_Liste(maillon_de_liste **P) {

    *P = (maillon_de_liste*)malloc(sizeof(maillon_de_liste));   // On alloue un espace pour un maillon de liste
    (*P)->File = (File*)malloc(sizeof(File));                   // On alloue de l'espace pour la structure de file a l'interieur de la liste
    (*P)->File->T = NULL;                                       // On initialise la tete de la file a NIL
    (*P)->File->Q = NULL;                                       // On initialise la queue de la file a NIL
    
}

void Allouer_File(maillon_de_file **P) {
    *P = (maillon_de_file*)malloc(sizeof(maillon_de_file));     // On alloue un espace pour un maillon de file
}

maillon_de_liste* Suivant_Liste(maillon_de_liste *ListeF) {
    return ListeF->adr;                                         // On renvoie le champ adr d'un maillon de liste
}

maillon_de_file* Suivant_File(maillon_de_file *P) {
    return P->adr;                                              // On renvoie le champ adr d'un maillon de file
}

int FileVide(File *File) {
    return (File->T == NULL);                                   // Si la tete pointe le NIL -> Vrai
}


void Enfiler(maillon_de_liste *ListeF, maillon_de_file *Cible, int Prio) {

    while (Prio != ListeF->priorite) ListeF = Suivant_Liste(ListeF);    // Tant que la priorite recherchee n'est pas atteinte on traverse la liste

    if (!FileVide(ListeF->File)) ListeF->File->Q->adr = Cible;  // Si la file n'est pas vide on chaine la queue avec la cible
    else ListeF->File->T = Cible;   // Sinon la tete sera la cible

    ListeF->File->Q = Cible;    // On met a jour la queue a la cible
    Cible->adr = NULL;          // Et on met a jour son adresse pour qu'elle pointe au NIL

}

void Defiler(maillon_de_liste *ListeF, maillon_de_file **Cible) {

    while (ListeF != NULL && FileVide(ListeF->File)) ListeF = Suivant_Liste(ListeF);   // On cherche la premiere priorite dont la file n'est pas vide

    if (ListeF == NULL) {   // Si la liste de files est vide (erreur)

        setColor(RED);
        printf("\n\nThe queue is empty.\n\n");
        setColor(WHITE);

    } else {                // Sinon

        *Cible = ListeF->File->T;                               // Notre cible sera la tete de la queue
        ListeF->File->T = Suivant_File(*Cible);                 // La nouvelle tete de la file sera le suivant de la cible
        if (FileVide(ListeF->File)) ListeF->File->Q = NULL;     // Si notre nouvelle file est vide on met a jour la queue
        (*Cible)->adr = NULL;                                   // On met a jour l'adresse de la cible a NIL

    }

}

/**********************************************************************/






/**************** Initialisation et création de la file prioritaire ****************/
/*=================================================================================*/



/******** Procédure qui permet d'initialiser la liste de files avec 4 priorités ********/

void InitialiserFile(maillon_de_liste **ListeDeFiles) {

    *ListeDeFiles = NULL;
    maillon_de_liste *P = NULL;
    maillon_de_liste *Q = NULL;

    for (int i = 4; i > 0; i--) {   // On va creer quatres priorites deja connues

        Allouer_Liste(&P);  // On alloue un maillon
        P->adr = Q;         // On affecte a son champ adr le maillon Q (qui est NULL au debut)
        P->priorite = i;    // On affecte la priorite
        Q = P;              // On met Q egale a P pour avancer dans le chainage

        // Ici on va chainer de facon inverse (le premier maillon qu'on alloue est en realite le dernier de la liste)

    }

    *ListeDeFiles = P;  // On renvoie la tete qui est la premiere priorite apres notre boucle (P.priorite = 1)

}

/***************************************************************************************/






/******* Fonction qui renvoie le degré priorité selon la raison de consultation *******/

int GetPriority(maillon_de_file *Cible) {

    // On va comparer avec nos raisons de cons. et on renvoie les priorites

    if (strcmp(Cible->ConsReason, "Work-accident") == 0) return 1;
    if (strcmp(Cible->ConsReason, "Occupational-disease") == 0) return 2;
    if (strcmp(Cible->ConsReason, "Return-to-work") == 0 || strcmp(Cible->ConsReason, "Pre-employment") == 0) return 3;
    if (strcmp(Cible->ConsReason, "Periodic") == 0) return 4;

}

/**************************************************************************************/






/***** Procédure qui permet de créer la file prioritaire à partir du fichier Consultations.txt *****/
/*========== tout en gardant le nombres de consultations programmées pour ne pas dépasser =========*/
/*=================================== 10 consultations par jour ===================================*/

int CreerFilePrioritaire(maillon_de_liste **ListeF, int *NumAppoint) {

    FILE *file = fopen("Consultations.txt", "r");   // On ouvre le fichier
    if (file == NULL) {
        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return 0;
    }

    *NumAppoint = 0;    // On initialize le nombre de consultations totales du jour (10 max.)

    char buffer[MAX_BUFFER_SIZE];
    maillon_de_file *P;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {   // Tant que le fichier n'arrive pas a sa fin

        if (strcmp(buffer, "\n") != 0) {    // Si une ligne entiere est differente du /n

            Allouer_File(&P);   // On alloue un maillon de file
            P->adr = NULL;      // On affecte a son champ adr le NIL

            // On separe selon les delimiteurs et on affecte chaque partie

            char *partie = strtok(buffer, ";");
            strcpy(P->ID, partie);
            partie = strtok(NULL, ";");
            strcpy(P->Name, partie);
            strtok(NULL, ";");
            partie = strtok(NULL, ".");
            CorrectHist(partie);
            strcpy(P->ConsReason, partie);

            int priority = GetPriority(P);  // On recupere la priorite du maillon
            Enfiler(*ListeF, P, priority);  // On enfile dans la liste de files selon la priorite recuperee

            (*NumAppoint)++;    // On incremente le nombre total de cons

        }

    }

    fclose(file);   // On ferme le fichier

    setColor(GREEN);
    printf("\nPriority queue generated successfully.");
    setColor(WHITE);

    return 1;

}

/***************************************************************************************************/



/*=================================================================================*/
/***********************************************************************************/






/******************* Manipulation de la file prioritaire *******************/
/*=========================================================================*/



/************************* Affichage de la file *************************/

void PrintQueue(maillon_de_liste *ListeF) {

    setColor(GRAY);
    printf("\n\n------------------------------------------------------------------------------------------------------");
    setColor(WHITE);

    while (ListeF != NULL) {

        maillon_de_file *temp = ListeF->File->T;

        while (temp != NULL) {

            setColor(GRAY);
            printf("\n   [ ID : ");
            setColor(WHITE);
            printf("%-8s", temp->ID);
            setColor(GRAY);
            printf(" | Name : ");
            setColor(WHITE);
            printf("%-24s", temp->Name);
            setColor(GRAY);
            printf(" | Consultation reason : ");
            setColor(WHITE);
            printf("%-20s", temp->ConsReason);
            setColor(GRAY);
            printf(" ]");
            setColor(WHITE);
            temp = Suivant_File(temp);

        }

        ListeF = Suivant_Liste(ListeF);

    }

    setColor(GRAY);
    printf("\n------------------------------------------------------------------------------------------------------");
    setColor(WHITE);

}

/************************************************************************/






/********* Fonction qui vérifie si la file de la case d'une liste est vide *********/

int CheckPriorityEmpty(maillon_de_liste *ListeDF, int prio) {

    while (ListeDF->priorite != prio) ListeDF = Suivant_Liste(ListeDF);     // On parcourt la liste jusqu'a la prio. recherchee

    if (FileVide(ListeDF->File)) return 1;  // Si la file est vide on retourne 1
    else return 0;                          // Sinon 0

}

/***********************************************************************************/






/*************** Procédure qui permet de rechercher un élément de la file d'attente ***************/

int SearchQueue(maillon_de_liste **ListeDF, maillon_de_file **Cible, maillon_de_file **AvantCible, maillon_de_liste **Prio) {

    maillon_de_liste *Trav = *ListeDF;

    char NameOrID[MAX_LENGTH_NAME];

    printf("\nEnter the full name of the employee or the ID : ");
    fgets(NameOrID, MAX_LENGTH_NAME, stdin);
    strtok(NameOrID, "\n");
    RemoveSuppSpaces(NameOrID);

    if (strstr(NameOrID, " ") != NULL) StandardizeName(NameOrID);   // Si le string contient un espace (donc un nom) on le standardise

    while (Trav != NULL) {

        *Cible = Trav->File->T; // La cible recoit la tete de la file
        *AvantCible = NULL;

        while (*Cible != NULL && strcmp((*Cible)->ID, NameOrID) != 0 && strcmp((*Cible)->Name, NameOrID) != 0) {

            // On parcourt la file tant qu'on ne trouve pas un ID ou un Nom qui match

            *AvantCible = *Cible;           // L'avant cible sera la cible
            *Cible = Suivant_File(*Cible);  // Et la cible sera le suivant de cette derniere

        }

        if (*Cible != NULL) {   // Si on a trouve une cible

            *Prio = Trav;       // Le maillon de liste de cette prio. sera Trav
            return 1;           // On sort de la fonct.

        } 

        Trav = Suivant_Liste(Trav);     // On avance dans la liste de files

    }

    if (*Cible == NULL) {   // Si on ne trouve rien

        setColor(RED);
        printf("\n\nConsultation not found.\n\n");
        setColor(WHITE);
        return 0;

    }

} 


/**************************************************************************************************/






/******** Procédure qui permet de reprogrammer la consultation de la priorité la plus basse ********/

int RescheduleLowPriority(maillonEmp **Tete, maillon_de_liste **ListeDF, int *NumAppoint) {

    int count = CountLines();   // On compte les lignes du fichier

    FILE *file = fopen("Consultations.txt", "a");   // On l'ouvre avec mode "append" pour ne pas ecraser le contenu
    if (file == NULL) {

        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return 0;

    }

    maillon_de_liste *Prio3 = *ListeDF;

    while (Prio3->priorite != 3) {      // On avance jusqu'a la prio. 3

        Prio3 = Suivant_Liste(Prio3);

    }
    
    maillon_de_liste *Prio4 = Suivant_Liste(Prio3);     // La prio. 4 sera la suivante de 3

    if (Prio4->File->T != NULL) {   // Si la file de la prio. 4 n'est pas vide (derniere priorite)

        if (Prio4->File->T == Prio4->File->Q) {     // Si la file contient un element

            free(Prio4->File->Q);   // On libere l'element
            Prio4->File->T = NULL;  // On met la tete et la queue de la file a NIL
            Prio4->File->Q = NULL;

        } else {    // Sinon

            maillon_de_file *Trav = Prio4->File->T;

            // On avance dans la file jusqu'a l'avant dernier element de cette derniere

            while (Suivant_File(Trav) != Prio4->File->Q) Trav = Suivant_File(Trav);

            free(Prio4->File->Q);           // On libere la queue de la file
            Prio4->File->Q = Trav;          // On met a jour la queue a l'avant dernier element
            Prio4->File->Q->adr = NULL;     // On affecte a l'adresse de la queue le NIL

        }

        (*NumAppoint)--;    // On decremente le nombre total de cons.


    } else if (Prio3->File->T != NULL) {    // Sinon

        if (strcmp(Prio3->File->Q->ConsReason, "Pre-employment") == 0) {    // Si la cause est un pre-employment

            // On l'ecrira a la fin du fichier Consultations.txt

            fprintf(file, "%s;%s;%s;Pre-employment.\n", Prio3->File->Q->ID, Prio3->File->Q->Name, ConsTime[count]);

        } else {    // Sinon

            maillonEmp *Cible = NULL;
            maillonEmp *AvantCible = NULL;
            SearchEmployee(*Tete, &Cible, &AvantCible, Prio3->File->Q->ID, 1);  // On cherche dans la liste de records l'employe qui est dans la queue de la file

            // Puis dans ce qui suit on va mettre a jour la rw date (on ajoute un jour)
            // puis on l'affecte a sa case rwdate dans le dossier medical

            struct tm UpdatedDate = {0};
            SeparateDate(Cible->RetWorkDate, &UpdatedDate);
            UpdatedDate.tm_mday += 1;
            mktime(&UpdatedDate);
            char UpdatedDateS[MAX_LENGTH_DATE];
            CalendarToString(UpdatedDate, UpdatedDateS);
            strcpy(Cible->RetWorkDate, UpdatedDateS);

        }

        // Memes etapes que pour la prio. 4

        if (Prio3->File->T == Prio3->File->Q) { 

            free(Prio3->File->Q);
            Prio3->File->T = NULL;
            Prio3->File->Q = NULL;

        } else {

            maillon_de_file *Trav = Prio3->File->T;
            while (Suivant_File(Trav) != Prio3->File->Q) Trav = Suivant_File(Trav);

            free(Prio3->File->Q);
            Prio3->File->Q = Trav;
            Prio3->File->Q->adr = NULL;

        }

        (*NumAppoint)--;

    } else {    // S'il n'y a aucune cons. return-to-work, pre-employment ou periodic on ne peut reprogrammer

        setColor(RED);
        printf("\nNo appointments can be rescheduled.\n");
        setColor(WHITE);
        fclose(file);
        return 0;

    }

    fclose(file);   // On ferme le fichier
    return 1;
    
}

/***************************************************************************************************/






/************ Procédure qui permet d'ajouter une consultation à la file d'attente ************/

void AddAppointment(maillonEmp **Tete, maillon_de_liste **ListeDF, int *NumAppoint) {

    char Reason[MAX_LENGTH_HIST];

    int ver = 0;

    printf("\nEnter the consultation reason : ");

    do {

        fgets(Reason, MAX_LENGTH_HIST, stdin);
        strtok(Reason, "\n");
        CorrectHist(Reason);

        // On peut ajouter que les cons. pre-employment, work-accident ou occupational-disease

        if (strcmp(Reason, "None") == 0 || strcmp(Reason, "Return-to-work") == 0 || strcmp(Reason, "Periodic") == 0) {

            setColor(RED);
            printf("\nEnter a valid reason : ");
            setColor(WHITE);

        } else ver = 1;

    } while (!ver);
    
    if (strcmp(Reason, "Work-accident") == 0 || strcmp(Reason, "Occupational-disease") == 0) {

        maillonEmp *Cible = NULL;
        maillonEmp *AvantCible = NULL;

        if (SearchEmployee(*Tete, &Cible, &AvantCible, NULL, 0)) {  // On cherche l'employe dans la liste de dossiers medicaux

            maillon_de_file *P;
            Allouer_File(&P);                   // On alloue un maillon de file et on le remplit
            strcpy(P->ConsReason, Reason);
            strcpy(P->ID, Cible->ID);
            strcpy(P->Name, Cible->Name);

            int prio;

            if (strcmp(Reason, "Work-accident") == 0) prio = 1; // On recupere la prio.
            else prio = 2;

            if (*NumAppoint == 10) {    // Si la queue est remplie

                if (RescheduleLowPriority(Tete, ListeDF, NumAppoint)) { // Si on peut reprogrammer une cons.

                    Enfiler(*ListeDF, P, prio); // On enfile
                    (*NumAppoint)++;            // On incremente

                    setColor(GREEN);
                    printf("\nAppointment added successfully.");
                    setColor(WHITE);

                } else {    // Sinon

                    free(P);        // On libere le maillon alloue precedemment
                    setColor(RED);
                    printf("\nFailed to add the appointment. Queue is full.");
                    setColor(WHITE);

                }
                
            } else { // Sinon on enfile normalement

                Enfiler(*ListeDF, P, prio);
                (*NumAppoint)++;

                setColor(GREEN);
                printf("\nAppointment added successfully.");
                setColor(WHITE);

            }

        } else return;

    } else {

        // Sinon si c'est un pre-employment, et que la priorite 4 (periodic) est vide et la queue est pleine
        // On n'ajoute pas (sinon on enleverait une cons. de la meme priorite alors qu'on suit le principe 
        // FIFO ce qui est illogique)

        if (CheckPriorityEmpty(*ListeDF, 4) && *NumAppoint == 10) { 

            setColor(RED);
            printf("\nYou cannot add a pre-employment visit right now. Queue is full.");
            setColor(WHITE);
            return;

        } else {    // Sinon

            char ID[MAX_LENGTH_ID];
            char Name[MAX_LENGTH_NAME];
            
            GetValidID(ID, *Tete);
            GetValidName(Name, *Tete);

            maillon_de_file *P;
            Allouer_File(&P);       // On alloue un maillon de file et on le remplit
            strcpy(P->ConsReason, "Pre-employment");
            strcpy(P->ID, ID);
            strcpy(P->Name, Name);

            if (*NumAppoint == 10) {    // Si la file est pleine

                RescheduleLowPriority(Tete, ListeDF, NumAppoint);   // On reprogramme
                Enfiler(*ListeDF, P, 3);    // On enfile
                (*NumAppoint)++;    // On incremente

            } else {    // Sinon on enfile directement

                Enfiler(*ListeDF, P, 3);
                (*NumAppoint)++;

            }

            setColor(GREEN);
            printf("\nAppointment added successfully.");
            setColor(WHITE);

        }

    }

}

/*********************************************************************************************/






/********* Procédure qui permet de reprogrammer une consultation au choix (avec des limites) *********/

void RescheduleAppointment(maillonEmp **Tete, maillon_de_liste **ListeDF, int *NumAppoint) {

    int count = CountLines();

    FILE *file = fopen("Consultations.txt", "a");
    if (file == NULL) {

        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return;

    }

    maillon_de_file *Cible = NULL;
    maillon_de_file *AvantCible = NULL;
    maillon_de_liste *CasePrio = NULL;

    if (SearchQueue(ListeDF, &Cible, &AvantCible, &CasePrio)) { // On cherche la cons. dans la queue

        // Si la raison est grave on ne peut pas reprogrammer

        if (strcmp(Cible->ConsReason, "Work-accident") == 0 || strcmp(Cible->ConsReason, "Occupational-disease") == 0) {

            setColor(RED);
            printf("\n\nThis appointment cannot be rescheduled (Accident related).\n\n");
            setColor(WHITE);

        } else {    // Sinon

            // On suit les memes etapes que pour la fonction RescheduleLowPriority

            if (strcmp(Cible->ConsReason, "Pre-employment") == 0) {

                fprintf(file, "%s;%s;%s;Pre-employment.\n", Cible->ID, Cible->Name, ConsTime[count]);
    
            } else if (strcmp(Cible->ConsReason, "Return-to-work") == 0) {
    
                maillonEmp *Cible2 = NULL;
                maillonEmp *AvantCible2 = NULL;
                SearchEmployee(*Tete, &Cible2, &AvantCible2, Cible->ID, 1);
                struct tm UpdatedDate = {0};
                SeparateDate(Cible2->RetWorkDate, &UpdatedDate);
                UpdatedDate.tm_mday += 1;
                mktime(&UpdatedDate);
                char UpdatedDateS[MAX_LENGTH_DATE];
                CalendarToString(UpdatedDate, UpdatedDateS);
                strcpy(Cible2->RetWorkDate, UpdatedDateS);
    
            }

            //  Si l'avant cible est different du NIL (donc la cible n'est pas la tete de la file)

            if (AvantCible != NULL) AvantCible->adr = Suivant_File(Cible);  // le suivant de l'avant cible sera le suivant de la cible

            else CasePrio->File->T = Suivant_File(Cible);   // Sinon la tete de la file sera le suivant de la cible

            if (CasePrio->File->Q == Cible) CasePrio->File->Q = AvantCible; // Si la cible est la queue, cette derniere deviendra AvantCible

            // Comme ca si la tete est NIL la queue le sera aussi
            
            free(Cible);    // On libere

            setColor(GREEN);
            printf("\n\nAppointment rescheduled succesfully.\n\n");
            setColor(WHITE);

            (*NumAppoint)--;    // On decremente

        }

    }

    fclose(file);

}

/*****************************************************************************************************/






/********** Procédure qui permet d'annuler une consultation au choix (avec des limites) **********/

void CancelAppointment(maillonEmp **Tete, maillon_de_liste **ListeDF, int *NumAppoint) {

    maillon_de_file *Cible = NULL;
    maillon_de_file *AvantCible = NULL;
    maillon_de_liste *CasePrio = NULL;

    // Meme principe que la fonction precedente
    // Sauf si la cons. est un return-to-work on lui affectera N/A dans son maillonEmp (dossier medical)
    // le chainage se fait de la meme facon

    if (SearchQueue(ListeDF, &Cible, &AvantCible, &CasePrio)) {

        if (strcmp(Cible->ConsReason, "Work-accident") == 0 || strcmp(Cible->ConsReason, "Occupational-disease") == 0) {

            setColor(RED);
            printf("\n\nThis appointment cannot be canceled (Accident related).\n\n");
            setColor(WHITE);

        } else {

            if (strcmp(Cible->ConsReason, "Return-to-work") == 0) {

                maillonEmp *Cible2 = NULL;
                maillonEmp *AvantCible2 = NULL;
                SearchEmployee(*Tete, &Cible2, &AvantCible2, Cible->ID, 1);
                strcpy(Cible2->RetWorkDate, "N/A");

            }

            if (AvantCible != NULL) {

                AvantCible->adr = Suivant_File(Cible);

            } else {

                CasePrio->File->T = Suivant_File(Cible);

            }

            if (CasePrio->File->Q == Cible) {

                CasePrio->File->Q = AvantCible;

            }
            
            free(Cible);

            setColor(GREEN);
            printf("\n\nAppointment cancelled succesfully.\n\n");
            setColor(WHITE);

            (*NumAppoint)--;

        }

    }

}

/*************************************************************************************************/






/*************** Procédure qui permet de fermer une consultation après son traitement ***************/

void CloseAppointment(maillonEmp *Tete, maillon_de_liste **ListeDF, struct tm currentDate) {

    maillon_de_file *Cible = NULL;

    Defiler(*ListeDF, &Cible);  // On defile

    if (Cible == NULL) {

        setColor(RED);
        printf("\nThere are no appointments to be closed.\n");
        setColor(WHITE);
        return;

    }

    setColor(GRAY);
    printf("\nClosing the appointment of : ");
    setColor(WHITE);
    printf("%s", Cible->Name);
    setColor(GRAY);
    printf(" / ID : ");
    setColor(WHITE);
    printf("%s", Cible->ID);
    setColor(GRAY);
    printf(" / Consultation reason : ");
    setColor(WHITE);
    printf("%s", Cible->ConsReason);
    setColor(GRAY);
    printf(" ...\n");
    setColor(WHITE);


    if (strcmp(Cible->ConsReason, "Pre-employment") == 0) {

        char choice;
        printf("\nDoes this person qualify for the job ? (y/n) : ");
        scanf("%c", &choice);
        while (getchar() != '\n');

        // Si le nouveau employe est ajoute

        if (choice == 'y' || choice == 'Y') {

            maillonEmp *Added;

            Allouer(&Added);        // On alloue un maillonEmp et on le remplit
            AffAdr(Added, NULL);

            AffID(Added, Cible->ID);
            AffNom(Added, Cible->Name);
            AffTNumCons(Added, 1);
            char LCDATE[MAX_LENGTH_DATE];
            CalendarToString(currentDate, LCDATE);
            AffLCDate(Added, LCDATE);
            AffRWDate(Added, "N/A");
            AffHistory(Added, "Pre-employment.");

            while (Suivant(Tete) != NULL) {     // On parcourt la liste jusqu'au dernier element

                Tete = Suivant(Tete);
        
            }
        
            AffAdr(Tete, Added);    // On chaine le dernier element avec le nouveau maillon

            setColor(GREEN);
            printf("\n\nCandidate successfully hired.");
            setColor(WHITE);

        } else {

            setColor(GREEN);
            printf("\n\nThe candidate was not hired.");
            setColor(WHITE);

        }

    } else {

        // Sinon on cherche l'employe dans la liste de dossiers medicaux on lui met a jour la date de consultation a celle d'aujourd'hui

        maillonEmp *Cible2 = NULL;
        maillonEmp *AvantCible2 = NULL;
        SearchEmployee(Tete, &Cible2, &AvantCible2, Cible->ID, 1);
        AffTNumCons(Cible2, Cible2->TNumCons + 1);
        char LCDATE[MAX_LENGTH_DATE];
        CalendarToString(currentDate, LCDATE);
        AffLCDate(Cible2, LCDATE);

        if (strcmp(Cible->ConsReason, "Work-accident") == 0 || strcmp(Cible->ConsReason, "Occupational-disease") == 0) {

            // Si c'est une cons. grave on demande une rw date

            char RWDATE[MAX_LENGTH_DATE];
            GetValidRWDate(RWDATE, Cible2);
            AffRWDate(Cible2, RWDATE);

        } else {

            AffRWDate(Cible2, "N/A");   // Sinon on affecte N/A

        }

        UpdateHistory(Cible2, Cible->ConsReason, 1);    // On met a jour l'historique

    }

    setColor(GREEN);
    printf("\nAppointment closed successfully.");
    setColor(WHITE);

    free(Cible);    // On libere le maillon de file

}

/****************************************************************************************************/






/*************** Procédure qui permet de programmer les consultations du prochain jour **************/

void ScheduleNextDayAppointments(maillonEmp *Tete, maillon_de_liste *ListeDF, struct tm CurrentDate) {

    // Dans l'approche suivante on utilisera notre liste de files pour programmer les cons. de demain
    // c'est pour ca que cette etape se fait en fin de journee apres avoir ferme toutes les consultations

    maillonEmp *Trav = Tete;

    int randomPreEmp = (rand() % 3) + 1;
    
    int count = CountLines();

    char date[MAX_LENGTH_DATE];

    char ExecDate[MAX_LENGTH_DATE];
    CurrentDate.tm_mday++;                          // On ajoute un jour a la date d'execution
    mktime(&CurrentDate);                           // On corrige les eventuelles erreurs
    CalendarToString(CurrentDate, ExecDate);        // On met au format DD/MM/YYYY

    while (Trav != NULL) {  // On parcourt la liste des dossiers medicaux

        if (count < 10) {   // S'il y'a moins de 10 cons.

            if (strcmp(ExecDate, Trav->RetWorkDate) == 0) {     // Si la date est la meme que la rw date

                maillon_de_file *P;
                Allouer_File(&P);   // On alloue un maillon de file et on le remplit
                strcpy(P->ConsReason, "Return-to-work");
                strcpy(P->ID, Trav->ID);
                strcpy(P->Name, Trav->Name);
                Enfiler(ListeDF, P, 3);     // On l'enfile dans notre liste de files
                count++;
        
            }

            // Ici meme principe que pour generer le fichier Consultations.txt sauf qu'on enfile cette fois

            int PreEmpRand = rand() % 2;

            if (PreEmpRand && randomPreEmp > 0) {

                char RandomEmpFName[MAX_LENGTH_NAME];
                char RandomEmpLName[MAX_LENGTH_NAME];
                char RandomEmpID[MAX_LENGTH_ID];
                generateRandomFName(RandomEmpFName);
                generateRandomLName(RandomEmpLName);
                generateRandomID(RandomEmpID);

                maillon_de_file *P;
                Allouer_File(&P);
                strcpy(P->ConsReason, "Pre-employment");
                strcpy(P->ID, RandomEmpID);
                strcpy(P->Name, RandomEmpLName);
                strcat(P->Name, " ");
                strcat(P->Name, RandomEmpFName);
                Enfiler(ListeDF, P, 3);
                count++;
                randomPreEmp--;

            }

        } else {    
            
            // Sinon on ajoutera un jour aux cons. return-to-work

            strcpy(date, Trav->RetWorkDate);

            if (strcmp(ExecDate, date) == 0) {

                char* temp = date;
                struct tm TempCal = {0};
                SeparateDate(date, &TempCal);
                TempCal.tm_mday += 1;
                mktime(&TempCal);
                CalendarToString(TempCal, temp);

                AffRWDate(Trav, temp);

            }

        }

        Trav = Suivant(Trav);

    }

    // Puisque les return-to-work sont plus prioritaires j'ai prefere parcourir la liste une fois pour les enfiler d'abord
    // Ensuite on fera un deuxieme parcours pour verifier les examinations periodiques
    // On suit le meme principe que la premiere fois

    Trav = Tete;

    while (Trav != NULL) {

        if (count < 10) {

            strcpy(date, Tete->LConsDate);
        
            struct tm LCDate = {0};
            SeparateDate(date, &LCDate);
        
            double diff = difftime(mktime(&CurrentDate), mktime(&LCDate));  // On calcule la difference entre les deux dates
                
            if (diff > ONE_YEAR) {
        
                maillon_de_file *P;
                Allouer_File(&P);
                strcpy(P->ConsReason, "Periodic");
                strcpy(P->ID, Trav->ID);
                strcpy(P->Name, Trav->Name);
                Enfiler(ListeDF, P, 4);
                count++;
        
            }

        }

        Trav = Suivant(Trav);

    }

    setColor(GREEN);
    printf("\nNext-day appointments scheduled successfully.");
    setColor(WHITE);

}

/****************************************************************************************************/






/**************************** Manipulation des fichiers ****************************/
/*=================================================================================*/



/****** Procédure qui permet de rénitialiser le fichier Consultations.txt ******/

void ResetConsultationsFile() {

    FILE *file = fopen("Consultations.txt", "w+");  // On l'ouvre avec le mode w+ ce qui ecrasera le contenu du fichier

    if (file == NULL) {

        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return;

    }

    fclose(file);   // On ferme le fichier

}

/*******************************************************************************/






/******* Procédure qui permet de mettre à jour le fichier EmpRecords.txt depuis la liste *******/

void UpdateEmpRecordsFile(maillonEmp *Tete) {

    FILE *file = fopen("EmpRecords.txt", "w+");     // On ouvre le fichier avec w+ pour ecraser le precedent
    if (file == NULL) {

        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return;

    }

    maillonEmp *Trav = Tete;

    while (Trav != NULL) {  // On parcourt la liste et on print a chaque fois

        fprintf(file, "%s;%s;%d;%s;", Trav->ID, Trav->Name, Trav->TNumCons, Trav->LConsDate);
        if (strcmp(Trav->RetWorkDate, "N/A") != 0) fprintf(file, "%s;", Trav->RetWorkDate);
        fprintf(file, "%s\n", Trav->History);

        Trav = Suivant(Trav);

    }

    fclose(file);

    setColor(GREEN);
    printf("\nEmpRecords.txt file updated successfully.");
    setColor(WHITE);

}

/***********************************************************************************************/






/******* Procédure qui permet de mettre à jour le fichier Consultations.txt depuis la file *******/

void UpdateConsFile(maillon_de_liste *ListeDF) {

    FILE *file = fopen("Consultations.txt", "a");
    if (file == NULL) {
        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return;
    }

    int count = CountLines();

    maillon_de_liste *Trav = ListeDF;

    while (Trav != NULL) {      // On parcours la liste de priorites

        while (Trav->File->T != NULL) {     // On parcours la file et a chaque fois on print

            count++;
            fprintf(file, "%s;%s;%s;%s\n", Trav->File->T->ID, Trav->File->T->Name, ConsTime[count-1], Trav->File->T->ConsReason);
            Trav->File->T = Suivant_File(Trav->File->T);    // On avance dans les maillons de file
            
        }

        Trav = Suivant_Liste(Trav);     // On avance dans la liste

    }

    fclose(file);   // On ferme le fichier

    setColor(GREEN);
    printf("\nConsultations.txt file updated successfully.");
    setColor(WHITE);

}

/*************************************************************************************************/



/*=================================================================================*/
/***********************************************************************************/






/****************** Libération de la mémoire allouée dynamiquement ******************/
/*==================================================================================*/

void LibererLFile(maillon_de_liste *ListeDF) {

    // On libere tous les maillons de file, avant de liberer le maillon de liste, et ce pour chaque priorite

    maillon_de_liste *SuivListe = NULL;
    maillon_de_file *SuivFile = NULL;

    while (ListeDF != NULL) {

        while (ListeDF->File->T != NULL) {

            SuivFile = Suivant_File(ListeDF->File->T);
            free(ListeDF->File->T);
            ListeDF->File->T = SuivFile;

        }

        free(ListeDF->File);

        SuivListe = Suivant_Liste(ListeDF);
        free(ListeDF);
        ListeDF = SuivListe;

    }

}

/************************************************************************************/


// Bibliothèque regroupant les fonctions qui permettent de manipuler les listes
// linéaires chainées afin de créer une liste des dossiers médicaux d'employés à partir
// du fichier EmpRecords.txt, auquel on pourra ajouter des dossiers, en supprimer ou en 
// mettre à jour.



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
#include "randomgen.h"
#include <math.h>
#include <ctype.h>
/*********************/




/********* Constantes et variables *********/

#define SIX_MONTHS (6 * 30 * 24 * 60 * 60)      // Approximation de 6 mois en secondes
#define ONE_YEAR (365 * 24 * 60 * 60)           // Approximation d'une année en secondes


char ConsTime[10][10] = {
    "8h30", "9h15", "10h", "10h45", "11h30", "13h", "13h45", "14h30", "15h15", "16h"
};

/*******************************************/






/******************* Structures de données *******************/

typedef struct typecell {
                                            
    char ID[MAX_LENGTH_ID];                 // ID
    char Name[MAX_LENGTH_NAME];             // Nom complet
    int TNumCons;                           // Nombre total de consultations
    char LConsDate[MAX_LENGTH_DATE];        // Dernière date de consultation
    char RetWorkDate[MAX_LENGTH_DATE];      // Date de retour au travail (Optionnelle, s'il n'y a pas on remplace par "N/A")
    char History[MAX_LENGTH_HIST];          // Historique
    
    struct typecell *adr;                   // Pointeur qui pointe le maillon suivant de type struct typecell

} maillonEmp;                               // On définit un type maillonEmp qu'on chaine pour avoir une liste

/*************************************************************/






/************************* Machine Abstraite **************************/

void Allouer(maillonEmp **A) {                          // Allouer un maillonEmp
    *A = (maillonEmp*)malloc(sizeof(maillonEmp));
}

void AffID(maillonEmp *Cible, char *ID) {               // Affecter un ID
    strcpy(Cible->ID, ID);
}

void AffNom(maillonEmp *Cible, char *Name) {            // Affecter un nom
    strcpy(Cible->Name, Name);
}

void AffTNumCons(maillonEmp *Cible, int TNumCons) {     // Affecter un nombre total de consultations
    Cible->TNumCons = TNumCons;
}

void AffLCDate(maillonEmp *Cible, char *LCDate) {       // Affecter une dernière date de consultation
    strcpy(Cible->LConsDate, LCDate);
}

void AffRWDate(maillonEmp *Cible, char *RWDate) {       // Affecter une date de retour au travail
    strcpy(Cible->RetWorkDate, RWDate);
}

void AffHistory(maillonEmp *Cible, char *History) {     // Affecter un historique
    strcpy(Cible->History, History);
}

void AffAdr(maillonEmp *A, maillonEmp *a) {             // Affecter une adresse dans le champ adresse du maillonEmp
    A->adr = a;
}

maillonEmp* Suivant(maillonEmp *A) {                    // Renvoyer l'adresse du suivant du maillonEmp cible
    return A->adr;
}

/**********************************************************************/






/**************** Vérification et correction des différents champs d'une structure maillonEmp ****************/
/*===========================================================================================================*/



/******************** Enlève les espaces supplémentaires (plus d'un) ********************/
/*========================= au début, entre les mots, à la fin =========================*/

void RemoveSuppSpaces(char *object) {

    int i = 0, j = 0;
    int inWord = 0;

    while (object[i] != '\0') {         // Tant qu'on atteint pas la fin du string

        if (!isspace(object[i])) {      // Si le char n'est pas un espace

            object[j++] = object[i];    // On met le char dans l'indice j++
            inWord = 1;

        } else if (inWord) {            // Si inWord = 1

            object[j++] = ' ';          // On met un espace seulement dans l'indice j++
            inWord = 0;                 // On renitialise inWord

        }

        i++;

    }

    if (j > 0 && object[j - 1] == ' ') object[j - 1] = '\0';    // Si l'avant dernier indice est un espace on le met a end of string

    else object[j] = '\0';      // Sinon c'est le dernier indice qui recevra ce traitement

}

/**************************************************************************************/






/************** Vérifier si l'ID entré existe ou pas **************/

int CheckIDValidity(const char *ID, maillonEmp *Tete) {

    int ver = 1;

    while (Tete != NULL && ver) {                   // On traverse la liste et on compare à chaque fois

        if (strcmp(Tete->ID, ID) == 0) ver = 0;     // Si on trouve on met ver à 0 et on le renvoie

        Tete = Suivant(Tete);

    }

    return ver;

}

/******************************************************************/






/************** Vérifier si le nom entré existe ou pas **************/

int CheckNameValidity(const char *Name, maillonEmp *Tete) {

    int ver = 1;

    while (Tete != NULL && ver) {                   // Meme concept que pour l'ID

        if (strcmp(Tete->Name, Name) == 0) ver = 0;

        Tete = Suivant(Tete);

    }

    return ver;

}

/********************************************************************/






/******** Séparer une date et la convertir en format calendrier (struct tm) ********/

int SeparateDate(const char *date, struct tm *EZdate) {

    char copy[MAX_LENGTH_DATE];
    strcpy(copy, date);

    char *Sday = strtok(copy, "/");
    char *Smonth = strtok(NULL, "/");       // On separe la date pour recuperer chaque champ
    char *Syear = strtok(NULL, "/");

    if (Sday == NULL || Smonth == NULL || Syear == NULL) return 0;     // Si un d'eux est invalide on renvoie 0

    char *endptrD, *endptrM, *endptrY;

    long day = strtol(Sday, &endptrD, 10);
    long month = strtol(Smonth, &endptrM, 10);      // On convertit les champs qu'on a recupere en nombres
    long year = strtol(Syear, &endptrY, 10);

    if (*endptrD != '\0' || *endptrM != '\0' || *endptrY != '\0') return 0;     // Si un des pointeurs est differents de end of string on renvoie 0

    if (year < 2020 || month <= 0 || day <= 0 || month > 12 || day > 31) return 0;

    EZdate->tm_mday = day;
    EZdate->tm_mon = month - 1;
    EZdate->tm_year = year - 1900;

    mktime(EZdate);         // On convertit ce qu'on a recupere en format calendrier et on corrige les eventuelles erreurs

    return 1;

}

/***********************************************************************************/






/********* Convertir une date format calendrier (struct tm) à un string *********/

void CalendarToString(struct tm EZDate, char *date) {

    char Day[MAX_LENGTH_DATE];
    char Month[MAX_LENGTH_DATE];
    char Year[MAX_LENGTH_DATE];

    sprintf(Day, "%02d", EZDate.tm_mday);           // On convertit chaque champ du format calendrier en string
    sprintf(Month, "%02d", EZDate.tm_mon + 1);
    sprintf(Year, "%d", EZDate.tm_year + 1900);
 
    strcpy(date, Day);                              // On le formate au format DD/MM/YYYY
    strcat(date, "/");
    strcat(date, Month);
    strcat(date, "/");
    strcat(date, Year);

}

/********************************************************************************/






/**************** Comparer une date avec la date d'exécution du programme ****************/

int CompareWithCurrentDate(const struct tm *date, const struct tm *CurrentDate) {

    if (date->tm_year > CurrentDate->tm_year ||
        date->tm_year == CurrentDate->tm_year && date->tm_mon > CurrentDate->tm_mon ||
        date->tm_year == CurrentDate->tm_year && date->tm_mon == CurrentDate->tm_mon && date->tm_mday > CurrentDate->tm_mday) {
            return 0;
    }

    // On compare chaque champ des deux calendriers et on verifie si date > CurrentDate
    // dans ce cas invalide

    return 1;

}

/*****************************************************************************************/






/**************** Comparer une date avec une autre date selon le mode choisi ****************/

int CompareWithOtherDate(const struct tm *date1, const struct tm *date2, int Mode) {

    if (Mode == 1) {

        if (date1->tm_year > date2->tm_year ||
            (date1->tm_year == date2->tm_year && date1->tm_mon > date2->tm_mon) ||
            (date1->tm_year == date2->tm_year && date1->tm_mon == date2->tm_mon && date1->tm_mday > date2->tm_mday)) {
            return 0;
        }

        // Meme que pour CurrentDate mais avec deux dates aleatoires et on verifie si date1 > date2 (invalide)

    } else if (Mode == 2) {

        time_t lastConsultationDate = mktime((struct tm *)date2);       // On convertit les deux dates en secondes
        time_t retWorkDate = mktime((struct tm *)date1);
        double range = difftime(retWorkDate, lastConsultationDate);     // On calcule la difference

        if (range < 0 || range > SIX_MONTHS) return 0;      // Si la difference est negative ou plus que 6 mois invalide

    }

    return 1;

}

/********************************************************************************************/






/******** Vérifier si la date entré est valide (bon format / selon les autres dates / etc.) ********/

int CheckDateValidity(char *date1, void *date2, int Mode) {

    struct tm StructuredDate1 = {0};
    if (!SeparateDate(date1, &StructuredDate1)) return 0;   // Verifie si la date est invalide
    CalendarToString(StructuredDate1, date1);

    // Selon le mode on va utiliser une des deux fonctions precedentes

    if (Mode == 0) {

        return CompareWithCurrentDate(&StructuredDate1, (struct tm *)date2);

    } else {

        struct tm StructuredDate2 = {0};
        if (!SeparateDate((char *)date2, &StructuredDate2)) return 0;
        CalendarToString(StructuredDate2, (char *)date2);
        return CompareWithOtherDate(&StructuredDate1, &StructuredDate2, Mode);

    }

}

/***************************************************************************************************/






/************************** Standardiser le nom, c'est à dire mettre en majuscule **************************/
/*========================= les premières lettres des Noms/Prénoms et en minuscule ========================*/
/*========================================== les autres lettres ===========================================*/

int StandardizeName(char *Name) {

    int capitalize = 1;

    for (int i = 0; Name[i] != '\0'; i++) {

        if (!isalpha(Name[i]) && Name[i] != ' ') return 0;      // Si le caractère est un caractère spécial différent d'espace
                                                                // alors on renvoie un zero pour indiquer que le nom est invalide
        if (capitalize && isalpha(Name[i])) {

            Name[i] = toupper(Name[i]);         // On met en majuscule le char
            capitalize = 0;                     // On renitialise capitalize

        } else if (!capitalize) Name[i] = tolower(Name[i]);     // Sinon on le met en minuscule

        if (Name[i] == ' ') capitalize = 1;     // Lorsqu'on rencontre un espace on met capitalize a 1 

    }

    return 1;

}

/***********************************************************************************************************/






/***** Algorithme de la distance de Levenshtein entre deux chaines, c'est à dire le cout minimal *****/
/*=============================== pour transformer chaine1 en chaine2 ===============================*/

/* https://fr.wikipedia.org/wiki/Distance_de_Levenshtein */

/****** NOTE: Algorithme purement facultatif qu'on a voulu implémenter seulement pour avoir une ******/
/*==================== fonctionnalité en plus qui permet d'éviter à chaque fois =====================*/
/*============================= d'écrire l'historique sans aucune faute =============================*/

int MargeErreur(const char *chaine1, const char *chaine2) {

    int length1 = strlen(chaine1);
    int length2 = strlen(chaine2);

    int D[length1 + 1][length2 + 1];

    for (int i = 0; i <= length1; i++) D[i][0] = i;

    for (int j = 0; j <= length2; j++) D[0][j] = j;

    for (int i = 1; i <= length1; i++) {

        for (int j = 1; j <= length2; j++) {

            int Marge = (chaine1[i - 1] == chaine2[j - 1]) ? 0 : 1;
            D[i][j] = fmin(D[i - 1][j] + 1, fmin(D[i][j - 1] + 1, D[i - 1][j - 1] + Marge));

        }

    }

    return D[length1][length2];

}

/*****************************************************************************************************/






/******* Renvoie la raison de consultation la plus proche d'une chaîne de caractères donnée *******/
/*=========================== en utilisant la distance de Levenshtein ============================*/

const char* FindCloseMatchHist(const char *hist) {

    int maxErreur = 10;                        // On met la marge d'erreur a 10 (la distance maximale entre deux chaines)
    const char *bestMatch = "None";            // Le best match est par defaut mis a None

    for (int i = 0; i < NUM_HIST; i++) {       // On compare la chaine avec chaque raison de consultation

        int dist = MargeErreur(hist, Random_History[i]);    // On calcule la distance
        if (dist == 0) return Random_History[i];            // Si c'est 0 (identique) on retourne l'element du tableau
        if (dist < maxErreur) {                 

            maxErreur = dist;                   // Si c'est moins que maxErreur on met le nouveau maxErreur a la distance calculee
            bestMatch = Random_History[i];      // Le best match est mis a cet element du tableau

        }

    }

    return bestMatch;

}

/**************************************************************************************************/






/***** Corriger l'historique en prenant en compte les raisons non-enregistrées *****/

void CorrectHist(char *hist) {

    char result[MAX_LENGTH_HIST] = "";
    char verification[MAX_LENGTH_HIST];
    strcpy(verification, hist);
    char *part = strtok(hist, ",");         // On separe les parties

    while (part != NULL) {

        while (*part == ' ') part++;        // On evite les espaces

        const char *correctedHist = FindCloseMatchHist(part);       // On utilise notre fonction pour corriger

        if (strcmp(correctedHist, "None") != 0) {                   // Si la raison est valide

            if (strlen(result) > 0) strcat(result, ", ");           // On met une virgule d'abord si c'est une deuxieme raison
            strcat(result, correctedHist);                          // puis on met la raison corrigee

        }

        part = strtok(NULL, ",");           // On avance dans les parties
    
    }

    if (strcmp(result, "") != 0) strcpy(hist, result);      // Si notre resultat n'est pas vide on le met dans l'historique

    else strcpy(hist, "None");                              // Sinon il n'a aucun historique "None"
    
}

/***********************************************************************************/






/***************************** Manipulation des listes linéaires chainées *****************************/
/*====================================================================================================*/



/***************** Génération d'une liste à partir du fichier EmpRecords.txt *****************/

int GenerateEmpList(maillonEmp **Head) {

    FILE *file = fopen("EmpRecords.txt", "r");      // On ouvre le fichier (procedure repetee plusieurs fois dans les fonct.)
    if (file == NULL) {

        setColor(RED);
        printf("\nError opening file.");
        setColor(WHITE);
        *Head = NULL;
        return 0;

    }

    char buffer[MAX_BUFFER_SIZE];

    maillonEmp *Tete = NULL;
    maillonEmp *P = NULL;
    maillonEmp *Q = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {       // Tant que le fichier n'atteint pas sa fin

        if (strcmp(buffer, "\n") != 0) {                        // On evite les lignes qui contiennent '\n' seulement

            Allouer(&P);        // On alloue un maillon
            AffAdr(P, NULL);    // On lui affecte le NIL

            if (Q != NULL) AffAdr(Q, P);    // Si ce n'est pas le premier maillon genere on met l'adresse de Q a P
            else Tete = P;                  // Sinon la tete recevra P

            Q = P;              // Pour avancer

            char *partie = strtok(buffer, ";");     // On commence les separations par les delimiteurs et on affecte a chaque fois
            AffID(P, partie);                       // le champ correspondant

            partie = strtok(NULL, ";");
            StandardizeName(partie);                // Pour standardiser le nom
            AffNom(P, partie);
            
            partie = strtok(NULL, ";");
            AffTNumCons(P, (int)strtol(partie, NULL, 10));

            partie = strtok(NULL, ";");
            AffLCDate(P, partie);

            partie = strtok(NULL, ";");

            if (strstr(partie, "/") == NULL) {      // Si la partie ne contient pas '/' (pas de ret work date)

                CorrectHist(partie);                // On corrige l'historique
                if (strstr(partie, ".") == NULL) strcat(partie, ".");   // On met un point s'il n'y en a pas
                AffHistory(P, partie);
                AffRWDate(P, "N/A");                // Pas de rw date

            } else {                                // Sinon on affecte le rw date et l'hist apres

                AffRWDate(P, partie);               
                partie = strtok(NULL, ";");
                CorrectHist(partie);
                if (strstr(partie, ".") == NULL) strcat(partie, ".");
                AffHistory(P, partie);

            }
            
        } else continue;

    }

    setColor(GREEN);
    printf("\nList generated successfully.");
    setColor(WHITE);

    *Head = Tete;

    return 1;

}

/*********************************************************************************************/






/*************************** Affichage des éléments de la liste ***************************/

void PrintEmpList(maillonEmp *Tete) {

    printf("\n");

    if (Tete == NULL) {

        setColor(RED);
        printf("\nEmpty list.");
        setColor(WHITE);

    } else {

        char choice1 = 'y';
        char choice2 = 'n';
        int count = 1;
        int iter = 0;

        setColor(GRAY);
        printf("\n __________________________________________________________________________________________________________________________________________________________");
        printf("\n|          |                         |     |            |            |                                                                                     |");
        printf("\n| "); setColor(CYAN); printf("ID      "); setColor(GRAY); printf(" | Full Name               | "); setColor(CYAN); printf("T.C "); setColor(GRAY); printf("|"); setColor(CYAN); printf(" Last Cons."); setColor(GRAY); printf(" |"); setColor(CYAN); printf(" Ret. Work"); setColor(GRAY); printf("  | History                                                                             |");
        printf("\n|----------|-------------------------|-----|------------|------------|-------------------------------------------------------------------------------------|");

        while (Tete != NULL) {

            setColor(GRAY); printf("\n| "); setColor(CYAN);
            printf("%-8s", Tete->ID); setColor(GRAY); printf(" | "); setColor(WHITE);
            printf("%-23s", Tete->Name); setColor(GRAY); printf(" | "); setColor(CYAN); 
            printf("%-3d", Tete->TNumCons); setColor(GRAY); printf(" | "); setColor(CYAN);
            printf("%-10s", Tete->LConsDate); setColor(GRAY); printf(" | "); setColor(CYAN);
            printf("%-10s", Tete->RetWorkDate); setColor(GRAY); printf(" | "); setColor(WHITE);
            printf("%-83s", Tete->History); setColor(GRAY); printf(" | "); setColor(WHITE);

            Tete = Suivant(Tete);
            count++;

            if (count > 10) {

                setColor(GRAY);
                printf("\n|__________|_________________________|_____|____________|____________|_____________________________________________________________________________________|");

                iter++;
                count = 1;

                if (iter == 3) {

                    printf("\n\nWould you like to display the entire list? (y/n): ");
                    setColor(WHITE);
                    scanf(" %c", &choice2);
                    while (getchar() != '\n');

                    if (choice2 == 'y') {

                        setColor(GRAY);
                        printf("\n __________________________________________________________________________________________________________________________________________________________");
                        printf("\n|          |                         |     |            |            |                                                                                     |");
                        
                        while (Tete != NULL) {

                            setColor(GRAY); printf("\n| "); setColor(CYAN);
                            printf("%-8s", Tete->ID); setColor(GRAY); printf(" | "); setColor(WHITE);
                            printf("%-23s", Tete->Name); setColor(GRAY); printf(" | "); setColor(CYAN); 
                            printf("%-3d", Tete->TNumCons); setColor(GRAY); printf(" | "); setColor(CYAN);
                            printf("%-10s", Tete->LConsDate); setColor(GRAY); printf(" | "); setColor(CYAN);
                            printf("%-10s", Tete->RetWorkDate); setColor(GRAY); printf(" | "); setColor(WHITE);
                            printf("%-83s", Tete->History); setColor(GRAY); printf(" | "); setColor(WHITE);

                            Tete = Suivant(Tete);

                        }

                        break;
                        
                    } else {
                        
                        iter = 0;
                        choice2 = 'n';

                    }

                }

                if (choice2 == 'n') {

                    setColor(GRAY);
                    printf("\n\nDo you wish to continue? (y/n): ");
                    setColor(WHITE);
                    scanf(" %c", &choice1);
                    while (getchar() != '\n');
                    if (choice1 == 'n') break;
                    else {
                        
                        choice1 = 'y';
                        setColor(GRAY);
                        printf("\n __________________________________________________________________________________________________________________________________________________________");
                        printf("\n|          |                         |     |            |            |                                                                                     |");

                    }

                }
                
            }
        }

        if (choice1 == 'y') {

            setColor(GRAY);
            printf("\n|__________|_________________________|_____|____________|____________|_____________________________________________________________________________________|");
            setColor(WHITE);

        }

    }
}

/******************************************************************************************/






/******* Compter le nombre de raisons de consultation dans l'historique d'un employé *******/

int CountHistReasons(maillonEmp *Cible) {

    int count = 0;

    char temp[MAX_LENGTH_HIST];
    char *partie;

    strcpy(temp, Cible->History);

    partie = strtok(temp, ",");     // On separe l'historique par les virgules et on compte a chaque fois jusqu'au NIL

    while (partie != NULL) {

        count++;
        partie = strtok(NULL , ",");

    }

    return count;                   // on renvoie ce qu'on a compte

}

/*******************************************************************************************/






/*********** Récupère un ID de l'utilisateur conforme aux exigeances ***********/

void GetValidID(char *ID, maillonEmp *Tete) {

    int ver = 0;

    printf("\nEmployee ID: ");

    do {

        fgets(ID, MAX_LENGTH_ID, stdin);
        strtok(ID, "\n");
        RemoveSuppSpaces(ID);       // S'il y'a des espaces a la fin ou au debut

        if (strlen(ID) > 8) {       // L'ID doit contenir jusqu'a 8 caracteres

            setColor(RED);
            printf("\nError# Enter a valid ID (Up to 8 characters) : ");
            setColor(WHITE);
            continue;

        }

        ver = CheckIDValidity(ID, Tete);        // On verifie si l'id est valide

        if (!ver) {

            setColor(RED);
            printf("\nError# ID already exists : ");
            setColor(WHITE);

        }

    } while (!ver);

}

/*******************************************************************************/






/********************** Récupère un nom de l'utilisateur ***********************/

void GetValidName(char *Name, maillonEmp *Tete) {

    int ver = 0;

    printf("\nFull Name: ");

    do {

        fgets(Name, MAX_LENGTH_NAME, stdin);
        strtok(Name, "\n");
        RemoveSuppSpaces(Name);     // S'il y'a des espaces a la fin ou au debut ou entre les noms

        if (!StandardizeName(Name)) {       // Si la fonction renvoie 0 (caracteres speciaux)

            setColor(RED);
            printf("\nError# Invalid name. Name must not contain special characters : ");
            setColor(WHITE);
            continue;

        }

        ver = CheckNameValidity(Name, Tete);    // On verifie si le nom est valide

        if (!ver) {

            setColor(RED);
            printf("\nError# Name already exists : ");
            setColor(WHITE);

        }

    } while (!ver);

}

/*******************************************************************************/






/********** Récupère un nombre total de consultations de l'utilisateur ***********/

void GetValidTNumCons(int *TNumCons) {

    printf("\nTotal number of Consultations: ");

    do {

        scanf("%d", TNumCons);
        while (getchar() != '\n');

        if (TNumCons < 0) {     // Il ne peut pas etre inferieur a 0

            setColor(RED);
            printf("\nError# Number of consultations cannot be inferior to 0 : ");
            setColor(WHITE);

        }

    } while (TNumCons < 0);

}

/*********************************************************************************/






/********** Récupère une date de dernière consultation de l'utilisateur ***********/

void GetValidLCDate(char *LCDate, struct tm CurrentDate) {

    int ver = 0;

    printf("\nLast consultation Date: ");

    do {

        fgets(LCDate, MAX_LENGTH_DATE, stdin);
        strtok(LCDate, "\n");
        ver = CheckDateValidity(LCDate, &CurrentDate, 0);   // On utilise notre fonction deja fabriquee pour verifier avec le Mode 0

        if (!ver) {

            setColor(RED);
            printf("\nError# Invalid date : ");
            setColor(WHITE);

        }

    } while (!ver);

}

/**********************************************************************************/






/********** Récupère une date de retour au travail de l'utilisateur ***********/

void GetValidRWDate(char *RWDate, maillonEmp *Cible) {

    int ver = 0;

    printf("\nReturn to work Date: ");

    do {

        fgets(RWDate, MAX_LENGTH_DATE, stdin);
        strtok(RWDate, "\n");
        ver = CheckDateValidity(RWDate, Cible->LConsDate, 2);   // Pareil mais avec le Mode 1

        if (!ver) {

            setColor(RED);
            printf("\nError# Invalid date : ");
            setColor(WHITE);

        }

    } while (!ver);

}

/******************************************************************************/






/****************** Récupère un historique de l'utilisateur *******************/

void GetValidHistory(char *History, maillonEmp *Cible) {

    int ver = 0;

    printf("\nHistory: ");

    do {
        
        int count = 0;
        char *partie;

        fgets(History, MAX_LENGTH_HIST, stdin);
        strtok(History, "\n");
        CorrectHist(History);   // On corrige l'historique
        strcat(History, ".");
        AffHistory(Cible, History);     // On affecte l'historique meme faux car notre fonction prend en parametre un maillon
        count = CountHistReasons(Cible);    // On compte les raisons qui ne doivent pas depasser 5

        if (count <= 5) ver = 1;
        else {

            setColor(RED);
            printf("\nError# History must not exceed 5 consultation reasons : ");
            setColor(WHITE);

        }

    } while (!ver);

}

/******************************************************************************/






/********** Fonction qui permet d'ajouter un dossier médical à la liste **********/
/*===============================================================================*/

void AddToEmpList(maillonEmp *Tete, struct tm CurrentDate) {

    maillonEmp *Added;
    char choice;

    Allouer(&Added);        // On alloue un maillon
    AffAdr(Added, NULL);    // On affecte le NIL

    char ID[MAX_LENGTH_ID];
    GetValidID(ID, Tete);   
    AffID(Added, ID);

    char Name[MAX_LENGTH_NAME];
    GetValidName(Name, Tete);
    AffNom(Added, Name);

    int TNumCons;
    GetValidTNumCons(&TNumCons);
    AffTNumCons(Added, TNumCons);

    char LCDate[MAX_LENGTH_DATE];
    GetValidLCDate(LCDate, CurrentDate);
    AffLCDate(Added, LCDate);


    printf("\nDoes the employee have a return to work date ? (y/n) : ");    // On demande si l'employe a une rw date

    do {

        scanf("%c", &choice);
        while (getchar() != '\n');
        
        if (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N') {

            setColor(RED);
            printf("\nInvalid choice : ");
            setColor(WHITE);
            
        }
            

    } while (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N');

    if (choice == 'y' || choice == 'Y') {

        char RWDate[MAX_LENGTH_DATE];
        GetValidRWDate(RWDate, Added);

        // Si ce que l'user a donne est dans le passe (par exemple 20/04/2024 alors qu'on est en 2025)
        // on met N/A parce que la rw date est deja passee

        if (CheckDateValidity(RWDate, &CurrentDate, 0)) AffRWDate(Added, "N/A");
        else AffRWDate(Added, RWDate);

    } else {

        AffRWDate(Added, "N/A");

    }

    char History[MAX_LENGTH_HIST];
    GetValidHistory(History, Added);
    AffHistory(Added, History);

    while (Suivant(Tete) != NULL) {

        Tete = Suivant(Tete);   // On avance dans la liste jusqu'a arriver au dernier element

    }

    AffAdr(Tete, Added);    // On affecte a l'adresse du dernier element le nouvel element cree
    
}

/*********************************************************************************/






/************* Fonction qui permet de rechercher un employé dans la liste **************/

int SearchEmployee(maillonEmp *Tete, maillonEmp **Cible, maillonEmp **AvantCible, void *ID, int Mode) {

    *Cible = Tete;

    char NameOrID[MAX_LENGTH_NAME];

    if (Mode == 0) {    // Si c'est l'user qui cherche l'employe

        printf("\nEnter the full name of the employee or the ID : ");
        fgets(NameOrID, MAX_LENGTH_NAME, stdin);
        strtok(NameOrID, "\n");
        RemoveSuppSpaces(NameOrID);     // On enleve les espaces supplementaires

        if (strstr(NameOrID, " ") != NULL) StandardizeName(NameOrID);   // S'il y'a des espaces (donc un nom) on standardise 

    } else {    // Sinon quand c'est nous qui voulons chercher un employe (sera utile dans d'autres fonctions)

        strcpy(NameOrID, (char*)ID);

    }

    // On avance dans la liste jusqu'a trouver ce qu'on cherche
    // en gardant l'avant cible

    while (strcmp((*Cible)->ID, NameOrID) != 0 && strcmp((*Cible)->Name, NameOrID) != 0) {

        *AvantCible = *Cible;
        *Cible = Suivant(*Cible);
        if (*Cible == NULL) break;

    }

    if (*Cible == NULL) {   // Si rien n'est trouve message d'erreur

        setColor(RED);
        printf("\n\nEmployee not found.\n\n");
        setColor(WHITE);
        return 0;

    }

    return 1;

}

/***************************************************************************************/






/********* Fonction qui permet de supprimer un dossier médical de la liste *********/
/*=================================================================================*/

void DeleteFromEmpList(maillonEmp **Tete) {

    maillonEmp *Cible = *Tete;
    maillonEmp *AvantCible = NULL;

    SearchEmployee(*Tete, &Cible, &AvantCible, NULL, 0);    // L'utilisateur cherche un employe (Mode 0)

    if (Cible == NULL) return;  // Si rien n'est trouve on sort de la fonct.

    else if (Cible == *Tete) {  // Si la cible est la tete de la liste

        *Tete = Suivant(Cible); // On met a jour la tete
        free(Cible);            // On libere l'ancienne tete

        setColor(GREEN);
        printf("\n\nEmployee deleted successfully.\n\n");
        setColor(WHITE);

    } else {

        AffAdr(AvantCible, Suivant(Cible));     // L'avant cible dans son champ adr recevra le suivant de la cible (peut etre NIL)
        free(Cible);                            // On libere la cible

        setColor(GREEN);
        printf("\n\nEmployee deleted successfully.\n\n");
        setColor(WHITE);

    }

}

/***********************************************************************************/






/**************** Mise à jour des dossiers médicaux de la liste ****************/
/*=============================================================================*/



/************* Mise à jour du nombre total de consultations *************/

void UpdateTNumCons(maillonEmp *Cible) {

    int TnumCons;

    printf("\nEnter the new total number of consultations : ");

    do {

        scanf("%d", &TnumCons);
        getchar();

        if (TnumCons <= Cible->TNumCons) {      // Le nouveau TNumCons ne peut pas etre inferieur ou egal au nouveau

            setColor(RED);
            printf("\nUpdated consultations number can't be inferior or equal to the precedent : ");
            setColor(WHITE);

        }

    } while (TnumCons <= Cible->TNumCons);
    
    AffTNumCons(Cible, TnumCons);   // On affecte

}

/************************************************************************/






/************* Mise à jour de la dernière date de consultation *************/

void UpdateLCDate(maillonEmp *Cible, struct tm CurrentDate) {

    int ver = 0;

    char UpdatedDate[MAX_LENGTH_DATE];

    printf("\nEnter the new last consultation date : ");

    do {
        
        scanf("%s", UpdatedDate);
        while (getchar() != '\n');
        ver = CheckDateValidity(Cible->LConsDate, UpdatedDate, 1);      // On verifie si la date est superieure a l'ancienne date

        if (!ver) {

            setColor(RED);
            printf("\nEnter a valid date (No special characters / Superior to previous date) : ");
            setColor(WHITE);

        } else {

            ver = CheckDateValidity(UpdatedDate, &CurrentDate, 0);      // Si elle est superieure on verifie si elle est inferieure a la
            if (!ver) {                                                 // date d'execution du programme

                setColor(RED);
                printf("\nEnter a valid date (No special characters / Superior to previous date / Inferior to today's date) : ");
                setColor(WHITE);

            }

        }

    } while (!ver);

    AffLCDate(Cible, UpdatedDate);      // On affecte

}

/***************************************************************************/






/************* Mise à jour de la date de retour au travail *************/

void UpdateRWDate(maillonEmp *Cible, struct tm CurrentDate) {

    int ver = 0;

    char UpdatedDate[MAX_LENGTH_DATE];

    printf("\nEnter the new return to work date : ");

    do {
            
        scanf("%s", UpdatedDate);
        getchar();
            
        if (strcmp(Cible->RetWorkDate, "N/A") != 0) {   // Si l'employe a une rw date

            ver = CheckDateValidity(Cible->RetWorkDate, UpdatedDate, 1);    // On verifie si la date est superieure a l'ancienne date
            if (!ver) {

                setColor(RED);
                printf("\nEnter a valid date (No special characters / Superior to previous date) : ");
                setColor(WHITE);

            }

        } else {

            ver = CheckDateValidity(UpdatedDate, &CurrentDate, 0);  // Sinon on verifie si elle est inferieure a la date d'execution
            
            if (ver) {

                AffRWDate(Cible, "N/A");    // Si elle est inferieure on met N/A vu qu'elle est deja passee
                return;

            } else {

                struct tm Verification = {0};
                ver = SeparateDate(UpdatedDate, &Verification); // Sinon on verifie le format de la date
                if (!ver) {
                    
                    setColor(RED);
                    printf("\nEnter a valid date (No special characters / DD/MM/YYYY Format) : ");
                    setColor(WHITE);

                }

            }

        }
        
    } while (!ver);

    AffRWDate(Cible, UpdatedDate);  // On affecte

}

/***********************************************************************/






/***************** Mise à jour de l'historique *****************/

void UpdateHistory(maillonEmp *Cible, void *HIST, int Mode) {

    int ver = 0;

    int count;

    char UpdateHist[MAX_LENGTH_HIST];

    if (Mode == 0) {    // Si le mode = 0 alors on demande au user la raison a etre ajoutee

        printf("\nEnter the new consultation reason to be added : ");

        do {
            
            fgets(UpdateHist, MAX_LENGTH_HIST, stdin);
            strtok(UpdateHist, "\n");
            RemoveSuppSpaces(UpdateHist);   // On enleve les espaces supplementaires
            CorrectHist(UpdateHist);        // On corrige l'historique

            if (strcmp(UpdateHist, "None") == 0) {

                setColor(RED);
                printf("\nEnter a valid consultation reason : ");
                setColor(WHITE);

            } else ver = 1;

        } while (!ver);

    } else {    // Sinon si on utilise un string directement comme parametre dans la fonction

        strcpy(UpdateHist, (char*)HIST);    // On met le string dans la variable qu'on va utiliser

    }

    count = CountHistReasons(Cible);    // On compte les raisons

    char temp[MAX_LENGTH_HIST];
    strcpy(temp, Cible->History);

    if (count == 5) {   // Si c'est plein

        char *ToDel = strtok(temp, ",");    // On separe la premiere raison
        char *ToKeep = strtok(NULL, ".");   // On garde les 4 autres
        strcpy(temp, ToKeep);               // On copie ce qu'on garde, on rajoute la nouvelle raison puis un point a la fin.
        strcat(temp, ", ");
        strcat(temp, UpdateHist);
        strcat(temp, ".");
        RemoveSuppSpaces(temp);             // S'il y'a des espaces supp on les enleve

    } else {    // Sinon on n'a rien a supprimer et on ajoute la raison avec un point directement

        char *ToKeep = strtok(temp, ".");
        strcpy(temp, ToKeep);
        strcat(temp, ", ");
        strcat(temp, UpdateHist);
        strcat(temp, ".");

    }

    AffHistory(Cible, temp);    // On affecte

}

/***************************************************************/






/********* Fonction englobant les fonctions de mise à jour avec choix *********/

void UpdateEmpList(maillonEmp *Tete, struct tm CurrentDate) {

    maillonEmp *Cible;
    maillonEmp *AvantCible;

    int choice;
    
    SearchEmployee(Tete, &Cible, &AvantCible, NULL, 0);     // On demande au user d'entrer l'employe a mettre a jour

    if (Cible != NULL) {

        setColor(CYAN);
        printf("\nChoose the field you want to update : ");
        setColor(WHITE);
        printf("\n\n\t1 - Total number of consultations");
        printf("\n\t2 - Last consultation date");
        printf("\n\t3 - Return to work date");
        printf("\n\t4 - History");
        printf("\n\nEnter your choice : ");

        do {

            scanf("%d", &choice);
            getchar();
            if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {

                setColor(RED);
                printf("\nEnter a valid choice : ");
                setColor(WHITE);

            }

        } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

        switch (choice) {   // Selon le choix on va mettre a jour un des champs de l'employe grace aux fonctions au dessus

        case 1:
            
            UpdateTNumCons(Cible);     
            break;
        
        case 2:

            UpdateLCDate(Cible, CurrentDate); 
            break;

        case 3:

            UpdateRWDate(Cible, CurrentDate);
            break;

        case 4:

            UpdateHistory(Cible, NULL, 0);
            break;
        
        default: break;

        }

    }
    
}

/******************************************************************************/



/*=============================================================================*/






/***** Fonction permettant de compter les lignes du fichier Consultations.txt *****/

int CountLines() {

    FILE *file = fopen("Consultations.txt", "r");   // On ouvre le fichier Consultations.txt avec le mode read
    if (file == NULL) {

        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return 0;

    }

    int count = 0;
    char buffer[MAX_BUFFER_SIZE];

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) count++;   // Tant que ce n'est pas la fin du fichier on incremente le compteur

    fclose(file);   // On ferme le fichier

    return count;   // On renvoie count

}

/**********************************************************************************/






/**** Génération du fichier Consultations.txt à partir de la liste des dossiers médicaux ****/

void GenerateConsultationsFile(maillonEmp *Tete, struct tm CurrentDate) {

    FILE *file = fopen("Consultations.txt", "a+");  // On ouvre le fichier avec le mode append (pour ne pas ecraser s'il y'a des lignes)
    if (file == NULL) {

        setColor(RED);
        printf("\nError opening file.\n");
        setColor(WHITE);
        return;

    }

    if (CountLines() == 0) {    // S'il n'y a aucune ligne dans le fichier

        int randomPreEmp = (rand() % 3) + 1;    // On genere un nombre aleat. de consultations pre-employment a ajouter (max 3)
    
        int count = 0;

        char date[MAX_LENGTH_DATE];

        char ExecDate[MAX_LENGTH_DATE];
        CalendarToString(CurrentDate, ExecDate);    // On recupere la date d'execution

        while (Tete != NULL) {  // Tant que la liste n'est pas vide

            if (count < 10) {   // Si count est inferieur a 10 (le nombre de cons. max)

                if (strcmp(ExecDate, Tete->RetWorkDate) == 0) {     // Si la rw date est la meme que celle d'exec

                    fprintf(file, "%s;%s;%s;Return-to-work.\n", Tete->ID, Tete->Name, ConsTime[count]); // On print une consultation retwork
                    count++;    // On incremente le compteur
        
                } else {
        
                    strcpy(date, Tete->LConsDate);  // Sinon on recupere la date de derniere cons.
        
                    struct tm LCDate = {0};
                    SeparateDate(date, &LCDate);    // On la met au format calendrier
        
                    double diff = difftime(mktime(&CurrentDate), mktime(&LCDate));  // On calcule la difference entre la date d'exec et lcdate
                
                    if (diff > ONE_YEAR) {  // Si la difference est superieure a un an
        
                        fprintf(file, "%s;%s;%s;Periodic.\n", Tete->ID, Tete->Name, ConsTime[count]);   // On print une cons. periodic
                        count++;    // On incremente le compteur
        
                    }
        
                }

                int PreEmpRand = rand() % 2;    // On genere un nombre pour voir si on ajoute une consultation pre employment ou pas
                                                // (modulo 2 donc 0 ou 1)

                if (PreEmpRand && randomPreEmp > 0) {   // Si PreEmprand == 1 et on a des cons. pre-emp. a generer alors

                    char RandomEmpFName[MAX_LENGTH_NAME];
                    char RandomEmpLName[MAX_LENGTH_NAME];
                    char RandomEmpID[MAX_LENGTH_ID];
                    generateRandomFName(RandomEmpFName);    // On genere un prenom
                    generateRandomLName(RandomEmpLName);    // On genere un nom de famille
                    generateRandomID(RandomEmpID);          // On genere un ID

                    // On print une consultation pre-employment
                    fprintf(file, "%s;%s %s;%s;Pre-employment.\n", RandomEmpID, RandomEmpLName, RandomEmpFName, ConsTime[count]);
                    count++;            // On incremente le compteur
                    randomPreEmp--;     // On decremente le nombres de cons. pre-emp a generer

                }

            } else {    // Si le nombre de cons. max est depasse

                if (strcmp(ExecDate, Tete->RetWorkDate) == 0) { // Si la date de ret-work est egale a la date d'exec

                    char* temp = date;
                    struct tm TempCal = {0};
                    SeparateDate(date, &TempCal);       // On met au format calendrier
                    TempCal.tm_mday += 1;               // On incremente d'un jour la date rw
                    mktime(&TempCal);                   // On corrige les eventuelles erreurs
                    CalendarToString(TempCal, temp);    // On remet au format string

                    AffRWDate(Tete, temp);              // On affecte

                }

            }

            Tete = Suivant(Tete);   // On avance dans la liste

        }

        setColor(GREEN);
        printf("\nConsultations.txt file generated successfully.");
        setColor(WHITE);

    }

    fclose(file);   // On ferme le fichier

}

/********************************************************************************************/






/****************** Libération de la mémoire allouée dynamiquement ******************/
/*==================================================================================*/

void LibererListe(maillonEmp *Tete) {

    maillonEmp *Suiv = NULL;

    while (Tete != NULL) {      // Tant que la liste n'est pas vide

        Suiv = Suivant(Tete);   // On recupere le maillon suivant dans Suiv
        free(Tete);             // On libere la tete
        Tete = Suiv;            // On met a jour la tete a Suiv

    }

}

/************************************************************************************/

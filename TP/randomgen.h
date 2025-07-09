


// Bibliothèque regroupant les fonctions qui permettent de générer aléatoirement
// des noms de familles, des prénoms, et tous les différents champs des employés
// pour enfin générer un fichier EmpRecords.txt aléatoire.



/*** Bibliothèques ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
/*********************/




/********* Constantes et variables *********/

#define NUM_HIST 6                              // Nombre de cas possible d'historique
#define NUM_NAMES 150                           // Nombre de noms dans les tableaux Random_LNames et FNames
#define MAX_LENGTH_NAME 50                     // Taille maximale d'un nom (100 par précaution)
#define MAX_LENGTH_HIST 150                     // Taille maximale d'un historique
#define MAX_LENGTH_DATE 14                      // Taille maximale d'une date format DD/MM/YYYY (20 par précaution)
#define MAX_LENGTH_ID 10                        // Taille maximale de l'ID d'employé (20 pour éviter le débordement)
#define MAX_BUFFER_SIZE 1024                    // Taille maximale d'une ligne de caractères (1kb)
#define RED 12                                  // Code pour la couleur rouge (Terminal)
#define GRAY 8                                  // Code pour la couleur grise
#define BLUE 9                                  // Code pour la couleur bleue
#define GREEN 10                                // Code pour la couleur verte
#define WHITE 15                                // Code pour la couleur blanche
#define CYAN 11                                 // Code pour la couleur cyan

/*******************************************/








/************************* Terminal ***************************/

void setColor(int ForgeC) {         // Choisir la couleur du texte affiché
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, ForgeC);
}

void clearScreen() {        // Rénitialiser l'écran
    system("cls");
}

/**************************************************************/






/************************************ Génération aléatoire du fichier EmpRecords.txt ************************************/
/*======================================================================================================================*/


/************************************ Déclaration des différents noms de famille ************************************/
char Random_LNames[NUM_NAMES][MAX_LENGTH_NAME] = {
    "Abdelkader", "Ait Ahmed", "Ait Bougmez", "Ait Boussad", "Ait Hamou", "Ait Ouakli", "Ait Yahia", "Benaissa", 
    "Benali", "Benamar","Benatia", "Benayad", "Benayoun", "Benaouda", "Benaouissef", "Benkhader", "Benmebarek", 
    "Bendida", "Benfifi", "Benhamou", "Benkheira","Benmessaoud", "Bennaceur", "Bennai", "Bennay", "Bennour", "Bentaibi", 
    "Bentaleb", "Berrabah", "Bouamama", "Bouchouicha","Boudiaf", "Boufenar", "Bougherara", "Boukerzaza", "Boumaza", 
    "Boumedine", "Bouras", "Bourouiba", "Bouzi", "Chebli","Chergui", "Cherif", "Dadoune", "Djellab", "Ferhati", "Ghazi", 
    "Goucem", "Guendouz", "Guerroudj", "Guezzi","Hadj", "Hamdani", "Hamdad", "Hamdache", "Hammouche", "Hamrouche", 
    "Hamouche", "Hannache", "Hannat", "Hannouche","Kacem", "Kaci", "Kader", "Kadi", "Kahlouche", "Kara", "Kerbouche", 
    "Khelili","Lounis", "Loucif", "Mazouzi", "Meghichi", "Merabet", "Merzougoui", "Messaoudi", "Mouaci", "Naceri", "Ouadah",
    "Ouamrane", "Ouali", "Rabah", "Rachid", "Rahhal", "Ramdani", "Remila", "Rezzoug", "Sadi", "Sadmi", "Sahnoune",
    "Sahraoui", "Said", "Saidi", "Saker", "Sediki", "Seghir", "Senounci", "Slimani", "Taleb", "Zaoui","Abdi", "Abid", 
    "Ait Ali", "Ait Brahim", "Ait El Hadj", "Ait Hadi", "Ait Kaci", "Ait Lahcen", "Ait Mansour", "Ait Moussa", "Ait Said", 
    "Ait Slimane", "Ait Youssef", "Amrani", "Bahloul", "Belhadj", "Belkacem", "Benabdelkader", "Benachour", "Benalioua",
    "Benamara", "Benattia", "Benazouz", "Bendahmane", "Bendebka", "Bendjelloul", "Benhamida", "Benkhaled", "Benmoussa", 
    "Benrabah", "Bensalem", "Benslimane", "Bensouilah", "Bensouissi", "Benyoucef", "Benziane", "Benzitouni", "Bouabdallah", 
    "Bouakkaz", "Bouaziz","Bouchenak", "Bouderbala", "Bouguerra", "Bouhadjar", "Boukercha", "Boukhari", "Boushaba", 
    "Chibane", "Djeffal", "Zerrouki"};
/********************************************************************************************************************/


/**************************************** Déclaration des différents prénoms ****************************************/  
char Random_FNames[NUM_NAMES][MAX_LENGTH_NAME] = {
    "Abdelkader", "Samia", "Kamel", "Djamila", "Fares", "Aziz", "Akrem", "Slimani", "Hamid", "Belkacem",
    "Morad", "Said", "Boudjemaa", "Adlene", "Lakhdar", "Belaid", "Mokrane", "Sirine", "Benali", "Farid",
    "Ferial", "Houda", "Wahiba", "Anis", "Amira", "Bilal", "Khaled", "Farida", "Hakim", "Karima",
    "Ali", "Salima", "Omar", "Nadia", "Yousef", "Houria", "Ahmed", "Hadjer", "Sofiane", "Sana",
    "Mohamed", "Laila", "Reda", "Nawel", "Amine", "Yasmina", "Mehdi", "Malika", "Karim", "Amel",
    "Rachid", "Rym", "Nassim", "Ines", "Nasser", "Hind", "Mounir", "Fatma", "Nabil", "Fatiha",
    "Hassan", "Zineb", "Zakaria", "Asma", "Rafik", "Sabrina", "Tarek", "Amina", "Nacer", "Dina",
    "Adel", "Fella", "Riyad", "Naila", "Kacem", "Sidali", "Walid", "Latifa", "Noureddine", "Rabia",
    "Amar", "Ilhem", "Hichem", "Saida", "Lotfi", "Sihem", "Soufiane", "Soraya", "Yacine", "Wafa", "Lina",
    "Nadir", "Ayoub", "Younes", "Haithem", "Samy", "Imane", "Lounis", "Nora", "Anissa", "Rida",
    "Aicha", "Amel", "Meriem", "Aymen", "Badis", "Chafik", "Chahinez", "Chawki", "Dalia",
    "Djamal", "Dounia", "Tarik", "Farouk", "Fatiha", "Fethi", "Fouad", "Hacene", "Tahar", "Halima",
    "Hanane", "Hania", "Zahir", "Houssem", "Idir", "Imane", "Ismail", "Larbi", "Khadija", "Kheira",
    "Lamine", "Lila", "Lynda", "Malek", "Marwa", "Samir", "Nassim", "Nawal", "Noura", "Nourredine",
    "Rachida", "Rania", "Riad", "Rima", "Yanis", "Salim", "Samira", "Selma", "Zouhir", "Souad"};
/********************************************************************************************************************/





/************************************ Déclaration des différentes causes de consultation ************************************/
char Random_History[NUM_HIST][MAX_LENGTH_HIST] = {
    "None", "Work-accident", "Occupational-disease", "Return-to-work", "Pre-employment", "Periodic"};
/****************************************************************************************************************************/





/*************************** Série de caractères alphanumériques ***************************/
char Alphanum[] = "0123456789";
/*******************************************************************************************/





/*********************** Générer un ID d'employé aléatoire ***********************/
void generateRandomID(char *id) {

    for (int i = 0; i < 8; i++) 
        id[i] = Alphanum[rand() % (sizeof(Alphanum) - 1)];      // On prend le cas de base et on génère un ID de 8 caractères
    id[8] = '\0';                                               // On met le dernier indice à null terminator

}
/*********************************************************************************/




/*********************** Générer un prénom d'employé aléatoire ***********************/
void generateRandomFName(char *fname) {

    strcpy(fname, Random_FNames[rand() % NUM_NAMES]);   // On choisit un prénom aléatoire du tableau pour cela

}
/*********************************************************************************************/





/*********************** Générer un nom de famille d'employé aléatoire ***********************/
void generateRandomLName(char *lname) {

    strcpy(lname, Random_LNames[rand() % NUM_NAMES]);   // On choisit un nom de famille aléatoire du tableau pour cela

}
/*************************************************************************************/





/*********************** Générer un historique d'employé aléatoire ***********************/

void generateRandomHist(char *hist) {
    
    int indices[NUM_HIST - 1];                  // Tableau qui contient les indicies des historiques sauf "None"
    hist[0] = '\0';                             // On initialise à null terminator

    // On remplit le tableau (on évite le 0 car il correspond à "None")

    for (int i = 0; i < NUM_HIST - 1; i++) indices[i] = i + 1;

    // On mélange les indices (sauf indice 0)

    for (int i = NUM_HIST - 2; i > 0; i--) {

        int j = rand() % (i + 1);               // On choisit un indice aléatoire j
        int temp = indices[i];                  // On sauvegarde l'indice qui est dans i dans temp
        indices[i] = indices[j];                // On échange l'indice contenu dans i avec celui dans j
        indices[j] = temp;

    }

    // On choisit aléatoirement un nombre d'historique à inclure (1 à 5)

    int numhist = rand() % 5 + 1;
    int count = 0;

    if (numhist < 5) {

        // Si le nombre est inférieur à 5, Pre-employment doit etre le premier

        strcpy(hist, Random_History[4]);        // Ajouter "Pre-employment" en premier
        count++;

        // On ajoute l'historique restant (sauf "None" et "Pre-employment")

        for (int i = 0; count < numhist && i < NUM_HIST - 1; i++) {

            int index = indices[i];
            if (index == 4) continue;           // On saute "Pre-employment"
            if (count > 0) strcat(hist, ",");
            strcat(hist, Random_History[index]);
            count++;

        }

    } else {

        // Si le nombre est égal à 5, "Pre-employment" peut ne pas apparaitre
        // On re mélange les indices

        for (int i = NUM_HIST - 2; i > 0; i--) {

            int j = rand() % (i + 1);
            int temp = indices[i];
            indices[i] = indices[j];
            indices[j] = temp;

        }

        // Vérifier s'il y'a "Pre-employment"

        int pre_employment_index = -1;

        for (int i = 0; i < NUM_HIST - 1; i++) {

            if (indices[i] == 4) {

                pre_employment_index = i;
                break;

            }

        }

        // S'il y est on le met au début

        if (pre_employment_index != -1) {

            int temp = indices[0];
            indices[0] = indices[pre_employment_index];
            indices[pre_employment_index] = temp;

        }

        // On ajoute enfin l'historique de la meme manière (sauf "None")

        for (int i = 0; count < numhist && i < NUM_HIST - 1; i++) {

            int index = indices[i];
            if (count > 0) strcat(hist, ",");
            strcat(hist, Random_History[index]);
            count++;

        }

    }

    strcat(hist, ".");  // On met un point à la fin

}

/*****************************************************************************************/





/************* Générer une date de consultation (et retour au travail optionnellement) aléatoire(s) *************/

void generateRandomDate(char *LCDate, char *RWDate, char *hist, struct tm currentDate, time_t currentTime) {

    int daysInPast = rand() % 201;      // On génère des jours passés aléatoirement (Entre 0 et 200)

    time_t lastConsultationTime = currentTime - (daysInPast * 24 * 60 * 60);        // On les soustrait à la date d'exec
    struct tm lastConsultationDate = *localtime(&lastConsultationTime);

    char buffer[MAX_BUFFER_SIZE];

    sprintf(buffer, "%02d", lastConsultationDate.tm_mday);              // On formate la date pour avoir DD/MM/YYYY
    strcpy(LCDate, buffer); 
    strcat(LCDate, "/");
    sprintf(buffer, "%02d", lastConsultationDate.tm_mon + 1);
    strcat(LCDate, buffer);
    strcat(LCDate, "/");
    sprintf(buffer, "%04d", lastConsultationDate.tm_year + 1900);
    strcat(LCDate, buffer);

    int randomRestDays = (rand() % 121) + 30;       // On génère des jours de repos aléatoirement        

    int randomDayRet = lastConsultationDate.tm_mday + randomRestDays;   // On les ajoute a la date d'exec
    int randomMonthRet = lastConsultationDate.tm_mon;
    int randomYearRet = lastConsultationDate.tm_year;

    struct tm returnDate = {0};
    returnDate.tm_mday = randomDayRet;
    returnDate.tm_mon = randomMonthRet;
    returnDate.tm_year = randomYearRet;

    mktime(&returnDate);                            // On corrige les eventuelles erreurs grace a mktime

    char *DernierHist = strrchr(hist, ',');         // On recupere la derniere raison de consultation (derniere chaine apres la virgule)
    if (DernierHist == NULL) DernierHist = hist;    // S'il n y'a pas de virgule ca sera le premier
    else DernierHist += 1;                          // On incremente le ptr pour enlever la virgule

    time_t tReturn = mktime(&returnDate);
    time_t tCurrent = mktime(&currentDate);

    if (tReturn > tCurrent  && (strcmp(DernierHist, "Work-accident.") == 0 || strcmp(DernierHist, "Occupational-disease.") == 0)) {

        sprintf(buffer, "%02d", returnDate.tm_mday);
        strcpy(RWDate, buffer);
        strcat(RWDate, "/");
        sprintf(buffer, "%02d", returnDate.tm_mon + 1);         // Si les conditions sont bonnes l'employé aura une date de retour
        strcat(RWDate, buffer);
        strcat(RWDate, "/");
        sprintf(buffer, "%04d", returnDate.tm_year + 1900);
        strcat(RWDate, buffer);

    } else strcpy(RWDate, "N/A");
}

/****************************************************************************************************************/





/************* Générer un fichier EmpRecords.txt aléatoire selon le nombre choisi d'employés *************/

void generateEmpRecord(int NombreEmp, struct tm currentDate, time_t currentTime) {

    char randomid[MAX_LENGTH_ID];
    char randomfname[MAX_LENGTH_NAME];
    char randomlname[MAX_LENGTH_NAME];
    char randomhist[MAX_LENGTH_HIST];
    char randomlcdate[MAX_LENGTH_DATE];
    char randomrwdate[MAX_LENGTH_DATE];

    FILE *file = fopen("EmpRecords.txt", "w");
    if (file == NULL) {

        setColor(4);
        printf("Error opening file.\n");
        setColor(7);
        return;

    }

    for (int i = 0; i < NombreEmp; i++) {

        generateRandomID(randomid);
        generateRandomFName(randomfname);
        generateRandomLName(randomlname);
        generateRandomHist(randomhist);
        generateRandomDate(randomlcdate, randomrwdate, randomhist, currentDate, currentTime);

        fprintf(file, "%s;%s %s;%d;%s;", randomid, randomfname, randomlname, (rand() % 6) + 1, randomlcdate);
        if (strcmp(randomrwdate, "N/A") != 0) fprintf(file, "%s;", randomrwdate);
        fprintf(file, "%s\n", randomhist);

    }

    fclose(file);

    setColor(GREEN);
    printf("\nFile generated successfully.");
    setColor(WHITE);

}

/*********************************************************************************************************/

/*======================================================================================================================*/
/************************************************************************************************************************/
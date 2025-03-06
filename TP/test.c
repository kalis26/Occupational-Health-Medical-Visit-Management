#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define NUM_NAMES 150
#define MAX_LENGTH_NAME 20
#define NUM_HIST 6
#define MAX_LENGTH_HIST 255
#define BUFFER_SIZE 255

typedef struct typecell {
    struct employee {
        char ID[8];
        char Name[MAX_LENGTH_NAME];
        int TNumCons;
        char LConsDate[10];
        char RetWorkDate[10];
        char History[MAX_LENGTH_HIST];
    };
    struct typecell *adr;
} maillonEmp;

maillonEmp *NIL = NULL;

void Allouer(maillonEmp **A)
{
    *A = malloc(sizeof(maillonEmp));
    if (*A == NULL)
    {
        printf("\nMemory allocation failed\n");
        exit(1);
    }
}

void AffAdr(maillonEmp *A, maillonEmp *a)
{
    A->adr = a;
}

maillonEmp* Suivant(maillonEmp *A)
{
    return A->adr;
}

char Random_LNames[NUM_NAMES][MAX_LENGTH_NAME] = {
    "Abdelkader", "Ait Ahmed", "Ait Bougmez", "Ait Boussad", "Ait Hamou", "Ait Ouakli", "Ait Yahia", "Benaissa", "Benali", "Benamar", 
    "Benatia", "Benayad", "Benayoun", "Benaouda", "Benaouissef", "Benkhader", "Benmebarek", "Bendida", "Benfifi", "Benhamou", "Benkheira",
    "Benmessaoud", "Bennaceur", "Bennai", "Bennay", "Bennour", "Bentaibi", "Bentaleb", "Berrabah", "Bouamama", "Bouchouicha",
    "Boudiaf", "Boufenar", "Bougherara", "Boukerzaza", "Boumaza", "Boumedine", "Bouras", "Bourouiba", "Bouzi", "Chebli",
    "Chergui", "Cherif", "Dadoune", "Djellab", "Ferhati", "Ghazi", "Goucem", "Guendouz", "Guerroudj", "Guezzi",
    "Hadj", "Hamdani", "Hamdad", "Hamdache", "Hammouche", "Hamrouche", "Hamouche", "Hannache", "Hannat", "Hannouche",
    "Kacem", "Kaci", "Kader", "Kadi", "Kahlouche", "Kara", "Kerbouche", "Khelili",
    "Lounis", "Loucif", "Mazouzi", "Meghichi", "Merabet", "Merzougoui", "Messaoudi", "Mouaci", "Naceri", "Ouadah",
    "Ouamrane", "Ouali", "Rabah", "Rachid", "Rahhal", "Ramdani", "Remila", "Rezzoug", "Sadi", "Sadmi", "Sahnoune",
    "Sahraoui", "Said", "Saidi", "Saker", "Sediki", "Seghir", "Senounci", "Slimani", "Taleb", "Zaoui",
    "Abdi", "Abid", "Ait Ali", "Ait Brahim", "Ait El Hadj", "Ait Hadi", "Ait Kaci", "Ait Lahcen", "Ait Mansour", "Ait Moussa",
    "Ait Said", "Ait Slimane", "Ait Youssef", "Amrani", "Bahloul", "Belhadj", "Belkacem", "Benabdelkader", "Benachour", "Benalioua",
    "Benamara", "Benattia", "Benazouz", "Bendahmane", "Bendebka", "Bendjelloul", "Benhamida", "Benkhaled", "Benmoussa", "Benrabah",
    "Bensalem", "Benslimane", "Bensouilah", "Bensouissi", "Benyoucef", "Benziane", "Benzitouni", "Bouabdallah", "Bouakkaz", "Bouaziz",
    "Bouchenak", "Bouderbala", "Bouguerra", "Bouhadjar", "Boukercha", "Boukhari", "Boushaba", "Chibane", "Djeffal", "Zerrouki"
};

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
    "Rachida", "Rania", "Riad", "Rima", "Yanis", "Salim", "Samira", "Selma", "Zouhir", "Souad"
};

char Random_History[NUM_HIST][MAX_LENGTH_HIST] = {
    "None", "Work accident", "Occupational disease", "Return-to-work visit", "Pre-employment visit", "Periodic examination"};

char Alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void setColor(int ForgeC)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, ForgeC);
}

void generateRandomID(char *id)
{
    for (int i = 0; i < 8; ++i)
    {
        id[i] = Alphanum[rand() % (sizeof(Alphanum) - 1)];
    }
    id[8] = '\0';
}

void generateRandomFName(char *fname)
{
    strcpy(fname, Random_FNames[rand() % NUM_NAMES]);
}

void generateRandomLName(char *lname)
{
    strcpy(lname, Random_LNames[rand() % NUM_NAMES]);
}

void generateRandomHist(char *hist)
{
    int index;
    int numhist = rand() % 5 + 1;
    int usedIndices[NUM_HIST] = {0};
    hist[0] = '\0';
    for (int i = 0; i < numhist; i++) {
        do {
            index = rand() % NUM_HIST;
        } while (usedIndices[index] || (index == 0 && numhist > 1));
        usedIndices[index] = 1;

        if (i > 0) {
            strcat(hist, ", ");
        }
        strcat(hist, Random_History[index]);
    }
}

void generateEmpList(FILE *file) {

    file = fopen("EmpRecords.txt", "r");
    if (file == NULL)
    {
        setColor(4);
        printf("Error opening file.\n");
        setColor(7);
        return;
    }

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        
    }
    

}

void generateEmpRecord(FILE *file) {

    char randomid[9];
    char randomfname[MAX_LENGTH_NAME];
    char randomlname[MAX_LENGTH_NAME];
    char randomhist[MAX_LENGTH_HIST];

    file = fopen("EmpRecords.txt", "w");
    if (file == NULL)
    {
        setColor(4);
        printf("Error opening file.\n");
        setColor(7);
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        generateRandomID(randomid);
        generateRandomFName(randomfname);
        generateRandomLName(randomlname);
        generateRandomHist(randomhist);

        fprintf(file, "Employee ID: %s\n", randomid);
        fprintf(file, "Full Name: %s %s\n", randomlname, randomfname);
        fprintf(file, "Total Number of Consultations: %d\n", (rand() % 6));
        fprintf(file, "Last consultation Date: %02d/%02d/202%d\n", (rand() % 31 + 1), (rand() % 12 + 1), (rand() % 2 + 4));
        fprintf(file, "History: %s\n\n", randomhist);
    }

    fclose(file);

    setColor(10);
    printf("\n\nFile generated successfully.\n\n");
    setColor(7);

}

void main()
{
    srand(time(0));

    FILE *EmpRecord;

    generateEmpRecord(EmpRecord);


}

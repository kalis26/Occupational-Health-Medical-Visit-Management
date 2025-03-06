#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct typecell {
    int val;
    struct typecell *adr;
} maillon;

maillon *NIL = NULL;

typedef struct typecellB {
    struct typecellB *adrG;
    int val;
    struct typecellB *adrD;
} maillonB;

maillonB *NILB = NULL;

#define Allouer(X) _Generic((X), \
    maillon * *: AllouerN,       \
    maillonB * *: AllouerB,      \
    default: AllouerN)(X)

#define AffVal(X, integer) _Generic((X), \
    maillon *: AffValN,                  \
    maillonB *: AffValB,                 \
    default: AffValN)(X, integer)

#define Valeur(X) _Generic((X), \
    maillon *: ValeurN,         \
    maillonB *: ValeurB,        \
    default: ValeurN)(X)

#define Suivant(X) _Generic((X), \
    maillon *: SuivantN,         \
    maillonB *: SuivantB,        \
    default: SuivantN)(X)

#define PrintList(X) _Generic((X), \
    maillon *: PrintListN,         \
    maillonB *: PrintListB,        \
    default: PrintListN)(X)

void AllouerN(maillon **A) {
    *A = malloc(sizeof(maillon));
    if (*A == NULL) {
        printf("\nMemory allocation failed\n");
        exit(1);
    }
}

void AllouerB(maillonB **A) {
    *A = malloc(sizeof(maillonB));
    if (*A == NULL) {
        printf("\nMemory allocation failed\n");
        exit(1);
    }
}

void AffValN(maillon *A, int N) {
    A->val = N;
}

void AffValB(maillonB *A, int N) {
    A->val = N;
}

void AffAdr(maillon *A, maillon *a) {
    A->adr = a;
}

void AffAdrG(maillonB *A, maillonB *a) {
    A->adrG = a;
}

void AffAdrD(maillonB *A, maillonB *a) {
    A->adrD = a;
}

int ValeurN(maillon *A) {
    return A->val;
}

int ValeurB(maillonB *A) {
    return A->val;
}

maillon* SuivantN(maillon *A) {
    return A->adr;
}

maillonB* SuivantB(maillonB *A) {
    return A->adrD;
}

maillonB* Precedent(maillonB *A) {
    return A->adrG;
}

void Liberer(maillon * Tete) {
    while (Tete != NIL) {
        maillon * suiv = Suivant(Tete);
        free(Tete);
        Tete = suiv;
    }
    printf("\n\nFreed all the memory.\n");
}

maillon *CreateList(int *N)
{
    printf("\nEnter the number of elements : ");
    scanf("%d", N);
    maillon *Tete = NIL;
    if (*N < 0) {
        printf("Invalid number of elements in CreateList(int *N)");
        exit(1);
    } else if (*N > 0) {
        int Val;
        printf("\nC[1] = ");
        scanf("%d", &Val);
        Allouer(&Tete);
        AffVal(Tete, Val);
        AffAdr(Tete, NIL);
        maillon *Temp = Tete;
        maillon *Trav;
        for (int i = 2; i <= *N; i++)
        {
            Allouer(&Trav);
            AffAdr(Temp, Trav);
            AffAdr(Trav, NIL);
            printf("\nC[%d] = ", i);
            scanf("%d", &Val);
            AffVal(Trav, Val);
            Temp = Trav;
        }
    }
    return Tete;
}

maillonB* CreateBList(int *N) {
    printf("\nEnter the number of elements : ");
    scanf("%d",N);
    maillonB *Tete;
    if (*N < 0) {
        printf("Invalid number of elements in CreateBList(int *N)");
        exit(1);
    } else if (*N > 0) {
        int Val;
        printf("\nC[1] = ");
        scanf("%d",&Val);
        Allouer(&Tete);
        AffAdrG(Tete,NILB);
        AffAdrD(Tete,NILB);
        AffVal(Tete,Val);
        maillonB *Temp = Tete;
        maillonB *Trav;
        for (int i = 2; i <= *N; i++)
        {
            Allouer(&Trav);
            AffAdrD(Temp, Trav);
            AffAdrG(Trav,Temp);
            AffAdrD(Trav, NILB);
            printf("\nC[%d] = ", i);
            scanf("%d", &Val);
            AffVal(Trav, Val);
            Temp = Trav;
        }  
    }
    return Tete;
}

void PrintListN(maillon *Tete)
{
    printf("\n");
    int count = 1;
    if (Tete == NIL) {
        printf("\nEmpty list.");
    } else {
        while (Tete != NIL) {
            printf("\nC[%d] = %d", count, Valeur(Tete));
            Tete = Suivant(Tete);
            count++;
        }
    }
}

void PrintListB(maillonB *Tete)
{
    printf("\n");
    int count = 1;
    if (Tete == NILB) {
        printf("\nEmpty list.");
    } else {
        while (Tete != NILB) {
            printf("\nC[%d] = %d", count, Valeur(Tete));
            Tete = Suivant(Tete);
            count++;
        }
    }
}

void FindPos(maillon *Tete, int Pos, maillon **Element)
{
    *Element = NIL;
    if (Tete == NIL)
    {
        printf("\nEmpty list.");
    }
    else
    {
        int count = 1;
        while (count != Pos && Tete != NIL)
        {
            Tete = Suivant(Tete);
            count++;
        }
        if (count == Pos && Tete != NIL)
        {
            *Element = Tete;
        }
    }
}

void InsertPos(maillon **Tete, int pos, int val)
{
    maillon *P, *Q;
    if (*Tete == NIL || pos == 1)
    {
        Allouer(&P);
        AffVal(P, val);
        AffAdr(P, *Tete);
        *Tete = P;
    }
    else
    {
        FindPos(*Tete, pos - 1, &Q);
        if (Q == NIL)
        {
            Q = *Tete;
            while (Suivant(Q) != NIL)
            {
                Q = Suivant(Q);
            }
            Allouer(&P);
            AffVal(P, val);
            AffAdr(P, NIL);
            AffAdr(Q, P);
        }
        else
        {
            Allouer(&P);
            AffVal(P, val);
            AffAdr(P, Suivant(Q));
            AffAdr(Q, P);
        }
    }
}
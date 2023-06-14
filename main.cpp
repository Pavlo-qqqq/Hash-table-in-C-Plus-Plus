#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef const char* nametype;

struct celltype {
    nametype element;
    celltype* next;
};

const int DICT_SIZE = 5;

typedef celltype* DICTIONARY[DICT_SIZE];

int hash(nametype x) {
    int sum = 0;

    for (unsigned int i = 0; i < strlen(x); i++) {
        sum += (int)x[i];
    }

    return sum % DICT_SIZE;
}

void MAKENULL(DICTIONARY A) {
    for (int i = 0; i < DICT_SIZE; i++) {
        A[i] = NULL;
    }
}

bool MEMBER(DICTIONARY A, nametype x) {
    int index = hash(x);

    celltype* current = A[index];
    while (current != NULL) {
        if (strcmp(current->element, x) == 0) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void INSERT(DICTIONARY A, nametype x) {
    int bucket = hash(x);
    celltype* oldheader = A[bucket];

    if (!MEMBER(A, x)) {
        A[bucket] = (celltype*)malloc(sizeof(celltype));
        A[bucket]->element = x;
        A[bucket]->next = oldheader;
    }
}

void DELETE(DICTIONARY A, nametype x) {
    int index = hash(x);

    if (A[index] != NULL) {
        celltype* current = A[index];
        celltype* previous = NULL;

        while (current != NULL && strcmp(current->element, x) != 0) {
            previous = current;
            current = current->next;
        }

        if (current != NULL) {
            if (previous == NULL) {
                A[index] = current->next;
            }
            else {
                previous->next = current->next;
            }

            free(current);
        }
    }
}

void PRINT(DICTIONARY A) {
    celltype* current;

    for (int i = 0; i < DICT_SIZE; i++) {
        printf("\n[%d]", i);

        current = A[i];
        while (current != NULL) {
            printf(" %s", current->element);
            current = current->next;
        }
    }
    printf("\n");
}

int main() {
    DICTIONARY A;
    MAKENULL(A);
    nametype cities[] = { "Kyiv", "Lviv", "Odesa", "Kharkiv", "Dnipro", "Vinnytsia",
                         "Zaporizhzhia", "Mykolayiv", "Lutsk", "Chernivtsi",
                         "Ivano-Frankivsk", "Ternopil", "Uzhhorod", "Poltava", "Sumy" };

    for (int i = 0; i < 15; i++) {
        INSERT(A, cities[i]);
    }

    PRINT(A);

    DELETE(A, "Lviv");

    if (MEMBER(A, "Lviv")) {
        printf("Lviv is in the dictionary.\n");
    }
    else {
        printf("Lviv is not in the dictionary.\n");
    }
}
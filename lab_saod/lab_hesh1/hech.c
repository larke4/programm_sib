#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int hash(char c, int size) {
    return (c % size + size) % size; 
}

int linearProbe(int *table, int size, int key) {
    int i = 0;
    int index;
    do {
        index = (key + i) % size;
        i++;
    } while (table[index] != 0 && i < size);
    return index;
}

int quadraticProbe(int *table, int size, int key) {
    int i = 0;
    int index;
    do {
        index = (key + i * i) % size;
        i++;
    } while (table[index] != 0 && i < size);
    return index;
}

int insert(int *table, int size, char c, int method) {
    int key = hash(c, size);
    int collisions = 0;
    int index;

    if (method == 1) { 
        index = linearProbe(table, size, key);
        collisions = (index - key + size) % size;
    } else { 
        index = quadraticProbe(table, size, key);
        collisions = (index - key + size) % size;
    }

    table[index] = c; 
    return collisions;
}

void printHashTable(int *table, int size, const char *method) {
    printf("%s хеш-таблица:\n", method);
    for (int i = 0; i < size; i++) {
        if (table[i] == 0) {
            printf("- "); 
        } else {
            printf("%c ", table[i]); 
        }
    }
    printf("\n\n");
}

int main() {
    char key[] = "ZHARIKOILYA";
    int numKeys = strlen(key);




    int size = 11;
    int *linearTable = (int *)calloc(size, sizeof(int));
    int *quadraticTable = (int *)calloc(size, sizeof(int));

    if (linearTable == NULL || quadraticTable == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    for (int j = 0; j < numKeys; j++) {
        insert(linearTable, size, key[j], 1);
        insert(quadraticTable, size, key[j], 2);
    }

    printHashTable(linearTable, size, "Линейная");
    printHashTable(quadraticTable, size, "Квадратичная");
    printf("| %-15s | %-19s | %-19s | %-19s |\n", "Размер", "Количество исх. символов", "Кол-во коллизий (Линейные пробы)", "Кол-во коллизий (Квадратичные пробы)");
    free(linearTable);
    free(quadraticTable);
    for (int size = 11; size <= 101; size++) {
        if (!isPrime(size)) continue;

        int *linearTable = (int *)calloc(size, sizeof(int));
        int *quadraticTable = (int *)calloc(size, sizeof(int));

        if (linearTable == NULL || quadraticTable == NULL) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            return 1;
        }

        int linearCollisions = 0;
        int quadraticCollisions = 0;

        for (int j = 0; j < numKeys; j++) {
            linearCollisions += insert(linearTable, size, key[j], 1);
            quadraticCollisions += insert(quadraticTable, size, key[j], 2);
        }

        

        printf("| %-9d | %-24d | %-32d | %-36d |\n", size, numKeys, linearCollisions, quadraticCollisions);

        free(linearTable);
        free(quadraticTable);
    }

    return 0;
}
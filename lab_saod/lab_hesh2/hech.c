#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int hash(char c, int size) {
    return (c % size + size) % size; 
}

//считаем количество уникальных символов
int countUniqueSym(char *str){
    int syms[256]  = {0}; //под каждый символ своя ячейка
    int counter = 0;
    for(int i = 0; str[i] != '\0'; i++){
        unsigned char c = (unsigned char)str[i];
        if (!syms[c]){
            syms[c] = 1;
            counter++;
        }
    }
    return counter;
}


//линейная проба
int linearProbe(int *table, int size, int key, int *probes) {
    int m = 0;
    int index;
    do {
        index = (key + m) % size;
        if (table[index] == 0) {
            *probes = m;
            return index;
        }
        m++;
    } while (m < size);
    *probes = -1; 
    return -1;
}


//квадратичная проба
int quadraticProbe(int *table, int size, int key, int *probes) {
    int m = 0;
    int index;
    do {
        index = (key + m * m) % size;
        if (table[index] == 0) {
            *probes = m;
            return index;
        }
        m++;
    } while (m < size);
    *probes = -1; 
    return -1;
}

//заполнение
int insert(int *table, int size, char c, int method) {
    int key = hash(c, size);
    for (int i = 0; i < size; i++) {
        int probeIndex;
        if (method == 1) {
            probeIndex = (key + i) % size;
        } else {
            probeIndex = (key + i * i) % size;
        }
        if (table[probeIndex] == 0) {
            break; 
        }
        if (table[probeIndex] == (int)c) {
            return 0; 
        }
    }
    int probes;
    int index;
    if (method == 1) {
        index = linearProbe(table, size, key, &probes);
    } else {
        index = quadraticProbe(table, size, key, &probes);
    }
    if (index == -1) {
        return -1; 
    }
    table[index] = (int)c;
    return probes; 
}

void printHashTable(int *table, int size, const char *method) {
    printf("\n%s [size: %d]\n", method, size);
    
    // Вывод позиций
    printf("Pos:");
    for (int i = 0; i < size; i++) {
        printf("|%2d", i);
    }
    printf("|\n");
    
    // Разделительная линия
    printf("    ");
    for (int i = 0; i < size; i++) {
        printf("+--");
    }
    printf("+\n");
    
    // Вывод значений
    printf("Val:");
    for (int i = 0; i < size; i++) {
        if (table[i] == 0) {
            printf("|  ");
        } else {
            printf("|%2c", table[i]);
        }
    }
    printf("|\n\n");
}
int main() {
    char *text ="Smart homes and cities are another frontier. AI-powered systems manage energy consumption, traffic flow, and security, making urban living more efficient and sustainable. Meanwhile, autonomous vehicles promise safer roads by eliminating human error.. Despite its benefits, AI poses ethical challenges. Bias in training data can lead to discriminatory outcomes, while deepfake technology threatens misinformation. Ensuring transparency, fairness, and accountability in AI systems is crucial for building public trust.As AI continues to evolve, collaboration between policymakers, technologists, and ethicists will shape its impact. By harnessing its potential responsibly, we can create a future where AI enhances human capabilities without compromising our values.";
    int numKeys = countUniqueSym(text);

    int size = 47;
    int *linearTable = (int *)calloc(size, sizeof(int));
    int *quadraticTable = (int *)calloc(size, sizeof(int));

    if (linearTable == NULL || quadraticTable == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    int linearCollisions = 0;
    int quadraticCollisions = 0;
    for (int j = 0; j < strlen(text); j++) {
        int lin_result = insert(linearTable, size, text[j], 1);
        int quad_result = insert(quadraticTable, size, text[j], 2);
        if (lin_result >= 0) linearCollisions += lin_result;
        if (quad_result >= 0) quadraticCollisions += quad_result;
    }

    printHashTable(linearTable, size, "Линейная");
    printHashTable(quadraticTable, size, "Квадратичная");

    printf("| %-15s | %-19s | %-19s | %-19s |\n", "Размер", "Количество исх. символов", "Кол-во коллизий (Линейные пробы)", "Кол-во коллизий (Квадратичные пробы)");
    printf("|-----------|--------------------------|----------------------------------|--------------------------------------|\n");

    free(linearTable);
    free(quadraticTable);


    int prime_numbers[10];
    int index = 0;
    int turn = 0;
    //вычислим все простые числа начиная с 14 до 101 и будем записывать каждое второе число 
    for(int i = 14; i < 102; i++){
        if (isPrime(i) && turn == 0){
            prime_numbers[index] = i;
            index++;
            turn = 1;
        }
        else if(isPrime(i) && turn == 1){
            turn = 0;
        }
    }

    for (int i = 0; i < 10; i++) {

        int *linearTable = (int *)calloc(prime_numbers[i], sizeof(int));
        int *quadraticTable = (int *)calloc(prime_numbers[i], sizeof(int));

   

        int linearCollisions = 0;
        int quadraticCollisions = 0;

        for (int j = 0; j < strlen(text); j++) {
            int lin_result = insert(linearTable, prime_numbers[i], text[j], 1);
            int quad_result = insert(quadraticTable, prime_numbers[i], text[j], 2);
            if (lin_result >= 0) linearCollisions += lin_result;
            if (quad_result >= 0) quadraticCollisions += quad_result;
        }

        printf("| %-9d | %-24d | %-32d | %-36d |\n|-----------|--------------------------|----------------------------------|--------------------------------------|\n", prime_numbers[i], numKeys, linearCollisions, quadraticCollisions);

        free(linearTable);
        free(quadraticTable);
    }

    return 0;
}
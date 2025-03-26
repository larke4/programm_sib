#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char surname[50];
    char name[50];
    char phone[15];
    int age;
} Abonent;

typedef enum {
    SORT_BY_SURNAME_AND_NAME,
    SORT_BY_PHONE,
    SORT_BY_NAME_AND_PHONE 
} SortKey;

SortKey currentSortKey = SORT_BY_SURNAME_AND_NAME;

int less(Abonent *a, Abonent *b) {
    int cmpResult;  // Объявляем переменную в начале функции
    
    switch (currentSortKey) {
        case SORT_BY_SURNAME_AND_NAME:
            cmpResult = strcmp(a->surname, b->surname);
            if (cmpResult != 0) {
                return cmpResult < 0;
            }
            return strcmp(a->name, b->name) < 0;
            
        case SORT_BY_PHONE:
            return strcmp(a->phone, b->phone) < 0;
            
        case SORT_BY_NAME_AND_PHONE:  // Новый случай сортировки
            cmpResult = strcmp(a->name, b->name);
            if (cmpResult != 0) {
                return cmpResult < 0;
            }
            return strcmp(a->phone, b->phone) < 0;
            
        default:
            return 0;
    }
}

void printPhonebook(Abonent *phonebook, int size) {
    printf("Фамилия\t\tИмя\t\tТелефон\t\tВозраст\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t\t%s\t\t%s\t\t%d\n", 
               phonebook[i].surname, 
               phonebook[i].name, 
               phonebook[i].phone, 
               phonebook[i].age);
    }
    printf("\n");
}

void insertionSort(Abonent *phonebook, int size) {
    for (int i = 1; i < size; i++) {
        Abonent key = phonebook[i];
        int j = i - 1;

        while (j >= 0 && less(&key, &phonebook[j])) {
            phonebook[j + 1] = phonebook[j];
            j--;
        }
        phonebook[j + 1] = key;
    }
}

int main() {
    Abonent phonebook[] = {
        {"Таубин", "Георгий", "123-456-789", 23},
        {"Столба", "Антон", "987-654-321", 23},
        {"Шапокляк", "Павел", "555-555-555", 26},
        {"Таубин", "Павел", "111-222-333", 11},
        {"Остапец", "Екатерина", "444-444-444", 22}
    };

    int size = sizeof(phonebook) / sizeof(phonebook[0]);

    printf("Исходная телефонная книга:\n");
    printPhonebook(phonebook, size);

    int choice;
    printf("Выберите ключ сортировки:\n");
    printf("1. По фамилии и имени\n");
    printf("2. По номеру телефона\n");
    printf("3. По имени и номеру телефона\n");  // Новая опция
    printf("Введите номер: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            currentSortKey = SORT_BY_SURNAME_AND_NAME;
            break;
        case 2:
            currentSortKey = SORT_BY_PHONE;
            break;
        case 3:  // Обработка нового ключа
            currentSortKey = SORT_BY_NAME_AND_PHONE;
            break;
        default:
            printf("Неверный выбор. Сортировка по умолчанию (фамилия и имя).\n");
            currentSortKey = SORT_BY_SURNAME_AND_NAME;
    }

    insertionSort(phonebook, size);

    printf("Отсортированная телефонная книга:\n");
    printPhonebook(phonebook, size);

    return 0;
}
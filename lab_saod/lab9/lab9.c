#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RECORDS 5
#define MAX_NAME 30    // Размер для ФИО
#define MAX_PHONE 16   // Размер для телефона
#define MAX_ADDRESS 40 // размер для адреса
#define MAX_EMAIL 25   // Размер для email

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
    char email[MAX_EMAIL];
} Contact;

// Исходные данные (5 записей)
Contact phonebook[MAX_RECORDS] = {
    {"Иванов И.И.", "+79161234567", "ул. Ленина, 10, кв.5", "ivanov@mail.ru"},
    {"Петров П.П.", "+79031234568", "пр. Мира, 15, кв.12", "petrov@gmail.com"},
    {"Сидоро А.С.", "+79261234569", "ул. Гагарина, 3     ", "sidoro@yandex.ru"},
    {"Кузнец А.В.", "+79091234570", "ул. Советская, 22   ", "kuznet@mail.ru"},
    {"Смирно О.Д.", "+79171234571", "пр. Победы, 45", "smirno@gmail.com"}
};

int name_index[MAX_RECORDS];
int phone_index[MAX_RECORDS];

void init_index_arrays() {
    for (int i = 0; i < MAX_RECORDS; i++) {
        name_index[i] = i;
        phone_index[i] = i;
    }
}

void sort_by_name() {
    for (int i = 0; i < MAX_RECORDS - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < MAX_RECORDS; j++) {
            if (strcmp(phonebook[name_index[j]].name, phonebook[name_index[min_idx]].name) < 0) {
                min_idx = j;
            }
        }
        int temp = name_index[i];
        name_index[i] = name_index[min_idx];
        name_index[min_idx] = temp;
    }
}

void sort_by_phone() {
    for (int i = 1; i < MAX_RECORDS; i++) {
        int key = phone_index[i];
        int j = i - 1;
        while (j >= 0 && strcmp(phonebook[phone_index[j]].phone, phonebook[key].phone) > 0) {
            phone_index[j + 1] = phone_index[j];
            j = j - 1;
        }
        phone_index[j + 1] = key;
    }
}

void print_table_header() {
    printf("\n┌──────────────────────────────┬─────────────────┬──────────────────────────────┬───────────────────────────┐\n");
    printf("│ %-28s    │ %-15s        │ %-28s      │ %-25s │\n", "ФИО", "Телефон", "Адрес", "Email");
    printf("├──────────────────────────────┼─────────────────┼──────────────────────────────┼───────────────────────────┤\n");
}

void print_contact(Contact c) {
    printf("│ %-28s         │ %-15s │ %-28s         │ %-25s │\n", c.name, c.phone, c.address, c.email);
}

void print_table_footer() {
    printf("└──────────────────────────────┴─────────────────┴──────────────────────────────┴───────────────────────────┘\n");
}

void print_index_array(int index_array[], const char *title) {
    printf("\n%s: [", title);
    for (int i = 0; i < MAX_RECORDS; i++) {
        printf("%d", index_array[i]);
        if (i < MAX_RECORDS - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void print_phonebook(int index_array[], const char *sort_type) {
    printf("\nТелефонный справочник (%s):", sort_type);
    print_table_header();
    for (int i = 0; i < MAX_RECORDS; i++) {
        print_contact(phonebook[index_array[i]]);
    }
    print_table_footer();
    print_index_array(index_array, "Индексный массив");
}

int main() {
    init_index_arrays();
    
    print_phonebook(name_index, "исходный порядок");
    
    sort_by_name();
    print_phonebook(name_index, "отсортировано по ФИО");
    
    sort_by_phone();
    print_phonebook(phone_index, "отсортировано по телефону");
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

// Функция для реверса строки
void reverse_string(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int main() {
    char filename[] = "output.txt";
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char **lines = NULL;
    int line_count = 0;

    // Создаем файл и записываем в него произвольные строки
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    fprintf(file, "Первая строка\n");
    fprintf(file, "Вторая строка\n");
    fprintf(file, "Третья строка\n");
    fprintf(file, "Четвертая строка\n");

    fclose(file);

    // Открываем файл для чтения
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    // Читаем строки из файла и сохраняем их в динамический массив
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // Убираем символ новой строки
        line[strcspn(line, "\n")] = '\0';

        // Выделяем память для новой строки и копируем ее
        lines = realloc(lines, (line_count + 1) * sizeof(char *));
        lines[line_count] = malloc((strlen(line) + 1) * sizeof(char));
        strcpy(lines[line_count], line);

        line_count++;
    }

    fclose(file);

    // Открываем файл для записи (перезаписываем)
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    // Переписываем строки в обратном порядке
    for (int i = line_count - 1; i >= 0; i--) {
        reverse_string(lines[i]);
        fprintf(file, "%s\n", lines[i]);
        free(lines[i]); // Освобождаем память
    }

    free(lines); // Освобождаем массив указателей
    fclose(file);

    printf("Строки успешно переписаны в обратном порядке.\n");

    return EXIT_SUCCESS;
}
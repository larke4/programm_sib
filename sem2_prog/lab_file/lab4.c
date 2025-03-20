#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define MAX_LINE_LENGTH 1000

// Функция для реверса строки широких символов
void reverse_wstring(wchar_t *str) {
    int length = wcslen(str);
    for (int i = 0; i < length / 2; i++) {
        wchar_t temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

// Функция для обработки файла с заранее заданным текстом
void process_existing_file(const wchar_t *input_filename, const wchar_t *output_filename) {
    FILE *input_file = fopen("existing_input.txt", "r");
    if (input_file == NULL) {
        fwprintf(stderr, L"Ошибка открытия файла '%ls' для чтения.\n", input_filename);
        return;
    }

    FILE *output_file = fopen("existing_output.txt", "w");
    if (output_file == NULL) {
        fwprintf(stderr, L"Ошибка открытия файла '%ls' для записи.\n", output_filename);
        fclose(input_file);
        return;
    }

    wchar_t line[MAX_LINE_LENGTH];
    while (fgetws(line, MAX_LINE_LENGTH, input_file) != NULL) {
        // Убираем символ новой строки
        line[wcslen(line) - 1] = L'\0';

        // Реверсируем строку
        reverse_wstring(line);

        // Записываем реверсированную строку в файл
        fputws(line, output_file);
        fputws(L"\n", output_file);
    }

    fclose(input_file);
    fclose(output_file);

    wprintf(L"Файл '%ls' успешно обработан. Реверсированные строки записаны в '%ls'.\n", input_filename, output_filename);
}

// Функция для ввода строк через консоль до стоп-символа
void input_strings_until_stop(const wchar_t *output_filename) {
    FILE *output_file = fopen("console_output.txt", "w");
    if (output_file == NULL) {
        fwprintf(stderr, L"Ошибка открытия файла '%ls' для записи.\n", output_filename);
        return;
    }

    wprintf(L"Введите строки (для завершения введите 'STOP'):\n");

    wchar_t line[MAX_LINE_LENGTH];
    while (1) {
        if (fgetws(line, MAX_LINE_LENGTH, stdin) == NULL) {
            fwprintf(stderr, L"Ошибка ввода строки.\n");
            break;
        }

        // Убираем символ новой строки
        line[wcslen(line) - 1] = L'\0';

        // Проверяем на стоп-символ
        if (wcscmp(line, L"STOP") == 0) {
            break;
        }

        // Реверсируем строку
        reverse_wstring(line);

        // Записываем реверсированную строку в файл
        fputws(line, output_file);
        fputws(L"\n", output_file);
    }

    fclose(output_file);

    wprintf(L"Строки успешно записаны в файл '%ls'.\n", output_filename);
}

int main() {
    // Устанавливаем локаль для корректной работы с UTF-8
    setlocale(LC_ALL, "Russian_Russia.65001");

    // Обработка файла с заранее заданным текстом
    process_existing_file(L"existing_input.txt", L"existing_output.txt");

    // Ввод строк через консоль до стоп-символа
    input_strings_until_stop(L"console_output.txt");

    return EXIT_SUCCESS;
}
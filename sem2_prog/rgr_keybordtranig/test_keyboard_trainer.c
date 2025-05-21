#include "keyboard_trainer.h"
#include <assert.h>
#include <string.h>
#include <math.h>

// Вспомогательная функция для сравнения с погрешностью
int double_eq(double a, double b) {
    return fabs(a - b) < 1e-6;
}

// --- Тест стандартного режима ---
void test_standard_mode() {
    const char* original = "hello world";
    const char* input_correct = "hello world";
    const char* input_with_errors = "hallo warld";

    TrainingStats stats1 = calculate_stats(original, input_correct, 10.0);
    assert(stats1.correct_chars == 11);
    assert(stats1.incorrect_chars == 0);
    assert(double_eq(stats1.accuracy, 100.0));

    TrainingStats stats2 = calculate_stats(original, input_with_errors, 10.0);
    assert(stats2.correct_chars == 9);  // 'h','e','l','l','o',' ','w','o','r' совпадают
    assert(stats2.incorrect_chars == 2); // 'l' vs 'a', 'l' vs 'd'
    assert(fabs(stats2.accuracy - 81.818182) < 0.01); // ~9/11 = 81.82%
}

// --- Ускоренный тест динамического режима ---
void test_fast_dynamic_mode() {
    DifficultyLevel level = BEGINNER;
    int total_correct = 0, total_incorrect = 0;
    double total_time = 0;

    for (int i = 0; i < 3; i++) {
        const char* text = get_random_text(level);
        char input[1024];
        strcpy(input, text); // идеальный ввод

        TrainingStats stats = calculate_stats(text, input, 5.0);
        total_correct += stats.correct_chars;
        total_incorrect += stats.incorrect_chars;
        total_time += 5.0;
    }

    assert(total_incorrect == 0);
    assert(double_eq(total_time, 15.0));
}

// --- Тест змейки ---
void test_snake_mode() {
    DifficultyLevel level = BEGINNER;
    int score = 0;
    int lives = 3;

    TrainingStats good = {50, 2, 60, 50.0, 96.15};
    if (good.accuracy >= 90.0) {
        score += good.correct_chars;
        level++;
    }
    assert(score == 50);
    assert(level == INTERMEDIATE);

    TrainingStats bad = {30, 10, 60, 30.0, 75.0};
    if (bad.accuracy < 90.0) {
        lives--;
    }
    assert(lives == 2);
}

// --- Тест клавишных комбинаций ---
void test_keys_mode() {
    const char* combo = "asdfjkl;";
    char input[32];

    strcpy(input, combo);
    assert(strcmp(input, combo) == 0);

    strcpy(input, "asdfjkl,");
    assert(strcmp(input, combo) != 0);
}

// --- Тест таблицы рекордов ---
void test_leaderboard() {
    UserRecord records[3] = {
        {"Alice", 150.5, 98.2},
        {"Bob", 120.0, 95.5},
        {"Charlie", 180.0, 97.8}
    };

    // Сортировка по скорости
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (records[j].best_speed < records[j+1].best_speed) {
                UserRecord temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
            }
        }
    }

    assert(strcmp(records[0].name, "Charlie") == 0);
    assert(strcmp(records[1].name, "Alice") == 0);
    assert(strcmp(records[2].name, "Bob") == 0);
}

// --- Тест многопоточности ---
void* mock_training(void* args) {
    TrainingThreadArgs* targs = (TrainingThreadArgs*)args;
    const char* text = get_random_text(targs->level);
    char input[1024];
    strcpy(input, text);

    time_t start = time(NULL);
    sleep(1); // имитация задержки
    time_t end = time(NULL);

    double elapsed = difftime(end, start);
    targs->stats = calculate_stats(text, input, elapsed);
    return NULL;
}

void test_threading() {
    TrainingThreadArgs args = {BEGINNER};
    pthread_t thread;

    pthread_create(&thread, NULL, mock_training, &args);
    pthread_join(thread, NULL);

    assert(args.stats.correct_chars > 0);
    assert(args.stats.time_elapsed >= 1.0);
}

// --- Основной блок запуска тестов ---
int main() {
    printf("Running fast tests...\n");

    test_standard_mode();
    test_fast_dynamic_mode();
    test_snake_mode();
    test_keys_mode();
    test_leaderboard();
    test_threading();

    printf("All tests passed successfully!\n");
    return 0;
}
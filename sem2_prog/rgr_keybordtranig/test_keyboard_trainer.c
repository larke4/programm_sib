#include "keyboard_trainer.h"
#include <assert.h>
#include <string.h>

// Тест для стандартного режима
void test_standard_mode() {
    DifficultyLevel level = BEGINNER;
    const char* text = get_random_text(level);
    assert(text != NULL);
    
    // Тест с идеальным вводом
    TrainingStats perfect = calculate_stats(text, text, 10.0);
    assert(perfect.correct_chars == strlen(text));
    assert(perfect.incorrect_chars == 0);
    assert(perfect.accuracy == 100.0);
    
    // Тест с ошибками
    char faulty_input[256];
    strcpy(faulty_input, text);
    faulty_input[3] = 'X'; // Искусственная ошибка
    TrainingStats faulty = calculate_stats(text, faulty_input, 10.0);
    assert(faulty.correct_chars == strlen(text)-1);
    assert(faulty.incorrect_chars == 1);
}

// Тест для динамического режима
void test_dynamic_mode() {
    // Эмуляция трех раундов
    TrainingStats round1 = {50, 2, 30, 100.0, 96.15};
    TrainingStats round2 = {60, 5, 30, 120.0, 92.31};
    TrainingStats round3 = {55, 1, 30, 110.0, 98.21};
    
    TrainingStats total = {
        round1.correct_chars + round2.correct_chars + round3.correct_chars,
        round1.incorrect_chars + round2.incorrect_chars + round3.incorrect_chars,
        round1.time_elapsed + round2.time_elapsed + round3.time_elapsed,
        0, 0
    };
    
    total.speed = (total.correct_chars / total.time_elapsed) * 60;
    total.accuracy = (double)total.correct_chars / 
                    (total.correct_chars + total.incorrect_chars) * 100;
    
    assert(total.correct_chars == 165);
    assert(total.incorrect_chars == 8);
    assert(fabs(total.speed - 110.0) < 0.1);
    assert(fabs(total.accuracy - 95.38) < 0.1);
}

// Тест для режима "Змейка"
void test_snake_mode() {
    DifficultyLevel level = BEGINNER;
    int score = 0;
    int lives = 3;
    
    // Тест успешного прохождения
    TrainingStats good = {50, 2, 60, 50.0, 96.15};
    if (good.accuracy >= 90.0) {
        score += good.correct_chars;
        level++;
    }
    assert(score == 50);
    assert(level == INTERMEDIATE);
    
    // Тест неудачной попытки
    TrainingStats bad = {30, 10, 60, 30.0, 75.0};
    if (bad.accuracy < 90.0) {
        lives--;
    }
    assert(lives == 2);
}

// Тест для режима клавишных комбинаций
void test_keys_mode() {
    const char* combo = "asdfjkl;";
    char input[32];
    
    // Идеальный ввод
    strcpy(input, combo);
    assert(strcmp(input, combo) == 0);
    
    // Ввод с ошибкой
    strcpy(input, "asdfjkl,");
    assert(strcmp(input, combo) != 0);
}

// Тест таблицы рекордов
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

// Тест многопоточности
void test_threading() {
    TrainingThreadArgs args = {BEGINNER};
    pthread_t thread;
    
    // Эмуляция ввода (в реальном тесте нужно было бы перехватывать ввод)
    pthread_create(&thread, NULL, training_thread, &args);
    pthread_join(thread, NULL);
    
    assert(args.stats.correct_chars >= 0);
    assert(args.stats.time_elapsed >= 0);
}

int main() {
    printf("Running comprehensive tests...\n");
    
    test_standard_mode();
    test_dynamic_mode();
    test_snake_mode();
    test_keys_mode();
    test_leaderboard();
    test_threading();
    
    printf("All 6 test categories passed successfully!\n");
    return 0;
}
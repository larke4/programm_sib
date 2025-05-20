#ifndef KEYBOARD_TRAINER_H
#define KEYBOARD_TRAINER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

typedef enum {
    BEGINNER,
    INTERMEDIATE,
    ADVANCED
} DifficultyLevel;

typedef enum {
    STANDARD_MODE,
    DYNAMIC_MODE,
    SNAKE_MODE,
    KEYS_MODE,
    COMPETITION_MODE
} TrainingMode;

typedef struct {
    int correct_chars;
    int incorrect_chars;
    double time_elapsed;
    double speed;
    double accuracy;
} TrainingStats;

typedef struct {
    char name[50];
    double best_speed;
    double best_accuracy;
} UserRecord;

typedef struct {
    DifficultyLevel level;
    TrainingStats stats;
} TrainingThreadArgs;

// Основные функции
void print_main_menu();
int get_menu_choice();
DifficultyLevel select_difficulty();
void start_selected_mode(int choice);

// Режимы тренировки
void standard_mode_training(DifficultyLevel level);
void dynamic_mode_training(DifficultyLevel level);
void snake_mode_training();
void keys_mode_training();
void competition_mode();

// Вспомогательные функции
const char* get_random_text(DifficultyLevel level);
TrainingStats calculate_stats(const char* original, const char* input, double time_elapsed);
void print_stats(TrainingStats stats);
void save_stats(TrainingStats stats);
void show_statistics();
void save_snake_score(int score);
void save_competition_result(const char* name, double speed, double accuracy);
void show_leaderboard();

// Многопоточность
void* training_thread(void* args);

#endif
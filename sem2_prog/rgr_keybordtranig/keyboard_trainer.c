#include "keyboard_trainer.h"

// Тексты для тренировки
const char* beginner_texts[] = {
    "hello world programming",
    "the quick brown fox jumps",
    "learn to type faster",
    "keyboard trainer application",
    "c programming is fun",
    "practice makes perfect",
    "computer science basics",
    "algorithm and data structures",
    "github repository commit",
    "linux terminal commands"
};

const char* intermediate_texts[] = {
    "The quick brown fox jumps over the lazy dog. This sentence contains all English letters.",
    "Programming is the process of creating instructions that enable a computer to perform tasks.",
    "Memory management in C requires careful allocation and deallocation to prevent leaks.",
    "Debugging involves identifying and removing errors from computer programs.",
    "Version control systems like Git help developers collaborate on projects efficiently.",
    "Regular expressions provide a powerful way to search and manipulate text patterns.",
    "Object-oriented programming focuses on data structures containing both data and functions.",
    "The Linux kernel is written mostly in C and forms the core of operating systems.",
    "Compilers translate high-level programming languages into machine code.",
    "Multithreading allows programs to execute multiple operations concurrently."
};

const char* advanced_texts[] = {
    "In computer science, a pointer is a programming language object that stores a memory address. Pointers are used to build complex data structures and manipulate memory directly.",
    "The C programming language, developed in 1972 by Dennis Ritchie at Bell Labs, revolutionized computing by providing low-level access to memory while maintaining portability.",
    "Modern cryptography relies on mathematical algorithms to secure communications, including public-key systems like RSA and elliptic-curve cryptography.",
    "Operating system kernels handle memory management, process scheduling, device I/O, and provide the fundamental interface between hardware and software components.",
    "The TCP/IP protocol suite forms the basis of internet communications, implementing reliable packet delivery, addressing, and routing across interconnected networks.",
    "Quantum computing leverages quantum-mechanical phenomena like superposition and entanglement to perform calculations exponentially faster than classical computers for certain problems.",
    "Distributed systems face unique challenges including network latency, partial failures, and consistency models like eventual consistency and strong consistency.",
    "Compiler optimization techniques include dead code elimination, loop unrolling, register allocation, and instruction scheduling to improve runtime performance.",
    "Functional programming paradigms emphasize immutable data and first-class functions, avoiding side effects and mutable state found in imperative programming.",
    "Computer architecture innovations like pipelining, speculative execution, and SIMD instructions have dramatically increased processor performance over decades."
};
void print_main_menu() {
    printf("\n=== Keyboard Trainer ===\n");
    printf("1. Standard Training\n");
    printf("2. Dynamic Mode (changing text)\n");
    printf("3. Snake Mode (progressive difficulty)\n");
    printf("4. Keys Practice\n");
    printf("5. Competition Mode\n");
    printf("6. View Statistics\n");
    printf("7. View Leaderboard\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

int get_menu_choice() {
    int choice;
    scanf("%d", &choice);
    while(getchar() != '\n');
    return choice;
}

DifficultyLevel select_difficulty() {
    printf("\nSelect difficulty:\n");
    printf("1. Beginner\n");
    printf("2. Intermediate\n");
    printf("3. Advanced\n");
    printf("Choice: ");
    return (DifficultyLevel)(get_menu_choice() - 1);
}

const char* get_random_text(DifficultyLevel level) {
    int count;
    const char** texts;
    
    switch(level) {
        case BEGINNER:
            texts = beginner_texts;
            count = sizeof(beginner_texts)/sizeof(beginner_texts[0]);
            break;
        case INTERMEDIATE:
            texts = intermediate_texts;
            count = sizeof(intermediate_texts)/sizeof(intermediate_texts[0]);
            break;
        case ADVANCED:
            texts = advanced_texts;
            count = sizeof(advanced_texts)/sizeof(advanced_texts[0]);
            break;
        default:
            return beginner_texts[0];
    }
    return texts[rand() % count];
}

TrainingStats calculate_stats(const char* original, const char* input, double time_elapsed) {
    TrainingStats stats = {0};
    stats.time_elapsed = time_elapsed;
    
    int original_len = strlen(original);
    int input_len = strlen(input);
    int min_len = original_len < input_len ? original_len : input_len;
    
    for (int i = 0; i < min_len; i++) {
        if (original[i] == input[i]) {
            stats.correct_chars++;
        } else {
            stats.incorrect_chars++;
        }
    }
    
    if (original_len > input_len) {
        stats.incorrect_chars += original_len - input_len;
    } else if (input_len > original_len) {
        stats.incorrect_chars += input_len - original_len;
    }
    
    stats.speed = (stats.correct_chars / time_elapsed) * 60;
    stats.accuracy = (double)stats.correct_chars / (stats.correct_chars + stats.incorrect_chars) * 100;
    
    return stats;
}

void print_stats(TrainingStats stats) {
    printf("\n--- Training Results ---\n");
    printf("Correct characters: %d\n", stats.correct_chars);
    printf("Incorrect characters: %d\n", stats.incorrect_chars);
    printf("Time elapsed: %.2f seconds\n", stats.time_elapsed);
    printf("Typing speed: %.2f characters per minute\n", stats.speed);
    printf("Accuracy: %.2f%%\n", stats.accuracy);
}

void save_stats(TrainingStats stats) {
    FILE *file = fopen("stats.txt", "a");
    if (file) {
        fprintf(file, "%d,%d,%.2f,%.2f,%.2f\n", 
                stats.correct_chars, 
                stats.incorrect_chars, 
                stats.time_elapsed, 
                stats.speed, 
                stats.accuracy);
        fclose(file);
    }
}

void show_statistics() {
    FILE *file = fopen("stats.txt", "r");
    if (!file) {
        printf("No statistics available yet.\n");
        return;
    }
    
    printf("\n--- Training History ---\n");
    printf("Correct | Incorrect | Time (s) | Speed (cpm) | Accuracy\n");
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    
    fclose(file);
}

void* training_thread(void* args) {
    TrainingThreadArgs* targs = (TrainingThreadArgs*)args;
    const char* text = get_random_text(targs->level);
    
    time_t start_time = time(NULL);
    char input[1024];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    
    time_t end_time = time(NULL);
    double time_elapsed = difftime(end_time, start_time);
    
    targs->stats = calculate_stats(text, input, time_elapsed);
    return NULL;
}

void standard_mode_training(DifficultyLevel level) {
    const char* text = get_random_text(level);
    printf("\nType the following text:\n%s\n", text);
    
    time_t start_time = time(NULL);
    printf("Start typing (press Enter when finished):\n");
    
    char input[1024];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    
    time_t end_time = time(NULL);
    double time_elapsed = difftime(end_time, start_time);
    
    TrainingStats stats = calculate_stats(text, input, time_elapsed);
    print_stats(stats);
    save_stats(stats);
}

void dynamic_mode_training(DifficultyLevel level) {
    printf("\nDynamic Mode: Text will appear immediately after each input\n");
    printf("Type '/q' at any time to quit.\n");

    int total_correct = 0, total_incorrect = 0;
    double total_time = 0;
    int rounds = 0;

    // Время на раунд в зависимости от уровня
    int round_seconds;
    switch(level) {
        case BEGINNER:      round_seconds = 30; break;
        case INTERMEDIATE:  round_seconds = 25; break;
        case ADVANCED:      round_seconds = 20; break;
        default:            round_seconds = 30; break;
    }

    while (1) {
        const char* text = get_random_text(level);
        printf("\nNew text (%d seconds to complete):", round_seconds);
        printf("\n%s\n", text);

        time_t round_start = time(NULL);
        char input[1024];
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input.\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';  // Удалить символ новой строки

        // Проверка на выход
        if (strcmp(input, "/q") == 0) {
            printf("Exiting Dynamic Mode early.\n");
            break;
        }

        time_t round_end = time(NULL);
        double round_time = difftime(round_end, round_start);

        // Если время больше лимита, засчитываем как ошибку
        if (round_time > round_seconds) {
            printf("Time limit exceeded!\n");
        }

        TrainingStats stats = calculate_stats(text, input, round_time);
        print_stats(stats);

        total_correct += stats.correct_chars;
        total_incorrect += stats.incorrect_chars;
        total_time += round_time;
        rounds++;
    }

    if (rounds > 0) {
        TrainingStats final_stats = {
            total_correct,
            total_incorrect,
            total_time,
            (total_correct / total_time) * 60,
            (double)total_correct / (total_correct + total_incorrect) * 100
        };
        printf("\n--- Final Dynamic Mode Results ---\n");
        print_stats(final_stats);
        save_stats(final_stats);
    } else {
        printf("No rounds completed.\n");
    }
}

void snake_mode_training() {
    DifficultyLevel current_level = BEGINNER;
    int score = 0;
    int lives = 3;
    
    while (lives > 0) {
        const char* text = get_random_text(current_level);
        printf("\nLevel: %d | Score: %d | Lives: %d\n", current_level + 1, score, lives);
        printf("Text to type:\n%s\n", text);
        
        time_t start = time(NULL);
        char input[1024];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        time_t end = time(NULL);
        double elapsed = difftime(end, start);
        
        TrainingStats stats = calculate_stats(text, input, elapsed);
        print_stats(stats);
        
        if (stats.accuracy >= 90.0) {
            score += stats.correct_chars;
            if (current_level < ADVANCED) current_level++;
        } else {
            lives--;
        }
    }
    
    printf("\nGame over! Final score: %d\n", score);
    save_snake_score(score);
}

void save_snake_score(int score) {
    FILE* file = fopen("snake_scores.txt", "a");
    if (file) {
        fprintf(file, "%d\n", score);
        fclose(file);
    }
}

void keys_mode_training() {
    const char* key_sets[] = {
        "asdfjkl;", "qwertyuiop", "zxcvbnm,./", "1234567890", "!@#$%^&*()"
    };
    
    printf("\nKeys Training Mode\n");
    
    for (int i = 0; i < 5; i++) {
        printf("\nType this combination 3 times: %s\n", key_sets[i]);
        
        int correct_attempts = 0;
        while (correct_attempts < 3) {
            printf("Attempt %d: ", correct_attempts + 1);
            
            char input[50];
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            
            if (strcmp(input, key_sets[i]) == 0) {
                correct_attempts++;
                printf("Correct!\n");
            } else {
                printf("Incorrect. Try again.\n");
            }
        }
    }
}

void competition_mode() {
    printf("\nCompetition Mode\n");
    printf("Enter your name: ");
    
    char name[50];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("\nYou have 1 minute to type as much as possible!\n");
    printf("Press Enter to start...");
    getchar();
    
    time_t start = time(NULL);
    int total_chars = 0;
    int correct_chars = 0;
    const char* text = get_random_text(INTERMEDIATE);
    
    printf("\nText to type:\n%s\n", text);
    
    while (difftime(time(NULL), start) < 60) {
        char input[1024];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        int len = strlen(input);
        total_chars += len;
        
        for (int i = 0; i < len && i < strlen(text); i++) {
            if (input[i] == text[i]) correct_chars++;
        }
        
        text = get_random_text(INTERMEDIATE);
        printf("\nNew text:\n%s\n", text);
    }
    
    double accuracy = (double)correct_chars / total_chars * 100;
    double speed = correct_chars;
    
    printf("\nTime's up!\nCorrect characters: %d\nAccuracy: %.2f%%\n", correct_chars, accuracy);
    save_competition_result(name, speed, accuracy);
    show_leaderboard();
}

void save_competition_result(const char* name, double speed, double accuracy) {
    FILE* file = fopen("leaderboard.txt", "a");
    if (file) {
        fprintf(file, "%s,%.2f,%.2f\n", name, speed, accuracy);
        fclose(file);
    }
}

void show_leaderboard() {
    FILE* file = fopen("leaderboard.txt", "r");
    if (!file) {
        printf("No leaderboard records yet.\n");
        return;
    }
    
    UserRecord records[100];
    int count = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), file) && count < 100) {
        char* token = strtok(line, ",");
        strcpy(records[count].name, token);
        records[count].best_speed = atof(strtok(NULL, ","));
        records[count].best_accuracy = atof(strtok(NULL, "\n"));
        count++;
    }
    fclose(file);
    
    // Сортировка по скорости
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (records[j].best_speed < records[j+1].best_speed) {
                UserRecord temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
            }
        }
    }
    
    printf("\n--- LEADERBOARD (Top 10) ---\n");
    printf("Rank | Name           | Speed (cpm) | Accuracy\n");
    for (int i = 0; i < (count < 10 ? count : 10); i++) {
        printf("%2d   | %-14s | %9.2f   | %.2f%%\n", 
               i+1, records[i].name, records[i].best_speed, records[i].best_accuracy);
    }
}

void start_selected_mode(int choice) {
    DifficultyLevel level;
    switch (choice) {
        case 1: standard_mode_training(select_difficulty()); break;
        case 2: dynamic_mode_training(select_difficulty()); break;
        case 3: snake_mode_training(); break;
        case 4: keys_mode_training(); break;
        case 5: competition_mode(); break;
        case 6: show_statistics(); break;
        case 7: show_leaderboard(); break;
    }
}
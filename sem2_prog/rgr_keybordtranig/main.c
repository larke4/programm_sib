#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "keyboard_trainer.h"

int main() {
    srand(time(NULL));
    
    int choice;
    do {
        print_main_menu();
        choice = get_menu_choice();
        
        if (choice >= 1 && choice <= 7) {
            start_selected_mode(choice);
        } else if (choice != 8) {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
    
    printf("Exiting...\n");
    return 0;
}
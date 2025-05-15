#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 
 
#define NUM_BUCKETS 256 
 
typedef struct Node { 
    int data; 
    struct Node* next; 
} Node; 
 
int M_f = 0; 
 
Node* create_desc(int n) { 
    Node* head = NULL; 
    for (int i = n; i >= 1; i--) { 
        Node* new_node = (Node*)malloc(sizeof(Node)); 
        new_node->data = i; 
        new_node->next = head; 
        head = new_node; 
    } 
    return head; 
} 
 
Node* create_asc(int n) { 
    Node* head = NULL; 
    for (int i = 1; i <= n; i++) { 
        Node* new_node = (Node*)malloc(sizeof(Node)); 
        new_node->data = i; 
        new_node->next = head; 
        head = new_node; 
    } 
    return head; 
} 
 
Node* create_random(int n) { 
    Node* head = NULL; 
    srand(time(NULL)); 
    for (int i = 0; i < n; i++) { 
        int num = rand() % 1000 + 1; 
        Node* new_node = (Node*)malloc(sizeof(Node)); 
        new_node->data = num; 
        new_node->next = head; 
        head = new_node; 
    } 
    return head; 
} 
 
void delete_list(Node** head) { 
    if (!head || !*head) return; 
    Node* current = *head; 
    while (current) { 
        Node* temp = current; 
        current = current->next; 
        free(temp); 
    } 
    *head = NULL; 
} 
 
Node* digitalSort(Node* head, int reverse, int bits) { 
    Node* buckets[2][NUM_BUCKETS] = {0};  
 
    for (int bit = 0; bit < bits; bit++) { 
        Node* current = head; 
        while (current) { 
            int digit = (current->data >> bit) & 0x1;  
            Node* next = current->next; 
            current->next = buckets[reverse][digit]; 
            buckets[reverse][digit] = current; 
            current = next; 
        } 
 
        head = NULL; 
        Node** tail = &head; 
        for (int i = 0; i < NUM_BUCKETS; i++) { 
            int idx = reverse ? (NUM_BUCKETS - 1 - i) : i; 
            Node* bucket = buckets[reverse][idx]; 
            while (bucket) { 
                *tail = bucket; 
                tail = &(bucket->next); 
                bucket = bucket->next; 
                M_f++; 
            } 
            buckets[reverse][idx] = NULL;  
        } 
    } 
 
    return head; 
} 
 
int checksum(Node* head) { 
    int sum = 0; 
    Node* current = head; 
    while (current) { 
        sum += current->data; 
        current = current->next; 
    } 
    return sum; 
} 
 
int count_series(Node* head) { 
    if (!head) return 0; 
    int count = 1; 
    int prev = head->data; 
    Node* current = head->next; 
    while (current) { 
        if (current->data < prev) count++; 
        prev = current->data; 
        current = current->next; 
    } 
    return count; 
} 
 
void printHeader() { 
    printf("| %-5s | %-11s | %-7s | %-7s | %-7s |\n",  
           "N", "Теория (M)", "Убыв.", "Случ.", "Возр."); 
    printf("|-------|-------------|---------|---------|---------|\n"); 
} 
 
void printRow(int n, int theory, int desc, int rand, int asc) { 
    printf("| %-5d | %-11d | %-7d | %-7d | %-7d |\n",  
           n, theory, desc, rand, asc); 
} 
 
void testDigitalSortBits(int bits) { 
    int sizes[] = {100, 200, 300, 400, 500}; 
    const char* bitLabel = (bits == 16) ? "16-bit" : "32-bit"; 
    printf("\nТрудоемкость цифровой сортировки DigitalSort (%s)\n", bitLabel); 
    printHeader(); 
 
    for (int i = 0; i < 5; i++) { 
        int n = sizes[i]; 
        int theory = bits * n;  
        int results[3] = {0};  
 
        for (int t = 0; t < 3; t++) { 
            Node* list = NULL; 
            switch(t) { 
                case 0: list = create_desc(n); break; 
                case 1: list = create_random(n); break; 
                case 2: list = create_asc(n); break; 
            } 
 
            M_f = 0; 
            list = digitalSort(list, 0, bits);
            results[t] = M_f; 
            delete_list(&list); 
        } 
 
        printRow(n, theory, results[0], results[1], results[2]); 
    } 
} 
 
int main() { 
    testDigitalSortBits(32); // Тест для 32-битных чисел 
    testDigitalSortBits(16); // Тест для 16-битных чисел 
    return 0; 
}
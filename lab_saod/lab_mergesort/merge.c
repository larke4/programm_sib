#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int Data;
    struct Node* Next;
} Node;

typedef Node* pLE;

typedef struct {
    pLE Head;
    pLE Tail;
} Queue;

int Cf = 0; 
int Mf = 0; 

void PrintList(pLE Head) {
    while (Head) {
        printf("%d ", Head->Data);
        Head = Head->Next;
    }
    printf("\n");
}

long long Checksum(pLE Head) {
    long long sum = 0;
    while (Head) {
        sum += Head->Data;
        Head = Head->Next;
    }
    return sum;
}

int CountElements(pLE Head) {
    int count = 0;
    while (Head) {
        count++;
        Head = Head->Next;
    }
    return count;
}

int Runnumber(pLE Head) {
    if (!Head || !Head->Next) return 1;

    int count = 1;
    int prev = Head->Data; //храним знач 1 эл
    Head = Head->Next;

    while (Head) {
        if (Head->Data < prev) count++;
        prev = Head->Data;
        Head = Head->Next;
    }

    return count;
}

void FreeList(pLE* Head) {
    pLE tmp;
    while (*Head) {
        tmp = *Head; //зап тек узел
        *Head = (*Head)->Next;
        free(tmp);
    }
}

void addStack(pLE* Head, int value) {
    pLE newNode = (pLE)malloc(sizeof(Node));
    newNode->Data = value;
    newNode->Next = *Head;
    *Head = newNode;
    Mf++;
}

void addqueue(Queue* q, int value) {
    pLE newNode = (pLE)malloc(sizeof(Node)); 
    newNode->Data = value;
    newNode->Next = NULL;
    Mf++;

    if (q->Tail) { //если оч не пуста
        q->Tail->Next = newNode; //новый эл - становится хвост
        Mf++;
    }
    else {
        q->Head = newNode; //голова = новый
        Mf++;
    }

    q->Tail = newNode; //хвост = новый
    Mf++;
}

int QueueEmpty(Queue* q) { //проверка пустая ли очередь
    return q->Head == NULL;
}

void SplitList(pLE S, pLE* a, pLE* b, int* n) { //деление списка на 2 части
    *a = S; 
    if (!S) return; 
    *b = S->Next;
    pLE k = *a, p = *b;
    *n = 1; //счетчик

    while (p && p->Next) { //пока есть эл
        (*n)++;
        k->Next = p->Next; //переплетаем указатели
        Mf++;
        k = p; 
        Mf++;
        p = p->Next->Next; 
        Mf++;
    }
    k->Next = NULL; //разрыв списка
    Mf++;
}

void MergeSeries(pLE* a, int q, pLE* b, int r, Queue* c) { //слияние в 1 очередь
    while (q > 0 && r > 0) {
        Cf++;
        if ((*a)->Data <= (*b)->Data) { //выбираем меньш
            addqueue(c, (*a)->Data); //добавляем из а
            *a = (*a)->Next; //переходим в а
            Mf++;
            q--;
        } else {
            addqueue(c, (*b)->Data);
            *b = (*b)->Next;
            Mf++;
            r--;
        }
    }
    while (q-- > 0) {
        addqueue(c, (*a)->Data);
        *a = (*a)->Next;
        Mf++;
    }
    while (r-- > 0) {
        addqueue(c, (*b)->Data);
        *b = (*b)->Next;
        Mf++;
    }
}

void MergeSort(pLE* S, int n) {
    pLE a = NULL, b = NULL;
    SplitList(*S, &a, &b, &n);

    int p = 1;
    while (p < n) {
        Queue c[2] = {{NULL, NULL}, {NULL, NULL}};
        int i = 0, m = n;
        while (m > 0) {
            int q = (m >= p) ? p : m; m -= q;
            int r = (m >= p) ? p : m; m -= r;
            MergeSeries(&a, q, &b, r, &c[i]);   
            i = 1 - i;
        }
        a = c[0].Head;
        b = c[1].Head;
        p *= 2;
    }
    *S = a;
}

void FillList(pLE* head, int n, int mode) {
    for (int i = 0; i < n; i++) {
        int val;
        if (mode == 0) val = rand() % 100;
        else if (mode == 1) val = i + 1;
        else val = n - i;
        addStack(head, val);
    }
}
void TestSplit() {
    printf("\nТест расщепления списка (n >= 20)\n");
    pLE list = NULL;
    FillList(&list, 20, 0);
    printf("Исходный список (20 элементов):\n");
    PrintList(list);
    printf("Контрольная сумма: %lld\n", Checksum(list));
    
    pLE a = NULL, b = NULL;
    int count = 0;
    SplitList(list, &a, &b, &count);
    
    printf("\nПосле расщепления:\n");
    printf("Список A (%d элементов):\n", CountElements(a));
    PrintList(a);
    printf("Список B (%d элементов):\n", CountElements(b));
    PrintList(b);
    printf("Общее количество элементов: %d\n", count);
    
    FreeList(&a);
    FreeList(&b);
}



void TestMerge() {
    printf("\nТест слияния серий\n");
    
    //Создаем два списка с сериями
    pLE a = NULL, b = NULL;
    //Вручную создаем списки с известными сериями
    for (int i = 0; i < 10; i += 2) addStack(&a, 10 - i);
    for (int i = 1; i < 10; i += 2) addStack(&b, 10 - i);
    
    printf("До слияния:\n");
    printf("Список A (серии: %d):\n", Runnumber(a));
    PrintList(a);
    printf("Контрольная сумма A: %lld\n", Checksum(a));
    printf("Список B (серии: %d):\n", Runnumber(b));
    PrintList(b);
    printf("Контрольная сумма B: %lld\n", Checksum(b));
    
    Queue c = {NULL, NULL};
    Cf = Mf = 0;
    int q = CountElements(a), r = CountElements(b);
    MergeSeries(&a, q, &b, r, &c);
    
    printf("\nПосле слияния:\n");
    printf("Результат (серии: %d):\n", Runnumber(c.Head));
    PrintList(c.Head);
    printf("Контрольная сумма: %lld\n", Checksum(c.Head));

    FreeList(&c.Head);
}

void TestMergeSort() {
    printf("\nТест сортировки слиянием\n");
    pLE list = NULL;
    FillList(&list, 20, 0);
    printf("Исходный список (20 элементов):\n");
    PrintList(list);
    printf("Серий: %d, Контрольная сумма: %lld\n", Runnumber(list), Checksum(list));
    
    Cf = Mf = 0;
    int n = CountElements(list);
    MergeSort(&list, n);
    
    printf("\nПосле сортировки:\n");
    PrintList(list);
    printf("Серий: %d, Контрольная сумма: %lld\n", Runnumber(list), Checksum(list));
    
    FreeList(&list);
}

void RunExperiments() {
    printf("--------------------------------------------------------\n");
    printf("|                 Сравнение трудоёмкости               |\n");
    printf("--------------------------------------------------------\n");
    printf("|  N   | Теор. M+C | Уб. Mf+Cf | Случ. Mf+Cf | Возр. Mf+Cf |\n");
    printf("--------------------------------------------------------\n");

    

    for (int n = 100; n <= 500; n += 100) {
        int log2n = (int)ceil(log2(n));
        int C = n * log2n;       
        int M = n * log2n + n;   
        int theo = C + M;        
        printf("| %4d | %9d |", n, theo);
        
        for (int mode = 2; mode >= 0; mode--) {
            pLE list = NULL;
            FillList(&list, n, mode);
            Cf = Mf = 0;
            MergeSort(&list, n);
            printf(" %9d |", Cf + Mf);
            FreeList(&list);
        }
        printf("\n");
    }
    printf("--------------------------------------------------------\n");
}

int main() {
    srand(time(NULL));

    TestMergeSort();
    TestSplit();
    TestMerge();
    RunExperiments();

    return 0;
}
#include<stdio.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define STR_INDEX_ERR fprintf(stderr, "\a\nFATAL ERROR! INVALID INDEX!\n")
#define STR_MEM_ERR fprintf(stderr, "\a\nFATAL ERROR! ALLOCATION FAILED!\n")
#define STR_EMPTY_LIST_ERR fprintf(stderr, "\a\nFATAL ERROR! EMPTY LIST!\n")

#undef malloc
void* alloc(size_t size) {

    void* mem = malloc(size);
    if (!mem) {
        STR_MEM_ERR;
        exit(EXIT_FAILURE);
    }

    return mem;
}

typedef struct {

    char itemID[7];
    char name[100];
    float price;
    char allergens[100];

} Menu;

typedef struct Node {

    Menu item;
    struct Node* next;

} Node;

Node* __new__(Menu*);
void __del__(Node*);

Node* push(int, Node*, Node*);
Node* pop(int, Node*);

int len(Node*);
void __str__(Node*);









void test(void);

int main(void) {

    //test();

    return 0;
}












Node* __new__(Menu* item) {

    Node* node = (Node*)alloc(sizeof(Node));

    node->item = *item;
    node->next = NULL;

    return node;
}

void __del__(Node* head) {

    while (head) {

        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return;
}

int len(Node* head) {

    int size = 0;
    Node* temp = head;

    while (temp) {
        size++;
        temp = temp->next;
    }

    return size;
}

void __str__(Node* head) {

    if (!head) {
        STR_EMPTY_LIST_ERR;
        return;
    }

    Node* temp = head;

    for (int i = 0; i < len(head); i++) {

        printf("Item ID: %s, Name: %s, Price: %.2f, Allergens: %s\n", temp->item.itemID, temp->item.name, temp->item.price, temp->item.allergens);

        temp = temp->next;
    }

    return;
}

Node* push(int index, Node* head, Node* insert) {

    if (!index) {

        insert->next = head;
        return insert;
    }

    if (index >= len(head) || index < 0) {
        STR_INDEX_ERR;
        return head;
    }

    Node* temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;

    insert->next = temp->next;
    temp->next = insert;

    return head;  
}

Node* pop(int index, Node* head) {

    if (!head) {
        STR_EMPTY_LIST_ERR;
        return NULL;
    }

    if (index >= len(head) || index < 0) {
        STR_INDEX_ERR;
        return head;
    }

    if (!index) {

        Node* temp = head;
        head = head->next;

        free(temp);
        return head;
    }

    Node* temp = head;
    
    for (int i = 0; i < index - 1; i++)
        temp = temp->next;

    if (index == len(head) - 1) {

        free(temp->next);
        temp->next = NULL;

        return head;
    }

    Node* node_del = temp->next;
    temp->next = temp->next->next;
    free(node_del);

    return head;
}

void format(Node* list) {

    puts("---------------------------------");
    __str__(list);
    printf("LENGTH: %d\n", len(list));
}

void test(void) {

    Menu a = {"1", "a", 1, "none"}, b = {"2", "b", 2, "none"}, c = {"3", "c", 3, "none"};

    Node* list = NULL;

    list = push(0, list, __new__(&a));
    format(list);

    list = pop(0, list);
    format(list);

    list = pop(0, list);

    list = push(0, list, __new__(&a));
    format(list);

    list = push(0, list, __new__(&b));
    format(list);

    list = push(1, list, __new__(&c));
    format(list);

    list = push(1, list, __new__(&b));
    format(list);

    list = push(2, list, __new__(&a));
    format(list);

    list = push(3, list, __new__(&b));
    format(list);

    list = pop(0, list);
    format(list);

    list = pop(0, list);
    format(list);

    list = pop(1, list);
    format(list);

    list = pop(2, list);
    format(list);

    __del__(list);
    return;
}

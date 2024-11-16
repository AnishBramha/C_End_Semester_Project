#include<stdio.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include "file_handler.h"

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



NodeMenu* __newItem__(Menu*);
NodeTable* __new__Table(Table*);
void __delMenu__(NodeMenu*);
void __delTable__(NodeTable*);

NodeMenu* pushItem(int, NodeMenu*, NodeMenu*);
NodeMenu* popItem(int, NodeMenu*);
NodeTable* pushTable(int, NodeTable*, NodeTable*);
NodeTable* popTable(int, NodeTable*);

int lenMenu(NodeMenu*);
int lenTable(NodeTable*);
void __strMenu__(NodeMenu*);
void __strTable__(NodeTable*);










void testMenu(void); // use for testing purposes only
void testTable(void); // use for testing purposes only
void formatItem(NodeMenu*);
void formatTable(NodeTable*);

// int main(void) {

//     //testMenu();
//     //testTable();

//     return 0;
// }












NodeMenu* __newItem__(Menu* item) {

    NodeMenu* node = (NodeMenu*)alloc(sizeof(NodeMenu));

    node->item = *item;
    node->next = NULL;

    return node;
}

NodeTable* __newTable__(Table* table) {

    NodeTable* node = (NodeTable*)alloc(sizeof(NodeTable));

    node->table = *table;
    node->next = NULL;
}

void __delMenu__(NodeMenu* head) {

    while (head) {

        NodeMenu* temp = head;
        head = head->next;
        free(temp);
    }

    return;
}

int lenMenu(NodeMenu* head) {

    int size = 0;
    NodeMenu* temp = head;

    while (temp) {
        size++;
        temp = temp->next;
    }

    return size;
}

int lenTable(NodeTable* head) {

    int size = 0;
    NodeTable* temp = head;

    while (temp) {
        size++;
        temp = temp->next;
    }

    return size;
}

void __strMenu__(NodeMenu* head) {

    if (!head) {
        STR_EMPTY_LIST_ERR;
        return;
    }

    NodeMenu* temp = head;

    for (int i = 0; i < lenMenu(head); i++) {

        printf("Item ID: %s, Name: %s, Price: %.2f, Allergens: %s\n", temp->item.itemID, temp->item.name, temp->item.price, temp->item.allergens);

        temp = temp->next;
    }

    return;
}

void __strTable__(NodeTable* head) {

    if (!head) {
        STR_EMPTY_LIST_ERR;
        return;
    }

    NodeTable* temp = head;

    for (int i = 0; i < lenTable(head); i++) {

        printf("Number: %d, Capacity: %d, Availability: %d\n", temp->table.number, temp->table.capacity, temp->table.available);

        temp = temp->next;
    }

    return;
}

NodeMenu* pushItem(int index, NodeMenu* head, NodeMenu* insert) {

    if (!index) {

        insert->next = head;
        return insert;
    }

    if (index >= lenMenu(head) || index < 0) {
        STR_INDEX_ERR;
        return head;
    }

    NodeMenu* temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;

    insert->next = temp->next;
    temp->next = insert;

    return head;  
}

NodeTable* pushTable(int index, NodeTable* head, NodeTable* insert) {

    if (!index) {

        insert->next = head;
        return insert;
    }

    if (index >= lenTable(head) || index < 0) {
        STR_INDEX_ERR;
        return head;
    }

    NodeTable* temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;

    insert->next = temp->next;
    temp->next = insert;

    return head;  
}

NodeMenu* popItem(int index, NodeMenu* head) {

    if (!head) {
        STR_EMPTY_LIST_ERR;
        return NULL;
    }

    if (index >= lenMenu(head) || index < 0) {
        STR_INDEX_ERR;
        return head;
    }

    if (!index) {

        NodeMenu* temp = head;
        head = head->next;

        free(temp);
        return head;
    }

    NodeMenu* temp = head;
    
    for (int i = 0; i < index - 1; i++)
        temp = temp->next;

    if (index == lenMenu(head) - 1) {

        free(temp->next);
        temp->next = NULL;

        return head;
    }

    NodeMenu* node_del = temp->next;
    temp->next = temp->next->next;
    free(node_del);

    return head;
}

NodeTable* popTable(int index, NodeTable* head) {

    if (!head) {
        STR_EMPTY_LIST_ERR;
        return NULL;
    }

    if (index >= lenTable(head) || index < 0) {
        STR_INDEX_ERR;
        return head;
    }

    if (!index) {

        NodeTable* temp = head;
        head = head->next;

        free(temp);
        return head;
    }

    NodeTable* temp = head;
    
    for (int i = 0; i < index - 1; i++)
        temp = temp->next;

    if (index == lenTable(head) - 1) {

        free(temp->next);
        temp->next = NULL;

        return head;
    }

    NodeTable* node_del = temp->next;
    temp->next = temp->next->next;
    free(node_del);

    return head;
}

void formatItem(NodeMenu* list) {

    puts("---------------------------------");
    __strMenu__(list);
    printf("LENGTH: %d\n", lenMenu(list));
}

void formatTable(NodeTable* list) {

    puts("---------------------------------");
    __strTable__(list);
    printf("LENGTH: %d\n", lenTable(list));
}

void testMenu(void) {

    Menu a = {"1", "a", 1, "none"}, b = {"2", "b", 2, "none"}, c = {"3", "c", 3, "none"};

    NodeMenu* list = NULL;

    list = pushItem(0, list, __newItem__(&a));
    formatItem(list);

    list = popItem(0, list);
    formatItem(list);

    list = popItem(0, list);

    list = pushItem(0, list, __newItem__(&a));
    formatItem(list);

    list = pushItem(0, list, __newItem__(&b));
    formatItem(list);

    list = pushItem(1, list, __newItem__(&c));
    formatItem(list);

    list = pushItem(1, list, __newItem__(&b));
    formatItem(list);

    list = pushItem(2, list, __newItem__(&a));
    formatItem(list);

    list = pushItem(3, list, __newItem__(&b));
    formatItem(list);

    list = popItem(0, list);
    formatItem(list);

    list = popItem(0, list);
    formatItem(list);

    list = popItem(1, list);
    formatItem(list);

    list = popItem(2, list);
    formatItem(list);

    __delMenu__(list);
    return;
}

void testTable(void) {

    Table a = {1,2,3}, b = {4,5,6}, c = {7,8,9};

    NodeTable* list = NULL;

    list = pushTable(0, list, __newTable__(&a));
    formatTable(list);
    writeTable(list);

    list = pushTable(0, list, __newTable__(&b));
    formatTable(list);
    writeTable(list);



    return;
}

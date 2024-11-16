#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define VAR_DECLS

#include<stdio.h>
#include<stddef.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define STR_INDEX_ERR fprintf(stderr, "\a\nFATAL ERROR! INVALID INDEX!\n")
#define STR_MEM_ERR fprintf(stderr, "\a\nFATAL ERROR! ALLOCATION FAILED!\n")
#define STR_EMPTY_LIST_ERR fprintf(stderr, "\a\nFATAL ERROR! EMPTY LIST!\n")

#undef malloc

void* alloc(size_t size);

typedef struct {

    char itemID[7];
    char name[100];
    float price;
    char allergens[100];

} Menu;

typedef struct {

    int number;
    int capacity;
    int available;
 
} Table;

typedef struct NodeMenu {

    Menu item;
    struct NodeMenu* next;

} NodeMenu;

typedef struct NodeTable {

    Table table;
    struct NodeTable* next;

} NodeTable;

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

#endif

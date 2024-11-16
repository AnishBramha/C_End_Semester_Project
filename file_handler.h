#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include "linked_list.h"

int addMenuItem(char name[],float price,char allergens[],int type, int spice, int veg_nonveg );
void printMenu();
void writeTable(NodeTable* head);

#endif

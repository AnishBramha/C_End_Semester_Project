#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "linked_list.h"

#undef malloc
void* alloc(size_t size);

#undef fopen
FILE* open(const char* fileName, const char* mode);

Menu* loadMenu(void);
void updateMenu(Menu* menu);
// menu.csv format -> 

Tables* loadTables(void);
void updateTables(Tables*);
// tables.csv format -> 

CurrentOrders* loadCurrentOrders(void);
void updateCurrentOrders(CurrentOrders* currentOrders);
// current.csv format -> 

OrderHistory* loadOrderHistory(void);
void updateOrderHistory(OrderHistory* orderHistory);
// history.csv format -> 

void logAction(const char* fileName, const char* functionCalled);
// actions.log format -> 

#endif

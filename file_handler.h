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
// menu.csv format -> Item_ID,Name,Price,Allergens(separated by spaces)

Tables* loadTables(void);
void updateTables(Tables*);
// tables.csv format -> Table_No,Capacity,Available

CurrentOrders* loadCurrentOrders(void);
void updateCurrentOrders(CurrentOrders* currentOrders);
// current.csv format -> orderID,name,phone,people,tableNo,itemIDs,OrderTime(HH:MM)(24-hr format),OrderDate(DD:MM:YY),amount

OrderHistory* loadOrderHistory(void);
void updateOrderHistory(OrderHistory* orderHistory);
// history.csv format -> orderID,name,phone,people,tableNo,itemIDs,OrderTime(HH:MM)(24-hr format),OrderDate(DD:MM:YY),amount

void logAction(const char* fileName, const char* functionCalled);
// actions.log format -> <filename.extension> -> <fucntion called> @ Time(HH:MM)(24-hr format) & Date(DD:MM:YY)

#endif

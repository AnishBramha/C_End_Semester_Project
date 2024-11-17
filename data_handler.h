#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "linked_list.h"

Menu* searchItemName(char* name, Menu* menu); // returns pointer to Menu struct with item details
Menu* searchVegEggNon(int code, Menu* menu);                // these three functions return pointer to head of 
Menu* searchItemPrice(float min, float max, Menu* menu);    // a new linked list, which is made after
Menu* searchAllergens(char* allergen, Menu* menu);          // filtering as per the given parameter

float totalRevenue(char* startDate, char* endDate, OrderHistory* orderHistory);
float averageRevenuePerDay(OrderHistory* orderHistory);
float averageRevenuePerWeek(OrderHistory* orderHistory);
float averageRevenueInLast30Days(OrderHistory* orderHistory);

#endif

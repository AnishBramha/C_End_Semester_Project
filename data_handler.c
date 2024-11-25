#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "linked_list.h"
#include "data_handler.h"

int compdate(char* d1,char* d2);  //compares two dates and returns 0 if d1==d2, -1 if d1<d2 and 1 if d1>d2 when d1 and d2 are in format DD:MM:YY
int diffdate(char* d1,char* d2); //compares two dates and return the number of days between d1 and d2 when d1 and d2 are in the format DD:MM:YY, only works when d2>d1

Menu* searchItemNames(char* name, Menu* menu){
  struct Menu* outlist = NULL;
  struct Menu* iter = menu;
  struct Item item;
  while(iter != NULL)
  {
    item = iter->item;
    char* check = strstr(item.name, name);
    if(check != NULL)
    {
      struct Menu* newlink = newItem(&item);
      outlist = addItem(newlink,outlist);
    }
    iter = iter->next;
  }
  return outlist;
}

Menu* searchVegEggNon(int code, Menu* menu){
  struct Menu* outlist = NULL;
  struct Menu* iter = menu;
  struct Item item;
  while(iter != NULL)
  {
    item = iter->item;
    int veg=(item.itemID/10000)%10;
    if(veg == code)
    {
      struct Menu* newlink = newItem(&item);
      outlist = addItem(newlink,outlist);
    }
    iter = iter->next;
  }
  return outlist;
}

Menu* searchCourse(int code, Menu* menu){
  struct Menu* outlist = NULL;
  struct Menu* iter = menu;
  struct Item item;
  while(iter != NULL)
  {
    item = iter->item;
    int course=(item.itemID/1000000)%10;
    if(course == code)
    {
      struct Menu* newlink = newItem(&item);
      outlist = addItem(newlink,outlist);
    }
    iter = iter->next;
  }
  return outlist;
}

Menu* searchItemPrice(float min, float max, Menu* menu){
  struct Menu* outlist = NULL;
  struct Menu* iter = menu;
  struct Item item;
  while(iter != NULL)
  {
    item = iter->item;
    float price = item.price;
    if(min<=price && max>=price)
    {
      struct Menu* newlink = newItem(&item);
      outlist = addItem(newlink,outlist);
    }
    iter = iter->next;
  }
  return outlist;
}


Menu* searchAllergens(char* allergen, Menu* menu){
  struct Menu* outlist = NULL;
  struct Menu* iter = menu;
  struct Item item;
  while(iter != NULL)
  {
    item = iter->item;
    char* flag = strstr(item.allergens,allergen);
    if(flag == NULL)
    {
      struct Menu* newlink = newItem(&item);
      outlist = addItem(newlink,outlist);
    }
    iter = iter->next;
  }
  return outlist;
}


float totalRevenue(char* startDate, char* endDate, OrderHistory* orderHistory, int* totalOrders){
  float rev = 0;
  *totalOrders = 0;
  struct OrderHistory* iter = orderHistory;
  struct Order order;
  if(strcmp(startDate,"")==0){
    startDate = "00:00:00";
  }
  if(strcmp(endDate,"")==0){
    endDate = "99:99:99";
  }


  while(iter != NULL)
  {
    order = iter->order;
    if(compdate(startDate,order.orderDate)==1||compdate(startDate,order.orderDate)==0){
      if(compdate(endDate,order.orderDate)==-1||compdate(endDate,order.orderDate)==0){
        rev += order.amount;
        (*totalOrders)++;
    }}
    iter = iter->next;
  }
  return rev;
}

float averageRevenuePerDay(OrderHistory* orderHistory, int* totalOrders){
  char currentdate[9] = "";
  strcpy(currentdate, getDate());
  char startdate[9] = "";
  if(orderHistory==NULL)
  {
    return 0;
  }
  struct Order order;
  order = orderHistory->order;
  strcpy(startdate, orderHistory->order.orderDate);
  int totdays = diffdate(startdate,currentdate) +1;
  float rev = totalRevenue(startdate,currentdate,orderHistory,totalOrders);
  rev = rev/totdays;
  return rev;
}

float averageRevenueInLast30Days(OrderHistory* orderHistory, int* totalOrders ){
  float rev = 0;
  char currentdate[9] = "";
  strcpy(currentdate, getDate());
  *totalOrders = 0;
  struct OrderHistory* iter = orderHistory;
  struct Order order;
  
  while(iter != NULL)
  {
    order = iter->order;
    int daydiff = diffdate(order.orderDate,currentdate);
    if(daydiff<30 && daydiff>=0){
     rev += order.amount;
     (*totalOrders)++;
    }
    iter = iter->next;
  }
  return rev/30;
}


void past30DaysData(OrderHistory* orderHistory, int data[30]){
  char currentdate[9]= "";
  data = {0}
  strcpy(currentdate, getDate());
  struct OrderHistory* iter = orderHistory;
  struct Order order;
  
  while(iter != NULL)
  {
    order = iter->order;
    int daydiff = diffdate(order.orderDate,currentdate);
    int i = 29 - daydiff;
    if(daydiff<30 && daydiff>=0){
     data[i] += order.amount;
    }
    iter = iter->next;
  }
}

int compdate(char* d1,char* d2){
  int flag = -2;
  if((int)d1[6]>(int)d2[6])
  {
    flag = -1;
  }
  else if((int)d1[7]>(int)d2[7])
  {
    flag = -1;
  }
  else if((int)d1[3]>(int)d2[3])
  {
    flag = -1;
  }
  else if((int)d1[4]>(int)d2[4])
  {
    flag = -1;
  }
  else if((int)d1[0]>(int)d2[0])
  {
    flag = -1;
  }
  else if((int)d1[1]>(int)d2[1])
  {
    flag = -1;
  }
  else if(strcmp(d1,d2)==0)
  {
    flag = 0;
  }
  else
  {
    flag = 1;
  }   
  return flag;
}

int diffdate(char *d1,char *d2) {
    struct tm tm1 = {0}, tm2 = {0};
    time_t time1, time2;
    
    sscanf(d1, "%d:%d:%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
    sscanf(d2, "%d:%d:%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);
    
    tm1.tm_mon -= 1;  
    tm2.tm_mon -= 1;
    tm1.tm_year += 100;  
    tm2.tm_year += 100;

    time1 = mktime(&tm1);
    time2 = mktime(&tm2);

    double difference = difftime(time2, time1) / (60 * 60 * 24);
    
    return (int)difference;
}


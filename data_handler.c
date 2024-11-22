
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "data_handler.h"

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



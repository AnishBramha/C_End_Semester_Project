#ifndef UI_H
#define UI_H

void ClearScreen();

#include "file_handler.h"
#include "linked_list.h"
#include "customer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>

// Constants for menu layout
#define MAX_ITEM_NAME_WIDTH  21
#define MAX_ITEM_NO_WIDTH     8
#define MAX_SPICE_WIDTH      10
#define MAX_TYPE_WIDTH        11
#define MAX_ALLERGEN_WIDTH   15
#define MAX_PRICE_WIDTH       7 

//Constants for passing heads of linked lists. 
#define HEADS struct Menu *menuHead, struct Tables *tablesHead, struct CurrentOrders *currentOrdersHead,struct OrderHistory *orderHistoryHead
#define HEADSFORHFILE struct Menu*, struct Tables *, struct CurrentOrders *,struct OrderHistory *
#define PASSHEADS menuHead,tablesHead,currentOrdersHead,orderHistoryHead


// Constants for Graph
#define DAYS 30
#define HEIGHT 25

// Terminal color codes
#define BLUE "\033[96m"
#define RED "\033[91m"
#define YELLOW "\033[33m"
#define BLINKING_YELLOW "\033[93m"
#define GREEN "\033[92m"
#define RESET "\033[0m"

// Function Prototypes
void logo(void);
void StartupPage(HEADSFORHFILE);

void GenerateBill(HEADS, long long orderID,int persons);
void OsSelectionPage(HEADSFORHFILE);
void LoginPage(HEADSFORHFILE);
void CustomerDetailsPage(int flag,HEADSFORHFILE);
void ManagerLoginPage(int flag,HEADSFORHFILE);
void orderDishesPage(HEADS,long long OID,int persons);
void Customerloggedinpage(HEADSFORHFILE,long long OID,int persons);
void ReserveTablePage(HEADS,long long OID,int persons);
void ManagerLoggedinpage(HEADSFORHFILE);
void menuLogo(void);
void menuHeader(void);
void menuFooter(void);
void menuRow(const char *item_name, const char *item_no, const char *spice, const char *type, const char *allergens, const char *price,int veg);
int get_wrapped_lines(const char *text, int max_width);
void print_wrapped_text(const char *text, int max_width, int line);

#endif

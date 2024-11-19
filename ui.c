#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>
#include "ui.h"
#include "file_handler.h"

int OS=1;

void ClearScreen(){
    if (OS==1) system("cls");
    if(OS==2) system("clear");
}


// #define MAX_ITEM_NAME_WIDTH  21
// #define MAX_ITEM_NO_WIDTH    8
// #define MAX_SPICE_WIDTH      10
// #define MAX_TYPE_WIDTH       11
// #define MAX_ALLERGEN_WIDTH   15
// #define MAX_PRICE_WIDTH      7

// #define DAYS 30
// #define HEIGHT 25

// void LoginPage();

// #define BLUE "\033[96m"
// #define RED "\033[91m"
// #define YELLOW "\033[33m"
// #define BLINKING_YELLOW "\033[93m"
// #define RESET "\033[0m"





void logo(void){
    printf("   ____     ____            _   _             \n");
    printf("  / ___|   / ___|  ___  ___| |_(_) ___  _ __  \n");
    printf(" | |   ____\\___ \\ / _ \\/ __| __| |/ _ \\| '_ \\ \n");
    printf(" | |__|_____|__) |  __/ (__| |_| | (_) | | | | \n");
    printf("  \\____|   |____/ \\___|\\___|\\__|_|\\___/|_| |_| \n\n");
}

// FOR MENU
// =============================================================================================================================================

int get_wrapped_lines(const char *text, int max_width) {
    int length = strlen(text);
    return (length + max_width - 1) / max_width;  // Calculate needed lines
}

void print_wrapped_text(const char *text, int max_width, int line) {
    int length = strlen(text);
    int start = line * max_width;
    if (start < length) {
        int width;
        if (length - start < max_width) {
            width = length - start;
        } 
        else {
            width = max_width;
        }
        printf("%-*.*s", max_width, width, text + start);

    } 
    else {
        printf("%-*s", max_width, " ");
    }
}

void menuRow(const char *item_name, const char *item_no, const char *spice, const char *type, const char *allergens, const char *price,int veg) {
    int max_lines = 0;
    max_lines = get_wrapped_lines(item_name, MAX_ITEM_NAME_WIDTH);
    if (get_wrapped_lines(item_no, MAX_ITEM_NO_WIDTH) > max_lines) max_lines = get_wrapped_lines(item_no, MAX_ITEM_NO_WIDTH);
    if (get_wrapped_lines(spice, MAX_SPICE_WIDTH) > max_lines) max_lines = get_wrapped_lines(spice, MAX_SPICE_WIDTH);
    if (get_wrapped_lines(type, MAX_TYPE_WIDTH) > max_lines) max_lines = get_wrapped_lines(type, MAX_TYPE_WIDTH);
    if (get_wrapped_lines(allergens, MAX_ALLERGEN_WIDTH) > max_lines) max_lines = get_wrapped_lines(allergens, MAX_ALLERGEN_WIDTH);
    if (get_wrapped_lines(price, MAX_PRICE_WIDTH) > max_lines) max_lines = get_wrapped_lines(price, MAX_PRICE_WIDTH);
    
    for (int line = 0; line < max_lines; line++) {
        if(veg==0)
        printf("%s| \033[92m",BLUE);
        if(veg==1)
        printf("%s| \033[93m",BLUE);
        if(veg==2)
        printf("%s| %s",BLUE,RED);
        
        print_wrapped_text(item_name, MAX_ITEM_NAME_WIDTH, line);
        printf("%s | %s",BLUE,RESET);
        print_wrapped_text(item_no, MAX_ITEM_NO_WIDTH, line);
        printf("%s | %s",BLUE,RESET);
        print_wrapped_text(spice, MAX_SPICE_WIDTH, line);
        printf("%s | %s",BLUE,RESET);
        print_wrapped_text(type, MAX_TYPE_WIDTH, line);
        printf("%s | %s",BLUE,RESET);
        print_wrapped_text(allergens, MAX_ALLERGEN_WIDTH, line);
        printf("%s | %s",BLUE,RESET);
        print_wrapped_text(price, MAX_PRICE_WIDTH, line);
        printf("%s |\n%s",BLUE,RESET);
    }
}

void menuFooter(){
    printf("%s+-----------------------+----------+------------+-------------+-----------------+---------+\n%s",BLUE,RESET);
}

void menuLogo(){
    printf("%s __  __  ______  _   _  _    _ \n",BLINKING_YELLOW);
    printf("|  \\/  ||  ____|| \\ | || |  | |\n");
    printf("| \\  / || |__   |  \\| || |  | |\n");
    printf("| |\\/| ||  __|  | . ` || |  | |\n");
    printf("| |  | || |____ | |\\  || |__| |\n");
    printf("|_|  |_||______||_| \\_| \\____/ \n%s",RESET);
}

void menuHeader(){
 
    printf("%s+-----------------------+----------+------------+-------------+-----------------+---------+\n",BLUE);
    printf("|       Item Name       |  Item No |   Spice    |     Type    |   Allergen(s)   | Price   |\n");
    printf("+-----------------------+----------+------------+-------------+-----------------+---------+\n%s",RESET);
          
}

// ============================================================================================================================================


void StartupPage() {
    ClearScreen();;
    
    printf("\033[96m***************************************************\n");
    printf("*                                                 *\n");
    printf("* \033[33m   ____     ____            _   _              \033[96m *\n");
    printf("* \033[33m  / ___|   / ___|  ___  ___| |_(_) ___  _ __    \033[96m*\n");
    printf("* \033[33m | |   ____\\___ \\ / _ \\/ __| __| |/ _ \\| '_ \\   \033[96m*\n");
    printf("* \033[33m | |__|_____|__) |  __/ (__| |_| | (_) | | | |  \033[96m*\n");
    printf("* \033[33m  \\____|   |____/ \\___|\\___|\\__|_|\\___/|_| |_|  \033[96m*\n");
    printf("*                                                 *\n");
    printf("*           \033[91m     Made by C Section    \033[96m            *\n");
    printf("*                                                 *\n");
    printf("***************************************************\n");
    printf("\n");

 
    printf(" \033[91m     Loading...\n\n \033[33m");

    for (int i = 0; i <= 20; i++) {
   
        int percentage = (i * 100) / 20;
        int progress = (i * 39) / 20;  
     
        printf("\r  || ");  
        for (int j = 0; j < 39; j++) {
            if (j <= progress){
                if(OS==1) printf("\xDB");
                if(OS==2) printf("\u2588");
            }
            else
                printf(" ");
        }
        if(percentage==80){
            usleep(1000000);
        }
        printf(" || %d%%", percentage); 

        fflush(stdout);  
        usleep(100000);  
    }

    printf("\n\n\033[0m ");  
    ClearScreen();
    LoginPage();
    
}


void OsSelectionPage(){
      
    printf("%s********************************************************\n",BLUE);
    printf("*                                                      *\n");
    printf("*         %sPlease select your operating system          %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*     %s____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*    %s|                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|    1. WINDOWS      |    |     2. UBUNTU      |  %s*\n",YELLOW,BLUE);
    printf("*    %s|____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n %sYour Choice: %s",BLINKING_YELLOW,RESET);
    extern int OS;
    scanf("%d",&OS);
    if(OS!=1 && OS!=2){
        OsSelectionPage();
    }
    else{
        StartupPage();
    }
 
}


void LoginPage() {
    ClearScreen();
    printf("%s********************************************************\n",BLUE);
    printf("*                                                      *\n");
    printf("*               %s Welcome to Taj Hotel                %s  *\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*                                                      *\n");
    printf("*   %s  ____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*   %s |                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*   %s |      CUSTOMER      |    |      MANAGER       |  %s*\n",YELLOW,BLUE);
    printf("*   %s |____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      %s*\n",BLUE);
    printf("*   %s  Press 1 for Customer      Press 2 for Manager   %s *\n",YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n \033[0m");
    int i;
    printf("%s Your Choice : %s %s",BLINKING_YELLOW,RESET,RED);
    scanf("%d",&i);
    printf("\033[0m");
    int c;
    while ((c = getchar()) != '\n');
    if(i==1){
        CustomerDetailsPage(0);
    }
    else if(i==2){
        ManagerLoginPage(0);
    }
    else {
        LoginPage();
    }
    
}

void CustomerDetailsPage(int flag) {  
    char name[100];char phone[100];int persons=1;
    ClearScreen();
    printf("%s****************************************************\n",BLUE);
    printf("*                                                  *\n");
    printf("*              %sCustomer Details Page%s               *\n",YELLOW,BLUE);
    printf("*                                                  *\n");
    printf("*     %sPlease provide the following details:%s        *\n",YELLOW,BLUE);
    
    if(flag==1){
        
        printf("*              %sEnter Correct Detials%s               *\n",RED,BLUE);
    }
    printf("*                                                  *\n");
    printf("****************************************************\n");
    
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Name: %s ",YELLOW,RED);
  
    scanf("%[^\n]",name);
    
    printf("\n\n%s*                                                  *\n",BLUE);
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Phone Number: %s",YELLOW,RED);
    scanf("%s",phone);
    printf("\n\n%s*                                                  *\n",BLUE);    
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Total Person: %s",YELLOW,RED);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%d",&persons);
    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter : %s %s",BLINKING_YELLOW,RESET,RED);
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice==1){
        int name_flag=0;
        for (int i = 0; name[i] != '\0'; i++) {
            if (name[i] >= '0' && name[i] <= '9') { 
            name_flag=1;
            }
        }
        int phone_flag=0;
        for (int i = 0; phone[i] != '\0'; i++) {
            if (phone[i] < '0' || phone[i] > '9') { 
            phone_flag=1;
            }
        }
        if(phone_flag==0 && name_flag==0 && persons>0){
            Customerloggedinpage(); 
        }
        else{
            CustomerDetailsPage(1);
        }
    }
    else{
        CustomerDetailsPage(0);
        
    }

}

void ManagerLoginPage(int flag){ 
    char username[100];char password[100];
    ClearScreen();;
    printf("%s****************************************************\n",BLUE);
    printf("*                                                  *\n");
    printf("*                %sManager Login Page                %s*\n",RED,BLUE);
    printf("*                                                  *\n");
    printf("*     %sPlease provide the following details:        %s*\n",RED,BLUE);
    
    if(flag==1){
        
        printf("*              %sEnter Correct Detials               %s*\n",RED,BLUE);
    }
    printf("*                                                  *\n");
    printf("****************************************************\n");
    
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Username : %s",YELLOW,RED);
  
    scanf("%[^\n]",username);
    int c;
    while ((c = getchar()) != '\n');
    printf("\n\n%s*                                                  *\n",BLUE);
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Password : %s",YELLOW,RED);
    scanf("%[^\n]",password);
    
    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice!=1){
        ManagerLoginPage(0);
    }

}

void Customerloggedinpage(){
    ClearScreen();
    printf("%s********************************************************\n",BLUE);
    printf("*                                                      *\n");
    printf("*                  %sWelcome to Taj Hotel                %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*    %sPlease select an option from the menu below:      %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*     %s____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*    %s|                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|  1. Reserve Table  |    |    2. View Menu    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("*     %s____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*    %s|                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|  3. Order Dishes   |    |  4. Retrieve Bill  |  %s*\n",YELLOW,BLUE);
    printf("*    %s|____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("*           %sPress 5 to Go Back to the Login Page       %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n");
    printf("\n%s Your Choice : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');

    if(choice==1){


    }
    else if(choice==2){
        printMenu();   
    }
    else if(choice==3){
        
    }
    else if(choice==4){
        
    }
    else if(choice==5){
        LoginPage();
    }
    else{
        Customerloggedinpage();
    }

}




// ____________
void ManagerLoggedinpage(){
    
    ClearScreen();
    printf("%s********************************************************\n",BLUE);
    printf("*                                                      *\n");
    printf("*                  %sWelcome, Dear Manager               %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*    %sPlease select an option from the menu below:      %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*     %s____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*    %s|                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|  1. Manage Tables  |    |  2. Manage Menu    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("*    %s ____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*    %s|                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|  3. Manage Orders  |    |  4. Sales Analysis |  %s*\n",YELLOW,BLUE);
    printf("*    %s|____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      %s*\n",BLUE);
    printf("*           %sPress 5 to Go Back to the Login Page       %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n");
}

void ManageMenuPage(){
    ClearScreen();
    printf("%s********************************************************\n",BLUE);
    printf("*                                                      *\n");
    printf("*                  %sWelcome, Dear Manager               %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*    %sPlease select an option from the menu below:      %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*     %s____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*    %s|                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|    1. Add Item     |    |  2. Remove Item    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("*                %s ____________________                 %s*\n",YELLOW,BLUE);
    printf("*                %s|                    |                %s*\n",YELLOW,BLUE);
    printf("*                %s|  3. Update Price   |                %s*\n",YELLOW,BLUE);
    printf("*                %s|____________________|                %s*\n",YELLOW,BLUE);
    printf("*                                                      %s*\n",BLUE);
    printf("*                  %sPress 5 to Go Back                  %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n");
   
}

void ManageTablesPage(){
    ClearScreen();
    printf("%s********************************************************\n",BLUE);
    printf("*                                                      *\n");
    printf("*                  %sWelcome, Dear Manager               %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*    %sPlease select an option from the menu below:      %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("*     %s____________________      ____________________   %s*\n",YELLOW,BLUE);
    printf("*    %s|                    |    |                    |  %s*\n",YELLOW,BLUE);
    printf("*    %s|    1. Add Table    |    |  2. Remove Table   |  %s*\n",YELLOW,BLUE);
    printf("*    %s|____________________|    |____________________|  %s*\n",YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("*                                                      %s*\n",BLUE);
    printf("*                  %sPress 5 to Go Back                  %s*\n",RED,BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n");
   
}



// ===========================================================================================================================================
// GRAPH TOOLS



int findMax(int revenue[], int size) {
    int max = revenue[0];
    for (int i = 1; i < size; i++) {
        if (revenue[i] > max) {
            max = revenue[i];
        }
    }
    return max;
}

void drawBarGraph(int revenue[], int size) {
    ClearScreen();
    printf("\n");
    int maxRevenue = findMax(revenue, size);

    float scale = (float)HEIGHT / maxRevenue;
 

    // main data frame and y axis.
    for (int i = HEIGHT; i > 0; i--) {

        if (i % 5 == 0) {
            printf("%s%5d %s|%s",RED ,(int)(i * maxRevenue / HEIGHT),BLUE,BLINKING_YELLOW); 
        } else {
            printf("%s      |%s",BLUE,BLINKING_YELLOW);
        }

        for (int j = 0; j < size; j++) {
            if ((int)(revenue[j] * scale) >= i) {
                
                if(OS==1) printf(" \xDB ");
                if(OS==2) printf(" \u2588 ");

            } 
            else {
                printf("   "); 
            }
        }
        printf("\n");
    }

    // X axis
    printf("%s      +",BLUE);
    for (int j = 0; j < size; j++) {
        printf("---");
    }
    printf("\n");   
    printf("       %s",RED);
    for (int j = 0; j < size; j++) {
        printf("%2d ", size - j); 
    }
    printf("\n");
    printf("%s               1 Represents Today, 2 Represents Yesterday and so on for last 30 days.                       %s",YELLOW,RESET);
    printf("\n\n");
}



// ===============================================================================================================


// void print(char msg[100]){
//     FILE *f;
//     f=fopen("degub.txt","a+");
//     fprintf(*f,"%s\n",msg);
// }



// int StartUI(){

//     FILE *f;
//     f=fopen("degub.txt","a+");
//     fprintf(f,"START!\n");

//     fprintf(f,"OS Selection Page\n");
//     //OS SELECTION PAGE
//     OsSelectionPage();
//     fprintf(f,"Selected OS = %d\n",OS);
    

//     // STARTUP PAGE AND LOGIN CHOICE
//     StartupPage();

//     LoginChoicePage:
//     LoginPage();
//     int i;
//     printf("%s Your Choice : %s %s",BLINKING_YELLOW,RESET,RED);
//     scanf("%d",&i);
//     printf("\033[0m");
//     int c;
//     while ((c = getchar()) != '\n');
    
//     //CUSTOMER 
//     if(i==1){
//         ClearScreen();
//         char name[100];
//         char phone[10];
//         int persons;
//         CustomerDetailsPage(name,phone,&persons,0);
//         //CUSTOMER DETAILS HAVE BEEN TAKEN

//         ClearScreen();

//         //CUSTOMER DASHBOARD
//         CustomerDashboard:
//         Customerloggedinpage();
//         int i;
//         printf("%s Your Choice : %s%s",BLINKING_YELLOW,RESET,RED);
//         scanf("%d",&i);
//         int c;
//         while ((c = getchar()) != '\n');
//             //RESERVE TABLE    
//             if(i==1){

//             }
//             // PRINT MENU
//             else if (i==2){
//                 ClearScreen();
//                 //call print menu
//             }

//             else if (i==3) {
//                 // ORDER FOOD
//             }
//             else if(i==4){
//                 // Retrive Bill
//             }
//             else {
//                 goto loginChoicePage;
//             }      
//     }







//     //MANAGER
//     else if(i==2) {
            
//         char username[100];
//         char password[100];
//         ManagerLoginPage(username,password,0);
//         printf("%s\n",username);
//         printf("%s",password);
//         ManagerLoggedinPageGOTO:
//         ManagerLoggedinpage();
//         int ch=0;
//         scanf("%d",&ch);
//         if(ch==1){
            
//             ManageTablesPage();
//         }
//         else if(ch==2){
            
//             ManageMenuPage();
//         }
//         else if(ch==4){
//             int revenue[30] = {
//         120, 180, 150, 200, 250, 300, 350, 400, 320, 280,
//         220, 180, 140, 100, 60, 50, 340, 130, 100, 2000,
//         250, 100, 650, 200, 250, 300, 350, 400, 450, 400
//             };

//             drawBarGraph(revenue, 30);

//         }
//     }

//     //END
//     return 0;
// // }


int main (){
    OsSelectionPage();
    return 0;
}

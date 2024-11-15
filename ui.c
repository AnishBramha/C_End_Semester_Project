#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>


#define CLEAR_SCREEN system("cls");

#define MAX_ITEM_NAME_WIDTH  21
#define MAX_ITEM_NO_WIDTH    8
#define MAX_SPICE_WIDTH      10
#define MAX_TYPE_WIDTH       8
#define MAX_ALLERGEN_WIDTH   15
#define MAX_PRICE_WIDTH      7

void LoginPage();

#define BLUE "\033[96m"
#define RED "\033[91m"
#define YELLOW "\033[33m"





void logo(void){
    printf("   ____     ____            _   _             \n");
    printf("  / ___|   / ___|  ___  ___| |_(_) ___  _ __  \n");
    printf(" | |   ____\\___ \\ / _ \\/ __| __| |/ _ \\| '_ \\ \n");
    printf(" | |__|_____|__) |  __/ (__| |_| | (_) | | | | \n");
    printf("  \\____|   |____/ \\___|\\___|\\__|_|\\___/|_| |_| \n\n");
}

// FOR MENU
// ===============================================================================================================

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

void menuRow(const char *item_name, const char *item_no, const char *spice, const char *type, const char *allergens, const char *price) {
    int max_lines = 0;
    max_lines = get_wrapped_lines(item_name, MAX_ITEM_NAME_WIDTH);
    if (get_wrapped_lines(item_no, MAX_ITEM_NO_WIDTH) > max_lines) max_lines = get_wrapped_lines(item_no, MAX_ITEM_NO_WIDTH);
    if (get_wrapped_lines(spice, MAX_SPICE_WIDTH) > max_lines) max_lines = get_wrapped_lines(spice, MAX_SPICE_WIDTH);
    if (get_wrapped_lines(type, MAX_TYPE_WIDTH) > max_lines) max_lines = get_wrapped_lines(type, MAX_TYPE_WIDTH);
    if (get_wrapped_lines(allergens, MAX_ALLERGEN_WIDTH) > max_lines) max_lines = get_wrapped_lines(allergens, MAX_ALLERGEN_WIDTH);
    if (get_wrapped_lines(price, MAX_PRICE_WIDTH) > max_lines) max_lines = get_wrapped_lines(price, MAX_PRICE_WIDTH);
    
    for (int line = 0; line < max_lines; line++) {
        printf("| ");
        print_wrapped_text(item_name, MAX_ITEM_NAME_WIDTH, line);
        printf(" | ");
        print_wrapped_text(item_no, MAX_ITEM_NO_WIDTH, line);
        printf(" | ");
        print_wrapped_text(spice, MAX_SPICE_WIDTH, line);
        printf(" | ");
        print_wrapped_text(type, MAX_TYPE_WIDTH, line);
        printf(" | ");
        print_wrapped_text(allergens, MAX_ALLERGEN_WIDTH, line);
        printf(" | ");
        print_wrapped_text(price, MAX_PRICE_WIDTH, line);
        printf(" |\n");
    }
}

void menuFooter(){
    printf("+-----------------------+----------+------------+----------+-----------------+---------+\n");
}

void menuLogo(){
    printf(" __  __  ______  _   _  _    _ \n");
    printf("|  \\/  ||  ____|| \\ | || |  | |\n");
    printf("| \\  / || |__   |  \\| || |  | |\n");
    printf("| |\\/| ||  __|  | . ` || |  | |\n");
    printf("| |  | || |____ | |\\  || |__| |\n");
    printf("|_|  |_||______||_| \\_| \\____/ \n");
}



void menuHeader(){
 
    printf("+-----------------------+----------+------------+----------+-----------------+---------+\n");
    printf("|       Item Name       |  Item No |   Spice    |   Type   |   Allergen(s)   | Price   |\n");
    printf("+-----------------------+----------+------------+----------+-----------------+---------+\n");
          
}



// ===============================================================================================================


void StartupPage() {
    CLEAR_SCREEN;
    
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

 
    printf(" \033[91m   Loading...\n \033[33m");

    for (int i = 0; i <= 20; i++) {
   
        int percentage = (i * 100) / 20;
        int progress = (i * 39) / 20;  
     
        printf("\r  [");  
        for (int j = 0; j < 39; j++) {
            if (j <= progress)
                printf("#");
            else
                printf(" ");
        }
        if(percentage==80){
            usleep(1000000);
        }
        printf("] %d%%", percentage); 

        fflush(stdout);  
        usleep(100000);  
    }

    printf("\n\n\033[0m ");  
    CLEAR_SCREEN
    LoginPage();
}


void LoginPage() {
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
}





void CustomerDetailsPage(char name[],char phone[],int *persons,int flag) {
    CLEAR_SCREEN;
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
    scanf("%d",persons);
    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter : %s",YELLOW,RED);
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
        if(phone_flag==0 && name_flag==0 && *persons>0){
        
        }
        else{
            CustomerDetailsPage(name,phone,persons,1);
        }
    }
    else{
        CustomerDetailsPage(name,phone,persons,0);
        
    }

}


void ManagerLoginPage(char username[],char password[],int flag){
    CLEAR_SCREEN;
    printf("****************************************************\n");
    printf("*                                                  *\n");
    printf("*                Manager Login Page                *\n");
    printf("*                                                  *\n");
    printf("*     Please provide the following details:        *\n");
    
    if(flag==1){
        
        printf("*              Enter Correct Detials               *\n");
    }
    printf("*                                                  *\n");
    printf("****************************************************\n");
    
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*   Username : ");
  
    scanf("%[^\n]",username);
    int c;
    while ((c = getchar()) != '\n');
    printf("\n\n*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*   Password : ");
    scanf("%[^\n]",password);
    
    printf("\n\n\n Enter 1 to confirm Details , 0 to Re-enter : ");
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice!=1){
        ManagerLoginPage(username,password,0);
    }

}


void Customerloggedinpage(){
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

}

void ManagerLoggedinpage(){
    
    CLEAR_SCREEN;
    printf("********************************************************\n");
    printf("*                                                      *\n");
    printf("*                  Welcome, Dear Manager               *\n");
    printf("*                                                      *\n");
    printf("*    Please select an option from the menu below:      *\n");
    printf("*                                                      *\n");
    printf("*     ____________________      ____________________   *\n");
    printf("*    |                    |    |                    |  *\n");
    printf("*    |  1. Manage Tables  |    |  2. Manage Menu    |  *\n");
    printf("*    |____________________|    |____________________|  *\n");
    printf("*                                                      *\n");
    printf("*     ____________________      ____________________   *\n");
    printf("*    |                    |    |                    |  *\n");
    printf("*    |  3. Manage Orders  |    |  4. Sales Analysis |  *\n");
    printf("*    |____________________|    |____________________|  *\n");
    printf("*                                                      *\n");
    printf("*           Press 5 to Go Back to the Login Page       *\n");
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n");
}




int main(){
    

    CLEAR_SCREEN;

    StartupPage();
    
    
   
    
    int i;
    printf("%s Your Choice : %s",RED,YELLOW);
    scanf("%d",&i);
    printf("\033[0m");
    int c;
    while ((c = getchar()) != '\n');
    if(i==1){
        CLEAR_SCREEN;
        char name[100];
        char phone[10];
        int persons;
        CustomerDetailsPage(name,phone,&persons,0);
        CLEAR_SCREEN;
        Customerloggedinpage();
        int i;
        scanf("%d",&i);
        int c;
        while ((c = getchar()) != '\n');
        if(i==2){
            CLEAR_SCREEN
            menuLogo();
            menuHeader();
            menuRow("Red Sauce Pasta","23094","9","Beverage","Nothing much","38.32");
            menuRow("Lasagne alla Bolognese With Extra CHeese","23094","9","Beverage","Nothing much","38.32");
            menuRow("Pizza Is good","23094","9","Beverage","Glutent Lactose Something Dsometihign something","38.32");
            menuRow("Red Sauce Pasta","23094","9","Beverage","Nothing much","38.32");
            menuFooter();
            printf("\n\n");
        }
        else{
            printf("NOTHING ELSE WORKS YET!");
        }      
    }
    else {
        
    char username[100];
    char password[100];
    ManagerLoginPage(username,password,0);
    printf("%s\n",username);
    printf("%s",password);
    ManagerLoggedinpage();
        
    }

        

    return 0;
}


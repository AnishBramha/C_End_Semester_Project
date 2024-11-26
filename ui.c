#include "ui.h"


int OS=2;
void ClearScreen(){
    if (OS==1) system("cls");
    if(OS==2) system("clear");
}





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

void printMenu(HEADS){
    ClearScreen();
    struct Menu *menu = menuHead;
    struct Item item;
    menuLogo();
    menuHeader();
    while (menu!=NULL){
        
        item=menu->item;
        int type=item.itemID/1000000;
        int spice=(item.itemID/100000)%10;
        int veg=(item.itemID/10000)%10;
        int itemNo=item.itemID%10000;
        char Sprice[20];
        snprintf(Sprice, sizeof(Sprice), "%.2f", item.price);
        char Sspice[2]={spice+48,'\0'};
        char Sveg[2]={veg-48,'\0'};
        char Sno[5]={((itemNo/1000))+48,((itemNo/100)%10)+48,((itemNo/10)%100)+48,(itemNo%10)+48,'\0'};

        if(type==0){
            menuRow(item.name,Sno,Sspice,"NIL",item.allergens,Sprice,veg);
        }
        
        if(type==1){
            menuRow(item.name,Sno,Sspice,"Starter",item.allergens,Sprice,veg);
        }
        
        if(type==2){
            menuRow(item.name,Sno,Sspice,"Main Course",item.allergens,Sprice,veg);
        }
        if(type==3){
            menuRow(item.name,Sno,Sspice,"Dessert",item.allergens,Sprice,veg);
        }
        if(type==4){
            menuRow(item.name,Sno,Sspice,"Beverage",item.allergens,Sprice,veg);
        }  
        menu=menu->next;
    }
    menuFooter();
}

void viewMenu(HEADS,long long OID,int persons){
    ClearScreen();
    printMenu(PASSHEADS);
    printf("\n %s The Following Options are available: %s",BLINKING_YELLOW,RESET);
    printf("\n %s 1 -> Search by Item Name %s",BLUE,RESET);
    printf("\n %s 2 -> Filter by Price Range %s",BLUE,RESET);
    printf("\n %s 3 -> Filter by Allergens %s",BLUE,RESET);
    printf("\n %s 4 -> Filter by Veg / Nonveg %s",BLUE,RESET);
    printf("\n %s 5 -> Go back %s",BLUE,RESET);
    printf("\n %s Your Choice :  %s",BLINKING_YELLOW,RESET);
    
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    if(choice==1){
        searchByNamePage(PASSHEADS,OID,persons);
    }
    else if(choice==2){
        searchByPriceRange(PASSHEADS,OID,persons);
    }
    else if(choice==3){
        filterByAllergens(PASSHEADS,OID,persons);
    }
    else if(choice==4){
        filterByVeg(PASSHEADS,OID,persons);
    }
    else if(choice==5){
        Customerloggedinpage(PASSHEADS,OID,persons);
    }
    else{
        viewMenu(PASSHEADS,OID,persons);
    }
}
// ============================================================================================================================================


void StartupPage(HEADS) {
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
    LoginPage(PASSHEADS);
    
}


void OsSelectionPage(HEADS){
      
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
    
    scanf("%d",&OS);
    int c;
    while((c=getchar())!='\n'){}
    if(OS!=1 && OS!=2){
        OsSelectionPage(PASSHEADS);
    }
    else{
        StartupPage(PASSHEADS);
    }
 
}


void LoginPage(HEADS) {
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
        CustomerDetailsPage(0,PASSHEADS);
    }
    else if(i==2){
        ManagerLoginPage(0,PASSHEADS);
    }
    else {
        LoginPage(PASSHEADS);
    }
    
}



void CustomerDetailsPage(int flag,HEADS) {  
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
        int len=0;
        for (int i = 0; phone[i] != '\0'; i++) {
            len++;
            if (phone[i] < '0' || phone[i] > '9') { 
            phone_flag=1;
            }
        }
        if(len!=10){
            phone_flag=1;
        }
        if(phone_flag==0 && name_flag==0 && persons>0){
            long long int OID;
            currentOrdersHead=createOrder(name,phone,persons,currentOrdersHead,orderHistoryHead,&OID,tablesHead);
            Customerloggedinpage(PASSHEADS,OID,persons); 
        }
        else{
            CustomerDetailsPage(1,PASSHEADS);
        }
    }
    else{
        CustomerDetailsPage(0,PASSHEADS);
        
    }

}

void Customerloggedinpage(HEADS,long long OID,int persons){
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
    int choice=0;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');

    if(choice==1){
        ReserveTablePage(PASSHEADS,OID,persons);

    }
    else if(choice==2){
        viewMenu(PASSHEADS,OID,persons);   
    }
    else if(choice==3){
        orderDishesPage(PASSHEADS,OID,persons);
        
    }
    else if(choice==4){
        GenerateBill(PASSHEADS,OID,persons);
    }
    else if(choice==5){
        LoginPage(PASSHEADS);
    }
    else{
        Customerloggedinpage(PASSHEADS,OID,persons);
    }

}

void ReserveTablePage(HEADS,long long OID,int persons){
    ClearScreen();
    long tableNO;
    int already_reserved_flag=0;
    CurrentOrders* tempCurrentOrders=currentOrdersHead;
    while(1==1){
        
        if(tempCurrentOrders->order.orderID==(long)OID){
            if(tempCurrentOrders->order.tableNo!=0){
                already_reserved_flag=1;
                break;
            }
        }
        if(tempCurrentOrders->next==NULL){
            break;
        }
        tempCurrentOrders=tempCurrentOrders->next;
    }
    if(already_reserved_flag==1){
        tableNO=tempCurrentOrders->order.tableNo;
        
    }
    else{
    tablesHead=reserveTable(OID,persons,tablesHead,currentOrdersHead,&tableNO);
    }

    tempCurrentOrders=currentOrdersHead;
    while(1==1){
        if(tempCurrentOrders->order.orderID==OID){
            tempCurrentOrders->order.tableNo=tableNO;
            break;
        }
        if(tempCurrentOrders->next==NULL){
            break;
        }
        tempCurrentOrders=tempCurrentOrders->next;
    }
    updateCurrentOrders(currentOrdersHead);

    if(tableNO==-1){
        printf("%s****************************************************\n",BLUE);
        printf("*                                                  *\n");
        printf("*   %sApologies, but we are currently fully booked%s     *\n",BLINKING_YELLOW,BLUE);
        printf("*                                                  *\n");
        printf("****************************************************%s\n",RESET);
    }
    
    else{ 
        printf("%s****************************************************\n",BLUE);
        printf("*                                                  *\n");
        printf("*               %sBOOKING SUCCESFULL!!%s               *\n",BLINKING_YELLOW,BLUE);
        printf("*                                                  *\n");
        printf("              %sYour Table Number: %ld %s               \n",BLINKING_YELLOW,tableNO,BLUE);
        printf("*                                                  *\n");
        printf("*      %sHoping you have a great time with us!%s       *\n",BLINKING_YELLOW,BLUE);
        printf("*                                                  *\n");
        printf("****************************************************%s\n",RESET);

    }
    printf("\n%s Press 5 to go back : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    Customerloggedinpage(PASSHEADS,OID,persons);

}

void orderDishesPage(HEADS,long long OID,int persons){
    ClearScreen();
    printf("\n");
    int alreadyReserved=0;
    CurrentOrders *tempCurrentOrders=currentOrdersHead;
    while (1==1){
        if(tempCurrentOrders->order.orderID==OID){
            if(tempCurrentOrders->order.tableNo!=0){
                alreadyReserved=1;
            }
        }
        if(tempCurrentOrders->next==NULL){
            break;
        }
        tempCurrentOrders=tempCurrentOrders->next;
    }    
    if(alreadyReserved==1){
    printMenu(PASSHEADS);
        while(1==1){
            printf("%s Enter Item ID you want to order (Without Leading Zeroes) or press \'0\' to stop ordering : %s",BLINKING_YELLOW,RESET);
            long long ItemID;
            int inputStatus=scanf("%lld",&ItemID);
            if (inputStatus != 1) {
            while (getchar() != '\n');
            orderDishesPage(PASSHEADS,OID,persons);
            break;
            }
            if(ItemID==0){
                Customerloggedinpage(PASSHEADS,OID,persons);
                break;
            }
            int isValid=0;
            Menu *tempMenu=menuHead;
            while(tempMenu->next!=NULL){
                
                
                if(tempMenu->item.itemID%10000==ItemID){
                    isValid=1;
                }
                tempMenu=tempMenu->next;
            }
            if(tempMenu->item.itemID==ItemID) { isValid=1; }
            if(isValid==1){
            currentOrdersHead= makeOrder(ItemID,currentOrdersHead,OID);
            
            printf("%s-> Item with itemID:%lld ordered Succesfully%s\n",BLUE,ItemID,RESET);
            }
            else{
                printf("%s-> Enter Valid Item ID%s\n",RED,RESET);
            }

        }
    }
    else{
        printf("%s****************************************************\n",BLUE);
        printf("*                                                  *\n");
        printf("*       %sPlease Reserve a Seat Before Ordering%s     *\n",BLINKING_YELLOW,BLUE);
        printf("*                                                  *\n");
        printf("****************************************************%s\n",RESET);   
        printf("\n%s Press 5 to go back : %s",BLINKING_YELLOW,RESET);
        int choice;
        scanf("%d",&choice);
        int c;
        while ((c = getchar()) != '\n');
        if(choice==5){
            Customerloggedinpage(PASSHEADS,OID,persons);
        }
        else{
            orderDishesPage(PASSHEADS,OID,persons);
        }
    }

}

void searchByNamePage(HEADS,long long OID,int persons){
    ClearScreen();
    char spaces[]="                                                                      ";
    printf("**********************************************************\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("**********************************************************\n%s\n%s\033[F\033[F\033[F\033[F* %s Enter the name of the dish: %s ",spaces,spaces,YELLOW,RED);
    char dishName[50];
    scanf("%[^\n]",dishName);
    printf("\n\n\n");
    viewMenu(PASSHEADS,OID,persons); //FOR NOW JUST TO BACK TO ORIGINAL PAGE

}

void searchByPriceRange(HEADS,long long OID,int persons){
    ClearScreen();
    char spaces[]="                                                                      ";
    printf(BLUE"**********************************************************\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("**********************************************************\n%s\n%s\033[F\033[F\033[F\033[F* %s Enter Minimum Price: %s ",spaces,spaces,YELLOW,RED);
    float min;
    if(scanf("%f",&min)!=1){
        while(getchar()!='\n');
        searchByPriceRange(PASSHEADS,OID,persons);
    }

    
    printf(BLUE"\n\n*                                                        *\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("**********************************************************\n%s\n%s\033[F\033[F\033[F\033[F* %s Enter Maximum Price: %s ",spaces,spaces,YELLOW,RED);
    float max;
    if(scanf("%f",&max)!=1){
        while(getchar()!='\n');
        searchByPriceRange(PASSHEADS,OID,persons);
    }
    
    printf("\n\nMin: %f   Max: %f\n\n",min,max);
    
    printf("\n%s Press 5 to go back : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    if(choice==5){
        viewMenu(PASSHEADS,OID,persons); 
 
    }
    else{
        searchByPriceRange(PASSHEADS,OID,persons);
    }
}


void filterByAllergens(HEADS,long long OID,int persons){
    ClearScreen();
    char spaces[]="                                                                      ";
    printf(BLUE"**********************************************************\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("*                                                        *\n");
    printf("**********************************************************\n%s\n%s\033[F\033[F\033[F\033[F* %s Enter Allergen you want to filter: %s ",spaces,spaces,YELLOW,RED);
 
    char allergen[50];
    if(scanf("%[^\n]",allergen)!=1){
        while(getchar()!='\n');   
        filterByAllergens(PASSHEADS,OID,persons);
    }
    while(getchar()!='\n');

    
    printf("\n\nAllergen: %s\n\n",allergen);
    
    printf("\n%s Press 5 to go back : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    if(choice==5){
        viewMenu(PASSHEADS,OID,persons); 
 
    }
    else{
        filterByAllergens(PASSHEADS,OID,persons);
    }
}

void filterByVeg(HEADS,long long OID,int persons){
    ClearScreen();
    printf("%s********************************************************\n",BLUE);
    printf("*                                                      *\n");
    printf("*                  %s ENTER YOUR CHOICE %s                 *\n",RESET,BLUE);
    printf("*                  %s 1 -> VEG %s                          *\n",GREEN,BLUE);
    printf("*                  %s 2 -> NON-VEG %s                      *\n",RED,BLUE);
    printf("*                  %s 3 -> EGG %s                          *\n",BLINKING_YELLOW,BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    
    printf("\n %s Your Choice :  %s",BLINKING_YELLOW,RESET);
    int vegOrNonVeg;
    scanf("%d",&vegOrNonVeg);
    

    
    printf("\nVeg? : %d\n",vegOrNonVeg);
    
    printf("\n%s Press 5 to go back : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    if(choice==5){
        viewMenu(PASSHEADS,OID,persons); 
 
    }
    else{
        filterByVeg(PASSHEADS,OID,persons);
    }

}




// ____________

void ManagerLoginPage(int flag,HEADS){ 
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
        ManagerLoginPage(0,PASSHEADS);
    }
    else{
        ManagerLoggedinpage(PASSHEADS);
    }

}

void ManagerLoggedinpage(HEADS){
    
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
    printf("\n%sYour Choice : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    if(choice==5){
        LoginPage(PASSHEADS);
    }
    else if(choice==4){
        ManagerLoggedinpage(PASSHEADS);//CHANGEEEEEEEEE
    }
    
    else if(choice==3){
        ManagerLoggedinpage(PASSHEADS);//CHANGEEEEEEEEE
    }
    else if(choice==2){
        ManageMenuPage(PASSHEADS);
    }
    else if(choice==1){
        ManageTablesPage(PASSHEADS);
    }
    else{
        ManagerLoggedinpage(PASSHEADS);
    }
}

void ManageMenuPage(HEADS){
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
    printf("\n%s Your Choice : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    
    if(choice==1){
        addItemPage(PASSHEADS);
    }
    else if(choice==2){
        removeItemPage(PASSHEADS);
    }
    else if(choice==3){
        updateItemPage(PASSHEADS);
    }
    else if(choice==5){
        ManagerLoggedinpage(PASSHEADS);
    }
    else{
        ManageMenuPage(PASSHEADS);
    }
   
}
void addItemPage(HEADS){
      ClearScreen();
    printf("%s******************************************************\n",BLUE);
    printf("*                                                    *\n");
    printf("*                %sAdd an Item                         %s*\n",RED,BLUE);
    printf("*                                                    *\n");
    printf("******************************************************\n");
    printf("*                                                    *\n");
    printf("*                                                    *\n");
    printf("*                                                    *\n");
    printf("******************************************************\033[F\033[F*  %s Item Number : %s",YELLOW,RED);
    long int tableNO;
    if(scanf("%ld",&tableNO)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addItemPage(PASSHEADS);
    }
    int c;
    while ((c = getchar()) != '\n');
    printf("\n\n%s*                                                    *\n",BLUE);
    printf("*                                                    *\n");
    printf("*                                                    *\n");
    printf("******************************************************\033[F\033[F*  %s Name : %s",YELLOW,RED);
    char name[100];
    if(scanf("%[^\n]",name)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addItemPage(PASSHEADS);
    }
    while ((c = getchar()) != '\n');

    printf("\n\n%s*                                                    *\n",BLUE);
    printf("*                                                    *\n");
    printf("*                                                    *\n");
    printf("******************************************************\033[F\033[F*  %s Spiciness : %s",YELLOW,RED);
    int spice;
    if(scanf("%d",&spice)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addItemPage(PASSHEADS);
    }
    while ((c = getchar()) != '\n');
    
    printf("\n\n%s*                                                    *\n",BLUE);
    printf("*                                                    *\n");
    printf("*                                                    *\n");
    printf("******************************************************\033[F\033[F*  %s Veg/Egg/NonVeg (0/1/2) : %s",YELLOW,RED);
    int veg;
    if(scanf("%d",&veg)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addItemPage(PASSHEADS);
    }
    while ((c = getchar()) != '\n');

    printf("\n\n%s*                                                    *\n",BLUE);
    printf("*                                                    *\n");
    printf("*                                                    *\n");
    printf("******************************************************\033[F\033[F*  %s Starter/MainCourse/Dessert/Beverage(1/2/3/4) : %s",YELLOW,RED);
    int type;
    if(scanf("%d",&type)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addItemPage(PASSHEADS);
    }
    while ((c = getchar()) != '\n');

    printf("\n\n%s*                                                    *\n",BLUE);
    printf("*                                                    *\n");
    printf("*                                                    *\n");
    printf("******************************************************\033[F\033[F*  %s New Price : %s",YELLOW,RED);
    float price;
    if(scanf("%f",&price)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addItemPage(PASSHEADS);
    }

    while ((c = getchar()) != '\n');


    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter , 5 to go back: %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice==1){
        ManageMenuPage(PASSHEADS);
    }
    else if(choice==5){
        ManageMenuPage(PASSHEADS);
    }
    else{
        addTablePage(PASSHEADS);
    }


}

void removeItemPage(HEADS){
      ClearScreen();
    printf("%s****************************************************\n",BLUE);
    printf("*                                                  *\n");
    printf("*                %sRemove a item                     %s*\n",RED,BLUE);
    printf("*                                                  *\n");
    printf("****************************************************\n");
    
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Item Number : %s",YELLOW,RED);
    long int itemNO;
    if(scanf("%ld",&itemNO)!=1){
        int c;
        while ((c = getchar()) != '\n');
        removeItemPage(PASSHEADS);
    }
    int c;
    while ((c = getchar()) != '\n');
    
    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter , 5 to go back: %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice==1){
        ManageMenuPage(PASSHEADS);
    }
    else if(choice==5){
        ManageMenuPage(PASSHEADS);
    }
    else{
        removeItemPage(PASSHEADS);
    }
}

void updateItemPage(HEADS){
      ClearScreen();
    printf("%s****************************************************\n",BLUE);
    printf("*                                                  *\n");
    printf("*                %sUpdate a Item                      %s*\n",RED,BLUE);
    printf("*                                                  *\n");
    printf("****************************************************\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Item Number : %s",YELLOW,RED);
    long int itemNO;
    if(scanf("%ld",&itemNO)!=1){
        int c;
        while ((c = getchar()) != '\n');
        updateItemPage(PASSHEADS);
    }
    int c;
    while ((c = getchar()) != '\n');
    printf("\n\n%s*                                                  *\n",BLUE);
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s New Price : %s",YELLOW,RED);
    float price;
    if(scanf("%f",&price)!=1){
        int c;
        while ((c = getchar()) != '\n');
        updateItemPage(PASSHEADS);
    }

    while ((c = getchar()) != '\n');
    
    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter , 5 to go back: %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice==1){
        ManageMenuPage(PASSHEADS);
    }
    else if(choice==5){
        ManageMenuPage(PASSHEADS);
    }
    else{
        updateItemPage(PASSHEADS);
    }

}



void ManageTablesPage(HEADS){
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
    printf("\n%s Your Choice : %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    int c;
    while ((c = getchar()) != '\n');
    if(choice==1){
        addTablePage(PASSHEADS);
    }
    else if(choice==2){
        removeTablePage(PASSHEADS);
    }
    else if(choice==5){
        ManagerLoggedinpage(PASSHEADS);
    }
    else{
        ManageTablesPage(PASSHEADS);
    }
   
}
void removeTablePage(HEADS){
    ClearScreen();
    printf("%s****************************************************\n",BLUE);
    printf("*                                                  *\n");
    printf("*                %sRemove A table                    %s*\n",RED,BLUE);
    printf("*                                                  *\n");
    printf("****************************************************\n");
    
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Table Number : %s",YELLOW,RED);
    long int tableNO;
    if(scanf("%ld",&tableNO)!=1){
        int c;
        while ((c = getchar()) != '\n');
        removeTablePage(PASSHEADS);
    }
    int c;
    while ((c = getchar()) != '\n');
    
    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter , 5 to go back: %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice==1){
        ManagerLoggedinpage(PASSHEADS);
    }
    else if(choice==5){
        ManagerLoggedinpage(PASSHEADS);
    }
    else{
        removeTablePage(PASSHEADS);
    }

}
void addTablePage(HEADS){
    ClearScreen();
    printf("%s****************************************************\n",BLUE);
    printf("*                                                  *\n");
    printf("*                %sAdd A table                       %s*\n",RED,BLUE);
    printf("*                                                  *\n");
    printf("****************************************************\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Table Number : %s",YELLOW,RED);
    long int tableNO;
    if(scanf("%ld",&tableNO)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addTablePage(PASSHEADS);
    }
    int c;
    while ((c = getchar()) != '\n');
    printf("\n\n%s*                                                  *\n",BLUE);
    printf("*                                                  *\n");
    printf("*                                                  *\n");
    printf("****************************************************\033[F\033[F*  %s Capacity : %s",YELLOW,RED);
    long int capacity;
    if(scanf("%ld",&capacity)!=1){
        int c;
        while ((c = getchar()) != '\n');
        addTablePage(PASSHEADS);
    }

    while ((c = getchar()) != '\n');
    
    printf("\n\n\n%s Enter 1 to confirm Details , 0 to Re-enter , 5 to go back: %s",BLINKING_YELLOW,RESET);
    int choice;
    scanf("%d",&choice);
    while ((c = getchar()) != '\n');
    if(choice==1){
        ManagerLoggedinpage(PASSHEADS);
    }
    else if(choice==5){
        ManagerLoggedinpage(PASSHEADS);
    }
    else{
        addTablePage(PASSHEADS);
    }

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




void GenerateBill(HEADS ,long long orderID,int persons) {
    ClearScreen();
    // Locate the order in the CurrentOrders linked list
    CurrentOrders* currentOrderNode = currentOrdersHead;
    while (currentOrderNode != NULL) {
        if (currentOrderNode->order.orderID == orderID) {
            break;
        }
        currentOrderNode = currentOrderNode->next;
    }

    if (currentOrderNode == NULL) {
        printf("Order with ID %lld not found.\n", orderID);
        return;
    }

    Order* order = &currentOrderNode->order;

    // Print bill header
    printf("%s********************************************************\n", BLUE);
    printf("*                                                      *\n");
    printf("*                        %sINVOICE                       %s*\n", RED, BLUE);
    printf("*                       %sTAJ HOTEL                      %s*\n", RED, BLUE);
    printf("*                                                      *\n");
    printf("*                                                      *\n");
    printf("*  %sCustomer Details                                    %s*\n", YELLOW, BLUE);
    printf("*%s------------------------------------------------------%s*\n", YELLOW, BLUE);
    printf("*  %-15s : %-34ld%s*\n", "Order ID", order->orderID, BLUE);
    printf("*  %-15s : %-34s%s*\n", "Customer Name", order->name, BLUE);
    printf("*  %-15s : %-34s%s*\n", "Phone", order->phone, BLUE);
    printf("*  %-15s : %-34ld%s*\n", "Table Number", order->tableNo, BLUE);
    printf("*  %-15s : %-34s%s*\n", "Order Date", order->orderDate, BLUE);
    printf("*  %-15s : %-34s%s*\n", "Order Time", order->orderTime, BLUE);
    printf("*%s------------------------------------------------------%s*\n", YELLOW, BLUE);

    printf("*  %sItem Name                          Price ₹          %s*\n", YELLOW, BLUE);
    printf("*%s------------------------------------------------------%s*\n", YELLOW, BLUE);

    float grandTotal = 0.0;

    // Iterate over itemIDs in the order and fetch details from the menu
    for (int i = 0; i < 100 && order->itemIDs[i] != 0; i++) {
        long long int itemID = order->itemIDs[i];

        // Search for the item in the menu linked list
        Menu* currentMenuNode = menuHead;
        while (currentMenuNode != NULL) {
            if (currentMenuNode->item.itemID % 10000 == itemID) {
                // Item found
                printf("*  %-34s  %-16.2f%s*\n", currentMenuNode->item.name, currentMenuNode->item.price, BLUE);
                grandTotal += currentMenuNode->item.price;
                break;
            }
            currentMenuNode = currentMenuNode->next;
        }
    }

    // Calculate taxes
    float sgst = grandTotal * 0.09; // 9% SGST
    float cgst = grandTotal * 0.09; // 9% CGST
    float totalWithTax = grandTotal + sgst + cgst;

    // Print the total
    printf("*%s------------------------------------------------------%s*\n", YELLOW, BLUE);
    printf("*%s  %-33s   %-16.2f%s*\n",RESET, "Subtotal", grandTotal, BLUE);
    printf("*%s  %-33s   %-16.2f%s*\n",RESET, "SGST (9%)", sgst, BLUE);
    printf("*%s  %-33s   %-16.2f%s*\n",RESET, "CGST (9%)", cgst, BLUE);
    printf("*%s------------------------------------------------------%s*\n", YELLOW, BLUE);
    printf("*%s  %-33s   %-16.2f%s*\n", GREEN, "GRAND TOTAL", totalWithTax, BLUE);
    printf("*%s------------------------------------------------------%s*\n", YELLOW, BLUE);
    printf("*                                                      *\n");
    printf("*   %sThank you for dining with us! Have a great day!    %s*\n", RED, BLUE);
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf(RESET);
     printf("\n%s Press 5 to go back : %s",BLINKING_YELLOW,RESET);
        int choice;
        scanf("%d",&choice);
        int c;
        while ((c = getchar()) != '\n');
        if(choice==5){
            Customerloggedinpage(PASSHEADS,orderID,persons);
        }
        else{
            GenerateBill(PASSHEADS,orderID,persons);
        }
}



int main (){
    
    struct Menu *menuHead=loadMenu();
    struct Tables *tablesHead=loadTables();
    struct OrderHistory *orderHistoryHead=loadOrderHistory();
    struct CurrentOrders *currentOrdersHead=loadCurrentOrders();
    
    // int arr[30]={1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,20,20,10,5,4,3,2,1,10,10};
    // drawBarGraph(arr,30);

    OsSelectionPage(PASSHEADS);
    // GenerateBill(currentOrdersHead,menuHead,6);
    return 0;
}

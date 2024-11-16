#include<stdio.h>
#include<string.h>
#include "ui.h"
#include "linked_list.h"
#include<stdlib.h>
#define CLEAR_SCREEN system("clear");


int addMenuItem(char name[],float price,char allergens[],int type, int spice, int veg_nonveg ){

    if(type!=1&&type!=2&&type!=3 && type!=4){
        printf("Error with \'TYPE\'!\n");
        return -1;
    }
    
    if(veg_nonveg!=0&&veg_nonveg!=1&&veg_nonveg!=2){
        printf("Error with \'Veg or Nonveg\'!\n");
        return -1;
    }
    
    if(spice>=10||spice<=-10){
        printf("Error with \'Spice Level\'!\n");
        return -1;
    }

    if(strlen(name)==0){
        printf("Name of the dish is empty!\n");
        return -1;
    }

    if(strlen(allergens)==0){
        printf("Allergen(s) is(are) missing!\n");
        return -1;
    }

    if(price<0){
        printf("Price can not be negative!\n");
        return -1;
    }

    
    FILE *f;
    f=  fopen("menu.csv","a+");
    long long int lastID=0;
    long long int finalLastID=0;
    int read=1;
    rewind(f);
    // Retriving the last ItemID so that I can automatically assign new ItemID.
    while (1==1){
        char c=fgetc(f);
        if(c==EOF){break;}
        if(read>=1){
            lastID=lastID*10+((int)c-48);
            read++;
        }
        if(read==8){read=0;}
        if(c=='\n'){
            read=1;
            finalLastID=lastID;
            lastID=0;
        }
    }
    long long int itemID=(1000000*type)+(100000*spice)+(10000*veg_nonveg)+(finalLastID%10000)+1;
    fprintf(f,"%lld,%s,%0.2f,%s\n",itemID,name,price,allergens);
    fclose(f);
    return 0;
}

void printMenu(){
    CLEAR_SCREEN
            menuLogo();
            menuHeader();
 FILE *f;
    f=  fopen("menu.csv","r+");
    int counter=0;
    long long int id=0;
    char name[100];
    char price[20];
    char allergens[100];
    int counter2=0;
    int counter3=0;
    int counter4=0;
    int flag1=0;
    while (1==1){
        char c=fgetc(f);
        if(c==EOF){break;}
        if(c=='\n'){
            char idArr[8];
            for(int i=6;i>=0;i--){
                idArr[i]=(char)((id%10)+48);
                id=id/10;
            }
            idArr[7]='\0';
            char spice[2]={idArr[1],'\0'};
            int veg=idArr[2]-48;
            
            switch(idArr[0]){
                case '1':
                    menuRow(name,&idArr[3],spice,"Starter",allergens,price,veg);
                    break;
                case '2':
                    menuRow(name,&idArr[3],spice,"Main Course",allergens,price,veg);
                    break;
                case '3':
                    menuRow(name,&idArr[3],spice,"Dessert",allergens,price,veg);
                    break;
                case '4':
                    menuRow(name,&idArr[3],spice,"Beverage",allergens,price,veg);
                    break;    
                    
            }
            memset(name, 0, sizeof(name));
            memset(price, 0, sizeof(price));
            memset(allergens, 0, sizeof(allergens));
            allergens[counter3]='\0';
            counter=0;counter2=0;counter3=0;flag1=0;id=0;counter4=0;
            continue;
        }
        if(c==','){
            counter++;
            name[counter2]='\0';
            price[counter4]='\0';
            allergens[counter3]='\0';
            continue;
        }
        if(c=='.'){flag1=1;}
        switch(counter){
            case 0:
                id=id*10+(int)c-48;
                break;
            case 1:
                name[counter2]=c;
                counter2++;
                break;
            
            case 2:
                price[counter4]=c;
                counter4++;
                break;
            case 3:
                allergens[counter3]=c;
                counter3++;
                break;    
        }
       
    }   
    menuFooter();
}


void writeTable(NodeTable* head) {

    FILE* fptr = fopen("tables.csv", "w");
    if (!fptr) {

        fprintf(stderr, "\n\aFATAL ERROR! FILE NOT FOUND!\n");
        exit(EXIT_FAILURE);
    }

    NodeTable* temp = head;

    for (int i = 0; i < lenTable(head); i++) {

        fprintf(fptr, "%d,%d,%d\n", temp->table.number, temp->table.capacity, temp->table.available);
        temp = temp->next;
    }

    fclose(fptr);
    return;
}



// int main (){
//     printMenu();
//     return 0;
// }


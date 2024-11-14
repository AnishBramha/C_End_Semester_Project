#include<stdio.h>
#include<string.h>
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





int main (){
    char name[]="Red Sauce Pasta";
    float price=149.99;
    char allergens[]="Lactose Gluten";

    addMenuItem(name,price,allergens,1,3,2);
    return 0;
}


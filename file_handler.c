#include<stdio.h>

void addMenuItem(char name[],float price,char allergens[],int type, int spice, int veg_nonveg ){
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
}

int main (){

    char name[]="Red Sauce Pasta";
    float price=149.99;
    char allergens[]="Lactose Gluten";

    addMenuItem(name,price,allergens,2,3,4);
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEM_NAME_WIDTH  21
#define MAX_ITEM_NO_WIDTH    8
#define MAX_SPICE_WIDTH      10
#define MAX_TYPE_WIDTH       8
#define MAX_ALLERGEN_WIDTH   15
#define MAX_PRICE_WIDTH      7


void logo(void){
    printf("   ____     ____            _   _             \n");
    printf("  / ___|   / ___|  ___  ___| |_(_) ___  _ __  \n");
    printf(" | |   ____\\___ \\ / _ \\/ __| __| |/ _ \\| '_ \\ \n");
    printf(" | |__|_____|__) |  __/ (__| |_| | (_) | | | | \n");
    printf("  \\____|   |____/ \\___|\\___|\\__|_|\\___/|_| |_| \n\n");
}


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



void menuHeader(){
    printf("+-----------------------+----------+------------+----------+-----------------+---------+\n");
    printf("|       Item Name       |  Item No |   Spice    |   Type   |   Allergen(s)   | Price   |\n");
    printf("+-----------------------+----------+------------+----------+-----------------+---------+\n");
          
}

int main(void){
    system("cls");
    logo();
    menuHeader();
    menuRow("Red Sauce Pasta","23094","9","Beverage","Nothing much","38.32");
    menuRow("Lasagne alla Bolognese With Extra CHeese","23094","9","Beverage","Nothing much","38.32");
    menuRow("Pizza Is good","23094","9","Beverage","Glutent Lactose Something Dsometihign something","38.32");
    menuRow("Red Sauce Pasta","23094","9","Beverage","Nothing much","38.32");
    printf("\n\n");

    // If the name of dish or allergens exceed the coloumn width , it will automatically get printed in the next line
    return 0;
}


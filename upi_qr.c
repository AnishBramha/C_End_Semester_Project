#include "qrencode.h"
#include "ui.h"
#include <stdio.h>

void showDynamicUPIQR(HEADS,long long int OID,int persons,float amount) {

    ClearScreen();
    // Build the UPI string
    char upi_url[512];
    snprintf(upi_url, sizeof(upi_url), 
             "upi://pay?pa=aryansharma0305@okaxis&pn=Aryan&am=%f&cu=INR", amount);

    // Generate QR code
    QRcode *qrcode = QRcode_encodeString(upi_url, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (qrcode == NULL) {
        fprintf(stderr, "Failed to generate QR Code\n");
        return;
    }
    
    printf("██████████████████████████████████████████████████████████████████████\n");
    // Print QR code to terminal as ASCII
    for (int y = 0; y < qrcode->width; y++) {
        printf("██");
        for (int x = 0; x < qrcode->width; x++) {
            printf((qrcode->data[y * qrcode->width + x] & 1) ? "  " : "██");
        }
        printf("██");
        putchar('\n');
    }
    
    printf("██████████████████████████████████████████████████████████████████████\n");

    // Free memory
    QRcode_free(qrcode);
    printf("%s\n Press 5 to go back : %s %s",BLINKING_YELLOW,RESET,RED);
    int i;
    scanf("%d",&i);
    printf("\033[0m");
    int c;
    while ((c = getchar()) != '\n');
    
    Customerloggedinpage(PASSHEADS,OID,persons);

}

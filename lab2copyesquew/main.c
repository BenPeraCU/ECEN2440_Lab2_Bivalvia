/**
 * main.c - Runs blink.c and scan.c
**/
#include "msp.h"
#include <stdio.h>

void blink()
{
    P1->DIR |= BIT0; //sets p1.0 as output
    P1->OUT &= ~BIT0; // sets bit0 to 0

    while(1){
        int i;
        P1->OUT |= BIT0; //Sets LED to HIGH (pin1.out = 1b)
        for(i = 0; i < 200000; i++); //Delays code
        P1->OUT &= ~BIT0; //Sets LED to LOW (pin1.out = 0b)
        for(i = 0; i < 200000; i++); //Delays code
    }

}


int scan() {

    int a = 0, b = 0;
    uint16_t *start = (uint16_t *)0x2001000A, *end = (uint16_t *)0x200103CC;

    while(start < end) {
        if( (*start) == 0xACCAu) { a++; }
        if( ((*start) == 0xABBAu) && (*start + 1) == 0xAFFAu) { b++; }
        start++;
    }

    printf("Value of a is: %d\nValue of b is: %d\n", a, b);

    return 0;
}


int main(int argsc, char *argsv[]) {

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    scan(); //scans subspace of SRAM looking for values

    blink(); //blinks an LED forever

    return 0;
}

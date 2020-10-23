//-----------------------------------------------------------------
//  Austin Moore
//  Homework 3
//  10/22/2020
//
//  Lights LEDs in a sequence depending on button switch pressed.
//  Uses Watchdog timer with interrupts enabled
//  Inputs: Three button switches
//  Outputs: Eight LEDs
//------------------------------------------------------------------
#include <msp430g2553.h>

int main(void)
{
    //--Configure Watchdog Timer

    WDTCTL = WDTPW + WDTTMSEL + WDTCNTCL;   // Enables password/ Sets timer mode/ Clears counter
    IE1 |= WDTIE;                           // Enable watchdog timer interrupt

    //--Configure ports

    P2SEL = 0;                              // Selects I/O function for P2
    P2SEL2 = 0;

    P2DIR = 0xFF;                           // Set all bits of P2 to output
    P2OUT = 0x00;                           // Turn off all LEDs

    P1DIR &= ~(BIT5 | BIT6 | BIT7);         // Set bits 5, 6, and 7 of P1 to input
    P1REN |= BIT5 | BIT6 | BIT7;            // Enables pullup/pulldown resistors of P1
    P1OUT &= ~(BIT5 | BIT6 | BIT7);         // Configures pulldown resistors of bits 5, 6 and 7 of p1

    _BIS_SR(LPM1_bits + GIE);               // Enable maskable interrupts and enter LPM1

    while(1){}                              // Run forever

    return 0;
}
//-----------------------------------------------------------------------------
//--Watchdog Timer Interrupt Handler

#pragma vector = WDT_VECTOR
__interrupt void watchdog_timer(void){

    //Sequence 1: LEDs light up sequentially from BIT 0
    //To BIT 7 then turn off
    if(P1IN & BIT5) {                       //If switch p1.5 is pushed
        P2OUT  = BIT0;
        __delay_cycles(100000);
        P2OUT |= BIT1;
        __delay_cycles(100000);
        P2OUT |= BIT2;
        __delay_cycles(100000);
        P2OUT |= BIT3;
        __delay_cycles(100000);
        P2OUT |= BIT4;
        __delay_cycles(100000);
        P2OUT |= BIT5;
        __delay_cycles(100000);
        P2OUT |= BIT6;
        __delay_cycles(100000);
        P2OUT |= BIT7;
        __delay_cycles(100000);
        P2OUT = 0X00;
    }
    //Sequence 2: LEDs light up sequentially inwards then
    //Turn off sequentially outwards
    else if(P1IN & BIT6) {                  //If switch P1.6 is pushed
        P2OUT = BIT0 | BIT7;
        __delay_cycles(100000);
        P2OUT |= BIT1 | BIT6;
        __delay_cycles(100000);
        P2OUT |= BIT2 | BIT5;
        __delay_cycles(100000);
        P2OUT |= BIT3 | BIT4;
        __delay_cycles(100000);
        P2OUT &= ~(BIT3 | BIT4);
        __delay_cycles(100000);
        P2OUT &= ~(BIT2 | BIT5);
        __delay_cycles(100000);
        P2OUT &= ~(BIT1 | BIT6);
        __delay_cycles(100000);
        P2OUT &= ~(BIT0 | BIT7);

    }
    //Sequence 3: LEDs light up sequentially from BIT 7
    //To BIT 0 then turn off
    else if(P1IN & BIT7) {                  //If switch P1.7 is pushed
        P2OUT  = BIT7;
        __delay_cycles(100000);
        P2OUT |= BIT6;
        __delay_cycles(100000);
        P2OUT |= BIT5;
        __delay_cycles(100000);
        P2OUT |= BIT4;
        __delay_cycles(100000);
        P2OUT |= BIT3;
        __delay_cycles(100000);
        P2OUT |= BIT2;
        __delay_cycles(100000);
        P2OUT |= BIT1;
        __delay_cycles(100000);
        P2OUT |= BIT0;
        __delay_cycles(100000);
        P2OUT = 0X00;
    }

    __delay_cycles(100000);
}

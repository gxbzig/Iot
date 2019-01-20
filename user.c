/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#ifdef __XC32
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include <sys/attribs.h>
#include <math.h>

 volatile static int sec_state = 0;
 volatile static int min_state = 0;
 volatile static int hou_state = 0;
/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/
void DelayMs(int t) {
    volatile long int count = t*33356;
    
    while (count--)
        ;
}
void InitTimer2(void) {
    T2CON = 0; // clear timer settings to defaults
    T3CON = 0;
    T2CONbits.TCKPS = 7; // divide clock by 256 with prescaler
    T2CONbits.T32 = 1;
    TMR2 = 0;
    PR2 = 0x0005F5E1; // 100 MHz / (256 * 1 Hz)
    // PR2 = 0x39062; // 100 MHz / (256 * 1 Hz)
    IPC3bits.T3IP = 3; // Priority level 3
    IPC3bits.T3IS = 0;
    
    IFS0bits.T3IF = 0; // Clear interrupt request flag
    IEC0bits.T3IE = 1; // Enable timer interrupt
}

void __ISR(_TIMER_3_VECTOR, IPL3SOFT) ISR_Timer_3 (void) {
   
    static int min_en = 0;
    static int hou_en = 0;
    
    if (sec_state > 58) {
		sec_state = 0;	
		min_en = 1;
	}
	else {
		sec_state++;
		min_en = 0;
	}
	
	if (min_en == 1){
		if (min_state > 58) {
			min_state = 0;	
			hou_en = 1;
		}
		else {
			min_state++;
			hou_en = 0;
		}
	}

	if (hou_en == 1){
		if (hou_state > 22) {
			hou_state = 0;	
		}
		else {
			hou_state++;
		}
	}
    // Reset interrupt flag
    IFS0bits.T3IF = 0;
}
int sec1(void) {
    return sec_state % 10;
}

int sec2(void) {
    return floor(sec_state / 10);
}

int min1(void) {
    return min_state % 10;
}

int min2(void) {
    return floor(min_state / 10);
}

int hou1(void) {
    return hou_state % 10;
}

int hou2(void) {
    return floor(hou_state / 10);
}

void InitGPIO(void) {
    /* Setup functionality and port direction */
    // LED output
    // Disable analog mode
    ANSELGbits.ANSG6 = 0;
    ANSELBbits.ANSB11 = 0;
    ANSELGbits.ANSG15 = 0;
    // Set directions to output
    TRISGbits.TRISG6 = 0;
    TRISBbits.TRISB11 = 0;
    TRISGbits.TRISG15 = 0;
    TRISDbits.TRISD4 = 0;

    // Turn off LEDs for initialization
    LD1_PORT_BIT = 0;
    LD2_PORT_BIT = 0;
    LD3_PORT_BIT = 0;
    LD4_PORT_BIT = 0;

    // Button inputs
    // Disable analog mode
    ANSELAbits.ANSA5 = 0;
    // Set directions to input
    TRISAbits.TRISA5 = 1;
    TRISAbits.TRISA4 = 1;
     
    TRISDCLR = 1<<11;
}

void InitApp(void) {
    // Initialize peripherals
    InitGPIO();
    OledHostInit();
    OledDspInit();
    InitTimer2();
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    T2CONbits.ON = 1;
}

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

/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/

void InitTimer2(void) {
    T2CON = 0; // clear timer settings to defaults
    T2CONbits.TCKPS = 7; // divide clock by 256 with prescaler
    TMR2 = 0;
    PR2 = 390625; // 100 MHz / (256 * 1 Hz)
    
    IPC2bits.T2IP = 1; // Priority level 1
    IPC2bits.T2IS = 0;
    
    IFS0bits.T2IF = 0; // Clear interrupt request flag
    IEC0bits.T2IE = 1; // Enable timer interrupt
}

void __ISR(_TIMER_2_VECTOR, IPL3SOFT) ISR_Timer_2 (void) {
    volatile int sec_state = 0;
    volatile int min_state = 0;
    volatile int hou_state = 0;

    static int min_en = 0;
    static int hou_en = 0;
    
    if (sec_state==59) {
		sec_state = 0;	
		min_en = 1;
	}
	else {
		sec_state++;
		min_en = 0;
	}
	
	if (min_en == 1){
		if (min_state==59) {
			min_state = 0;	
			hou_en = 1;
		}
		else {
			min_state++;
			hou_en = 0;
		}
	}

	if (hou_en == 1){
		if (hou_state==23) {
			hou_state = 0;	
		}
		else {
			hou_state++;
		}
	}
    // Reset interrupt flag
    IFS0bits.T2IF = 0;
}

void InitGPIO(void) {
    // Button inputs
    // Disable analog mode
    ANSELAbits.ANSA5 = 0;
    // Set directions to input
    TRISAbits.TRISA5 = 1;
}

void InitApp(void) {
    // Initialize peripherals
    InitGPIO();
    InitTimer2();
    
    // Set Interrupt Controller for multi-vector mode
    INTCONSET = _INTCON_MVEC_MASK;
    // Globally enable interrupts
    __builtin_enable_interrupts();
    // Enable peripherals which can generate an interrupt
    T2CONbits.ON = 1; // Start Timer 2
}

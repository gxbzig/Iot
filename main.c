/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "user.h"           /* User funct/params, such as InitApp             */
#include "OLED.h"
#include "stdio.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{
    uint8_t pattern[5]= {0x0, 0x11, 0x99, 0xbb, 0xff};
   volatile char buffer[32];
    int n;
    /* Initialize I/O 
     * and Peripherals
     * for application */
    InitApp();
    OledDvrInit();
    OledSetDrawColor(1);
    OledSetDrawMode(modOledSet);
    OledSetFillPattern(OledGetStdPattern(3));

    while (1) {
        OledSetCursor(0, 0);
        sprintf(buffer, hou_state, "%:s", min_state, "%:s", sec_state);
        OledPutString(buffer);

    }

}

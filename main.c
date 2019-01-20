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
#include <math.h>
#define M_PI 3.14159265358979323846
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
    char buffer[32];
    int x1,y1,x2,y2,x3,y3;
    int n,i1=0,i2=0,i3=0;
    int s1,s2,m1,m2,h1,h2;
    /* Initialize I/O 
     * and Peripherals
     * for application */
    InitApp();
    
    OledDvrInit();
    
    OledSetDrawColor(1);
    OledSetDrawMode(modOledSet);
    OledSetFillPattern(OledGetStdPattern(3));
    

    while (1) {
        s1=sec1();
        s2=sec2();
        m1=min1();
        m2=min2();
        h1=hou1();
        h2=hou2();
        OledSetCursor(0, 0);
        sprintf(buffer,"%d%d%c%d%d%c%d%d ",h2,h1,':',m2,m1,':',s2,s1);
        OledPutString(buffer);

        OledMoveTo(96,16);
        OledSetDrawColor(0);
        x1 = 96 + 15*cos(2*M_PI*i1/60.0);
        y1 = 16 + 15*sin(2*M_PI*i1/60.0);
        x2 = 96 + 15*cos(2*M_PI*i2/60.0);
        y2 = 16 + 15*sin(2*M_PI*i2/60.0);
        x3 = 96 + 15*cos(2*M_PI*i3/24.0);
        y3 = 16 + 15*sin(2*M_PI*i3/24.0);
        OledLineTo(x1, y1);
        OledMoveTo(96,16);
        OledLineTo(x2, y2);
        OledMoveTo(96,16);
        OledLineTo(x3, y3);
        i1 = s2*10 + s1 + 45;
        i2 = m2*10 + m1 + 45;
        i3 = h2*10 + h1 + 18;
        OledSetDrawColor(1);
        OledMoveTo(96,16);
        x1 = 96 + 15*cos(2*M_PI*i1/60.0);
        y1 = 16 + 15*sin(2*M_PI*i1/60.0);
        x2 = 96 + 15*cos(2*M_PI*i2/60.0);
        y2 = 16 + 15*sin(2*M_PI*i2/60.0);
        x3 = 96 + 15*cos(2*M_PI*i3/24.0);
        y3 = 16 + 15*sin(2*M_PI*i3/24.0);
        OledLineTo(x1, y1);
        OledMoveTo(96,16);
        OledLineTo(x2, y2);
        OledMoveTo(96,16);
        OledLineTo(x3, y3);
        OledUpdate();
        
    }

}

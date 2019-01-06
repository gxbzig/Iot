/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include <stdint.h>

typedef uint8_t BYTE;

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

#define MASK(x) (1<<(x))

#if 0
/* ------------------------------------------------------------ */
/* Pin definitions for access to OLED control signals on chipKIT Uno32
*/
#define prtVddCtrl PORTF
#define bitVddCtrl MASK(6)

#define prtVbatCtrl PORTF
#define bitVbatCtrl MASK(5)

#define prtDataCmd PORTF
#define bitDataCmd MASK(4)

#define prtReset PORTG
#define bitReset MASK(9)
#endif

/* ------------------------------------------------------------ */
/* Pin definitions for access to OLED control signals on chipKIT wiFIRE
*/
#define prtVddCtrl PORTD
#define bitVddCtrl MASK(12)

#define prtVbatCtrl PORTD
#define bitVbatCtrl MASK(15)

#define prtDataCmd PORTD
#define bitDataCmd MASK(14)

#define prtReset PORTG
#define bitReset MASK(9)
/* ------------------------------------------------------------ */
/* Symbols describing the geometry of the display. 
 */
#define cbOledDispMax 512 //max number of bytes in display buffer
#define ccolOledMax 128 //number of display columns
#define crowOledMax 32 //number of display rows
#define cpagOledMax 4 //number of display memory pages

#define	cbOledChar		8		//font glyph definitions is 8 bytes long
#define	chOledUserMax	0x20	//number of character defs in user font table
#define	cbOledFontUser	(chOledUserMax*cbOledChar)

/* Graphics drawing modes.
*/
#define	modOledSet		0
#define	modOledOr		1
#define	modOledAnd		2
#define	modOledXor		3

/* ------------------------------------------------------------ */
/* This array is the off-screen frame buffer used for rendering.
** It isn't possible to read back from the OLED display device,
** so display data is rendered into this off-screen buffer and then
** copied to the display.
*/
BYTE rgbOledBmp[cbOledDispMax];



// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation
void	OledInit();
void    OledDvrInit();
void	OledTerm();
void	OledDisplayOn();
void	OledDisplayOff();
void	OledClear();
void	OledClearBuffer();
void	OledUpdate();

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


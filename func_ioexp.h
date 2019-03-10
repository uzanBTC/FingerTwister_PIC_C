/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * Processor:       PIC18F2550
 * Compiler:        XC8 1.35+
 * Author:          Jeroen Van Aken
 * Updated:         24/02/2017
 ********************************************************************/

#ifndef _FUNC_IOEXP_
#define	_FUNC_IOEXP_

/** I N C L U D E S *************************************************/  
#include "config.h"

#if ENABLE_IOEXP == TRUE

/** P U B L I C   P R O T O T Y P E S *******************************/
void IOEXP_init(void);
unsigned char IOEXP_send(unsigned char data, unsigned char dest);

#endif

#endif


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

/** I N C L U D E S *************************************************/
#include "func_ioexp.h"

/** D E F I N E S ***************************************************/
#define IO_OPCODE   0b01000000
#define IO_IOCON    0x05
#define IO_IOCON_value 0b00001000
#define IO_TRIS     0x00
#define IO_LAT      0x0A
#define IO_WRITE    0
#define IO_READ     1

/** P U B L I C   V A R I A B L E S *********************************/
// in order for the variable to be used in other file, it also has to
// be declared as 'extern' in the corresponding .h file


/** P R I V A T E   V A R I A B L E S *******************************/
// 'static' implies that the variable can only be used in this file
// (cfr. 'private' in Java)


/** P R I V A T E   P R O T O T Y P E S *****************************/
// 'static' implies that the function can only be used in this file
// (cfr. 'private' in Java)
static unsigned char SPI_send(unsigned char data);

/********************************************************************/
/** P U B L I C   D E C L A R A T I O N S ***************************/
/********************************************************************
 * Function:        void IOEXP_init(void)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Overview:        Initializes all registers for communication with
 *                  the IO expander
 ********************************************************************/
void IOEXP_init() {
    PIE1bits.SSPIE = 0;         // disable interrupt
    SSPSTATbits.SMP = 0;        // sample at middle
    SSPSTATbits.CKE = 1;        // transmit @ idle to active
	SSPCON1bits.WCOL = 0;       // clear collision
    SSPCON1bits.SSPOV = 0;      // clear overflow
    SSPCON1bits.SSPEN = 1;      // enable spi
    SSPCON1bits.CKP = 0;        // clk idle = low
    SSPCON1bits.SSPM = 0b0010;  // Fosc/64
    
    /* Configure all port for SPI communication */
    IOEXP_DATA = 0;
    IOEXP_CS = 1;
    IOEXP_CLK = 0;
  
    // initialize IOexpander 1 
    IOEXP_CS = 0;                 //CS low
    SPI_send(IO_OPCODE | (0 << 1) | IO_WRITE );
    SPI_send(IO_TRIS);
    SPI_send(0x00);     // set all as output
    IOEXP_CS = 1;                 //CS high
    Nop();
    IOEXP_CS = 0;                 //CS low
    SPI_send(IO_OPCODE | (0 << 1) | IO_WRITE );
    SPI_send(IO_IOCON);
    SPI_send(IO_IOCON_value);     // put hardware addressing IOexp ON
    IOEXP_CS = 1;                 //CS high
    
    // uncomment when 2 IOexpanders are used
    /*
    IOEXP_CS = 0;                 //CS low
    SPI_send(IO_OPCODE | (1 << 1) | IO_WRITE );
    SPI_send(IO_TRIS);
    SPI_send(0x00);     // set all as output
    IOEXP_CS = 1;                 //CS high
    Nop();
    IOEXP_CS = 0;                 //CS low
    SPI_send(IO_OPCODE | (1 << 1) | IO_WRITE );
    SPI_send(IO_IOCON);
    SPI_send(IO_IOCON_value);     // put hardware addressing IOexp ON
    IOEXP_CS = 1;                 //CS high
    */
    
    // uncomment when 3 IOexpanders are used
    /*
    IOEXP_CS = 0;                 //CS low
    SPI_send(IO_OPCODE | (2 << 1) | IO_WRITE );
    SPI_send(IO_TRIS);
    SPI_send(0x00);     // set all as output
    IOEXP_CS = 1;                 //CS high
    Nop();
    IOEXP_CS = 0;                 //CS low
    SPI_send(IO_OPCODE | (2 << 1) | IO_WRITE );
    SPI_send(IO_IOCON);
    SPI_send(IO_IOCON_value);     // put hardware addressing IOexp ON
    IOEXP_CS = 1;                 //CS high
    */
}

/********************************************************************
 * Function:        unsigned char IOEXP_send(...)
 * PreCondition:    IOEXP_init()
 * Input:           data :  the 8 bits (1 byte) that need to set the outputs
 *                  dest :  the address of the IO expander
 * Output:          0 if everything was OK, 1 in case the previous data was not 
 *                  yet fully send.
 * Overview:        Prepares the data bytes for sending
 ********************************************************************/
unsigned char IOEXP_send(unsigned char data, unsigned char dest) {
    dest = (IO_OPCODE | ((dest & 0x03) << 1) | IO_WRITE);  // set the correct mode
    IOEXP_CS = 0;                 //CS low
    if (SPI_send(dest) == 1) return 1;  //device address    
    SPI_send(IO_LAT);
    SPI_send(data);
    IOEXP_CS = 1;                 //CS high
    return 0;
}

/********************************************************************/
/** P R I V A T E   D E C L A R A T I O N S *************************/
/********************************************************************
 * Function:        void SPI_send(unsigned char data)
 * PreCondition:    IOEXP_init()
 * Input:           data: the 8 bits (1 byte) of data
 * Output:          0 if everything was OK, 1 in case the previous data was not 
 *                  yet fully send.
 * Overview:        Will send the byte to the internal SPI module
 ********************************************************************/
static unsigned char SPI_send(unsigned char data) {
    PIR1bits.SSPIF = 0;
    SSPBUF = data;
    if (SSPCON1bits.WCOL == 1) {
        SSPCON1bits.WCOL = 0;
        return 1;   // you are already sending
    }
    while (PIR1bits.SSPIF == 0) { Nop(); };     // wait until finished
    return 0;
}

//EOF-----------------------------------------------------------------

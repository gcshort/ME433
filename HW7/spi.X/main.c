#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>
// DEVCFG0
#pragma config DEBUG = OFF // disable debugging
#pragma config JTAGEN = OFF // disable jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // disable flash write protect
#pragma config BWP = OFF // disable boot write protect
#pragma config CP = OFF // disable code protect

// DEVCFG1
#pragma config FNOSC = FRCPLL // use internal oscillator with pll
#pragma config FSOSCEN = OFF // disable secondary oscillator
#pragma config IESO = OFF // disable switching clocks
#pragma config POSCMOD = OFF // internal RC
#pragma config OSCIOFNC = OFF // disable clock output
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD	 // disable clock switch and FSCM
#pragma config WDTPS = PS1048576 // use largest wdt
#pragma config WINDIS = OFF // use non-window mode wdt
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations

void ReadUART1(char * string, int maxLength);
void WriteUART1(const char * string);
void initSPI();
unsigned char spi_io(unsigned char o);

int main() {

    __builtin_disable_interrupts(); // disable interrupts while initializing things

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;

    // do your TRIS and LAT commands here
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 0;
    TRISBbits.TRISB4 = 1;
    
    
    U1RXRbits.U1RXR = 0b0001; //sets B6 to RX
    RPB7Rbits.RPB7R = 0b0001; //sets B7 to TX
    
     // turn on UART3 without an interrupt
    U1MODEbits.BRGH = 0; // set baud to NU32_DESIRED_BAUD
    U1BRG = ((48000000 / 115200) / 16) - 1;

    // 8 bit, no parity bit, and 1 stop bit (8N1 setup)
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;

     // configure TX & RX pins as output & input pins
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    // enable the uart
    U1MODEbits.ON = 1;
  
    initSPI();
    __builtin_enable_interrupts();
    char m[100];
    int i =0;
    unsigned char a = 0;
    unsigned char b = 1;
    unsigned short v[100] = {0,
 81,
 163,
 245,
 327,
 409,
 491,
 573,
 655,
 737,
 819,
 901,
 983,
 1064,
 1146,
 1228,
 1310,
 1392,
 1474,
 1556,
 1638,
 1720,
 1802,
 1884,
 1966,
 2048,
 2129,
 2211,
 2293,
 2375,
 2457,
 2539,
 2621,
 2703,
 2785,
 2867,
 2949,
 3031,
 3112,
 3194,
 3276,
 3358,
 3440,
 3522,
 3604,
 3686,
 3768,
 3850,
 3932,
 4014,
 4095,
 4014,
 3932,
 3850,
 3768,
 3686,
 3604,
 3522,
 3440,
 3358,
 3276,
 3194,
 3112,
 3031,
 2949,
 2867,
 2785,
 2703,
 2621,
 2539,
 2457,
 2375,
 2293,
 2211,
 2129,
 2048,
 1966,
 1884,
 1802,
 1720,
 1638,
 1556,
 1474,
 1392,
 1310,
 1228,
 1146,
 1064,
 983,
 901,
 819,
 737,
 655,
 573,
 491,
 409,
 327,
 245,
 163,
 81};
    
    unsigned short vs[50] = {2048,2305,2557,2802,3035,3252,3450,3626,
3777,3901,3996,4060,4092,4092,4060,3996,
3901,3777,3626,3450,3252,3035,2802,2557,
2305,2048,1791,1539,1294,1061,844,646,
470,319,195,100,36,4,4,36,
100,195,319,470,646,844,1061,1294,
1539,1791,2048};
    
    int ii = 0;
    unsigned short p;
    unsigned short q;
    while (1) {
        
        
        p = a << 15;
        p = p | (0b111 << 12);
        p = p | v[i];
        
        LATAbits.LATA0 = 0;
        spi_io((p>>8));
        spi_io(p);
        LATAbits.LATA0 = 1;
        
        i++;
        
        if (i == 100){
            i = 0;
        }
        
        q = b << 15;
        q = q | (0b111 << 12);
        q = q | vs[ii];
        
        
        LATAbits.LATA0 = 0;
        spi_io((q>>8));
        spi_io(q);
        LATAbits.LATA0 = 1;
        
        
        ii++;
        
        if (ii == 50){
            ii = 0;
        }
        
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 240000){
        }
        
        if(PORTBbits.RB4 == 0){
            _CP0_SET_COUNT(0);
            LATAbits.LATA4 = 1;
            while(_CP0_GET_COUNT() < 12000000){
            }
            _CP0_SET_COUNT(0);
            LATAbits.LATA4 = 0;
            while(_CP0_GET_COUNT() < 12000000){
            }
            _CP0_SET_COUNT(0);
            LATAbits.LATA4 = 1;
            while(_CP0_GET_COUNT() < 12000000){
            }
            LATAbits.LATA4 = 0;
            
            
            sprintf(m,"hello!\r\n");
            WriteUART1(m);
        }
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        // remember the core timer runs at half the sysclk

    }
}

// Read from UART3
// block other functions until you get a '\r' or '\n'
// send the pointer to your char array and the number of elements in the array
void ReadUART1(char * message, int maxLength) {
  char data = 0;
  int complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (U1STAbits.URXDA) { // if data is available
      data = U1RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}

// Write a character array using UART3
void WriteUART1(const char * string) {
  while (*string != '\0') {
    while (U1STAbits.UTXBF) {
      ; // wait until tx buffer isn't full
    }
    U1TXREG = *string;
    ++string;
  }
}

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    // Turn of analog pins
    ANSELA = 0;
    // Make an output pin for CS
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 =1;
    //...
    // Set SDO1
    RPA1Rbits.RPA1R = 0b0011; //A1
    // Set SDI1
    SDI1Rbits.SDI1R = 0b0001; //B5

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}

unsigned char spi_io(unsigned char o) {
    SPI1BUF = o;
    while (!SPI1STATbits.SPIRBF){
        ;
    }
    return SPI1BUF;
}
#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include "ws2812b.h"
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
    
    
    //U1RXRbits.U1RXR = 0b0001; //sets B6 to RX
    //RPB7Rbits.RPB7R = 0b0001; //sets B7 to TX
    
     // turn on UART3 without an interrupt
    //U1MODEbits.BRGH = 0; // set baud to NU32_DESIRED_BAUD
    //U1BRG = ((48000000 / 115200) / 16) - 1;

    // 8 bit, no parity bit, and 1 stop bit (8N1 setup)
    //U1MODEbits.PDSEL = 0;
    //U1MODEbits.STSEL = 0;

     // configure TX & RX pins as output & input pins
    //U1STAbits.UTXEN = 1;
    //U1STAbits.URXEN = 1;
    // enable the uart
    //U1MODEbits.ON = 1;
    ws2812b_setup();
    __builtin_enable_interrupts();
    
    char m[100];
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    while (1) {
        _CP0_SET_COUNT(0);
        
        while(_CP0_GET_COUNT() < 150000){
        }
            
            
            //sprintf(m,"hello!\r\n");
            //WriteUART1(m);
        wsColor color1 = HSBtoRGB(0 + i,1,0.1);
        wsColor color2 = HSBtoRGB(90 + j,1,0.1);
        wsColor color3 = HSBtoRGB(180 + k,1,0.1);
        wsColor color4 = HSBtoRGB(270 + l,1,0.1);
        
        wsColor color[4] = {color1,color2,color3,color4};
        ws2812b_setColor(&color,4);
        i += 1;
        j += 1;
        k += 1;
        l += 1;
        if(i == 360){
            i=0;
        }
        if(j == 270){
            j=-90;
        }
        if(k == 180){
            k=-180;
        }
        if(l == 90){
            l=-270;
        
        }
        
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        // remember the core timer runs at half the sysclk

    }
}

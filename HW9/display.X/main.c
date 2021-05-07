#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include "ST7789.h"
#include "spi.h"
#include "font.h"
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

  
    initSPI();
    LCD_init();
    __builtin_enable_interrupts();
    
    char m[100];
    float time = 0;
    int i = 0;
    float fps = 0;
    int x;
    int y;
    LCD_clearScreen(BLACK);
    while (1) {
        
        _CP0_SET_COUNT(0);
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        // remember the core timer runs at half the sysclk
        sprintf(m,"FPS %f",fps);
        char* q = m;
        drawString(28,100,WHITE,q);
        sprintf(m,"Hello World %d!",i);
        char* p = m;
        drawString(28,32,WHITE,p);
        int j = i;
        for(j;j>0;j--){
            LCD_drawPixel(20+j,50,WHITE);
            LCD_drawPixel(20+j,51,WHITE);
            LCD_drawPixel(20+j,52,WHITE);
        }
        i++;
        if(i>100){
            i =0;
            for(x = 20;x<121;x++){
                for(y = 50;y<53;y++){
                    LCD_drawPixel(x,y,BLACK);
                }
            }   
        }
       
        for(x = 85;x<110;x++){
            for(y = 32;y<40;y++){
                LCD_drawPixel(x,y,BLACK);
            }
        }
        for(x = 28;x<100;x++){
            for(y = 100;y<107;y++){
                LCD_drawPixel(x,y,BLACK);
            }
        }
        
        
        time = (float) _CP0_GET_COUNT()/24000000;
        fps = 1/time;
    }
}


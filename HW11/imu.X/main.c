#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include "ST7789.h"
#include "spi.h"
#include "font.h"
#include "imu.h"
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

    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1;
    
    
    initSPI();
    LCD_init();
    imu_setup();
    __builtin_enable_interrupts();
    
    char m[100];
    float time = 0;
    int i = 0;
    float fps = 0;
    int x;
    int y;
    signed short data[14];
    LCD_clearScreen(BLACK);
    while (1) {
        
     
        _CP0_SET_COUNT(0);
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        // remember the core timer runs at half the sysclk
        imu_read(IMU_OUT_TEMP_L,data,14);
        
        signed short temp = (data[1]<<8) | data[0];
        signed short gyro_x = data[3]<<8 | data[2];
        signed short gyro_y = data[5]<<8 | data[4];
        signed short gyro_z = data[7]<<8 | data[6];
        signed short accel_x = data[9]<<8 | data[8];
        signed short accel_y = data[11]<<8 | data[10];
        signed short accel_z = data[13]<<8 | data[12];
        if(0){                         
            sprintf(m,"GYRO %hi, %hi, %hi",gyro_x,gyro_y,gyro_z);
            char* s = m;
            drawString(28,10,WHITE,s);
            sprintf(m,"Accel %hi, %hi, %hi",accel_x,accel_y,accel_z);
            char* p = m;
            drawString(28,30,WHITE,p);
            sprintf(m,"Temp %hi",temp);
            char* o = m;
            drawString(28,50,WHITE,o);
            sprintf(m,"FPS %f",fps);
            char* q = m;
            drawString(28,100,WHITE,q);
            for(x = 28;x<100;x++){
                for(y = 100;y<107;y++){
                    LCD_drawPixel(x,y,BLACK);
                }
            }
            for(x = 28;x<150;x++){
                for(y = 10;y<17;y++){
                    LCD_drawPixel(x,y,BLACK);
                }
            }
            for(x = 28;x<155;x++){
                for(y = 30;y<37;y++){
                    LCD_drawPixel(x,y,BLACK);
                }
            }
            for(x = 28;x<90;x++){
                for(y = 50;y<56;y++){
                    LCD_drawPixel(x,y,BLACK);
                }
            }
        }
        else{
          
            
            y = -240* accel_x/32000 + 120;
            x = -240* accel_y/32000 +120;
                   
            if(x>120){
               
                for(i=120;i<x;i++){
                    LCD_drawPixel(i,119,RED);
                    LCD_drawPixel(i,120,RED);
                    LCD_drawPixel(i,121,RED);
                    }
            }
            else{
                for(i=x;i<120;i++){
                    LCD_drawPixel(i,119,RED);
                    LCD_drawPixel(i,120,RED);
                    LCD_drawPixel(i,121,RED);
                
                    }
            }
            
            if(y>120){
               
                for(i=120;i<y;i++){
                    LCD_drawPixel(119,i,YELLOW);
                    LCD_drawPixel(120,i,YELLOW);
                    LCD_drawPixel(121,i,YELLOW);
                    }
            }
            else{
                for(i=y;i<120;i++){
                    LCD_drawPixel(119,i,YELLOW);
                    LCD_drawPixel(120,i,YELLOW);
                    LCD_drawPixel(121,i,YELLOW);
                
                    }
            }
            
            
            
            for(x = 119;x<122;x++){
                for(y = 0;y<241;y++){
                    LCD_drawPixel(x,y,BLACK);
                }
            }
            for(x = 0;x<241;x++){
                for(y = 119;y<122;y++){
                    LCD_drawPixel(x,y,BLACK);
                }
            }
            
        }
        time = (float) _CP0_GET_COUNT()/24000000;
        fps = 1/time;
    }
}


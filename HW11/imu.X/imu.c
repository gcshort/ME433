#include "imu.h"
#include "i2c_master_noint.h"
void imu_setup(){
    
    i2c_master_setup();
    unsigned char who = 0;
    //read from imu who am i
    
    who = read(0x0f);
    
    if(who != 0b01101001){
        while(1){
        _CP0_SET_COUNT(0);
        LATAbits.LATA4 = 1;
        while(_CP0_GET_COUNT() < 1500000){
        }
        _CP0_SET_COUNT(0);
        LATAbits.LATA4 = 0;
        while(_CP0_GET_COUNT() < 1500000){
        }
        }
    }
    write(IMU_CTRL1_XL,0b10000010); // set accel rate to 1.66 kHz, 2g sensitivity, 100hz filter
    write(IMU_CTRL2_G,0b10001000); //set gyro rate to 1.66 kHz, 1000 dps
    write(IMU_CTRL3_C,0b00000100); //enable IF_INC
}





void imu_read(unsigned char reg, signed short * data, int len){
    
    i2c_master_start();
    
    i2c_master_send(0b11010100);
    i2c_master_send(reg);//where im reading from
    i2c_master_restart();
    i2c_master_send(0b11010101);
    int i;
    for(i=0;i<len-1;i++){
        data[i] = i2c_master_recv();
        i2c_master_ack(0);
    }
    data[len-1] = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
}
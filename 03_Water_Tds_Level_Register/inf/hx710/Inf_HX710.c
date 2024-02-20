#include "Inf_HX710.h"


void Inf_HX710_Init(void) {
    
    // 初始化GPIO端口
    Driver_GPIO_Init();

}


/**
 * @brief 读取水位传感器的值
 * 
 * @return uint32_t 
 */
uint32_t Inf_HX710_ReadValue(void) {

    uint32_t data = 0x0;

    SCK_L;
    // 等待芯片输出变低，表示数据准备好了
    while(OUT_READ);

    for(uint8_t i=0; i<24; i++) {
        SCK_H;
        Delay_us(5);
        SCK_L;
        data <<= 1;
        if(OUT_READ) {
            data |= 1;
        }
    }

    SCK_H;
    Delay_us(5);
    SCK_L;

    return data ^ 0x800000;

}



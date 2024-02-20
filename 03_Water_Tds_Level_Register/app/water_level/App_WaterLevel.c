#include "App_WaterLevel.h"
#include "Common_Debug.h"
#include "string.h"
#include "stdio.h"
#include "Inf_W25Q32.h"
#include "stdlib.h"

//#define CLEAR

void App_WaterLevel_Start(void) {

    Inf_HX710_Init();
    
    Inf_W25Q32_Init();
#ifdef CLEAR
    Inf_W25Q32_EraseSector(0, 0);
#endif
    // y=ax+b
    // 做校准
    App_WaterLevel_CalibrateI();

}

double a, b;
uint32_t y1, y2;
uint8_t len;    // 写入的数据的长度（字节数）
uint8_t buff[50] = {0}; // 存储要写入到flash中的数据
void App_WaterLevel_CalibrateI(void) {

    // 1.先从flash中读取a和b的值
    Inf_W25Q32_Read(0, 0, 0, &len, 1);
    if(len >0 && len<255) { // 表示曾经校准过

        Inf_W25Q32_Read(0, 0, 1, buff, len);
        // 按“#”切割字符串
        a = strtod(strtok((char *)buff, "#"), NULL);
        b = strtod(strtok(NULL, "#"), NULL);

        debug_printfln("a=%.2f, b=%.2f", a, b);

        return;
    }


    /*
            x表示水位
            y表示读到的那个电压值
        y=ax+b

        x=0         y1=b
        x=10cm      y2=10a+b

        a=(y2-y1)/10;
        b=y1

    */
   Inf_LCD_WriteAsciiString(10, 120, 24, "Start Calibrate...", RED, BLUE);
   Inf_LCD_WriteAsciiString(10, 164, 24, "Do not put into water, then press key3...", RED, BLUE);

    // 第一次按下按键
    Driver_GPIO_WaiteKey3Pressed();

    y1 = Inf_HX710_ReadValue();
    Inf_LCD_WriteAsciiString(10, 164, 24, "Please put into water 10cm, then Press key3...", RED, BLUE);
    debug_printfln("y1=%d", y1);
    // 第二次按下按键
    Driver_GPIO_WaiteKey3Pressed();
    y2 = Inf_HX710_ReadValue();

    b=y1;
    a=(y2-y1)/15.0;

    // debug_printfln("a=%.2f, b=%.2f", a, b);

    // 2.把a和b的值存储到flash中
        // 2.1 把数据长度写入
        sprintf((char *)buff, "%.2f#%.2f", a, b);
        // sizeof算的总空间长度， strlen算的有效字符的长度，'/0'为止
        len = strlen((char *)buff);
        debug_printfln("y2=%d  y1=%d", y2, y1);
        debug_printfln("%s len=%d", buff, len);
        Inf_W25Q32_EraseSector(0, 0);
        Inf_W25Q32_WritePage(0, 0, 0, &len, 1);
        Inf_W25Q32_WritePage(0, 0, 1, buff, len);

}   

double App_WaterLevel_ReadWaterLevel(void) {
    uint32_t y = Inf_HX710_ReadValue();
    return (y-b)/a;
}


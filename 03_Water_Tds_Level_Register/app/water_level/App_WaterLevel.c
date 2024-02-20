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
    // ��У׼
    App_WaterLevel_CalibrateI();

}

double a, b;
uint32_t y1, y2;
uint8_t len;    // д������ݵĳ��ȣ��ֽ�����
uint8_t buff[50] = {0}; // �洢Ҫд�뵽flash�е�����
void App_WaterLevel_CalibrateI(void) {

    // 1.�ȴ�flash�ж�ȡa��b��ֵ
    Inf_W25Q32_Read(0, 0, 0, &len, 1);
    if(len >0 && len<255) { // ��ʾ����У׼��

        Inf_W25Q32_Read(0, 0, 1, buff, len);
        // ����#���и��ַ���
        a = strtod(strtok((char *)buff, "#"), NULL);
        b = strtod(strtok(NULL, "#"), NULL);

        debug_printfln("a=%.2f, b=%.2f", a, b);

        return;
    }


    /*
            x��ʾˮλ
            y��ʾ�������Ǹ���ѹֵ
        y=ax+b

        x=0         y1=b
        x=10cm      y2=10a+b

        a=(y2-y1)/10;
        b=y1

    */
   Inf_LCD_WriteAsciiString(10, 120, 24, "Start Calibrate...", RED, BLUE);
   Inf_LCD_WriteAsciiString(10, 164, 24, "Do not put into water, then press key3...", RED, BLUE);

    // ��һ�ΰ��°���
    Driver_GPIO_WaiteKey3Pressed();

    y1 = Inf_HX710_ReadValue();
    Inf_LCD_WriteAsciiString(10, 164, 24, "Please put into water 10cm, then Press key3...", RED, BLUE);
    debug_printfln("y1=%d", y1);
    // �ڶ��ΰ��°���
    Driver_GPIO_WaiteKey3Pressed();
    y2 = Inf_HX710_ReadValue();

    b=y1;
    a=(y2-y1)/15.0;

    // debug_printfln("a=%.2f, b=%.2f", a, b);

    // 2.��a��b��ֵ�洢��flash��
        // 2.1 �����ݳ���д��
        sprintf((char *)buff, "%.2f#%.2f", a, b);
        // sizeof����ܿռ䳤�ȣ� strlen�����Ч�ַ��ĳ��ȣ�'/0'Ϊֹ
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


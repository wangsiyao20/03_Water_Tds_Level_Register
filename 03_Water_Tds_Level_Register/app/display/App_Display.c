#include "App_Display.h"
#include "stdio.h"


/**
 * @brief 启动显示模块
 * 
 */
void App_Display_Start(void) {
	// 初始化硬件接口层 ： LCD
    Inf_LCD_Init();
    // 清屏
    Inf_LCD_ClearAll(BLACK);  
}


/**
 * @brief test
 * 
 */
void App_Display_ShowLogo(void) {
    Inf_LCD_WriteAtguiguLogo(57, 5);
}

void App_Display_ShowTitle(void) {
    for(uint8_t i = 0; i<9; i++) {
        Inf_LCD_WriteChineseChar(i*32+16, 70, i, BLUE, BLACK);
    }
}

// TODO
// void App_Display_ShowTDS() {

// }

uint8_t d_buff[50];
void App_Display_ShowWaterLevel(double wl) {
    sprintf((char *)d_buff, "water_level=%.2f        ", wl);
    Inf_LCD_WriteAsciiString(10, 120, 24, d_buff, RED, BLACK);
}



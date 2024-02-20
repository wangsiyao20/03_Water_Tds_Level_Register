#include "Driver_GPIO.h"


void Driver_GPIO_Init(void) {

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // sck = PB12  时钟  配置为通用推挽输出  mode = 11;   cnf = 00
    GPIOB->CRH |= GPIO_CRH_MODE12;
    GPIOB->CRH &= ~GPIO_CRH_CNF12;

    // out = PB13  32从这里读   配置为浮空输入  mode = 00  cnf = 01
    GPIOB->CRH &= ~GPIO_CRH_MODE13;
    GPIOB->CRH = ((GPIOB->CRH | GPIO_CRH_CNF13_0) & ~GPIO_CRH_CNF13_1);

    // 按键3   PF10
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;
    // 下拉输入   mode  00       cnf  10
    GPIOF->CRH &= ~GPIO_CRH_MODE10;
    GPIOF->CRH = (GPIOF->CRH | GPIO_CRH_CNF10_1) & (~GPIO_CRH_CNF10_0);
    GPIOF->ODR &= ~GPIO_ODR_ODR10;

}


/**
 * @brief 等待按键sw4被按下次
 * 
 */
void Driver_GPIO_WaiteKey3Pressed(void) {
    while(1) {
        while(!(GPIOF->IDR & GPIO_IDR_IDR10));
        Delay_ms(200);
        if(GPIOF->IDR & GPIO_IDR_IDR10) {
            return;
        }

    }
}


#include "Driver_SPI.h"

void Driver_SPI_Init(void)
{
    /* 1. 开启SPI1的时钟 开启GPIO时钟 PA和PC*/
    RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN);

    /* 2. 设置引脚的工作模式 */
    /* 2.1 cs: 通用推挽输出 PC13*  CNF=00 MODE=11 */
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;
    /* 2.2 sck: 推挽输出 PA5*/ /* cnf=10  mode=11 */
    /* 2.3 mosi: 推挽输出 PA7*/
    GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF5_1);
    GPIOA->CRL &= ~(GPIO_CRL_CNF5_0 | GPIO_CRL_CNF7_0);
    /* 2.4 miso: 浮空输入 PA6  CNF=01 MODE=00*/
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    /* 3. SPI相关的配置 */
    /* 3.1 配置SPI1为主模式 */
    SPI1->CR1 |= SPI_CR1_MSTR;
    /* 3.2 NSS禁用, 从设备的片选使用普通的GPIO控制*/
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR2 &= ~SPI_CR2_SSOE;
    SPI1->CR1 |= SPI_CR1_SSI;
    /* 3.3 配置SPI的工作模式 模式0   时钟极性和相位*/
    SPI1->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);
    /* 3.4 配置波特率的分频系数 0=2分频 1=4分频 2=8分频 ....*/
    SPI1->CR1 &= ~SPI_CR1_BR;
    SPI1->CR1 |= SPI_CR1_BR_1;
    /* 3.5 配置数据帧的格式: 8为或16位 */
    SPI1->CR1 &= ~SPI_CR1_DFF;
    /* 3.6 配置LSB 或 MSB*/
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
    /* 3.7 使能SPI */
    SPI1->CR1 |= SPI_CR1_SPE;
}
void Driver_SPI_Start(void)
{
    CS_LOW;
}

void Driver_SPI_Stop(void)
{
    CS_HIGH;
}

uint8_t Driver_SPI_SwapByte(uint8_t byte)
{
    /* 1. 写数据到发送缓冲区 */
    /* 1.1 判断发送缓冲功区为空 */
    while ((SPI1->SR & SPI_SR_TXE) == 0)
        ;
    /* 1.2 把数据放入DR寄存器 */
    SPI1->DR = byte;
    /* 2. 读数据 */
    /* 2.1 先判断接收缓冲区非空 */
    while ((SPI1->SR & SPI_SR_RXNE) == 0)
        ;
    /* 2.1 从接收缓冲区读取数据 */
    return (uint8_t)(SPI1->DR & 0xff);
}

#include "Driver_SPI.h"

void Driver_SPI_Init(void)
{
    /* 1. ����SPI1��ʱ�� ����GPIOʱ�� PA��PC*/
    RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN);

    /* 2. �������ŵĹ���ģʽ */
    /* 2.1 cs: ͨ��������� PC13*  CNF=00 MODE=11 */
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;
    /* 2.2 sck: ������� PA5*/ /* cnf=10  mode=11 */
    /* 2.3 mosi: ������� PA7*/
    GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF5_1);
    GPIOA->CRL &= ~(GPIO_CRL_CNF5_0 | GPIO_CRL_CNF7_0);
    /* 2.4 miso: �������� PA6  CNF=01 MODE=00*/
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    /* 3. SPI��ص����� */
    /* 3.1 ����SPI1Ϊ��ģʽ */
    SPI1->CR1 |= SPI_CR1_MSTR;
    /* 3.2 NSS����, ���豸��Ƭѡʹ����ͨ��GPIO����*/
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR2 &= ~SPI_CR2_SSOE;
    SPI1->CR1 |= SPI_CR1_SSI;
    /* 3.3 ����SPI�Ĺ���ģʽ ģʽ0   ʱ�Ӽ��Ժ���λ*/
    SPI1->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);
    /* 3.4 ���ò����ʵķ�Ƶϵ�� 0=2��Ƶ 1=4��Ƶ 2=8��Ƶ ....*/
    SPI1->CR1 &= ~SPI_CR1_BR;
    SPI1->CR1 |= SPI_CR1_BR_1;
    /* 3.5 ��������֡�ĸ�ʽ: 8Ϊ��16λ */
    SPI1->CR1 &= ~SPI_CR1_DFF;
    /* 3.6 ����LSB �� MSB*/
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;
    /* 3.7 ʹ��SPI */
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
    /* 1. д���ݵ����ͻ����� */
    /* 1.1 �жϷ��ͻ��幦��Ϊ�� */
    while ((SPI1->SR & SPI_SR_TXE) == 0)
        ;
    /* 1.2 �����ݷ���DR�Ĵ��� */
    SPI1->DR = byte;
    /* 2. ������ */
    /* 2.1 ���жϽ��ջ������ǿ� */
    while ((SPI1->SR & SPI_SR_RXNE) == 0)
        ;
    /* 2.1 �ӽ��ջ�������ȡ���� */
    return (uint8_t)(SPI1->DR & 0xff);
}

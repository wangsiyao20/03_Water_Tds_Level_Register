#include "Driver_USART1.h"

/**
 * @description: ����1��ʼ��
 */
void Driver_USART1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* �������� PA9=Tx  mode=11  cnf=10*/
    GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    /* �������� PA10=Rx mode=00 cnf=01 */
    GPIOA->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10);
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    /* ������ 115200*/
    USART1->BRR = 0x271;

    /* ����һ���ֵĳ��� 8λ */
    USART1->CR1 &= ~USART_CR1_M;
    /* ���ò���ҪУ��λ */
    USART1->CR1 &= ~USART_CR1_PCE;
    /* ����ֹͣλ�ĳ��� */
    USART1->CR2 &= ~USART_CR2_STOP;

    /* ʹ�ܷ��� */
    USART1->CR1 |= USART_CR1_TE;
}

/**
 * @description: ��������1

 */
void Driver_USART1_Start(void) { USART1->CR1 |= USART_CR1_UE; }

/**
 * @description: ֹͣ����1

 */
void Driver_USART1_Stop(void) { USART1->CR1 &= ~USART_CR1_UE; }

/**
 * @description: ʹ�ô���1����һ���ַ�
 * @param {uint8_t} c
 */
void Driver_USART1_SendChar(uint8_t c)
{
    while((USART1->SR & USART_SR_TXE) == 0)
        ;
    USART1->DR = c;
}

/**
 * @description: ʹ�ô���1����һ���ַ���
 * @param {uint8_t} *str
 * @param {uint16_t} len
 */
void Driver_USART1_SendString(uint8_t *str, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        Driver_USART1_SendChar(str[i]);
    }
}

int fputc(int c, FILE *file)
{
    Driver_USART1_SendChar((uint8_t)c);
    return c;
}

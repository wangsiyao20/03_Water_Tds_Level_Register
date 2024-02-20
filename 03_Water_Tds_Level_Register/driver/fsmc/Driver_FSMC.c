#include "Driver_FSMC.h"

void Driver_FSMC_GPIO_Init(void)
{
    /* 1 ���� A0-A18 ��ַ�˿ڵ����ģʽ �����������CNF:10 50MHz�ٶ� MODE:11*/
    /* =============MODE=============== */
    GPIOG->CRL |= GPIO_CRL_MODE0;
    /* =============CNF=============== */
    GPIOG->CRL |= GPIO_CRL_CNF0_1 ;
    GPIOG->CRL &= ~GPIO_CRL_CNF0_0;
    /*
        2 ���ݶ˿� �����������
            ��ʵ��Ӧ���У���ʹ�����߱�����Ϊ���ģʽ��FSMC��������Ȼ�ܹ����������ߵķ���ʹ������Ҫʱ��Ϊ�����ߡ�
            �����Զ��л�����FSMC������Ӳ������ģ�����Ҫ�����Ԥ��
            ��ˣ���ʹGPIO����Ϊ�������������FSMC��Ȼ����ʵ�ֶ�ȡ������
    */
    /* =============MODE=============== */
    GPIOD->CRL |= (GPIO_CRL_MODE0 |
                   GPIO_CRL_MODE1);
    GPIOD->CRH |= (GPIO_CRH_MODE8 |
                   GPIO_CRH_MODE9 |
                   GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE14 |
                   GPIO_CRH_MODE15);

    GPIOE->CRL |= (GPIO_CRL_MODE7);
    GPIOE->CRH |= (GPIO_CRH_MODE8 |
                   GPIO_CRH_MODE9 |
                   GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE11 |
                   GPIO_CRH_MODE12 |
                   GPIO_CRH_MODE13 |
                   GPIO_CRH_MODE14 |
                   GPIO_CRH_MODE15);

    /* =============CNF=============== */
    GPIOD->CRL |= (GPIO_CRL_CNF0_1 |
                   GPIO_CRL_CNF1_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0_0 |
                    GPIO_CRL_CNF1_0);

    GPIOD->CRH |= (GPIO_CRH_CNF8_1 |
                   GPIO_CRH_CNF9_1 |
                   GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF8_0 |
                    GPIO_CRH_CNF9_0 |
                    GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);

    GPIOE->CRL |= (GPIO_CRL_CNF7_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF7_0);

    GPIOE->CRH |= (GPIO_CRH_CNF8_1 |
                   GPIO_CRH_CNF9_1 |
                   GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF11_1 |
                   GPIO_CRH_CNF12_1 |
                   GPIO_CRH_CNF13_1 |
                   GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOE->CRH &= ~(GPIO_CRH_CNF8_0 |
                    GPIO_CRH_CNF9_0 |
                    GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF11_0 |
                    GPIO_CRH_CNF12_0 |
                    GPIO_CRH_CNF13_0 |
                    GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);


    /* 3 �������ƶ˿�  ����������� */
    /* 3.1 PD4: ����������  PD5�� д�������� */
    GPIOD->CRL |= (GPIO_CRL_MODE4 |
                   GPIO_CRL_MODE5);
    GPIOD->CRL |= (GPIO_CRL_CNF4_1 |
                   GPIO_CRL_CNF5_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF4_0 |
                    GPIO_CRL_CNF5_0);

    /* 3.2  PG12��NE4*/
    GPIOG->CRH |= (GPIO_CRH_MODE12);
    GPIOG->CRH |= (GPIO_CRH_CNF12_1);
    GPIOG->CRH &= ~(GPIO_CRH_CNF12_0);

    /* 3.3  ��������PB0��ͨ���������*/
    GPIOB->CRL |= GPIO_CRL_MODE0;
    GPIOB->CRL &= ~GPIO_CRL_CNF0;

    /* 3.4  ��������PG15��ͨ���������*/
    GPIOG->CRH |= GPIO_CRH_MODE15;
    GPIOG->CRH &= ~GPIO_CRH_CNF15;

}

void Driver_FSMC_Init(void)
{
    /* 1. ʱ�ӿ��� */
    RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN |
                     RCC_APB2ENR_IOPBEN |
                     RCC_APB2ENR_IOPEEN |
                     RCC_APB2ENR_IOPFEN |
                     RCC_APB2ENR_IOPGEN |
                     RCC_APB2ENR_AFIOEN);

    RCC->AHBENR |= RCC_AHBENR_FSMCEN;
    /* 2. �������ŵ�ģʽ������ */
    Driver_FSMC_GPIO_Init();
    /* 3. fsmc������ Bank1�� 4�� BCR4 */
    /* 3.1 �洢��ʹ�� */
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MBKEN;
    /* 3.2 ���ô洢���� 00=SRAM ROM*/
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MTYP;
    /* 3.3 ��ֹ������� */
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_FACCEN;
    /* 3.4 ��ַ�����ݸ���: ������ */
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MUXEN;
    /* 3.5 �������ߵĿ�� 16λ���=01 */
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MWID_1;
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MWID_0;
    /* 3.6 дʹ�� */;
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_WREN;

    /* 3. fsmc�� ʱ�� */
    /* 3.1 ��ַ����ʱ�� ��ͬ����д��˵,��Զһ������ */
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_ADDSET;
    /* 3.2 ��ַ����ʱ�� ��ͬ����д��˵,��Զһ������ */
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_ADDHLD;
    /* 3.3 ���ݱ���ʱ�� �ֲ᲻�ܵ���55ns ��������1us*/
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_DATAST;
    FSMC_Bank1->BTCR[7] |= (71 << 8);
    /* 3.4 ����ʱ��ģʽ */
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_ACCMOD;
}

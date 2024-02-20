#include "Inf_HX710.h"


void Inf_HX710_Init(void) {
    
    // ��ʼ��GPIO�˿�
    Driver_GPIO_Init();

}


/**
 * @brief ��ȡˮλ��������ֵ
 * 
 * @return uint32_t 
 */
uint32_t Inf_HX710_ReadValue(void) {

    uint32_t data = 0x0;

    SCK_L;
    // �ȴ�оƬ�����ͣ���ʾ����׼������
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



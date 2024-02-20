#include "Ads1115.h"
#include "Driver_I2C2.h"
#include "Common_Debug.h"

void Inf_ADS1115_Init(void) {
    // 1.��ʼ��I2C
    Driver_I2C2_Init();

    // 2.����ADS1115
    Inf_ADS1115_Config();
}


void Inf_ADS1115_Config(void) {
    uint16_t conf = 0x8583;

    // 1.����ģ���ź�ͨ��Ϊ0ͨ��
    conf &= ~ADS1115_REG_CONFIG_MUX_MASK;
    conf |= ADS1115_REG_CONFIG_MUX_SINGLE_0;

    // 2.�������棺�����̷�Χ
    conf &= ~ADS1115_REG_CONFIG_PGA_MASK;
    conf |= ADS1115_REG_CONFIG_PGA_4_096V;

    // 3.��������ת���� ��Ӧ��λ��Ϊ0
    conf &= ~ADS1115_REG_CONFIG_MODE_MASK;
    conf |= ADS1115_REG_CONFIG_MODE_CONTIN;

    // ����д��
    Driver_I2C2_Start();
    Driver_I2C_SendAddr(ADS1115_ADDRESS_W);
    Driver_I2C_SendByte(0x01);
    Driver_I2C_SendByte(conf >> 8);
    Driver_I2C_SendByte(conf & 0xff);

    Driver_I2C2_Stop();
}


/**
 * @brief ��ȡ�����ѹֵ
 * 
 * @return double 
 */
double Inf_ADS1115_ReadV(void) {
    Driver_I2C2_Start();
    Driver_I2C_SendAddr(ADS1115_ADDRESS_W);
    Driver_I2C_SendByte(0x00);
    Driver_I2C2_Stop();
    Driver_I2C2_Start();
    Driver_I2C_SendAddr(ADS1115_ADDRESS_R);

    uint16_t tmp = 0;
    tmp |= (Driver_I2C_ReadByte() << 8);
    Driver_I2C2_Ack();
    tmp |= Driver_I2C_ReadByte();
    Driver_I2C2_Ack();

    Driver_I2C2_Stop();
    debug_printfln("tmp=%d", tmp);
    return tmp * 4.096 / 32767;
}


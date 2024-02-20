#include "Inf_W25Q32.h"
/*
һ��64��(0-63) ÿ��16������(0-15)  ÿ������16ҳ(0-15)  ÿҳ256���ֽ�
*/
void Inf_W25Q32_Init(void)
{
    Driver_SPI_Init();
}

void Inf_W25Q32_ReadId(uint8_t* mid, uint16_t* did)
{

    Driver_SPI_Start();

    /* 1. ���� Jedec idָ�� */
    Driver_SPI_SwapByte(0x9f);

    /* 2. ��ȡ����id (���͵���������)*/
    *mid = Driver_SPI_SwapByte(0xff);

    /* 3. ��ȡ�豸id */
    *did = 0;
    *did |= Driver_SPI_SwapByte(0xff) << 8;
    *did |= Driver_SPI_SwapByte(0xff) & 0xff;

    Driver_SPI_Stop();
}

/**
 * @description: ��ȡ�ڲ��Ĵ�����busy,һֱ�ȵ���æ�ٽ�������
 * @return {*}
 */
void Inf_W25Q32_WaiteNotBusy(void)
{
    Driver_SPI_Start();
    Driver_SPI_SwapByte(0x05);

    while (Driver_SPI_SwapByte(0xff) & 0x01)
        ;
    Driver_SPI_Stop();
}

/**
 * @description: FLASHдʹ��  0x06
 * @return {*}
 */
void Inf_W25q32_WiteEnable(void)
{
    Driver_SPI_Start();
    Driver_SPI_SwapByte(0x06);
    Driver_SPI_Stop();
}

/**
 * @description: FLASHдʧ��  0x04
 * @return {*}
 */
void Inf_W25q32_WiteDisanable(void)
{
    Driver_SPI_Start();
    Driver_SPI_SwapByte(0x04);
    Driver_SPI_Stop();
}

/**
 * @description: ����ָ�����ڵ�ָ������
 *  һ��64��(0-63) ÿ��16������(0-15)  ÿ������16ҳ(0-15)  ÿҳ256���ֽ�
 * @param {uint8_t} block
 * @param {uint8_t} sector
 */
void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector)
{
    Inf_W25Q32_WaiteNotBusy();

    Inf_W25q32_WiteEnable();
    /* �����Ҫ�������������׵�ַ */
    uint32_t sectorAddr = block * 0x010000 + sector * 0x001000;

    Driver_SPI_Start();
    Driver_SPI_SwapByte(0x20);
    // 0000 0000 0000 0000 0000 0000
    Driver_SPI_SwapByte(sectorAddr >> 16 & 0xff);
    Driver_SPI_SwapByte(sectorAddr >> 8 & 0xff);
    Driver_SPI_SwapByte(sectorAddr & 0xff);
    Driver_SPI_Stop();

    Inf_W25q32_WiteDisanable();
}

/**
 * @description: ִ��ҳд�� д��ʱ,��ָ��ҳ���׵�ַ��ʼд��.
 * @param {uint8_t} block
 * @param {uint8_t} sector
 * @param {uint8_t} page
 * @param {uint8_t*} data
 * @param {uint16_t} len
 */
void Inf_W25Q32_WritePage(uint8_t block, uint8_t sector, uint8_t page, uint8_t* data, uint16_t len)
{
    Inf_W25Q32_WaiteNotBusy();

    Inf_W25q32_WiteEnable();
    /* �����Ҫд������ݵ�ҳ���׵�ַ */
    uint32_t pageAddr = block * 0x010000 + sector * 0x001000 + page * 0x000100;

    Driver_SPI_Start();
    Driver_SPI_SwapByte(0x02);

    Driver_SPI_SwapByte(pageAddr >> 16 & 0xff);
    Driver_SPI_SwapByte(pageAddr >> 8 & 0xff);
    Driver_SPI_SwapByte(pageAddr & 0xff);

    for (uint16_t i = 0; i < len; i++) {
        Driver_SPI_SwapByte(data[i]);
    }

    Driver_SPI_Stop();

    Inf_W25q32_WiteDisanable();
}

/**
 * @description: ��flash��ȡ����
 * @return {*}
 */
void Inf_W25Q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t* data, uint16_t len)
{
    Inf_W25Q32_WaiteNotBusy();

    uint32_t pageAddr = block * 0x010000 + sector * 0x001000 + page * 0x000100;

    Driver_SPI_Start();
    Driver_SPI_SwapByte(0x03);

    Driver_SPI_SwapByte(pageAddr >> 16 & 0xff);
    Driver_SPI_SwapByte(pageAddr >> 8 & 0xff);
    Driver_SPI_SwapByte(pageAddr & 0xff);
    for (uint16_t i = 0; i < len; i++) {
        data[i] = Driver_SPI_SwapByte(0xff);
    }

    Driver_SPI_Stop();
}
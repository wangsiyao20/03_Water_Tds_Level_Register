#include "Inf_LCD.h"
#include "Inf_LCD_Font.h"

void Inf_LCD_Reset(void)
{
    GPIOG->ODR &= ~GPIO_ODR_ODR15;
    Delay_ms(100);
    GPIOG->ODR |= GPIO_ODR_ODR15;
    Delay_ms(100);
}

/**
 * @description: ��LCD��������
 * @return {*}
 */
void Inf_LCD_BKOpen()
{
    GPIOB->ODR |= GPIO_ODR_ODR0;
}

/**
 * @description: �ر�LCD�ı���
 * @return {*}
 */
void Inf_LCD_BKClose()
{
    GPIOB->ODR &= ~GPIO_ODR_ODR0;
}

void Inf_LCD_WriteCmd(uint16_t cmd)
{
    *LCD_ADDR_CMD = cmd;
}

void Inf_LCD_WriteData(uint16_t data)
{
    *LCD_ADDR_DATA = data;
}

uint16_t Inf_LCD_ReadData(void)
{
    return *LCD_ADDR_DATA;
}

/* ��ʼ���Ĵ�����ֵ */
void Inf_LCD_RegConfig(void)
{
    /* 1. ���ûҽ׵�ѹ�Ե���TFT����٤�����ԣ� ��У׼��һ����������ú��� */
    Inf_LCD_WriteCmd(0xE0);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x07);
    Inf_LCD_WriteData(0x10);
    Inf_LCD_WriteData(0x09);
    Inf_LCD_WriteData(0x17);
    Inf_LCD_WriteData(0x0B);
    Inf_LCD_WriteData(0x41);
    Inf_LCD_WriteData(0x89);
    Inf_LCD_WriteData(0x4B);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x0C);
    Inf_LCD_WriteData(0x0E);
    Inf_LCD_WriteData(0x18);
    Inf_LCD_WriteData(0x1B);
    Inf_LCD_WriteData(0x0F);

    /* 2. ���ûҽ׵�ѹ�Ե���TFT����٤�����ԣ���У׼ */
    Inf_LCD_WriteCmd(0XE1);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x17);
    Inf_LCD_WriteData(0x1A);
    Inf_LCD_WriteData(0x04);
    Inf_LCD_WriteData(0x0E);
    Inf_LCD_WriteData(0x06);
    Inf_LCD_WriteData(0x2F);
    Inf_LCD_WriteData(0x45);
    Inf_LCD_WriteData(0x43);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x09);
    Inf_LCD_WriteData(0x32);
    Inf_LCD_WriteData(0x36);
    Inf_LCD_WriteData(0x0F);

    /* 3.  Adjust Control 3 (F7h)  */
    /*LCD_WriteCmd(0XF7);
   Inf_LCD_WriteData(0xA9);
   Inf_LCD_WriteData(0x51);
   Inf_LCD_WriteData(0x2C);
   Inf_LCD_WriteData(0x82);*/
    /* DSI write DCS command, use loose packet RGB 666 */

    /* 4. ��Դ����1*/
    Inf_LCD_WriteCmd(0xC0);
    Inf_LCD_WriteData(0x11); /* ��٤���ѹ */
    Inf_LCD_WriteData(0x09); /* ��٤���ѹ */

    /* 5. ��Դ����2 */
    Inf_LCD_WriteCmd(0xC1);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x03);

    /* 6. VCOM���� */
    Inf_LCD_WriteCmd(0XC5);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x80);

    /* 7. Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    Inf_LCD_WriteCmd(0xB1);
    Inf_LCD_WriteData(0xB0);
    Inf_LCD_WriteData(0x11);

    /* 8.  Display Inversion Control (B4h) ��������ѹ��ת�����ٵ�Ÿ��ţ�*/
    Inf_LCD_WriteCmd(0xB4);
    Inf_LCD_WriteData(0x02);

    /* 9.  Display Function Control (B6h)  */
    Inf_LCD_WriteCmd(0xB6);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0xA2);

    /* 10. Entry Mode Set (B7h)  */
    Inf_LCD_WriteCmd(0xB7);
    Inf_LCD_WriteData(0xc6);

    /* 11. HS Lanes Control (BEh) */
    Inf_LCD_WriteCmd(0xBE);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x04);

    /* 12.  Interface Pixel Format (3Ah) */
    Inf_LCD_WriteCmd(0x3A);
    Inf_LCD_WriteData(0x55); /* 0x55 : 16 bits/pixel  */

    /* 13. Sleep Out (11h) �ر�����ģʽ */
    Inf_LCD_WriteCmd(0x11);

    /* 14. ������Ļ�����RGB */
    Inf_LCD_WriteCmd(0x36);
    Inf_LCD_WriteData(0x08);

    Delay_ms(120);

    /* 14. display on */
    Inf_LCD_WriteCmd(0x29);
}

/**
 * @description: ��ʼ��LCD
 * @return {*}
 */
void Inf_LCD_Init(void)
{
    /* 1. ��ʼ��FSMC */
    Driver_FSMC_Init();
    /* 3. ����LCD */
    Inf_LCD_Reset();
    /* 4. �������� */
    Inf_LCD_BKOpen();
    /* 5. ��LCD��һЩ�������� */
    Inf_LCD_RegConfig();
}

/**
 * @description: ��ȡid, һ��������֤�����Ƿ�����
 */
uint32_t Inf_LCD_ReadId(void)
{
    uint32_t id = 0;
    /* ���ȷ��Ͷ�ȡID��ָ�� */
    Inf_LCD_WriteCmd(0x04);
    Inf_LCD_ReadData();
    id |= (Inf_LCD_ReadData() & 0xff) << 16;
    id |= (Inf_LCD_ReadData() & 0xff) << 8;
    id |= (Inf_LCD_ReadData() & 0xff);
    return id;
}
/**
 * @description:
 * @param {uint16_t} x �ַ���x����
 * @param {uint16_t} y �ַ���y����
 * @param {uint16_t} heigh �ַ��ĸ߶�. ����Ǹ߶ȵ�һ��
 * @param {uint8_t} c Ҫ��ʾ���ַ�
 * @param {uint16_t} fColor �ַ���ɫ
 * @param {uint16_t} bColor �ַ��ı���ɫ
 */
void Inf_LCD_WriteAsciiChar(uint16_t x,
                            uint16_t y,
                            uint16_t heigh,
                            uint8_t c,
                            uint16_t fColor,
                            uint16_t bColor)
{
    /* 1. ��ȷ������ */
    Inf_LCD_SetArea(x, y, heigh / 2, heigh);
    /* 2. ��ʾ�ַ� */
    // ������ʾ��ɫ��ָ��
    Inf_LCD_WriteCmd(0x2C);
    /* 2.1 ������ַ��ڶ�Ӧ�������е��±� */
    uint8_t index = c - ' ';
    /* 2.2 �ҵ�����ַ��ı��� */
    if (heigh == 16 || heigh == 12)
    {
        for (uint8_t i = 0; i < heigh; i++)
        {
            uint8_t tmp = heigh == 16 ? ascii_1608[index][i] : ascii_1206[index][i];
            /* �����ֽ��е�ÿһλ */
            for (uint8_t j = 0; j < heigh / 2; j++)
            {
                if (tmp & 0x01) // �����1��ʾǰ��ɫ
                {
                    Inf_LCD_WriteData(fColor);
                }
                else // ��ʾ����ɫ
                {
                    Inf_LCD_WriteData(bColor);
                }
                tmp >>= 1;
            }
        }
    }
    else if (heigh == 24)
    {
        for (uint8_t i = 0; i < 48; i++)
        {
            uint8_t tmp = ascii_2412[index][i];
            uint8_t jCount = i % 2 ? 4 : 8; /* �����±��ʱ��,ֻ��Ҫ������4λ */
            for (uint8_t j = 0; j < jCount; j++)
            {
                if (tmp & 0x01) // �����1��ʾǰ��ɫ
                {
                    Inf_LCD_WriteData(fColor);
                }
                else // ��ʾ����ɫ
                {
                    Inf_LCD_WriteData(bColor);
                }
                tmp >>= 1;
            }
        }
    }
    else if (heigh == 32)
    {
        for (uint8_t i = 0; i < 64; i++)
        {
            uint8_t tmp = ascii_3216[index][i];
            for (uint8_t j = 0; j < 8; j++)
            {
                if (tmp & 0x01) // �����1��ʾǰ��ɫ
                {
                    Inf_LCD_WriteData(fColor);
                }
                else // ��ʾ����ɫ
                {
                    Inf_LCD_WriteData(bColor);
                }
                tmp >>= 1;
            }
        }
    }
}

/**
 * @description: ����Ҫд���ַ�������
 * @param {int16_t} x
 * @param {uint16_t} y
 * @return {*}
 */
void Inf_LCD_SetArea(int16_t x,
                     uint16_t y,
                     uint16_t w,
                     uint16_t h)
{
    /* 1. ������ */
    Inf_LCD_WriteCmd(0x2a);
    /* 1.1 ��ʼ�� */
    Inf_LCD_WriteData(x >> 8);   /* �еĸ�λ */
    Inf_LCD_WriteData(x & 0xff); /* �е�λ */
    /* 1.2 ������ */
    Inf_LCD_WriteData((x + w - 1) >> 8);
    Inf_LCD_WriteData((x + w - 1) & 0xff);

    /* 2. ������ */
    Inf_LCD_WriteCmd(0x2b);
    /* 2.1 ��ʼ�� */
    Inf_LCD_WriteData(y >> 8);
    Inf_LCD_WriteData(y & 0xff);
    /* 2.2 ������ */
    Inf_LCD_WriteData((y + h - 1) >> 8);
    Inf_LCD_WriteData((y + h - 1) & 0xff);
}

/**
 * @description: ����Ļ���Ϊָ������ɫ
 * @param {uint16_t} color
 */
void Inf_LCD_ClearAll(uint16_t color)
{
    Inf_LCD_SetArea(0, 0, 320, 480);
    Inf_LCD_WriteCmd(0x2C);
    for (uint32_t i = 0, count = 320 * 480; i < count; i++)
    {
        Inf_LCD_WriteData(color);
    }
}

void Inf_LCD_WriteAsciiString(uint16_t x,
                              uint16_t y,
                              uint16_t heigh,
                              uint8_t *c,
                              uint16_t fColor,
                              uint16_t bColor) // "abc"
{
    uint8_t i = 0;
    while (c[i] != '\0')
    {
        if (c[i] != '\n')
        {
            if (x + heigh / 2 > DISPLAY_W)
            {
                x = 0;
                y += heigh;
            }
            Inf_LCD_WriteAsciiChar(x, y, heigh, c[i], fColor, bColor);
            x += heigh / 2;
        }
        else
        {
            x = 0;
            y += heigh;
        }

        i++;
    }
}

void Inf_LCD_WriteChineseChar(uint16_t x,
                              uint16_t y,
                              uint8_t index,
                              uint16_t fColor,
                              uint16_t bColor)
{
    Inf_LCD_SetArea(x, y, 32, 32);

    Inf_LCD_WriteCmd(0x2C);

    for (uint16_t i = 0; i < 128; i++)
    {
        uint8_t tmp = chinese[index][i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (tmp & 0x01) // �����1��ʾǰ��ɫ
            {
                Inf_LCD_WriteData(fColor);
            }
            else // ��ʾ����ɫ
            {
                Inf_LCD_WriteData(bColor);
            }
            tmp >>= 1;
        }
    }
}

void Inf_LCD_WriteAtguiguLogo(uint16_t x, uint16_t y)
{
    Inf_LCD_SetArea(x, y, 206, 54);

    Inf_LCD_WriteCmd(0x2C);
    uint16_t len = sizeof(gImage_atguigu);
    for (uint16_t i = 0; i < len; i += 2)
    {
        uint16_t p = gImage_atguigu[i]  + (gImage_atguigu[i + 1] << 8);
        Inf_LCD_WriteData(p);
    }
}


// void Inf_LCD_WriteAtguiguLogo(uint16_t x, uint16_t y)
// {
//     Inf_LCD_SetArea(x, y, DISPLAY_W, DISPLAY_H);

//     Inf_LCD_WriteCmd(0x2C);
//     uint32_t len = sizeof(gImage_a);
//     for (uint32_t i = 0; i < len; i += 2)
//     {
//         uint16_t p = gImage_a[i]  + (gImage_a[i + 1] << 8);
//         Inf_LCD_WriteData(p);
//     }
// }


void Inf_LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t w, uint16_t color)
{
    Inf_LCD_SetArea(x, y, w, w);
    Inf_LCD_WriteCmd(0x2C);
    uint16_t count = w * w;
    for (uint16_t i = 0; i < count; i++)
    {
        Inf_LCD_WriteData(color);
    }
}
#include "stdio.h"

void Inf_LCD_DrawLine(uint16_t x1,
                      uint16_t y1,
                      uint16_t x2,
                      uint16_t y2,
                      uint16_t w,
                      uint16_t color)
{
    if (x1 == x2)
    {
        for (uint16_t y = y1; y <= y2; y++)
        {
            Inf_LCD_DrawPoint(x1, y, w, color);
        }
        return;
    }

    /*
        y = kx + b
            k = (y2 - y1)/(x2 - x1);
            b = y1 - k * x1
    */
    double k = 1.0 * (y2 - y1) / (x2 - x1);
    double b = y1 - k * x1;

    //printf("%d,%d,%d,%d\r\n", x1, y1,x2,y2);
    //printf("k=%f,d=%f\r\n", k, b);
    

    for (uint16_t x = x1; x <= x2; x++)
    {
        uint16_t y = (uint16_t)(k * x + b);
        Inf_LCD_DrawPoint(x, y, w, color);
    }
}

void Inf_LCD_DrawRectangle(uint16_t x1,
                           uint16_t y1,
                           uint16_t x2,
                           uint16_t y2,
                           uint16_t w,
                           uint16_t color)
{
    Inf_LCD_DrawLine(x1, y1, x2, y1, w, color);
    Inf_LCD_DrawLine(x2, y1, x2, y2, w, color);
    Inf_LCD_DrawLine(x1, y1, x1, y2, w, color);
    Inf_LCD_DrawLine(x1, y2, x2, y2, w, color);
}

void Inf_LCD_DrawCircle(uint16_t xCenter,
                        uint16_t yCenter,
                        uint16_t r,
                        uint16_t w,
                        uint16_t color)
{
    for (uint16_t angle = 0; angle < 360; angle++)
    {
        uint16_t x = xCenter + r * sin(angle * 3.14 / 180);
        uint16_t y = yCenter + r * cos(angle * 3.14 / 180);

        Inf_LCD_DrawPoint(x, y, w, color);
    }
}

void Inf_LCD_DrawCircle_1(uint16_t xCenter,
                          uint16_t yCenter,
                          uint16_t r,
                          uint16_t w,
                          uint16_t color)
{
    for (uint16_t angle = 0; angle < 90; angle++)
    {
        uint16_t s = r * sin(angle * 3.14 / 180);
        uint16_t c = r * cos(angle * 3.14 / 180);

        uint16_t x = xCenter + s;
        uint16_t y = yCenter + c;
        Inf_LCD_DrawPoint(x, y, w, color);

        x = xCenter - s;
        y = yCenter + c;
        Inf_LCD_DrawPoint(x, y, w, color);

        x = xCenter + s;
        y = yCenter - c;
        Inf_LCD_DrawPoint(x, y, w, color);

        x = xCenter - s;
        y = yCenter - c;
        Inf_LCD_DrawPoint(x, y, w, color);
    }
}

void Inf_LCD_DrawCircleFill(uint16_t xCenter,
                            uint16_t yCenter,
                            uint16_t r,
                            uint16_t w,
                            uint16_t BColor,
                            uint16_t FColor)
{
    for (uint16_t i = 0; i <= r; i++)
    {
        for (uint16_t angle = 0; angle < 360; angle++)
        {
            uint16_t x = xCenter + i * sin(angle * 3.14 / 180);
            uint16_t y = yCenter + i * cos(angle * 3.14 / 180);
            if (i == r)
            {
                Inf_LCD_DrawPoint(x, y, w, BColor);
            }
            else
            {
                Inf_LCD_DrawPoint(x, y, w, FColor);
            }
        }
    }
}

void Inf_LCD_DrawCircleFill_1(uint16_t xCenter,
                              uint16_t yCenter,
                              uint16_t r,
                              uint16_t w,
                              uint16_t BColor,
                              uint16_t FColor)
{

    for (uint16_t angle = 0; angle < 90; angle++)
    {
        uint16_t s = r * sin(angle * 3.14 / 180);
        uint16_t c = r * cos(angle * 3.14 / 180);

        uint16_t x1 = xCenter + s;
        uint16_t y1 = yCenter + c;
        Inf_LCD_DrawPoint(x1, y1, w, BColor);

        uint16_t x2 = xCenter - s;
        uint16_t y2 = yCenter + c;
        Inf_LCD_DrawPoint(x2, y2, w, BColor);

        Inf_LCD_DrawLine(x2 + w, y1, x1 - w, y2, w, FColor);

        x1 = xCenter + s;
        y1 = yCenter - c;
        Inf_LCD_DrawPoint(x1, y1, w, BColor);

        x2 = xCenter - s;
        y2 = yCenter - c;
        Inf_LCD_DrawPoint(x2, y2, w, BColor);

        Inf_LCD_DrawLine(x2 + w, y1, x1 - w, y2, w, FColor);
    }
}


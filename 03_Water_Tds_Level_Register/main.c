#include "stdint.h"
#include "stm32f10x.h" // Device header
#include "Common_Debug.h"
#include "App_Display.h"
#include "Inf_HX710.h"
#include "App_WaterLevel.h"


int main()
{
    debug_init();
    debug_printfln("ˮ��ˮλ��Ŀ...");

   // 1.������ʾģ��
   App_Display_Start();

//    // test
//    App_Display_ShowLogo();
//    App_Display_ShowTitle();

   Inf_HX710_Init();

   // ����ˮλ����
   App_WaterLevel_Start();

    while (1)
    {
      // ���ֵ�ѹֵ
      //  uint32_t value = Inf_HX710_ReadValue();
      //  debug_printfln("%d", value);
      //  Delay_s(1);

      // ˮλ
      double wl = App_WaterLevel_ReadWaterLevel();
      App_Display_ShowWaterLevel(wl);
      Delay_ms(500);
    }
}


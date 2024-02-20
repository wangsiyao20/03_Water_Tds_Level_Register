#include "stdint.h"
#include "stm32f10x.h" // Device header
#include "Common_Debug.h"
#include "App_Display.h"
#include "Inf_HX710.h"
#include "App_WaterLevel.h"
#include "App_Tds.h"



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

   // ����ˮ�ʲ���
   App_TDS_Start();

    while (1)
    {
      // ���ֵ�ѹֵ
      //  uint32_t value = Inf_HX710_ReadValue();
      //  debug_printfln("%d", value);
      //  Delay_s(1);

      // // ˮλ
      // double wl = App_WaterLevel_ReadWaterLevel();
      // App_Display_ShowWaterLevel(wl);

      // ��ȡTDS��ֵ
      double tds = App_TDS_CaculateTDS();
      App_Display_ShowTDS(tds);

      Delay_ms(1000);

    }
}


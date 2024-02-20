#include "stdint.h"
#include "stm32f10x.h" // Device header
#include "Common_Debug.h"
#include "App_Display.h"
#include "Inf_HX710.h"
#include "App_WaterLevel.h"


int main()
{
    debug_init();
    debug_printfln("水质水位项目...");

   // 1.启动显示模块
   App_Display_Start();

//    // test
//    App_Display_ShowLogo();
//    App_Display_ShowTitle();

   Inf_HX710_Init();

   // 开启水位测量
   App_WaterLevel_Start();

    while (1)
    {
      // 数字电压值
      //  uint32_t value = Inf_HX710_ReadValue();
      //  debug_printfln("%d", value);
      //  Delay_s(1);

      // 水位
      double wl = App_WaterLevel_ReadWaterLevel();
      App_Display_ShowWaterLevel(wl);
      Delay_ms(500);
    }
}


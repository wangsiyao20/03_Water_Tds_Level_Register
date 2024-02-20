#include "App_Tds.h"
#include "ads1115.h"



void App_TDS_Start(void) {
    Inf_ADS1115_Init();
}

double App_TDS_CaculateTDS(void) {
    double v = Inf_ADS1115_ReadV();

    double vv = v * v;
    double vvv = vv * v;
    return 66.71 * vv - 127.93 * vv + 428.7 * v;
}



#ifndef __APP_WATER_LEVEL_H__
#define __APP_WATER_LEVEL_H__

#include "Inf_HX710.h"
#include "Inf_LCD.h"

void App_WaterLevel_Start(void);

void App_WaterLevel_CalibrateI(void);

double App_WaterLevel_ReadWaterLevel(void);

#endif


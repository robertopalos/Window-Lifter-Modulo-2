#ifndef _PLL_H_
#define _PLL_H_
void DisableWatchdog(void);
void InitTimer(void);
void InitModesAndClock(void);
void InitPeriClkGen(void);
void InitSysclk(void);
void InitGPIO(void);
void InitLeds(void);
void InitHW(void);
void delay(vuint32_t tiempo);
#endif

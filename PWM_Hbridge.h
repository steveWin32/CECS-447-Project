#include "tm4c123gh6pm.h"
#include <stdint.h>

#define PF0 0x01
#define PF1 0x02
#define PF2 0x04
#define PF3 0x08
#define PF4 0x10
#define PF5 0x20
#define PF6 0x40
#define PF7 0x80

void PortF_Init(void);
void PF1_M1_PWM5_Init(uint16_t period, uint16_t duty);
void PF2_M1_PWM6_Init(uint16_t period, uint16_t duty);
void PF1_M1_PWM5_Duty(uint16_t duty);
void PF2_M1_PWM6_Duty(uint16_t duty);

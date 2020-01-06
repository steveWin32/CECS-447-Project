#include "PLL.h"
#include "PWM_Hbridge.h"
int main(void) {
	PLL_Init();
	PortF_Init();
	PF1_M1_PWM5_Init(40000, 20000);
  PF2_M1_PWM6_Init(40000, 20000);
	while (1) {
		
	}
}

void GPIOPortF_Handler(void){
	if ((GPIO_PORTF_RIS_R &PF0)){	
		
	}
	if ((GPIO_PORTF_RIS_R & PF4)){
	}
}
#include "PWM_Hbridge.h"

void PortF_Init(void) {
	SYSCTL_RCGC2_R |= 0x00000020;
	GPIO_PORTF_LOCK_R = 0x4C4F434B; 
	GPIO_PORTF_CR_R |= (PF0|PF1|PF2|PF3|PF4|PF5);
	GPIO_PORTF_DATA_R &= ~(PF0|PF1|PF2|PF3|PF4|PF5); 
	GPIO_PORTF_AMSEL_R &= ~(PF0|PF1|PF2|PF3|PF4|PF5); 
	GPIO_PORTF_PCTL_R &= ~0xFFFFFFFF; 
  GPIO_PORTF_DIR_R &= ~(PF4|PF0);
	GPIO_PORTF_DIR_R |= (PF1|PF2|PF3|PF5);
	GPIO_PORTF_AFSEL_R &= ~(PF0|PF1|PF2|PF3|PF4|PF5); 
	GPIO_PORTF_DEN_R |= (PF0|PF1|PF2|PF3|PF4|PF5);
	GPIO_PORTF_PUR_R |= (PF4|PF0); 
	
	//Edge triggered interrupt
	GPIO_PORTE_RIS_R &= ~(PF4|PF0);
	GPIO_PORTE_IBE_R &= ~(PF4|PF0);
	GPIO_PORTE_IEV_R &= ~(PF4|PF0);
	GPIO_PORTE_ICR_R = (PF4|PF0);
	GPIO_PORTE_IM_R |= (PF4|PF0);
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;
	NVIC_EN0_R = 0x40000000;
}

void PF1_M1_PWM5_Init(uint16_t period, uint16_t duty) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;
  SYSCTL_RCGCPWM_R |= 0x01;  

	GPIO_PORTF_LOCK_R = 0x4C4F434B;   
  GPIO_PORTF_AFSEL_R |= 0x02; 
  GPIO_PORTF_PCTL_R &= ~0x000000F0; 
  GPIO_PORTF_PCTL_R |= 0x00000050;
  GPIO_PORTF_AMSEL_R &= ~0x02; 
  GPIO_PORTF_DEN_R |= 0x02;   
	
  SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV; 
  SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M; 
  SYSCTL_RCC_R += SYSCTL_RCC_PWMDIV_2;
	
  PWM1_2_CTL_R = 0;   //disable PWM
  PWM1_2_GENB_R = (PWM_0_GENB_ACTCMPBD_ONE |  PWM_0_GENB_ACTLOAD_ZERO ); 							
  PWM1_2_LOAD_R = period - 1; 
  PWM1_2_CMPB_R = duty - 1; 
  PWM1_2_CTL_R |= 0x00000001;   //Enable PWM
	PWM1_ENABLE_R |= 0x00000020;  //PWM5
}

void PF2_M1_PWM6_Init(uint16_t period, uint16_t duty) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;
  SYSCTL_RCGCPWM_R |= 0x02; 
	
	GPIO_PORTF_LOCK_R = 0x4C4F434B;  
  GPIO_PORTF_AFSEL_R |= 0x04;  
  GPIO_PORTF_PCTL_R &= ~0x00000F00; 
  GPIO_PORTF_PCTL_R |= 0x00000500;
  GPIO_PORTF_AMSEL_R &= ~0x04; 
  GPIO_PORTF_DEN_R |= 0x04; 
	
  SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV; 
  SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M; 
  SYSCTL_RCC_R += SYSCTL_RCC_PWMDIV_2;
	
  PWM1_3_CTL_R = 0;   
  PWM1_3_GENA_R = (PWM_0_GENA_ACTCMPAD_ONE |  PWM_0_GENA_ACTLOAD_ZERO );
  PWM1_3_LOAD_R = period - 1;  
	PWM1_3_CMPA_R = duty - 1; 
  PWM1_3_CTL_R |= 0x00000001; 
	PWM1_ENABLE_R |= 0x00000040; //PWM6
}
void PF1_M1_PWM5_Duty(uint16_t duty) {
	  PWM1_2_CMPB_R = duty - 1;    
}
void PF2_M1_PWM6_Duty(uint16_t duty) {
	  PWM1_3_CMPA_R = duty - 1;  
}
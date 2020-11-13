
#include"tim.h"
#include"music.h"

void MelodySummer(void)
{
	Melody(g6,100);
	Melody(c7,100);
	Melody(d7,100);
	Melody(e7,100);
	Melody(d7,100);
	HAL_Delay(50);
	Melody(c7,50);
	HAL_Delay(50);
	Melody(c7,200);
}

void MelodyRayearth(void){
	Melody(f5,100);
	HAL_Delay(10);
	Melody(f5,600);
	Melody(c6,400);
	Melody(d6,200);
	Melody(a5h,600);
}

void MelodyGoal(void)
{
	Melody(g6,300);
	Melody(f6,300);
	Melody(e6,300);
}

void MelodyUrara(void){
	Melody(d7,100);
	Melody(a6,100);
	HAL_Delay(10);
	Melody(a6,200);
	HAL_Delay(50);

	Melody(d7,100);
	Melody(a6,100);
	HAL_Delay(10);
	Melody(a6,200);
	HAL_Delay(50);

	Melody(d7,100);
	Melody(c7,100);
	Melody(d7,100);
	Melody(c7,100);
	Melody(a6,200);
	HAL_Delay(50);

}

void MelodyMrLawrence()
{
	Melody(d7,100);
	Melody(e7,100);
	Melody(d7,100);
	Melody(a6,100);
	Melody(d7,100);

	HAL_Delay(400);

	Melody(d7,100);
	Melody(e7,100);
	Melody(d7,100);
	Melody(e6,100);
	Melody(g7,100);
	Melody(e6,100);
	Melody(d7,100);
	Melody(e7,100);
	Melody(d7,100);
	Melody(c7,100);
	Melody(a6,100);
}

void MelodyNatsumatsuri()
{
	Melody(d6,200);
	Melody(f6,200);
	Melody(g6,200);
	Melody(f6,100);
	Melody(g6,100);
	Melody(a6,200);
	Melody(c6,200);
	Melody(d6,200);

}

void MelodyKurenai(void){
	Melody(c7,300);
	HAL_Delay(10);
	Melody(c7,100);
	Melody(b6,100);
	Melody(c7,300);
	HAL_Delay(10);
	Melody(d6,100);
	Melody(e7,300);
	Melody(d7,100);
	Melody(c7,100);
	Melody(b6,300);
}

void MelodyYamato(){
	Melody(e6,100);
	HAL_Delay(10);
	Melody(e6,200);
	Melody(f6,100);
	Melody(e6,200);
	Melody(c6,200);

	Melody(f6,400);
	Melody(e6,400);
	Melody(d6,400);
}

void Melody(uint32_t hz, uint32_t ms)
{
	TIM_OC_InitTypeDef sConfigOC;
//TIM8 Setting
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 840-1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 100000 / hz;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.RepetitionCounter = 0;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//Config Setting
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse =  95000 / hz ;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//TIM8 OUTPUT
	if(HAL_TIM_PWM_Init(&htim3) != HAL_OK){
		Error_Handler();
	}
	if(HAL_TIM_PWM_ConfigChannel(&htim3,&sConfigOC,TIM_CHANNEL_3) != HAL_OK){
		Error_Handler();
	}
	if(HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3) != HAL_OK){
		Error_Handler();
	}
	HAL_Delay(ms);
	if(HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3) != HAL_OK){
		Error_Handler();
	}
}

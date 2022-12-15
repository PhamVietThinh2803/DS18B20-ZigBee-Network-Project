#include "DS18B20.h"
//************************** Low Level Layer ********************************************************//
#include "delay_timer.h"

static void DS18B20_DelayInit(DS18B20_Name* DS18B20)
{
	DELAY_TIM_Init(DS18B20->Timer);
}
static void DS18B20_DelayUs(DS18B20_Name* DS18B20, uint16_t Time)
{
	DELAY_TIM_Us(DS18B20->Timer, Time);
}
static void DS18B20_DelayMs(DS18B20_Name* DS18B20, uint16_t Time)
{
	DELAY_TIM_Ms(DS18B20->Timer, Time);
}

static void DS18B20_SetPinOut(DS18B20_Name* DS18B20)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DS18B20->Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DS18B20->PORT, &GPIO_InitStruct);
}
static void DS18B20_SetPinIn(DS18B20_Name* DS18B20)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DS18B20->Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DS18B20->PORT, &GPIO_InitStruct);
}
static void DS18B20_WritePin(DS18B20_Name* DS18B20, uint8_t Value)
{
	HAL_GPIO_WritePin(DS18B20->PORT, DS18B20->Pin, Value);
}
static uint8_t DS18B20_ReadPin(DS18B20_Name* DS18B20)
{
	return  HAL_GPIO_ReadPin(DS18B20->PORT, DS18B20->Pin);
}
//********************************* Middle level Layer ****************************************************//
static uint8_t DS18B20_Start(DS18B20_Name* DS18B20)
{
	uint8_t Response = 0;
	DS18B20_SetPinOut(DS18B20);  	// Set the Pin as Output
	DS18B20_WritePin(DS18B20, 0);	// Pull the Pin low for 480 us
	DS18B20_DelayUs(DS18B20, 480);   
	DS18B20_SetPinIn(DS18B20);    // Set the Pin as Input for 80 us
	DS18B20_DelayUs(DS18B20, 80); 
	if (!(DS18B20_ReadPin(DS18B20))){
		Response = 1;
	}  else {
		Response = -1;
	}
	DS18B20_DelayUs(DS18B20, 400); // 480 us delay totally.

	return Response;
}
static void DS18B20_Write(DS18B20_Name* DS18B20, uint8_t Data)
{
	DS18B20_SetPinOut(DS18B20); // Set as Output
	for(int i = 0; i < 8; i++)
	{
		if((Data&(1 << i)) != 0)  // If the bit is High
		{
			DS18B20_SetPinOut(DS18B20);
			DS18B20_WritePin(DS18B20, 0);
			DS18B20_DelayUs(DS18B20, 1);
			DS18B20_SetPinIn(DS18B20);
			DS18B20_DelayUs(DS18B20, 50);
		}
		else // If the bit is Low
		{
			DS18B20_SetPinOut(DS18B20);
			DS18B20_WritePin(DS18B20, 0);
			DS18B20_DelayUs(DS18B20, 50);
			DS18B20_SetPinIn(DS18B20);
		}
	}
}
static uint8_t DS18B20_Read(DS18B20_Name* DS18B20)
{
	uint8_t Value = 0;
	DS18B20_SetPinIn(DS18B20);
	for(int i = 0; i < 8; i++)
	{
		DS18B20_SetPinOut(DS18B20);
		DS18B20_WritePin(DS18B20, 0);
		DS18B20_DelayUs(DS18B20, 2);
		DS18B20_SetPinIn(DS18B20);
		if(DS18B20_ReadPin(DS18B20)){
			Value |= 1 << i;
		}
		DS18B20_DelayUs(DS18B20, 60);
	}
	return Value;
}

//************************** High Level Layer ********************************************************//
void DS18B20_Init(DS18B20_Name* DS18B20, TIM_HandleTypeDef* Timer, GPIO_TypeDef* DS_PORT, uint16_t DS_Pin)
{
	DS18B20 -> PORT = DS_PORT;		// Set Port
	DS18B20->Pin = DS_Pin;			// Set Pin
	DS18B20->Timer = Timer;     // Set Timer
	DS18B20_DelayInit(DS18B20); // Set Timer
}

float DS18B20_ReadTemp(DS18B20_Name* DS18B20)
{
	uint8_t Temp_byte_1, Temp_byte_2;
	float Temp;
	DS18B20_Start(DS18B20);
	DS18B20_DelayMs(DS18B20, 1);
	DS18B20_Write(DS18B20, DS18B20_SKIPROM);
	DS18B20_Write(DS18B20, DS18B20_CONVERT);
	DS18B20_DelayMs(DS18B20, 800);
	DS18B20_Start(DS18B20);
	DS18B20_DelayMs(DS18B20, 1);
	DS18B20_Write(DS18B20, DS18B20_SKIPROM);
	DS18B20_Write(DS18B20, DS18B20_READSCRAT);
	Temp_byte_1 = DS18B20_Read(DS18B20);
	Temp_byte_2 = DS18B20_Read(DS18B20);
	Temp = (Temp_byte_2 << 8) | Temp_byte_1;
	DS18B20 -> Temp = Temp / 16;
	return DS18B20 -> Temp;
}

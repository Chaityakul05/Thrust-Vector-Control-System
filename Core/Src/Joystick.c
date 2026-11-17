/*
 * Joystick.c
 *
 *  Created on: Feb 24, 2026
 *      Author: chait
 */

#include "Joystick.h"
#include "Joystick_cfg.h"

static ADC_HandleTypeDef hadc[JOYSTICK_UNITS] = {0};

void JoyStick_Init(uint16_t JoyStick_Instance)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* ================= GPIO CLOCK ENABLE ================= */

    if (JoyStick_CfgParam[JoyStick_Instance].JoyStick_xGPIO == GPIOA ||
        JoyStick_CfgParam[JoyStick_Instance].JoyStick_yGPIO == GPIOA)
        __HAL_RCC_GPIOA_CLK_ENABLE();

    if (JoyStick_CfgParam[JoyStick_Instance].JoyStick_xGPIO == GPIOB ||
        JoyStick_CfgParam[JoyStick_Instance].JoyStick_yGPIO == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();

    if (JoyStick_CfgParam[JoyStick_Instance].JoyStick_xGPIO == GPIOC ||
        JoyStick_CfgParam[JoyStick_Instance].JoyStick_yGPIO == GPIOC)
        __HAL_RCC_GPIOC_CLK_ENABLE();

    if (JoyStick_CfgParam[JoyStick_Instance].JoyStick_xGPIO == GPIOD ||
        JoyStick_CfgParam[JoyStick_Instance].JoyStick_yGPIO == GPIOD)
        __HAL_RCC_GPIOD_CLK_ENABLE();

    if (JoyStick_CfgParam[JoyStick_Instance].JoyStick_xGPIO == GPIOE ||
        JoyStick_CfgParam[JoyStick_Instance].JoyStick_yGPIO == GPIOE)
        __HAL_RCC_GPIOE_CLK_ENABLE();


    /* ================= GPIO CONFIG ================= */

    GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;

    GPIO_InitStruct.Pin = JoyStick_CfgParam[JoyStick_Instance].JoyStick_xPIN;
    HAL_GPIO_Init(JoyStick_CfgParam[JoyStick_Instance].JoyStick_xGPIO, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = JoyStick_CfgParam[JoyStick_Instance].JoyStick_yPIN;
    HAL_GPIO_Init(JoyStick_CfgParam[JoyStick_Instance].JoyStick_yGPIO, &GPIO_InitStruct);


    /* ================= ADC CLOCK ENABLE ================= */

    if (JoyStick_CfgParam[JoyStick_Instance].ADC_Instance == ADC1)
        __HAL_RCC_ADC1_CLK_ENABLE();


    /* ================= ADC CONFIG ================= */

    hadc[JoyStick_Instance].Instance = JoyStick_CfgParam[JoyStick_Instance].ADC_Instance;

    hadc[JoyStick_Instance].Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc[JoyStick_Instance].Init.Resolution            = ADC_RESOLUTION_12B;
    hadc[JoyStick_Instance].Init.ScanConvMode          = DISABLE;
    hadc[JoyStick_Instance].Init.ContinuousConvMode    = DISABLE;
    hadc[JoyStick_Instance].Init.DiscontinuousConvMode = DISABLE;
    hadc[JoyStick_Instance].Init.NbrOfConversion       = 1;
    hadc[JoyStick_Instance].Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc[JoyStick_Instance].Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    hadc[JoyStick_Instance].Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc[JoyStick_Instance].Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
    hadc[JoyStick_Instance].Init.DMAContinuousRequests = DISABLE;

    HAL_ADC_Init(&hadc[JoyStick_Instance]);
}


void JoyStick_Read(uint16_t JoyStick_Instance, uint16_t* JoyStick_XY)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    /* Common channel configuration parameters */
      sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;

    /* ================= READ X AXIS ================= */

    sConfig.Channel = JoyStick_CfgParam[JoyStick_Instance].ADCx_CH;
    HAL_ADC_ConfigChannel(&hadc[JoyStick_Instance], &sConfig);

    HAL_ADC_Start(&hadc[JoyStick_Instance]);
    HAL_ADC_PollForConversion(&hadc[JoyStick_Instance], HAL_MAX_DELAY);
    JoyStick_XY[0] = HAL_ADC_GetValue(&hadc[JoyStick_Instance]);
    HAL_ADC_Stop(&hadc[JoyStick_Instance]);


    /* ================= READ Y AXIS ================= */

    sConfig.Channel = JoyStick_CfgParam[JoyStick_Instance].ADCy_CH;
    HAL_ADC_ConfigChannel(&hadc[JoyStick_Instance], &sConfig);

    HAL_ADC_Start(&hadc[JoyStick_Instance]);
    HAL_ADC_PollForConversion(&hadc[JoyStick_Instance], HAL_MAX_DELAY);
    JoyStick_XY[1] = HAL_ADC_GetValue(&hadc[JoyStick_Instance]);
    HAL_ADC_Stop(&hadc[JoyStick_Instance]);
}

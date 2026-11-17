/*
 * Joystick_cfg.c
 *
 *  Created on: Feb 24, 2026
 *      Author: chait
 */

#include "Joystick.h"

const JoyStick_CfgType JoyStick_CfgParam[JOYSTICK_UNITS] =
{
    // JoyStick unit 1 Configurations
    {
    GPIOA,
    GPIOA,
    GPIO_PIN_1,
    GPIO_PIN_2,
    ADC1,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2
    }
};

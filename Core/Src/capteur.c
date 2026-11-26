#include "capteur.h"

static ADC_HandleTypeDef *s_hadc = NULL;

/* Fonction interne : lit la tension (en V) sur un canal ADC donné */
static float Lire_Tension_Canal(uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    if (s_hadc == NULL) {
        return 0.0f;
    }

    sConfig.Channel = channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;

    if (HAL_ADC_ConfigChannel(s_hadc, &sConfig) != HAL_OK) {
        return 0.0f;
    }

    if (HAL_ADC_Start(s_hadc) != HAL_OK) {
        return 0.0f;
    }

    if (HAL_ADC_PollForConversion(s_hadc, 10) == HAL_OK) {
        uint32_t raw = HAL_ADC_GetValue(s_hadc);
        HAL_ADC_Stop(s_hadc);
        return ((float)raw / ADC_MAX_VAL) * VREF_VOLTS;
    }

    HAL_ADC_Stop(s_hadc);
    return 0.0f;
}

void Capteur_Init(ADC_HandleTypeDef *hadc)
{
    s_hadc = hadc;
    if (s_hadc != NULL) {
        HAL_ADCEx_Calibration_Start(s_hadc);
    }
}

float Capteur_LireTemperature(void)
{
    /* PB0 -> ADC_TEMP -> ADC1_IN8 */
    float v_out = Lire_Tension_Canal(ADC_CHANNEL_8);
    float temp_c = ((v_out - TEMP_V_AT_0C) / TEMP_SLOPE_V_PER_C) + TEMP_OFFSET_C;
    return temp_c;
}

float Capteur_LireHumidite(void)
{
    /* PB1 -> ADC_HUM -> ADC1_IN9 */
    float v_mesuree = Lire_Tension_Canal(ADC_CHANNEL_9);
    float denom = MOIST_V_DRY - MOIST_V_WET;

    if (denom == 0.0f) {
        return 0.0f;
    }

    float hum = ((MOIST_V_DRY - v_mesuree) / denom) * 100.0f;

    if (hum < 0.0f) {
        hum = 0.0f;
    } else if (hum > 100.0f) {
        hum = 100.0f;
    }

    return hum;
}

float Capteur_LireTensionHumidite(void)
{
    /* PB1 -> ADC_HUM -> ADC1_IN9 */
    return Lire_Tension_Canal(ADC_CHANNEL_9);
}

float Capteur_LireTensionTemperature(void)
{
    /* PB0 -> ADC_TEMP -> ADC1_IN8 */
    return Lire_Tension_Canal(ADC_CHANNEL_8);
}

/*
 * capteur.h
 *
 *  Created on: Nov 25, 2026
 *      Author: remic
 */

#ifndef CAPTEUR_H
#define CAPTEUR_H
#include "main.h"

/* Constantes de conversion et calibration */
#define ADC_MAX_VAL        4095.0f
#define VREF_VOLTS         3.30f

/* Calibration capteur d'humidité capacitif (à ajuster selon vos mesures) */
#define MOIST_V_DRY        2.08f   /* Tension à l'air libre / sol sec (0%) */
#define MOIST_V_WET        1.24f   /* Tension dans l'eau / saturé (100%) */

/* Calibration capteur de température TMP235 */
#define TEMP_V_AT_0C       0.50f   /* À adapter selon votre courbe / offset */
#define TEMP_SLOPE_V_PER_C 0.01f   /* 10 mV / °C */
#define TEMP_OFFSET_C      0.0f    /* Offset empirique après comparaison étalon */

/* Initialisation du module d'acquisition */
void Capteur_Init(ADC_HandleTypeDef *hadc);

/* Lectures en unités physiques */
float Capteur_LireTemperature(void);
float Capteur_LireHumidite(void);
float Capteur_LireTensionHumidite(void);
float Capteur_LireTensionTemperature(void);

#endif /* CAPTEUR_H */

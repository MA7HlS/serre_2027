/*
 * lcd.c
 *
 *  Created on: Oct 30, 2026
 *      Author: mathi
 */


#include "lcd.h"

#define LCD_CMD_CLEAR         0x01  /* efface l'écran (dure environ 1,5 ms)           */
#define LCD_CMD_ENTRY_MODE    0x06  /* le curseur avance vers la droite               */
#define LCD_CMD_DISPLAY_OFF   0x08  /* afficheur éteint                               */
#define LCD_CMD_DISPLAY_ON    0x0C  /* afficheur allumé, sans curseur                 */
#define LCD_CMD_FUNCTION_SET  0x28  /* bus 4 bits, 2 lignes, caractères 5x8           */
#define LCD_CMD_SET_DDRAM     0x80  /* placer le curseur (on ajoute l'adresse)        */

#define LCD_LINE_1_ADDRESS    0x00	/* Adresse mémoire du début de chaque ligne */
#define LCD_LINE_2_ADDRESS    0x40

#define LCD_SEND_COMMAND      0		/* Valeurs pour la fonction lcd_send_byte */
#define LCD_SEND_DATA         1


static void lcd_short_delay(void)
{
    volatile uint8_t i;

    for (i = 0; i < 20; i++)
    {
        __NOP();
    }
}


static void lcd_pulse_enable(void)
{
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
    lcd_short_delay();
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
    lcd_short_delay();
}


static void lcd_write_4_bits(uint8_t value)
{
    if ((value & 0x01) != 0)
    {
        HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_RESET);
    }

    if ((value & 0x02) != 0)
    {
        HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, GPIO_PIN_RESET);
    }

    if ((value & 0x04) != 0)
    {
        HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, GPIO_PIN_RESET);
    }

    if ((value & 0x08) != 0)
    {
        HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, GPIO_PIN_RESET);
    }

    lcd_pulse_enable();
}


static void lcd_send_byte(uint8_t value, uint8_t type)
{
    if (type == LCD_SEND_DATA)
    {
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    }

    lcd_write_4_bits(value >> 4);       /* d'abord les 4 bits de poids fort */
    lcd_write_4_bits(value & 0x0F);     /* puis les 4 bits de poids faible  */

    HAL_Delay(1);                       /* temps d'exécution de la commande */
}


void lcd_init(void)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET); 	/* Toutes les lignes de commande au repos */
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);

    HAL_Delay(50);											/* Attendre que l'afficheur soit prêt après la mise sous tension (plus de 40 ms) */

    lcd_write_4_bits(0x03);									/* Séquence d'initialisation du HD44780 pour le mode 4 bits (voir sa datasheet) */
    HAL_Delay(5);
    lcd_write_4_bits(0x03);
    HAL_Delay(1);
    lcd_write_4_bits(0x03);
    HAL_Delay(1);
    lcd_write_4_bits(0x02);             					/* passage en mode 4 bits */
    HAL_Delay(1);

    lcd_send_byte(LCD_CMD_FUNCTION_SET, LCD_SEND_COMMAND);	/* Configuration de l'afficheur */
    lcd_send_byte(LCD_CMD_DISPLAY_OFF, LCD_SEND_COMMAND);
    lcd_clear();
    lcd_send_byte(LCD_CMD_ENTRY_MODE, LCD_SEND_COMMAND);
    lcd_send_byte(LCD_CMD_DISPLAY_ON, LCD_SEND_COMMAND);
}

void lcd_clear(void)
{
    lcd_send_byte(LCD_CMD_CLEAR, LCD_SEND_COMMAND);
    HAL_Delay(2);                       			/* l'effacement dure environ 1,5 ms */
}

int lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address;
    if ((row >= LCD_ROWS) || (col >= LCD_COLS))		/* Vérification des paramètres */
    {
        return -1;
    }

    if (row == 0)									/* Adresse mémoire de la case demandée */
    {
        address = (uint8_t)(LCD_LINE_1_ADDRESS + col);
    }
    else
    {
        address = (uint8_t)(LCD_LINE_2_ADDRESS + col);
    }

    lcd_send_byte((uint8_t)(LCD_CMD_SET_DDRAM + address), LCD_SEND_COMMAND);
    return 0;
}


void lcd_write_char(char c)
{
    lcd_send_byte((uint8_t)c, LCD_SEND_DATA);
}

int lcd_write_string(const char *text)
{
    uint8_t i = 0;

    if (text == NULL)
    {
        return -1;
    }

    while (text[i] != '\0')
    {
        lcd_write_char(text[i]);
        i++;
    }
    return 0;
}


int lcd_write_line(uint8_t row, const char *text)
{
    uint8_t col = 0;
    if (text == NULL)
    {
        return -1;
    }

    if (lcd_set_cursor(row, 0) != 0)				/* On se place au début de la ligne (retourne -1 si la ligne n'existe pas) */
    {
        return -1;
    }
    while ((text[col] != '\0') && (col < LCD_COLS))	/* On écrit les caractères de la chaîne, 16 au maximum */
    {
        lcd_write_char(text[col]);
        col++;
    }
    while (col < LCD_COLS)							/* On complète la ligne avec des espaces pour effacer l'ancien texte */
    {
        lcd_write_char(' ');
        col++;
    }
    return 0;
}

/*
 * u_lcd_helper.h
 * Funzioni di supporto per l'OLIMEX SHIELD_LCD16x2
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#ifndef INC_U_LCD_HELPER_H_
#define INC_U_LCD_HELPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "u_types.h"

// Maschere per i bottoni
#define D_BUTTON1_MASK 0x01
#define D_BUTTON2_MASK 0x02
#define D_BUTTON3_MASK 0x04
#define D_BUTTON4_MASK 0x08

// Righe dell'LCD
#define H_LCD_ROW_TOP 0
#define H_LCD_ROW_BTM 1

typedef enum {
	top = 0,
	bottom
} row_t;

#define H_LCD_TX_BUF_DIM 64 // Dimensione del buffer dell'LCD
#define H_LCD_TX_GRACE 50 // [ms] Delay di trasmissione

UART_HandleTypeDef huart3; // Porta UART per l'LCD
uint8_t lcd_tx_buffer[H_LCD_TX_BUF_DIM]; // Buffer di trasmissione per l'LCD

typedef struct state_t state_t;

// Stato FSM
struct state_t {
	state_t* transitions[4]; // B1, next; B2, page; B3, null; B4, prev;
};

state_t* fsm_state_buffer[2]; // Buffer per l'aggiornamento degli stati
state_t pAc1A, pAc1B, pAc2A, pAc2B, pGyrA, pGyrB, pMagA, pMagB, pPrs; // Stati della FSM

static inline void H_LCD_Perform_Tx(row_t row) {
	HAL_UART_Transmit(&huart3, lcd_tx_buffer, strlen((char const*) lcd_tx_buffer), 1000);
	HAL_Delay(H_LCD_TX_GRACE);
	lcdSetCursor(0, row);
	lcdPrint((char const*) lcd_tx_buffer);
}

void H_LCD_Round_Error(const float mean, int *round, int *error);
void H_LCD_Print(char const* text, const int num_a, const int num_b, row_t row);
void H_LCD_Blank(row_t row);

void H_LCD_Button_InitFSM();
void H_LCD_Button_StepFSM(uint8_t but);

#endif /* INC_U_LCD_HELPER_H_ */

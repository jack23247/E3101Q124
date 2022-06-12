/*
 * u_lcd_helper.c
 * Funzioni di supporto per l'OLIMEX SHIELD_LCD16x2
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#include "u_lcd_helper.h"

void H_LCD_Round_Error(const float mean, int *round, int *error) {
	float tmp = mean;
	*round = (int) tmp;
	tmp -= *round;
	tmp *= 100;
	*error = abs((int) tmp);
}

// _tttt:-0000.00_
void H_LCD_Print(char const* text, const int num_a, const int num_b, row_t row) {
	sprintf((char*) lcd_tx_buffer, " %s:%.5d.%.2d ", text, num_a, num_b);
	H_LCD_Perform_Tx(row);
}

void H_LCD_Blank(row_t row) {
	memset(lcd_tx_buffer, '\0', 16);
	H_LCD_Perform_Tx(row);
}

void H_LCD_Button_InitFSM() {

	pAc1A.transitions[0] = &pAc2A;
	pAc1A.transitions[1] = &pAc1B;
	pAc1A.transitions[2] = &pAc1A;
	pAc1A.transitions[3] = &pPrs;

	pAc1B.transitions[0] = &pAc2A;
	pAc1B.transitions[1] = &pAc1A;
	pAc1B.transitions[2] = &pAc1B;
	pAc1B.transitions[3] = &pPrs;

	pAc2A.transitions[0] = &pGyrA;
	pAc2A.transitions[1] = &pAc2B;
	pAc2A.transitions[2] = &pAc2A;
	pAc2A.transitions[3] = &pAc1A;

	pAc2B.transitions[0] = &pGyrA;
	pAc2B.transitions[1] = &pAc2A;
	pAc2B.transitions[2] = &pAc2B;
	pAc2B.transitions[3] = &pAc1A;

	pGyrA.transitions[0] = &pMagA;
	pGyrA.transitions[1] = &pGyrB;
	pGyrA.transitions[2] = &pGyrA;
	pGyrA.transitions[3] = &pAc2A;

	pGyrB.transitions[0] = &pMagA;
	pGyrB.transitions[1] = &pGyrA;
	pGyrB.transitions[2] = &pGyrB;
	pGyrB.transitions[3] = &pAc2A;

	pMagA.transitions[0] = &pPrs;
	pMagA.transitions[1] = &pMagB;
	pMagA.transitions[2] = &pMagA;
	pMagA.transitions[3] = &pGyrA;

	pMagB.transitions[0] = &pPrs;
	pMagB.transitions[1] = &pMagA;
	pMagB.transitions[2] = &pMagB;
	pMagB.transitions[3] = &pGyrA;

	pPrs.transitions[0] = &pAc1A;
	pPrs.transitions[1] = &pPrs;
	pPrs.transitions[2] = &pPrs;
	pPrs.transitions[3] = &pMagA;

	fsm_state_buffer[0] = &pAc1A;
	fsm_state_buffer[1] = &pAc1A;
}

void H_LCD_Button_StepFSM(uint8_t but) {
	int tid = -1;
	if (!(but & D_BUTTON1_MASK)) tid = 0;
	else if (!(but & D_BUTTON2_MASK)) tid = 1;
	else if (!(but & D_BUTTON3_MASK)) tid = 2;
	else if (!(but & D_BUTTON4_MASK)) tid = 3;
	if(tid != -1) {
		fsm_state_buffer[1] = fsm_state_buffer[0]->transitions[tid];
	}
}

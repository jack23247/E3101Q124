/*
 * u_timings.c
 * Temporizzazione dei task
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#ifndef INC_U_TIMINGS_H_
#define INC_U_TIMINGS_H_

// 1Hz -> 1000
// 10Hz -> 100
// 75Hz -> ~13

// 100Hz -> 10

#define M_CALCALL_TASK_PERIOD 100

#define LCD_DISPLAY_TASK_PERIOD 1000
#define LCD_BUTTON_READALL_TASK_PERIOD 50

#define XL_GETDATA_TASK_PERIOD 25
#define MG_GETDATA_TASK_PERIOD 250
#define XL2_GETDATA_TASK_PERIOD 24
#define G_GETDATA_TASK_PERIOD 23
#define P_GETDATA_TASK_PERIOD 13

#endif /* INC_U_TIMINGS_H_ */

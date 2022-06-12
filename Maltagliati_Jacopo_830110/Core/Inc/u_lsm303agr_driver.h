/*
 * u_lsm303agr_driver.h
 * Interfaccia per il driver del sensore LSM303AGR
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#ifndef INC_U_LSM303AGR_DRIVER_H_
#define INC_U_LSM303AGR_DRIVER_H_

#include <string.h>
#include "u_root.h"
#include "u_types.h"
#include "u_list.h"
#include "lsm303agr_reg.h"

// Dimensione liste dati
#define LSM303AGR_XL_LIST_SIZE 10
#define LSM303AGR_MG_LIST_SIZE 3

// Registri controllo periferica
stmdev_ctx_t lsm303agr_dev_ctx_xl;
stmdev_ctx_t lsm303agr_dev_ctx_mg;

// Buffer dati
lsm303agr_data_t lsm303agr_xl_data;
lsm303agr_data_t lsm303agr_mg_data;

// Liste dati e medie (da stampare)
list_t* lsm303agr_acc_x_list;
list_t* lsm303agr_acc_y_list;
list_t* lsm303agr_acc_z_list;
list_t* lsm303agr_mag_x_list;
list_t* lsm303agr_mag_y_list;
list_t* lsm303agr_mag_z_list;

int32_t lsm303agr_platform_write(void *handle, uint8_t reg,
		uint8_t *bufp, uint16_t len);
int32_t lsm303agr_platform_read(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);

void D_LSM303AGR_Init();
void D_LSM303AGR_XL_Read();
void D_LSM303AGR_MG_Read();

#endif /* INC_U_LSM303AGR_DRIVER_H_ */

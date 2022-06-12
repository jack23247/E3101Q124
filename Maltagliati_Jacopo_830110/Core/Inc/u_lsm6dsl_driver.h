/*
 * u_lsm303agr_driver.h
 * Interfaccia per il driver del sensore LSM303AGR
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#ifndef U_LSM6DSL_DRIVER_H_
#define U_LSM6DSL_DRIVER_H_

#include <string.h>
#include "u_root.h"
#include "u_types.h"
#include "u_list.h"
#include "lsm6dsl_reg.h"

// Dimensione liste dati
#define LSM6DSL_LIN_LIST_SIZE 10
#define LSM6DSL_ANG_LIST_SIZE 10

// Registri controllo periferica
stmdev_ctx_t lsm6dsl_dev_ctx;

// Buffer dati
lsm6dsl_data_t lsm6dsl_xl_data;
lsm6dsl_data_t lsm6dsl_g_data;

// Liste dati e medie (da stampare)
list_t *lsm6dsl_lin_x_list;
list_t *lsm6dsl_lin_y_list;
list_t *lsm6dsl_lin_z_list;
list_t *lsm6dsl_ang_x_list;
list_t *lsm6dsl_ang_y_list;
list_t *lsm6dsl_ang_z_list;

int32_t lsm6dsl_platform_write(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);
int32_t lsm6dsl_platform_read(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);

void D_LSM6DSL_Init();
void D_LSM6DSL_XL_Read();
void D_LSM6DSL_G_Read();

#endif /* U_LSM6DSL_DRIVER_H_ */

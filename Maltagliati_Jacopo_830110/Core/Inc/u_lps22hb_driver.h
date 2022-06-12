/*
 * u_lps22hb_driver.h
 * Interfaccia per il driver del sensore LPS22HB
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#ifndef INC_U_LPS22HB_DRIVER_H_
#define INC_U_LPS22HB_DRIVER_H_

#include <string.h>
#include "u_root.h"
#include "u_types.h"
#include "u_list.h"
#include "lps22hb_reg.h"

#define LPS22HB_LIST_SIZE 40 // Dimensione lista dati

stmdev_ctx_t lps22hb_dev_ctx; // Registro controllo periferica
lps22hb_data_t lps22hb_data; // Buffer dati
list_t *lps22hb_hPa_list; // Lista dati e media (da stampare)

int32_t lps22hb_platform_write(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);
int32_t lps22hb_platform_read(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);

void D_LPS22HB_Init();
void D_LPS22HB_Read();

#endif // INC_U_LPS22HB_DRIVER_H_

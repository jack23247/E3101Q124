/*
 * u_types.h
 * Definizione di tipi personalizzati
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#ifndef INC_U_TYPES_H_
#define INC_U_TYPES_H_

#include <stdint.h>
#include <stddef.h>

// Tipi di dato x sensori

typedef struct data_1x32b lps22hb_data_t;
typedef struct data_3x16b lsm303agr_data_t;
typedef struct data_3x16b lsm6dsl_data_t;

// Tipi union molto comodi

typedef union {
	int16_t i16bit;
	uint8_t u8bit[2];
} axis1bit16_t;

typedef union{
  int32_t i32bit;
  uint8_t u8bit[4];
} axis1bit32_t;

typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

typedef union{
  int32_t i32bit[3];
  uint8_t u8bit[12];
} axis3bit32_t;

// Container dati generici

struct data_1x32b {
	axis1bit32_t raw;
	float hPa;
};

struct data_3x16b {
	axis3bit16_t raw;
	float x;
	float y;
	float z;
};

#endif // INC_U_TYPES_H_

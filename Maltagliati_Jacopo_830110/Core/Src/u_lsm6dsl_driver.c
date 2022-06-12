/*
 * u_lsm6dsl_driver.c
 * Interfaccia per il driver del sensore LSM6DSL
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#include "u_lsm6dsl_driver.h"

int32_t lsm6dsl_platform_write(void *handle, uint8_t Reg, uint8_t *Bufp,
		uint16_t len) {
	if (handle == &hi2c1) {
		HAL_I2C_Mem_Write(handle, LSM6DSL_I2C_ADD_H, Reg,
		I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
	}
	return 0;
}

int32_t lsm6dsl_platform_read(void *handle, uint8_t Reg, uint8_t *Bufp,
		uint16_t len) {
	if (handle == &hi2c1) {
		HAL_I2C_Mem_Read(handle, LSM6DSL_I2C_ADD_H, Reg,
		I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
	}
	return 0;
}

void D_LSM6DSL_Init() {
	uint8_t id, rst = 0;

	lsm6dsl_lin_x_list = L_New(LSM6DSL_LIN_LIST_SIZE);
	lsm6dsl_lin_y_list = L_New(LSM6DSL_LIN_LIST_SIZE);
	lsm6dsl_lin_z_list = L_New(LSM6DSL_LIN_LIST_SIZE);

	lsm6dsl_ang_x_list = L_New(LSM6DSL_ANG_LIST_SIZE);
	lsm6dsl_ang_y_list = L_New(LSM6DSL_ANG_LIST_SIZE);
	lsm6dsl_ang_z_list = L_New(LSM6DSL_ANG_LIST_SIZE);

	lsm6dsl_dev_ctx.write_reg = lsm6dsl_platform_write;
	lsm6dsl_dev_ctx.read_reg = lsm6dsl_platform_read;
	lsm6dsl_dev_ctx.handle = &hi2c1;

	// Poll device
	while (id != LSM6DSL_ID) {
		lsm6dsl_device_id_get(&lsm6dsl_dev_ctx, &id);
	}

	/*
	 *  Restore default configuration
	 */
	lsm6dsl_reset_set(&lsm6dsl_dev_ctx, PROPERTY_ENABLE);
	do {
		lsm6dsl_reset_get(&lsm6dsl_dev_ctx, &rst);
	} while (rst);
	/*
	 *  Enable Block Data Update
	 */
	lsm6dsl_block_data_update_set(&lsm6dsl_dev_ctx, PROPERTY_ENABLE);
	/*
	 * Set Output Data Rate
	 */
	lsm6dsl_xl_data_rate_set(&lsm6dsl_dev_ctx, LSM6DSL_XL_ODR_12Hz5);
	lsm6dsl_gy_data_rate_set(&lsm6dsl_dev_ctx, LSM6DSL_GY_ODR_12Hz5);
	/*
	 * Set full scale
	 */
	lsm6dsl_xl_full_scale_set(&lsm6dsl_dev_ctx, LSM6DSL_2g);
	lsm6dsl_gy_full_scale_set(&lsm6dsl_dev_ctx, LSM6DSL_2000dps);

	/*
	 * Configure filtering chain(No aux interface)
	 */
	/* Accelerometer - analog filter */
	lsm6dsl_xl_filter_analog_set(&lsm6dsl_dev_ctx, LSM6DSL_XL_ANA_BW_400Hz);

	/* Accelerometer - LPF1 path ( LPF2 not used )*/
	//lsm6dsl_xl_lp1_bandwidth_set(&lsm6dsl_dev_ctx, LSM6DSL_XL_LP1_ODR_DIV_4);
	/* Accelerometer - LPF1 + LPF2 path */
	lsm6dsl_xl_lp2_bandwidth_set(&lsm6dsl_dev_ctx,
			LSM6DSL_XL_LOW_NOISE_LP_ODR_DIV_100);

	/* Accelerometer - High Pass / Slope path */
	//lsm6dsl_xl_reference_mode_set(&lsm6dsl_dev_ctx, PROPERTY_DISABLE);
	//lsm6dsl_xl_hp_bandwidth_set(&lsm6dsl_dev_ctx, LSM6DSL_XL_HP_ODR_DIV_100);
	/* Gyroscope - filtering chain */
	lsm6dsl_gy_band_pass_set(&lsm6dsl_dev_ctx, LSM6DSL_HP_260mHz_LP1_STRONG);
}

void D_LSM6DSL_XL_Read() {
	/* Read output only if new value is available */
	lsm6dsl_reg_t reg;
	lsm6dsl_status_reg_get(&lsm6dsl_dev_ctx, &reg.status_reg);
	if (reg.status_reg.xlda) {
		memset(lsm6dsl_xl_data.raw.u8bit, 0x00, 3 * sizeof(int16_t));
		lsm6dsl_acceleration_raw_get(&lsm6dsl_dev_ctx, lsm6dsl_xl_data.raw.u8bit);
		lsm6dsl_xl_data.x = lsm6dsl_from_fs2g_to_mg(lsm6dsl_xl_data.raw.i16bit[0]);
		lsm6dsl_xl_data.y = lsm6dsl_from_fs2g_to_mg(lsm6dsl_xl_data.raw.i16bit[1]);
		lsm6dsl_xl_data.z = lsm6dsl_from_fs2g_to_mg(lsm6dsl_xl_data.raw.i16bit[2]);
	}
}

void D_LSM6DSL_G_Read() {
	/* Read output only if new value is available */
	lsm6dsl_reg_t reg;
	lsm6dsl_status_reg_get(&lsm6dsl_dev_ctx, &reg.status_reg);
	if (reg.status_reg.gda) {
		memset(lsm6dsl_g_data.raw.u8bit, 0x00, 3 * sizeof(int16_t));
		lsm6dsl_angular_rate_raw_get(&lsm6dsl_dev_ctx, lsm6dsl_g_data.raw.u8bit);
		lsm6dsl_g_data.x = lsm6dsl_from_fs2000dps_to_mdps(
				lsm6dsl_g_data.raw.i16bit[0]);
		lsm6dsl_g_data.y = lsm6dsl_from_fs2000dps_to_mdps(
				lsm6dsl_g_data.raw.i16bit[1]);
		lsm6dsl_g_data.z = lsm6dsl_from_fs2000dps_to_mdps(
				lsm6dsl_g_data.raw.i16bit[2]);
	}
}


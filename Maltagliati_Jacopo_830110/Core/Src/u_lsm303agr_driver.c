/*
 * u_lsm303agr_driver.c
 * Interfaccia per il driver del sensore LSM303AGR
 *
 * Progetto d'esame 1920-3-E3101Q124 - Lug 2020
 * Copyright 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
 *
 */

#include "u_lsm303agr_driver.h"

int32_t lsm303agr_platform_write(void *handle, uint8_t Reg,
		uint8_t *Bufp, uint16_t len) {
	uint32_t i2c_add = (uint32_t) handle;
	if (i2c_add == LSM303AGR_I2C_ADD_XL) {
		/* enable auto incremented in multiple read/write commands */
		Reg |= 0x80;
	}
	HAL_I2C_Mem_Write(&hi2c1, i2c_add, Reg, I2C_MEMADD_SIZE_8BIT, Bufp, len,
			1000);
	return 0;
}

int32_t lsm303agr_platform_read(void *handle, uint8_t Reg, uint8_t *Bufp,
		uint16_t len) {
	uint32_t i2c_add = (uint32_t) handle;
	if (i2c_add == LSM303AGR_I2C_ADD_XL) {
		/* enable auto incremented in multiple read/write commands */
		Reg |= 0x80;
	}
	HAL_I2C_Mem_Read(&hi2c1, (uint8_t) i2c_add, Reg, I2C_MEMADD_SIZE_8BIT, Bufp,
			len, 1000);
	return 0;
}

void D_LSM303AGR_Init() {
	uint8_t id, rst = 0;

	lsm303agr_acc_x_list = L_New(LSM303AGR_XL_LIST_SIZE);
	lsm303agr_acc_y_list = L_New(LSM303AGR_XL_LIST_SIZE);
	lsm303agr_acc_z_list = L_New(LSM303AGR_XL_LIST_SIZE);

	// Accelerometro
	lsm303agr_dev_ctx_xl.write_reg = lsm303agr_platform_write;
	lsm303agr_dev_ctx_xl.read_reg = lsm303agr_platform_read;
	lsm303agr_dev_ctx_xl.handle = (void*) LSM303AGR_I2C_ADD_XL;

	// Poll device
	while (id != LSM303AGR_ID_XL) {
		lsm303agr_xl_device_id_get(&lsm303agr_dev_ctx_xl, &id);
	}

	/* Enable Block Data Update */
	lsm303agr_xl_block_data_update_set(&lsm303agr_dev_ctx_xl, PROPERTY_ENABLE);

	/* Set Output Data Rate */
	lsm303agr_xl_data_rate_set(&lsm303agr_dev_ctx_xl, LSM303AGR_XL_ODR_1Hz);

	/* Set accelerometer full scale */
	lsm303agr_xl_full_scale_set(&lsm303agr_dev_ctx_xl, LSM303AGR_2g);

	/* Enable temperature sensor */
	lsm303agr_temperature_meas_set(&lsm303agr_dev_ctx_xl, LSM303AGR_TEMP_ENABLE);
	/* Set device in continuos mode */
	lsm303agr_xl_operating_mode_set(&lsm303agr_dev_ctx_xl, LSM303AGR_HR_12bit);

	// Magnetometro
	id = 0;
	rst = 0;

	lsm303agr_mag_x_list = L_New(LSM303AGR_MG_LIST_SIZE);
	lsm303agr_mag_y_list = L_New(LSM303AGR_MG_LIST_SIZE);
	lsm303agr_mag_z_list = L_New(LSM303AGR_MG_LIST_SIZE);

	lsm303agr_dev_ctx_mg.write_reg = lsm303agr_platform_write;
	lsm303agr_dev_ctx_mg.read_reg = lsm303agr_platform_read;
	lsm303agr_dev_ctx_mg.handle = (void*) LSM303AGR_I2C_ADD_MG;

	// Poll device
	while (id != LSM303AGR_ID_MG) {
		lsm303agr_mag_device_id_get(&lsm303agr_dev_ctx_mg, &id);
	}

	/* Restore default configuration for magnetometer */
	lsm303agr_mag_reset_set(&lsm303agr_dev_ctx_mg, PROPERTY_ENABLE);
	do {
		lsm303agr_mag_reset_get(&lsm303agr_dev_ctx_mg, &rst);
	} while (rst);

	/* Enable Block Data Update */
	lsm303agr_mag_block_data_update_set(&lsm303agr_dev_ctx_mg, PROPERTY_ENABLE);

	/* Set Output Data Rate */
	lsm303agr_mag_data_rate_set(&lsm303agr_dev_ctx_mg, LSM303AGR_MG_ODR_10Hz);

	/* Set / Reset magnetic sensor mode */
	lsm303agr_mag_set_rst_mode_set(&lsm303agr_dev_ctx_mg,
			LSM303AGR_SENS_OFF_CANC_EVERY_ODR);

	/* Enable temperature compensation on mag sensor */
	lsm303agr_mag_offset_temp_comp_set(&lsm303agr_dev_ctx_mg, PROPERTY_ENABLE);

	/* Set magnetometer in continuos mode */
	lsm303agr_mag_operating_mode_set(&lsm303agr_dev_ctx_mg,
			LSM303AGR_CONTINUOUS_MODE);
}

void D_LSM303AGR_XL_Read() {
	/* Read output only if new value is available */
	lsm303agr_reg_t reg;
	lsm303agr_xl_status_get(&lsm303agr_dev_ctx_xl, &reg.status_reg_a);

	if (reg.status_reg_a.zyxda) {
		/* Read accelerometer data */
		memset(lsm303agr_xl_data.raw.u8bit, 0x00, 3 * sizeof(int16_t));
		lsm303agr_acceleration_raw_get(&lsm303agr_dev_ctx_xl,
				lsm303agr_xl_data.raw.u8bit);
		lsm303agr_xl_data.x = lsm303agr_from_fs_2g_hr_to_mg(
				lsm303agr_xl_data.raw.i16bit[0]);
		lsm303agr_xl_data.y = lsm303agr_from_fs_2g_hr_to_mg(
				lsm303agr_xl_data.raw.i16bit[1]);
		lsm303agr_xl_data.z = lsm303agr_from_fs_2g_hr_to_mg(
				lsm303agr_xl_data.raw.i16bit[2]);
	}
}

void D_LSM303AGR_MG_Read() {
	/* Read output only if new value is available */
	lsm303agr_reg_t reg;

	lsm303agr_mag_status_get(&lsm303agr_dev_ctx_mg, &reg.status_reg_m);
	if (reg.status_reg_m.zyxda) {
		/* Read magnetic field data */
		memset(lsm303agr_mg_data.raw.u8bit, 0x00, 3 * sizeof(int16_t));
		lsm303agr_magnetic_raw_get(&lsm303agr_dev_ctx_mg, lsm303agr_mg_data.raw.u8bit);
		lsm303agr_mg_data.x = lsm303agr_from_lsb_to_mgauss(
				lsm303agr_mg_data.raw.i16bit[0]);
		lsm303agr_mg_data.y = lsm303agr_from_lsb_to_mgauss(
				lsm303agr_mg_data.raw.i16bit[1]);
		lsm303agr_mg_data.z = lsm303agr_from_lsb_to_mgauss(
				lsm303agr_mg_data.raw.i16bit[2]);
	}
}


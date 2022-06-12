/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <string.h>
#include "u_root.h"
#include "u_types.h"
#include "u_timings.h"
#include "u_lcd_helper.h"
#include "u_lsm303agr_driver.h"
#include "u_lsm6dsl_driver.h"
#include "u_lps22hb_driver.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Task_T_Reserved */
osThreadId_t Task_T_ReservedHandle;
const osThreadAttr_t Task_T_Reserved_attributes = {
  .name = "Task_T_Reserved",
  .priority = (osPriority_t) osPriorityRealtime7,
  .stack_size = 128 * 4
};
/* Definitions for Task_M_CalcAll */
osThreadId_t Task_M_CalcAllHandle;
const osThreadAttr_t Task_M_CalcAll_attributes = {
  .name = "Task_M_CalcAll",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task_LCD_Disply */
osThreadId_t Task_LCD_DisplyHandle;
const osThreadAttr_t Task_LCD_Disply_attributes = {
  .name = "Task_LCD_Disply",
  .priority = (osPriority_t) osPriorityRealtime,
  .stack_size = 128 * 4
};
/* Definitions for Task_LCD_Button */
osThreadId_t Task_LCD_ButtonHandle;
const osThreadAttr_t Task_LCD_Button_attributes = {
  .name = "Task_LCD_Button",
  .priority = (osPriority_t) osPriorityRealtime1,
  .stack_size = 128 * 4
};
/* Definitions for Task_XL_GetData */
osThreadId_t Task_XL_GetDataHandle;
const osThreadAttr_t Task_XL_GetData_attributes = {
  .name = "Task_XL_GetData",
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 128 * 4
};
/* Definitions for Task_MG_GetData */
osThreadId_t Task_MG_GetDataHandle;
const osThreadAttr_t Task_MG_GetData_attributes = {
  .name = "Task_MG_GetData",
  .priority = (osPriority_t) osPriorityNormal2,
  .stack_size = 128 * 4
};
/* Definitions for Task_B_GetData */
osThreadId_t Task_B_GetDataHandle;
const osThreadAttr_t Task_B_GetData_attributes = {
  .name = "Task_B_GetData",
  .priority = (osPriority_t) osPriorityNormal3,
  .stack_size = 128 * 4
};
/* Definitions for Task_XL2_GetDat */
osThreadId_t Task_XL2_GetDatHandle;
const osThreadAttr_t Task_XL2_GetDat_attributes = {
  .name = "Task_XL2_GetDat",
  .priority = (osPriority_t) osPriorityNormal4,
  .stack_size = 128 * 4
};
/* Definitions for Task_G_GetData */
osThreadId_t Task_G_GetDataHandle;
const osThreadAttr_t Task_G_GetData_attributes = {
  .name = "Task_G_GetData",
  .priority = (osPriority_t) osPriorityNormal5,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void T_Reserved(void *argument);
void M_CalcAll(void *argument);
void LCD_Display(void *argument);
void LCD_Button_Readall(void *argument);
void XL_GetData(void *argument);
void MG_GetData(void *argument);
void B_GetData(void *argument);
void XL2_GetData(void *argument);
void G_GetData(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_T_Reserved */
  Task_T_ReservedHandle = osThreadNew(T_Reserved, NULL, &Task_T_Reserved_attributes);

  /* creation of Task_M_CalcAll */
  Task_M_CalcAllHandle = osThreadNew(M_CalcAll, NULL, &Task_M_CalcAll_attributes);

  /* creation of Task_LCD_Disply */
  Task_LCD_DisplyHandle = osThreadNew(LCD_Display, NULL, &Task_LCD_Disply_attributes);

  /* creation of Task_LCD_Button */
  Task_LCD_ButtonHandle = osThreadNew(LCD_Button_Readall, NULL, &Task_LCD_Button_attributes);

  /* creation of Task_XL_GetData */
  Task_XL_GetDataHandle = osThreadNew(XL_GetData, NULL, &Task_XL_GetData_attributes);

  /* creation of Task_MG_GetData */
  Task_MG_GetDataHandle = osThreadNew(MG_GetData, NULL, &Task_MG_GetData_attributes);

  /* creation of Task_B_GetData */
  Task_B_GetDataHandle = osThreadNew(B_GetData, NULL, &Task_B_GetData_attributes);

  /* creation of Task_XL2_GetDat */
  Task_XL2_GetDatHandle = osThreadNew(XL2_GetData, NULL, &Task_XL2_GetDat_attributes);

  /* creation of Task_G_GetData */
  Task_G_GetDataHandle = osThreadNew(G_GetData, NULL, &Task_G_GetData_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_T_Reserved */
/**
 * @brief  Function implementing the Task_T_Reserved thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_T_Reserved */
void T_Reserved(void *argument)
{
  /* USER CODE BEGIN T_Reserved */
	// Task riservato (default, inizializzazione)
	HAL_Delay(500);
	sprintf((char*) lcd_tx_buffer, " FreeRTOS * GO! ");
	H_LCD_Perform_Tx(H_LCD_ROW_TOP);
	HAL_Delay(1000);
	vTaskDelete(NULL);
  /* USER CODE END T_Reserved */
}

/* USER CODE BEGIN Header_M_CalcAll */
/**
 * @brief Function implementing the Task_M_CalcAll thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_M_CalcAll */
void M_CalcAll(void *argument)
{
  /* USER CODE BEGIN M_CalcAll */
	/* Infinite loop */
	for (;;) {
		// Acc1
		L_UpdateMean(lsm303agr_acc_x_list);
		L_UpdateMean(lsm303agr_acc_y_list);
		L_UpdateMean(lsm303agr_acc_z_list);
		// Acc2
		L_UpdateMean(lsm6dsl_lin_x_list);
		L_UpdateMean(lsm6dsl_lin_y_list);
		L_UpdateMean(lsm6dsl_lin_z_list);
		// Gyr
		L_UpdateMean(lsm6dsl_ang_x_list);
		L_UpdateMean(lsm6dsl_ang_y_list);
		L_UpdateMean(lsm6dsl_ang_z_list);
		// Mag
		L_UpdateMean(lsm303agr_mag_x_list);
		L_UpdateMean(lsm303agr_mag_y_list);
		L_UpdateMean(lsm303agr_mag_z_list);
		// Prs
		L_UpdateMean(lps22hb_hPa_list);
		osDelay(M_CALCALL_TASK_PERIOD);
	}
  /* USER CODE END M_CalcAll */
}

/* USER CODE BEGIN Header_LCD_Display */
/**
 * @brief Function implementing the Task_LCD_Disply thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_LCD_Display */
void LCD_Display(void *argument)
{
  /* USER CODE BEGIN LCD_Display */
	static int mean_round, mean_err;
	/* Infinite loop */
	for (;;) {
		// Se il backbuffer è stato aggiornato, ho cambiato stato
		if (fsm_state_buffer[0] != fsm_state_buffer[1]) {
			fsm_state_buffer[0] = fsm_state_buffer[1]; // Aggiorno il frontbuffer
			lcdClear(); // Pulisco l'LCD (per convenienza)
		}
		// Stampa in base agli stati
		if (fsm_state_buffer[0] == &pAc1A) {
			// Stato: Accelerometro 1 Pagina A
			H_LCD_Round_Error(lsm303agr_acc_x_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Ac1x", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Round_Error(lsm303agr_acc_y_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Ac1y", mean_round, mean_err, H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pAc1B) {
			// Stato: Accelerometro 1 Pagina B
			H_LCD_Round_Error(lsm303agr_acc_z_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Ac1z", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Blank(H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pAc2A) {
			// Stato: Accelerometro 2 Pagina A
			H_LCD_Round_Error(lsm6dsl_lin_x_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Ac2x", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Round_Error(lsm6dsl_lin_y_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Ac2y", mean_round, mean_err, H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pAc2B) {
			// Stato: Accelerometro 2 Pagina B
			H_LCD_Round_Error(lsm6dsl_lin_z_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Ac2z", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Blank(H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pGyrA) {
			// Stato: Giroscopio Pagina A
			H_LCD_Round_Error(lsm6dsl_ang_x_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Gyrx", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Round_Error(lsm6dsl_ang_y_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Gyry", mean_round, mean_err, H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pGyrB) {
			// Stato: Giroscopio Pagina B
			H_LCD_Round_Error(lsm6dsl_ang_z_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Gyrz", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Blank(H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pMagA) {
			// Stato: Magnetometro Pagina 1
			H_LCD_Round_Error(lsm303agr_mag_x_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Magx", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Round_Error(lsm303agr_mag_y_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Magy", mean_round, mean_err, H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pMagB) {
			// Stato: Magnetometro Pagina 2
			H_LCD_Round_Error(lsm303agr_acc_z_list->mean, &mean_round, &mean_err);
			H_LCD_Print("Magz", mean_round, mean_err, H_LCD_ROW_TOP);
			H_LCD_Blank(H_LCD_ROW_BTM);
		} else if (fsm_state_buffer[0] == &pPrs) {
			// Stato: Barometro
			H_LCD_Round_Error(lps22hb_hPa_list->mean, &mean_round, &mean_err);
			mean_err = mean_err/10; // QAD hack - perché %.1d non funziona?
			sprintf((char*) lcd_tx_buffer, " %s:%.5d.%.1d ", "Bar ", mean_round, mean_err);
			H_LCD_Perform_Tx(H_LCD_ROW_TOP);
			H_LCD_Blank(H_LCD_ROW_BTM);
		}
		osDelay(LCD_DISPLAY_TASK_PERIOD);
	}
  /* USER CODE END LCD_Display */
}

/* USER CODE BEGIN Header_LCD_Button_Readall */
/**
 * @brief Function implementing the Task_LCD_Button thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_LCD_Button_Readall */
void LCD_Button_Readall(void *argument)
{
  /* USER CODE BEGIN LCD_Button_Readall */
	/* Infinite loop */
	for (;;) {
		HAL_Delay(50); // Assolutamente necessario (conflitto r/w del bus I2C?)
		H_LCD_Button_StepFSM(lcdReadButtons());
		osDelay(LCD_BUTTON_READALL_TASK_PERIOD);
	}
  /* USER CODE END LCD_Button_Readall */
}

/* USER CODE BEGIN Header_XL_GetData */
/**
 * @brief Function implementing the Task_XL_GetData thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_XL_GetData */
void XL_GetData(void *argument)
{
  /* USER CODE BEGIN XL_GetData */
	/* Infinite loop */
	for (;;) {
		D_LSM303AGR_XL_Read();
		L_Insert(lsm303agr_acc_x_list, lsm303agr_xl_data.x);
		L_Insert(lsm303agr_acc_y_list, lsm303agr_xl_data.y);
		L_Insert(lsm303agr_acc_z_list, lsm303agr_xl_data.z);
		osDelay(XL_GETDATA_TASK_PERIOD);
	}
  /* USER CODE END XL_GetData */
}

/* USER CODE BEGIN Header_MG_GetData */
/**
 * @brief Function implementing the Task_MG_GetData thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_MG_GetData */
void MG_GetData(void *argument)
{
  /* USER CODE BEGIN MG_GetData */
	/* Infinite loop */
	for (;;) {
		D_LSM303AGR_MG_Read();
		L_Insert(lsm303agr_mag_x_list, lsm303agr_mg_data.x);
		L_Insert(lsm303agr_mag_y_list, lsm303agr_mg_data.y);
		L_Insert(lsm303agr_mag_z_list, lsm303agr_mg_data.z);
		osDelay(MG_GETDATA_TASK_PERIOD);
	}
  /* USER CODE END MG_GetData */
}

/* USER CODE BEGIN Header_B_GetData */
/**
 * @brief Function implementing the OS_B_GetData thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_B_GetData */
void B_GetData(void *argument)
{
  /* USER CODE BEGIN B_GetData */
	/* Infinite loop */
	for (;;) {
		D_LPS22HB_Read();
		L_Insert(lps22hb_hPa_list, lps22hb_data.hPa);
		osDelay(P_GETDATA_TASK_PERIOD);
	}
  /* USER CODE END B_GetData */
}

/* USER CODE BEGIN Header_XL2_GetData */
/**
 * @brief Function implementing the Task_XL2_GetDat thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_XL2_GetData */
void XL2_GetData(void *argument)
{
  /* USER CODE BEGIN XL2_GetData */
	/* Infinite loop */
	for (;;) {
		D_LSM6DSL_XL_Read();
		L_Insert(lsm6dsl_lin_x_list, lsm6dsl_xl_data.x);
		L_Insert(lsm6dsl_lin_y_list, lsm6dsl_xl_data.y);
		L_Insert(lsm6dsl_lin_z_list, lsm6dsl_xl_data.z);
		osDelay(XL2_GETDATA_TASK_PERIOD);
	}
  /* USER CODE END XL2_GetData */
}

/* USER CODE BEGIN Header_G_GetData */
/**
 * @brief Function implementing the Task_G_GetData thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_G_GetData */
void G_GetData(void *argument)
{
  /* USER CODE BEGIN G_GetData */
	/* Infinite loop */
	for (;;) {
		D_LSM6DSL_G_Read();
		L_Insert(lsm6dsl_ang_x_list, lsm6dsl_g_data.x);
		L_Insert(lsm6dsl_ang_y_list, lsm6dsl_g_data.y);
		L_Insert(lsm6dsl_ang_z_list, lsm6dsl_g_data.z);
		osDelay(G_GETDATA_TASK_PERIOD);
	}
  /* USER CODE END G_GetData */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

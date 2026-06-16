/*
 * bme_280.h
 *
 *  Created on: Jan 29, 2026
 *      Author: bahti
 */

#ifndef INC_BME_280_H_
#define INC_BME_280_H_

#include "stm32f4xx_hal.h"


/* ============================================================
 *                 BME280 REGISTER ADDRESSES
 * ============================================================
 */

/* -------------------- Humidity data registers -------------------- */
/* Nem ölçüm sonucu (16-bit) */
#define BME280_HUM_MSB            (0xFDU)
#define BME280_HUM_LSB            (0xFEU)

/* -------------------- Temperature data registers ----------------- */
/* Sıcaklık ölçüm sonucu (20-bit: MSB + LSB + XLSB) (8+8+4)*/
#define BME280_TEMP_MSB           (0xFAU)
#define BME280_TEMP_LSB           (0xFBU)
#define BME280_TEMP_XLSB          (0xFCU)

/* -------------------- Pressure data registers -------------------- */
/* Basınç ölçüm sonucu (20-bit: MSB + LSB + XLSB) (8+8+4) */
#define BME280_PRESS_MSB          (0xF7U)
#define BME280_PRESS_LSB          (0xF8U)
#define BME280_PRESS_XLSB         (0xF9U)

/* ---------------- Status / Control / Config registers ------------ */
/* Status: sensör meşgul mü, NVM kopyalama durumu */
#define BME280_STATUS             (0xF3U)
#define BME280_STATUS_MEASURING_MASK   (0x08U)   // bit3

/* ctrl_meas: sıcaklık & basınç oversampling + mode */
#define BME280_CTRL_MEAS          (0xF4U)

/* config: IIR filter, standby time (normal mode için) */
#define BME280_CONFIG             (0xF5U)

/* ctrl_hum: nem oversampling */
#define BME280_CTRL_HUM           (0xF2U)

/* -------------------- Reset / ID registers ----------------------- */
/* Soft reset register */
#define BME280_RESET              (0xE0U)

/* Chip ID register (0x60 beklenir) */
#define BME280_ID                 (0xD0U)

/* ============================================================
 *                 CALIBRATION REGISTERS
 * ============================================================
 * Sensöre özel kalibrasyon katsayıları.
 * Ham veriyi gerçek fiziksel değere çevirmek için kullanılır.
 */

/* Temp + Pressure + H1 kalibrasyon bloğu */
#define BME280_CALIB00            (0x88U)  /* dig_T1 LSB başlar */
#define BME280_CALIB25            (0xA1U)  /* dig_H1 burada */

/* Humidity kalibrasyon bloğu */
#define BME280_CALIB26            (0xE1U)  /* dig_H2 LSB başlar */
#define BME280_CALIB41            (0xF0U)  /* dig_H6’ya kadar */

/* ============================================================
 *                 I2C ADDRESS & CHIP INFO
 * ============================================================
 */

/* SDO pinine göre 7-bit I2C adresleri */
#define BME280_SDO_LOW            ((0x76U)<<1)
#define BME280_SDO_HIGH           ((0x77U)<<1)

#define BME280_SOFT_RESET_CMD   (0xB6U)

/* BME280 chip ID değeri */
#define BME280_CHIP_ID            (0x60U)

/* HAL I2C timeout süresi (ms) */
#define BME280_I2C_TIMEOUT_MS     (100U)

/* ============================================================
 *                 CALIBRATION STRUCT
 * ============================================================
 * Kalibrasyon katsayıları RAM’de bu struct içinde tutulur.
 * Init sırasında bir kere okunur, sonra sürekli kullanılır.
 */
typedef struct
{
    /* Temperature calibration */
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;

    /* Pressure calibration */
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

    /* Humidity calibration */
    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;

} bme280_calib_t;

/* ============================================================
 *           CALIBRATION REGISTER BLOCK DEFINITIONS
 * ============================================================
 */

/* Temperature + Pressure calibration block */
#define BME280_CALIB_TP_START     0x88
#define BME280_CALIB_TP_LEN       26

/* Humidity calibration block */
#define BME280_CALIB_H_START      0xE1
#define BME280_CALIB_H_LEN        7

/* ============================================================
 *            CTRL_MEAS OVERSAMPLING DEFINITIONS
 * ============================================================
 */

/* Temperature oversampling (bits 7:5) */
#define BME280_OSR_T_SKIP         (0x00U << 5)
#define BME280_OSR_T_X1           (0x01U << 5)
#define BME280_OSR_T_X2           (0x02U << 5)
#define BME280_OSR_T_X4           (0x03U << 5)
#define BME280_OSR_T_X8           (0x04U << 5)
#define BME280_OSR_T_X16          (0x05U << 5)

/* Pressure oversampling (bits 4:2) */
#define BME280_OSR_P_SKIP         (0x00U << 2)
#define BME280_OSR_P_X1           (0x01U << 2)
#define BME280_OSR_P_X2           (0x02U << 2)
#define BME280_OSR_P_X4           (0x03U << 2)
#define BME280_OSR_P_X8           (0x04U << 2)
#define BME280_OSR_P_X16          (0x05U << 2)

/* Sensor mode (bits 1:0) */
#define BME280_MODE_SLEEP         (0x00U)
#define BME280_MODE_FORCED        (0x01U)
#define BME280_MODE_NORMAL        (0x03U)
#define BME280_CTRL_MEAS_MODE_MASK   (0x03U)  //	bit1:0 mask
/* ============================================================
 *                 CONFIG REGISTER DEFINITIONS
 * ============================================================
 */

/* Standby time (normal mode için, bits 7:5) */
#define BME280_TSB_0_5_MS         (0x00U << 5)
#define BME280_TSB_62_5_MS        (0x01U << 5)
#define BME280_TSB_125_MS         (0x02U << 5)
#define BME280_TSB_250_MS         (0x03U << 5)
#define BME280_TSB_500_MS         (0x04U << 5)
#define BME280_TSB_1000_MS        (0x05U << 5)
#define BME280_TSB_10_MS          (0x06U << 5)
#define BME280_TSB_20_MS          (0x07U << 5)

/* IIR filter (bits 4:2) */
#define BME280_FILTER_OFF         (0x00U << 2)
#define BME280_FILTER_2           (0x01U << 2)
#define BME280_FILTER_4           (0x02U << 2)
#define BME280_FILTER_8           (0x03U << 2)
#define BME280_FILTER_16          (0x04U << 2)

/* SPI 3-wire enable (I2C kullanıyorsan DISABLE) */
#define BME280_SPI3W_DISABLE      (0x00U)
#define BME280_SPI3W_ENABLE       (0x01U)

/* ============================================================
 *            RAW OVERSAMPLING VALUES (HAM DEĞERLER)
 * ============================================================
 */
#define BME280_OSRS_SKIP          (0x00U)
#define BME280_OSRS_X1            (0x01U)
#define BME280_OSRS_X2            (0x02U)
#define BME280_OSRS_X4            (0x03U)
#define BME280_OSRS_X8            (0x04U)
#define BME280_OSRS_X16           (0x05U)

typedef struct
{
	int32_t adc_P;   // 20-bit ham basınç (signed int32 içine koyuldu)
	int32_t adc_T;   // 20-bit ham sıcaklık
	int32_t adc_H;   // 16-bit ham nem
} bme280_raw_t;

HAL_StatusTypeDef bme280_init(void);
HAL_StatusTypeDef bme280_force_measure(void);
uint8_t bme280_is_measuring(void);
HAL_StatusTypeDef bme280_read_raw(bme280_raw_t *raw);

double bme280_compensate_T_double(int32_t adc_T);
double bme280_compensate_P_double(int32_t adc_P);
double bme280_compensate_H_double(int32_t adc_H);
#endif /* INC_BME_280_H_ */

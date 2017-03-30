#ifndef P9025AC_I2C_H_
#define P9025AC_I2C_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/*
 * Makra s³u¿¹ce do ³atwiejszego korzystania z rejestrów chipu P9025AC
 */

#define P9025AC_I2C_SLAVE_ADDR (0x25 << 1) // adres chipu P9025AC 0100 101x

#define P9025AC_I2C_MEASUREMENTS_BASE_ADDR (0x40)
#define P9025AC_I2C_MEASUREMENTS_REGS_COUNT (6)

#define P9025AC_I2C_MEASUREMENTS_ADC1_MSB_ADDR (0X40)
#define P9025AC_I2C_MEASUREMENTS_ADC1_LSB_ADDR (0X41)
#define P9025AC_I2C_MEASUREMENTS_ADC2_MSB_ADDR (0X42)
#define P9025AC_I2C_MEASUREMENTS_ADC2_LSB_ADDR (0X43)
#define P9025AC_I2C_MEASUREMENTS_FREQ_MSB_ADDR (0X44)
#define P9025AC_I2C_MEASUREMENTS_FREQ_LSB_ADDR (0X45)

/*
 * Globalne zmienne zdefiniowane w pliku P9025AC_I2C.c
 */

//Bufor zawierajacy rejestry z danymi pomiarowymi z P9025AC
extern volatile uint8_t g_P9025AC_I2C_ADC1_ADC2_FREQ_REGs[6];

extern volatile uint8_t g_P9025AC_ADC1_MSB;
extern volatile uint8_t g_P9025AC_ADC1_LSB;
extern volatile uint8_t g_P9025AC_ADC2_MSB;
extern volatile uint8_t g_P9025AC_ADC2_LSB;
extern volatile uint8_t g_P9025AC_FREQ_MSB;
extern volatile uint8_t g_P9025AC_FREQ_LSB;




extern volatile float g_P9025AC_Vrect_Volts;
extern volatile uint16_t g_P9025AC_I_out_mA;
extern volatile uint16_t g_P9025AC_f_clk_Hz;

extern volatile uint8_t g_MeasurementsFlag;

extern I2C_HandleTypeDef hi2c1; //Struktura potrzebna do korzystania z peryferium i2c
/*
 *  Funkcje s³u¿¹ce do odpytywanie P9025AC poprzez I2C
 */

void JG_I2C_ReadMeasurementsFromP9025ACMem_IT();
void JG_I2C_ReadMeasurementsFromP9025ACMem_Blocking();
void JG_I2C_PutMeasurementsValuesToGlobalVariablesFromRaw();

#endif /* P9025AC_I2C_H_ */

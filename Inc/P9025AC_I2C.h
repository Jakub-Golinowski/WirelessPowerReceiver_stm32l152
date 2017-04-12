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
#define P9025AC_I2C_MEASUREMENTS_MISC_1_ADDR   (0X47)
#define P9025AC_I2C_MEASUREMENTS_MISC_2_ADDR   (0X48)
#define P9025AC_I2C_MEASUREMENTS_WPC_ID_B0_ADDR (0X54)
#define P9025AC_I2C_MEASUREMENTS_WPC_ID_B1_ADDR (0X55)
#define P9025AC_I2C_MEASUREMENTS_WPC_ID_B2_ADDR (0X56)
#define P9025AC_I2C_MEASUREMENTS_WPC_ID_B3_ADDR (0X57)
#define P9025AC_I2C_MEASUREMENTS_WPC_ID_B4_ADDR (0X58)
#define P9025AC_I2C_MEASUREMENTS_WPC_ID_B5_ADDR (0X59)
#define P9025AC_I2C_MEASUREMENTS_WPC_ID_B6_ADDR (0X5A)

#define P9025AC_I2C_MISC_1_VRECT_HIGHER_THAN_UVLO_MASK (1 << 3)
#define P9025AC_I2C_MISC_1_VRECT_HIGHER_THAN_AC_CLAMP_MASK (1 << 2)
#define P9025AC_I2C_MISC_1_LDO_CURRENT_LIMIT_EXCEEDED_MASK (1 << 1)

#define P9025AC_I2C_MISC_2_CHARGE_COMPLETE_MASK (1 << 7)
#define P9025AC_I2C_MISC_2_DIE_TEMP_OVER_150_CELSIUS_MASK (1 << 1)

#define P9025AC_I2C_MAJOR_VERSION_MASK (0xF0)
#define P9025AC_I2C_MINOR_VERSION_MASK (0x0F)
/*
 * Globalne zmienne zdefiniowane w pliku P9025AC_I2C.c
 */

//Bufor zawierajacy rejestry z danymi pomiarowymi z P9025AC
extern volatile uint8_t g_P9025AC_I2C_ADC1_ADC2_FREQ_REGs[6];

//Zmienne na wartoœci rejestrów P9025AC
extern volatile uint8_t g_P9025AC_ADC1_MSB;
extern volatile uint8_t g_P9025AC_ADC1_LSB;
extern volatile uint8_t g_P9025AC_ADC2_MSB;
extern volatile uint8_t g_P9025AC_ADC2_LSB;
extern volatile uint8_t g_P9025AC_FREQ_MSB;
extern volatile uint8_t g_P9025AC_FREQ_LSB;
extern volatile uint8_t g_P9025AC_MISC_1;
extern volatile uint8_t g_P9025AC_MISC_2;
extern volatile uint8_t g_P9025AC_WPC_ID_B0;
extern volatile uint8_t g_P9025AC_WPC_ID_B1;
extern volatile uint8_t g_P9025AC_WPC_ID_B2;
extern volatile uint8_t g_P9025AC_WPC_ID_B3;
extern volatile uint8_t g_P9025AC_WPC_ID_B4;
extern volatile uint8_t g_P9025AC_WPC_ID_B5;
extern volatile uint8_t g_P9025AC_WPC_ID_B6;


//Zmienne zawieraj¹ce wartoœci wielkoœci pochodz¹cych z diagnostyki P9025AC
extern volatile float g_P9025AC_Vrect_Volts;
extern volatile uint16_t g_P9025AC_I_out_mA;
extern volatile uint16_t g_P9025AC_f_clk_Hz;
extern volatile uint8_t g_PA9025AC_VrectHigherThanUVLOThreshold;
extern volatile uint8_t g_PA9025AC_VrectHigherThanACClampThreshold;
extern volatile uint8_t g_PA9025AC_LDOCurrentLimitExceeded;
extern volatile uint8_t g_PA9025AC_ChargeComplete;
extern volatile uint8_t g_PA9025AC_DieTemperatureOver150Celsius;
extern volatile uint8_t g_PA9025AC_WPC_VersionMajorRevision;
extern volatile uint8_t g_PA9025AC_WPC_VersionMinorRevision;
extern volatile uint32_t g_PA9025AC_WPC_ID_MostSignificantWord;
extern volatile uint32_t g_PA9025AC_WPC_ID_LeastSignificantWord;

extern volatile uint8_t g_MeasurementsFlag;

extern I2C_HandleTypeDef hi2c1; //Struktura potrzebna do korzystania z peryferium i2c
/*
 *  Funkcje s³u¿¹ce do odpytywanie P9025AC poprzez I2C
 */

void JG_I2C_ReadMeasurementsFromP9025ACMem_IT();
void JG_I2C_ReadMeasurementsFromP9025ACMem_Blocking();
void JG_I2C_PutMeasurementsValuesToGlobalVariablesFromRaw();

void JG_I2C_ReadMiscellaneousRegistersFromP9025ACMem_Blocking();
void JG_I2C_PutMiscellaneousValuesToGlobalVariablesFromRaw();

void JG_I2C_ReadWPCIDRegistersFromP9025ACMem_Blocking();
void JG_I2C_PutWPCIDValuesToGlobalVariablesFromRaw();

#endif /* P9025AC_I2C_H_ */

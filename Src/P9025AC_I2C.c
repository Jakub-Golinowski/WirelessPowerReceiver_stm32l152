#include "P9025AC_I2C.h"

volatile uint8_t g_P9025AC_I2C_ADC1_ADC2_FREQ_REGs[P9025AC_I2C_MEASUREMENTS_REGS_COUNT];

volatile uint8_t g_P9025AC_ADC1_MSB;
volatile uint8_t g_P9025AC_ADC1_LSB;
volatile uint8_t g_P9025AC_ADC2_MSB;
volatile uint8_t g_P9025AC_ADC2_LSB;
volatile uint8_t g_P9025AC_FREQ_MSB;
volatile uint8_t g_P9025AC_FREQ_LSB;

volatile float g_P9025AC_Vrect_Volts;
volatile uint16_t g_P9025AC_I_out_mA;
volatile uint16_t g_P9025AC_f_clk_Hz;

volatile uint8_t g_MeasurementsFlag;

void JG_I2C_ReadMeasurementsFromP9025ACMem_IT()
{
	//NOT WORKING PROPERLY - tylko pierwszy bajt jest sensowny, reszta zawiera 0xFF
	HAL_I2C_Mem_Read_IT(&hi2c1,P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_BASE_ADDR,1,g_P9025AC_I2C_ADC1_ADC2_FREQ_REGs, 6);
}

void JG_I2C_ReadMeasurementsFromP9025ACMem_Blocking()
{
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_ADC1_MSB_ADDR, 1, &g_P9025AC_ADC1_MSB, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_ADC1_LSB_ADDR, 1, &g_P9025AC_ADC1_LSB, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_ADC2_MSB_ADDR, 1, &g_P9025AC_ADC2_MSB, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_ADC2_LSB_ADDR, 1, &g_P9025AC_ADC2_LSB, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_FREQ_MSB_ADDR, 1, &g_P9025AC_FREQ_MSB, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_FREQ_LSB_ADDR, 1, &g_P9025AC_FREQ_LSB, 1, 100);
}

void JG_I2C_PutMeasurementsValuesToGlobalVariablesFromRaw()
{
	//Obliczanie wartoœci Vrect na podstawie wartoœci rejestrów ADC1 (por. datasheet)
	uint16_t P9025AC_ADC1_Value = ( (uint16_t)g_P9025AC_ADC1_MSB << 4 ) + ( (uint16_t)g_P9025AC_ADC1_LSB >> 4 );
	g_P9025AC_Vrect_Volts = (5.0 * (float)P9025AC_ADC1_Value * 1.8)/4096;

	//Obliczanie wartoœci Iout na podstawie wartoœci rejestrów ADC2 (por. datasheet)
	g_P9025AC_I_out_mA = ((( 18000 * (( (uint16_t)g_P9025AC_ADC2_MSB << 4 ) + ( (uint16_t)g_P9025AC_ADC2_LSB >> 4 )) )/4096)+5)/10;

	//Obliczanie wartoœci FREQ na podstawie wartoœci rejestrów FREQ (por. datasheet)
	uint16_t count = ((uint16_t)g_P9025AC_FREQ_MSB << 2 ) + ( (uint16_t)g_P9025AC_FREQ_LSB >> 6 );
	g_P9025AC_f_clk_Hz = 65536/count;
}


#include "P9025AC_I2C.h"

volatile uint8_t g_P9025AC_I2C_ADC1_ADC2_FREQ_REGs[P9025AC_I2C_MEASUREMENTS_REGS_COUNT];

volatile uint8_t g_P9025AC_ADC1_MSB;
volatile uint8_t g_P9025AC_ADC1_LSB;
volatile uint8_t g_P9025AC_ADC2_MSB;
volatile uint8_t g_P9025AC_ADC2_LSB;
volatile uint8_t g_P9025AC_FREQ_MSB;
volatile uint8_t g_P9025AC_FREQ_LSB;
volatile uint8_t g_P9025AC_MISC_1;
volatile uint8_t g_P9025AC_MISC_2;
volatile uint8_t g_P9025AC_WPC_ID_B0;
volatile uint8_t g_P9025AC_WPC_ID_B1;
volatile uint8_t g_P9025AC_WPC_ID_B2;
volatile uint8_t g_P9025AC_WPC_ID_B3;
volatile uint8_t g_P9025AC_WPC_ID_B4;
volatile uint8_t g_P9025AC_WPC_ID_B5;
volatile uint8_t g_P9025AC_WPC_ID_B6;

volatile float g_P9025AC_Vrect_Volts;
volatile uint16_t g_P9025AC_I_out_mA;
volatile uint16_t g_P9025AC_f_clk_Hz;
volatile uint8_t g_PA9025AC_VrectHigherThanUVLOThreshold;
volatile uint8_t g_PA9025AC_VrectHigherThanACClampThreshold;
volatile uint8_t g_PA9025AC_LDOCurrentLimitExceeded;
volatile uint8_t g_PA9025AC_ChargeComplete;
volatile uint8_t g_PA9025AC_DieTemperatureOver150Celsius;
volatile uint8_t g_PA9025AC_WPC_VersionMajorRevision;
volatile uint8_t g_PA9025AC_WPC_VersionMinorRevision;
volatile uint32_t g_PA9025AC_WPC_ID_MostSignificantWord;
volatile uint32_t g_PA9025AC_WPC_ID_LeastSignificantWord;


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

void JG_I2C_ReadMiscellaneousRegistersFromP9025ACMem_Blocking()
{
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_MISC_1_ADDR, 1, &g_P9025AC_MISC_1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_MISC_2_ADDR, 1, &g_P9025AC_MISC_2, 1, 100);
}

void JG_I2C_PutMiscellaneousValuesToGlobalVariablesFromRaw()
{
	g_PA9025AC_VrectHigherThanUVLOThreshold = (g_P9025AC_MISC_1 & P9025AC_I2C_MISC_1_VRECT_HIGHER_THAN_UVLO_MASK) && 1;
	g_PA9025AC_VrectHigherThanACClampThreshold = (g_P9025AC_MISC_1 & P9025AC_I2C_MISC_1_VRECT_HIGHER_THAN_AC_CLAMP_MASK) && 1;
	g_PA9025AC_LDOCurrentLimitExceeded = (g_P9025AC_MISC_1 & P9025AC_I2C_MISC_1_LDO_CURRENT_LIMIT_EXCEEDED_MASK) && 1;
	g_PA9025AC_ChargeComplete = (g_P9025AC_MISC_2 & P9025AC_I2C_MISC_2_CHARGE_COMPLETE_MASK) && 1;
	g_PA9025AC_DieTemperatureOver150Celsius = (g_P9025AC_MISC_2 & P9025AC_I2C_MISC_2_DIE_TEMP_OVER_150_CELSIUS_MASK) && 1;
}

void JG_I2C_ReadWPCIDRegistersFromP9025ACMem_Blocking()
{
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_WPC_ID_B0_ADDR, 1, &g_P9025AC_WPC_ID_B0, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_WPC_ID_B1_ADDR, 1, &g_P9025AC_WPC_ID_B1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_WPC_ID_B2_ADDR, 1, &g_P9025AC_WPC_ID_B2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_WPC_ID_B3_ADDR, 1, &g_P9025AC_WPC_ID_B3, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_WPC_ID_B5_ADDR, 1, &g_P9025AC_WPC_ID_B4, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_WPC_ID_B2_ADDR, 1, &g_P9025AC_WPC_ID_B5, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, P9025AC_I2C_SLAVE_ADDR, P9025AC_I2C_MEASUREMENTS_WPC_ID_B6_ADDR, 1, &g_P9025AC_WPC_ID_B6, 1, 100);
}

void JG_I2C_PutWPCIDValuesToGlobalVariablesFromRaw()
{
	g_PA9025AC_WPC_VersionMajorRevision = (g_P9025AC_WPC_ID_B0 & P9025AC_I2C_MAJOR_VERSION_MASK) >> 4;
	g_PA9025AC_WPC_VersionMinorRevision = g_P9025AC_WPC_ID_B0 & P9025AC_I2C_MINOR_VERSION_MASK;
	g_PA9025AC_WPC_ID_LeastSignificantWord = (g_P9025AC_WPC_ID_B4 << 3*8) | ( g_P9025AC_WPC_ID_B3 << 2*8) | ( g_P9025AC_WPC_ID_B2 << 8) | (g_P9025AC_WPC_ID_B1);
	g_PA9025AC_WPC_ID_MostSignificantWord  = (g_P9025AC_WPC_ID_B6 << 1*8) | (g_P9025AC_WPC_ID_B5);
}

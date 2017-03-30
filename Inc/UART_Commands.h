/*
 * Komendy s³u¿¹ce do komunikacji z MCU poprzez UART
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

#ifndef UART_COMMANDS_H_
#define UART_COMMANDS_H_

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#define JG_Command_IdentificationCommandCode (0x69)		// 0x69 oznacza 'i' w kodzie ASCII
#define JG_Command_IdenticationCommandRespone ("IDT P9025AC I2C Polling Device. Compilation time: " __DATE__ " " __TIME__ "\n\r")
#define JG_Command_IdentificationCommandResponseLength (sizeof(JG_Command_IdenticationCommandRespone)-1)

#define JG_Command_VoltageRectifiedCommandCode (0x76)		// 0x76 oznacza 'v' w kodzie ASCII
#define JG_Command_VoltageRectifiedCommandResponeBeginning ("V_rect = ")
#define JG_Command_VoltageRectifiedCommandResponeLength (sizeof(JG_Command_VoltageRectifiedCommandRespone)-1)


#define JG_Command_UnknownCommandRespone ("Unknown Command.\n\r")
#define JG_Command_UnknownCommandResponseLength (sizeof(JG_Command_UnknownCommandRespone)-1)

#endif /* UART_COMMANDS_H_ */

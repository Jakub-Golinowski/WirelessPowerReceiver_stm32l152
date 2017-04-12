#ifndef JG_BINARYPROTOCOLCOMMANDS_H_
#define JG_BINARYPROTOCOLCOMMANDS_H_


/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "P9025AC_I2C.h"
#include "stm32l1xx_hal.h"

/* Defines ------------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

//Cykliczny bufor kommend.
#define COMMAND_BUFFER_SIZE 32 // Command buffer, should be a power of 2 (f.e. 2^5 = 32)
#define COMMAND_BUFFER_MASK (COMMAND_BUFFER_SIZE-1) //USART receiving buffer mask, to control buffer head and tail indexes

#define BINARY_PROTOCOL_RESPONSE_BUFFER_LENGTH 200

#define JG_Command_IdentificationCommandCode (0x69)		// 0x69 oznacza 'i' w kodzie ASCII
#define JG_Command_IdenticationCommandRespone ("IDT P9025AC I2C Polling Device. Compilation time: " __DATE__ " " __TIME__ "\n\r")
#define JG_Command_IdentificationCommandResponseLength (sizeof(JG_Command_IdenticationCommandRespone)-1)

#define JG_Command_VoltageRectifiedCommandCode (0x76)		// 0x76 oznacza 'v' w kodzie ASCII
#define JG_Command_VoltageRectifiedCommandResponeBeginning ("V_rect = ")

#define JG_Command_RepeatModeEnableCommandCode (0x72)		// 0x72 oznacza 'r' w kodzie ASCII
#define JG_Command_RepeatModeEnableCommandResponseBeginning ("\n\r========= ==================== =========\n\r          Entering Repeat Mode          \n\r========= ==================== =========\n\r")
#define JG_Command_RepeatModeEnableCommandResponseBeginningLength (sizeof(JG_Command_RepeatModeEnableCommandResponseBeginning)-1)

#define JG_Command_ExtendedRepeatModeEnableCommandCode (0x52)		// 0x52 oznacza 'R' w kodzie ASCII
#define JG_Command_ExtendedRepeatModeEnableCommandResponseBeginning ("\n\r========= ============================= ========\n\r          Entering Extended Repeat Mode          \n\r========= ============================= ========\n\r")
#define JG_Command_ExtendedRepeatModeEnableCommandResponseBeginningLength (sizeof(JG_Command_ExtendedRepeatModeEnableCommandResponseBeginning)-1)

#define JG_Command_SingleDiagCommandCode (0x73)		// 0x73 oznacza 's' w kodzie ASCII
#define JG_Command_SingleDiagCommandResponseBeginning ("P9025AC_Params ")
#define JG_Command_SingleDiagCommandResponeBeginningLength (sizeof(JG_Command_SingleDiagCommandResponseBeginning)-1)

#define JG_Command_UnknownCommandRespone ("Unknown Command.\n\r")
#define JG_Command_UnknownCommandResponseLength (sizeof(JG_Command_UnknownCommandRespone)-1)

/* Global Variables ------------------------------------------------------------------*/
extern volatile uint8_t g_CommandReceivedCounter;
extern volatile uint8_t g_CommandBufferFullFlag;
extern volatile uint8_t g_RepeatModeFlag;
volatile uint8_t g_ExtendedRepeatModeFlag;

extern volatile uint8_t aTxBuffer_GV[BINARY_PROTOCOL_RESPONSE_BUFFER_LENGTH];

extern volatile uint8_t command_buffer_tail_index_GV;
extern volatile uint8_t command_buffer_head_index_GV;
extern volatile uint8_t command_buffer_GV[COMMAND_BUFFER_SIZE];

//TODO zmienic tak ¿eby w tym pliku nie by³ widoczny provider po³¹czenia:
extern UART_HandleTypeDef huart2;
/* Function Declarations ------------------------------------------------------------------*/
int8_t JG_CommandBuffer_GetCommand(uint8_t * receivedData);
void JG_ProcessCurrentCommand(uint8_t Command);


#endif /*JG_BINARYPROTOCOLCOMMANDS_H_ */

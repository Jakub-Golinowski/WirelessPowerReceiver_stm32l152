#include "JG_BinaryProtocolCommands.h"

/* Global Variables ------------------------------------------------------------------*/
volatile uint8_t g_CommandReceivedCounter;
volatile uint8_t g_CommandBufferFullFlag;

volatile uint8_t aTxBuffer_GV[BINARY_PROTOCOL_RESPONSE_BUFFER_LENGTH];

volatile uint8_t command_buffer_tail_index_GV;
volatile uint8_t command_buffer_head_index_GV;
volatile uint8_t command_buffer_GV[COMMAND_BUFFER_SIZE];

/* Function Definitions ------------------------------------------------------------------*/
int8_t JG_CommandBuffer_GetCommand(uint8_t * receivedData)
{
	if(command_buffer_head_index_GV == command_buffer_tail_index_GV)
		return -1; //Return error code when the buffer is empty

	command_buffer_tail_index_GV = (command_buffer_tail_index_GV+1) & COMMAND_BUFFER_MASK; //Increment tail index and & with mask, so it never exceeds the buffer size - 1

	*receivedData = command_buffer_GV[command_buffer_tail_index_GV];		//Insert byte from Data Register to circular buffer

	return 1;
}



void JG_ProcessCurrentCommand(uint8_t Command)
{
	switch(Command)
	{
		case JG_Command_IdentificationCommandCode :
			HAL_UART_Transmit_DMA(&huart2,(uint8_t*)JG_Command_IdenticationCommandRespone,JG_Command_IdentificationCommandResponseLength);
			break;

		case JG_Command_VoltageRectifiedCommandCode:
		{
			uint8_t size = sprintf(aTxBuffer_GV, "%s %3.2f V\r\n", JG_Command_VoltageRectifiedCommandResponeBeginning, g_P9025AC_Vrect_Volts);
			HAL_UART_Transmit_DMA(&huart2,aTxBuffer_GV,size);
			break;
		}
		default : HAL_UART_Transmit_DMA(&huart2,(uint8_t*)JG_Command_UnknownCommandRespone,JG_Command_UnknownCommandResponseLength);
	}
}






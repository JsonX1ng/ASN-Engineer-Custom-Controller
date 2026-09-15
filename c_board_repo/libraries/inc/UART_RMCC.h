/*
 * UART_RMCC.h
 *
 *  Created on: Jun 12, 2026
 *      Author: Gen6
 */

#include "main.h"
#ifdef INCLUDE_UART_RMCC
#ifndef INC_UART_RMCC_H_
#define INC_UART_RMCC_H_

typedef enum
{
	CC_FRAME_HEADER = 0xA5,
	CC_TO_CLIENT_HEADER = 0x0306,
	CC_TO_ROBOT_HEADER = 0x0302,
	CC_FROM_ROBOT_HEADER = 0x0309,

}RMCC_HEADERS;

typedef enum
{
	CC_FRAME_HEADER_LEN = 5,
	CC_TO_CLIENT_LEN = 8,
	CC_TO_ROBOT_LEN = 30,
	CC_FROM_ROBOT_LEN = 30,

}RMCC_FRAME_LENGTHS;

typedef struct __attribute__((packed)){
	uint8_t data[30];
}custom_controller_data_t;

uint8_t RMCC_Get_CRC8_Check_Sum(uint8_t *pchMessage, uint32_t dwLength, uint8_t ucCRC8);
uint8_t RMCC_Verify_CRC8_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);


uint16_t RMCC_Get_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength,uint16_t wCRC);
uint32_t RMCC_Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void RMCC_Append_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength);

void RMCC_Transmit(UART_HandleTypeDef *huart,uint16_t cmd_id, uint8_t data[]);

#endif /* INC_UART_RMCC_H_ */
#endif

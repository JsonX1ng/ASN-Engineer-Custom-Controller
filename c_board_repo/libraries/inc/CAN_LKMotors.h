/*
 * CAN_LK.h
 *
 *  Created on: Jun 12, 2026
 *      Author: Jason
 */
 
#include "main.h"
#ifdef INCLUDE_CAN_LKMOTORS
#ifndef INC_CAN_LK_H_
#define INC_CAN_LK_H_

typedef enum{
//	LK_DISABLED = 6,
//	LK_ENABLED = 7,
//	LK_OVERVOLTAGE = 14,
	LK_UNDERVOLTAGE = 0x80,
//	LK_OVERCURRENT = 0x00,
//	LK_MOS_OVERHEAT = 0x01,
	LK_MOTOR_OVERHEAT = 0x10,
//	LK_NO_COMM = 0x03,
//	LK_OVERLOAD = 0x04,
	LK_OVERALLOCATION_ERROR = 202,
	LK_MALLOC_ERROR = 220
}LK_ERROR;

typedef enum {
	MOTOR_MS = 1,
	MOTOR_MF = 2,
	MOTOR_MH = 3,
	MOTOR_MG = 4
} LK_MOTORTYPES;

#define LK_IDENTIFIER 0x140

#define MAX_MOTOR_COUNT 8

typedef enum{
	// no rom commands included

	LK_MOTOR_OFF = 0x80, // LED slow flashes, clears turns, can still replay but no actions //CM0
	LK_MOTOR_ON = 0x88, // LED solid, default state 										//CM1
	LK_MOTOR_STOP = 0x81, // Stops the motor, will start again after sending commmands 		//CM2
	LK_SET_POWER_OPEN = 0xa0, // Open loop torque, ONLY FOR MS series motors				//CM3
	LK_SET_POWER_CLOSED = 0xa1, // Closed loop torque, ONLY FOR MF,MH,and MG, series motors //CM4
	LK_SET_SPEED = 0xa2, 																	//CM5
	LK_SET_ANGLE_MULTI = 0xa3, // Multi rotation angle control 								//CM6
	LK_SET_ANGLE_MULTI_LIM = 0xa4, //Speed limited Multi rotation angle control 			//CM7
	LK_SET_ANGLE_SINGLE = 0xa5, // Single rotation angle control 							//CM8
	LK_SET_ANGLE_SINGLE_LIM = 0xa6, // Speed limited Single rotation angle control 			//CM9
	//LK_SET_INC_ANGLE = 0xa7, // Increment angle
	//LK_SET_INC_ANGLE_LIM = 0xa8,// Speed limited Increment angle
	LK_READ_PID = 0x30, 																	//CM10
	LK_SET_PID = 0x31, 																		//CM11
	//LK_READ_ACC = 0x33, // Read acceleration
	//LK_SET_ACC = 0x34, // Set acceleration
	//LK_READ_ENCODER = 0x90,
	LK_READ_ANGLE_MULTI = 0x92, 															//CM12
	LK_READ_ANGLE_SINGLE = 0x94, 															//CM13
	LK_READ_ERROR = 0x9a, 																	//CM14
	LK_CLEAR_ERROR = 0x9b, // clears the error state 										//CM15
	LK_READ_GENERAL = 0x9c // reads temperature, torque, low res motor speed, and encoder 	//CM16
	//LK_READ_PHASE = 0x9d //reads motor coil phases
}LK_CAN_COMMAND_BYTE;


typedef struct {
	uint32_t canId;
	CAN_HandleTypeDef* currentBus;
	int8_t motorTemp; // In degrees Celsius
	int8_t errorState;

	uint16_t sendSpinDirection; // 0x00 for clockwise, 0x01 for CCW
	uint16_t sendMaxSpeed;  // In degrees per second

	uint32_t sendAngleSingle; // In 0.01 degree increments
	int32_t sendAngleMulti; // In 0.01 degree increments

	int32_t sendSpeed; // In 0.01 degree per second increments

	int16_t sendTorque; // From -850 to 850

	int16_t currentTorque; // From -2048 to 2048
	int16_t currentSpeed; // In degrees per second
	uint16_t currentPos; // From 0 -> 16383 for 1 revolution

	uint32_t currentAngleSingle; // In 0.01 degree increments
	int64_t currentAngleMulti; // In 0.01 degree increments

	uint8_t sendPosKp; //default is 50
	uint8_t sendPosKi; //default is 50
	uint8_t sendSpeedKp; //default is 50
	uint8_t sendSpeedKi; //default is 50

	uint8_t commandBytes[17]; // Stores which commands need to be sent out
	// uint8_t recieveCounter;


} LK_Motor_t;

void delay_us(uint16_t us);

void CAN_LK_InitMotor(uint8_t busNum, uint8_t canID);

CAN_LibraryInfo CAN_LKMotors();

void CAN_LK_Recieve(CAN_HandleTypeDef *hcan, uint32_t StdId,uint32_t ExtId, uint8_t rx_data[8]);

uint8_t CAN_LK_Add_Motor(CAN_HandleTypeDef *hcanx, uint32_t canID);

void CAN_LK_Update(uint8_t delay);

uint8_t CAN_LK_Lookup_Insert(uint32_t canID, uint8_t motorIndex);


//
void setLKTorque(uint8_t motorID, int16_t drivingTorque, uint8_t motorType);
//
float getLKTorque(uint8_t motorID);
//
float getLKRPM(uint8_t motorID);
//
void setLKRPM(uint8_t motorID, float RPM, uint8_t kp, uint8_t ki);
//
uint32_t getLKAngleSingle(uint8_t motorID);
//
int64_t getLKAngleMulti(uint8_t motorID);
//
void setLKAngleSingle(uint8_t motorID, uint32_t targetAngle, uint16_t rpmLimit, uint8_t kp, uint8_t ki, uint8_t spinDirection);
//
void setLKAngleMulti(uint8_t motorID, int32_t targetAngle, uint16_t rpmLimit, uint8_t kp, uint8_t ki);

void clearMotionCmds(uint8_t motorID);
//uint8_t getLKStatus(uint8_t motorID);

#endif /* INC_CAN_LK_H_ */
#endif

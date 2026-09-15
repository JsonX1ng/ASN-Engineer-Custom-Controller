/*
 * CAN_LK.c
 *
 *  Created on: Jun 12, 2026
 *      Author: Jason
 */
    
#include "main.h"
#ifdef INCLUDE_CAN_LKMOTORS
#include "CAN_Core.h"
#include "string.h"
#include "stdlib.h"

LK_Motor_t *listOfMotors;
uint8_t activeMotors = 0;

uint8_t *motorLookup;
uint8_t motorLookupSize = 0;

volatile uint8_t waitCount = 0;


CAN_HandleTypeDef hcan1 __attribute__((weak));
CAN_HandleTypeDef hcan2 __attribute__((weak));


/* Description: Motor initialization wrapper for c_board
 * Input: CAN bus number to initialize the motor on (BUS1 or BUS2), motor id number (LK1 or LK2 ...)
 */
void CAN_LK_InitMotor(uint8_t busNum, uint8_t canID){

	if(canID<1||canID>8){
		return;
	}

	if(busNum==1){
		extern CAN_HandleTypeDef hcan1;
		CAN_LK_Add_Motor(&hcan1,canID);
	}
	if(busNum==2){
		extern CAN_HandleTypeDef hcan2;
		CAN_LK_Add_Motor(&hcan2,canID);
	}
	//extern TIM_HandleTypeDef htim13;
	//PID_Init(&htim13);
}


CAN_LibraryInfo CAN_LKMotors(){
	CAN_LibraryInfo CAN_LKMotorsInfo;
	CAN_LKMotorsInfo.rx_passThrough_Fn = &CAN_LK_Recieve;
	return CAN_LKMotorsInfo;
}

void CAN_LK_Recieve(CAN_HandleTypeDef *hcan, uint32_t StdId,uint32_t ExtId, uint8_t rx_data[8]){


		//parse lower nibble of motor ID
		uint8_t motorID = StdId - LK_IDENTIFIER;

		//convert to list index
		if(motorID>motorLookupSize){
			CAN_LK_Add_Motor(hcan,motorID);
		}else if(motorLookup[motorID-1]==0){
			CAN_LK_Add_Motor(hcan,motorID);
		}

		//load values into the according motor
		listOfMotors[motorLookup[motorID-1]-1].currentBus = hcan;
		switch (rx_data[0]) { // command byte
			case LK_READ_GENERAL:
				listOfMotors[motorLookup[motorID-1]-1].currentTorque = rx_data[2] | rx_data[3] << 8;
				listOfMotors[motorLookup[motorID-1]-1].currentSpeed = rx_data[4] | rx_data[5] << 8;
				break;
			case LK_READ_ANGLE_SINGLE:
				listOfMotors[motorLookup[motorID-1]-1].currentAngleSingle = (uint32_t)rx_data[4] | (uint32_t)rx_data[5] << 8 | (uint32_t)rx_data[6] << 16 | (uint32_t)rx_data[7] << 24;
				break;
			case LK_READ_ANGLE_MULTI:
				listOfMotors[motorLookup[motorID-1]-1].currentAngleMulti = (int64_t)rx_data[1] | (int64_t)rx_data[2] << 8 | (int64_t)rx_data[3] << 16 | (int64_t)rx_data[4] << 24 | (int64_t)rx_data[5] << 32 | (int64_t)rx_data[6] << 40 | (int64_t)rx_data[7] << 48;
				break;
			case LK_READ_ERROR:
				listOfMotors[motorLookup[motorID-1]-1].errorState = rx_data[7];
				break;
		}

		//count number of recieves since last send in the lower nibble of recieveCounter
		//listOfMotors[motorLookup[motorID-1]-1].recieveCounter=((listOfMotors[motorLookup[motorID-1]-1].recieveCounter&0x0f)+1)&0xf;
}

/* Description: Sends all the currently available motor packages with a builtin delay of x milliseconds
 * Input: delay in milliseconds between send cycle
 */
void CAN_LK_Update(uint8_t delay){

	//wait for the number of delay iterations
	if(waitCount<delay-1){
		waitCount++;
	}else{

		//iterate through list of active motors and send the according message
		for(uint8_t i = 0;i<activeMotors;i++){
			if(listOfMotors[i].currentBus){
				// For each non-empty command byte,
				for (uint8_t j = 0; j<sizeof(listOfMotors[i].commandBytes);j++) {

					uint8_t txBuff[8] = {0};

					switch(listOfMotors[i].commandBytes[j]) {
						case LK_MOTOR_OFF:
							txBuff[0] = LK_MOTOR_OFF;
							break;
						case LK_MOTOR_ON:
							txBuff[0] = LK_MOTOR_ON;
							break;
						case LK_MOTOR_STOP:
							txBuff[0] = LK_MOTOR_STOP;
							break;
						case LK_SET_POWER_OPEN:
							txBuff[0] = LK_SET_POWER_OPEN;
							txBuff[4] = (listOfMotors[i].sendTorque & 0x00ff) ;
							txBuff[5] = (listOfMotors[i].sendTorque & 0xff00) >> 8;
							break;
						case LK_SET_POWER_CLOSED:
							txBuff[0] = LK_SET_POWER_CLOSED;
							txBuff[4] = (listOfMotors[i].sendTorque & 0x00ff) ;
							txBuff[5] = (listOfMotors[i].sendTorque & 0xff00) >> 8;
							break;
						case LK_SET_SPEED:
							txBuff[0] = LK_SET_SPEED;
							txBuff[4] = (listOfMotors[i].sendSpeed & 0x000000ff);
							txBuff[5] = (listOfMotors[i].sendSpeed & 0x0000ff00) >> 8;
							txBuff[6] = (listOfMotors[i].sendSpeed & 0x00ff0000) >> 16;
							txBuff[7] = (listOfMotors[i].sendSpeed & 0xff000000) >> 24;
							break;
						case LK_SET_ANGLE_MULTI:
							txBuff[0] = LK_SET_ANGLE_MULTI;
							txBuff[4] = (listOfMotors[i].sendAngleMulti & 0x000000ff);
							txBuff[5] = (listOfMotors[i].sendAngleMulti & 0x0000ff00) >> 8;
							txBuff[6] = (listOfMotors[i].sendAngleMulti & 0x00ff0000) >> 16;
							txBuff[7] = (listOfMotors[i].sendAngleMulti & 0xff000000) >> 24;
							break;
						// more commands below
						case LK_SET_ANGLE_MULTI_LIM:
							txBuff[0] = LK_SET_ANGLE_MULTI_LIM;
							txBuff[2] = listOfMotors[i].sendMaxSpeed & 0x00ff;
							txBuff[3] = (listOfMotors[i].sendMaxSpeed & 0xff00) >> 8 ;
							txBuff[4] = (listOfMotors[i].sendAngleMulti & 0x000000ff);
							txBuff[5] = (listOfMotors[i].sendAngleMulti & 0x0000ff00) >> 8;
							txBuff[6] = (listOfMotors[i].sendAngleMulti & 0x00ff0000) >> 16;
							txBuff[7] = (listOfMotors[i].sendAngleMulti & 0xff000000) >> 24;
							break;
						case LK_SET_ANGLE_SINGLE:
							txBuff[0] = LK_SET_ANGLE_SINGLE;
							txBuff[1] = listOfMotors[i].sendSpinDirection;
							txBuff[4] = (listOfMotors[i].sendAngleSingle & 0x000000ff);
							txBuff[5] = (listOfMotors[i].sendAngleSingle & 0x0000ff00) >> 8;
							txBuff[6] = (listOfMotors[i].sendAngleSingle & 0x00ff0000) >> 16;
							txBuff[7] = (listOfMotors[i].sendAngleSingle & 0xff000000) >> 24;
							break;
						case LK_SET_ANGLE_SINGLE_LIM:
							txBuff[0] = LK_SET_ANGLE_SINGLE_LIM;
							txBuff[1] = listOfMotors[i].sendSpinDirection;
							txBuff[2] = listOfMotors[i].sendMaxSpeed & 0x00ff;
							txBuff[3] = (listOfMotors[i].sendMaxSpeed & 0xff00) >> 8 ;
							txBuff[4] = (listOfMotors[i].sendAngleSingle & 0x000000ff);
							txBuff[5] = (listOfMotors[i].sendAngleSingle & 0x0000ff00) >> 8;
							txBuff[6] = (listOfMotors[i].sendAngleSingle & 0x00ff0000) >> 16;
							txBuff[7] = (listOfMotors[i].sendAngleSingle & 0xff000000) >> 24;
							break;
						case LK_READ_PID:
							txBuff[0] = LK_READ_PID;
							break;
						case LK_SET_PID:
							txBuff[0] = LK_SET_PID;
							txBuff[2] = listOfMotors[i].sendPosKp;
							txBuff[3] = listOfMotors[i].sendPosKi;
							txBuff[4] = listOfMotors[i].sendSpeedKp;
							txBuff[5] = listOfMotors[i].sendSpeedKi;
							break;
						case LK_READ_ANGLE_MULTI:
							txBuff[0] = LK_READ_ANGLE_MULTI;
							break;
						case LK_READ_ANGLE_SINGLE:
							txBuff[0] = LK_READ_ANGLE_SINGLE;
							break;
						case LK_READ_ERROR:
							txBuff[0] = LK_READ_ERROR;
							break;
						case LK_CLEAR_ERROR:
							txBuff[0] = LK_CLEAR_ERROR;
							break;
						case LK_READ_GENERAL:
							txBuff[0] = LK_READ_GENERAL;
							break;
						default:
							//UART_Printf(UART1,"Bad command: %d \r\n",listOfMotors[i].commandBytes[j]);
							txBuff[0] = 0x00;
						}
					if (txBuff[0] != 0x00) { // Only send valid commands
						//UART_Printf(UART2,"Motor: %d, Command byte: %d, Command: %d %d %d %d %d %d %d \r\n",i,txBuff[0], txBuff[1], txBuff[2], txBuff[3], txBuff[4], txBuff[5], txBuff[6], txBuff[7]);
						delay_us(250); // prevents overloading the can buffer idk?
						CAN_Transmit(listOfMotors[i].currentBus,listOfMotors[i].canId,txBuff);
					}
				}
				memset(listOfMotors[i].commandBytes, 0, sizeof(listOfMotors[i].commandBytes));
			}
		}
		waitCount = 0;
	}
}



uint8_t CAN_LK_Add_Motor(CAN_HandleTypeDef *hcanx, uint32_t canID_Lower){
	//stop creating motors if there are already 32 listed (to prevent excessive memory usage in case of misused function)
	if(activeMotors>8){
		return LK_OVERALLOCATION_ERROR;
	}

	//if the motor list is empty, create the list
	if(!activeMotors){

		listOfMotors = (LK_Motor_t*) malloc(sizeof(LK_Motor_t));
	    if (!listOfMotors) {
	        return LK_MALLOC_ERROR;
	    }

	//if the list already exists, append a motor to it
	}else{

		LK_Motor_t *temp = realloc(listOfMotors,(activeMotors+1)*sizeof(LK_Motor_t));
		if(temp){
			listOfMotors = temp;
		}else{
			free(temp);
			return LK_MALLOC_ERROR;
		}
	}

	//initialize the motor values according to the documentation
	listOfMotors[activeMotors].currentBus = hcanx;
	listOfMotors[activeMotors].canId = 0x140 + canID_Lower;
	listOfMotors[activeMotors].currentPos = 0x0;

	listOfMotors[activeMotors].sendSpinDirection = 0x00; // 0x00 for clockwise, 0x01 for CCW
	listOfMotors[activeMotors].sendMaxSpeed = 0x00;  // In degrees per second

	listOfMotors[activeMotors].sendAngleSingle = 0x0000; // In 0.01 degree increments
	listOfMotors[activeMotors].sendAngleMulti = 0x0000; // In 0.01 degree increments

	listOfMotors[activeMotors].sendSpeed = 0x0000; // In 0.01 degree per second increments

	listOfMotors[activeMotors].sendTorque = 0x00; // From -850 to 850 for MS motors, -2048 to 2048 for other motors

	listOfMotors[activeMotors].currentTorque = 0x00; // From -2048 to 2048
	listOfMotors[activeMotors].currentSpeed = 0x00; // In degrees per second
	listOfMotors[activeMotors].currentPos = 0x00; // From 0 -> 16383 for 1 revolution

	listOfMotors[activeMotors].currentAngleSingle = 0x0000; // In 0.01 degree increments
	listOfMotors[activeMotors].currentAngleMulti = 0x00000000; // In 0.01 degree increments

	listOfMotors[activeMotors].sendPosKp = 50;
	listOfMotors[activeMotors].sendPosKi = 50;
	listOfMotors[activeMotors].sendSpeedKp = 50;
	listOfMotors[activeMotors].sendSpeedKi = 50;

	memset(listOfMotors[activeMotors].commandBytes, 0, sizeof(listOfMotors[activeMotors].commandBytes));

	activeMotors++;

	//add the motor ID and the list index to the lookup table
	if(CAN_LK_Lookup_Insert(canID_Lower,activeMotors)){
		return LK_MALLOC_ERROR;
	}

	return 0;
}



/* Description: Take a canID lower order value and map it as an input to its current location in the listOfMotors array
 * 				ALL 1 INDEXED
 * Input: ID of the motor (1 indexed), the location of the motor in list of motors (1 indexed)
 * Return: If memory reallocation error: 220, else 0
 * Eg: Position of the motor initialization order in the array (1 indexed) is the motor ID (1 indexed)
 */
uint8_t CAN_LK_Lookup_Insert(uint32_t canID_Lower, uint8_t motorIndex){

	if(!motorLookupSize){

		motorLookup = (uint8_t*) malloc(canID_Lower*sizeof(uint8_t));
		motorLookupSize = canID_Lower;

		for(uint8_t i = 0;i<canID_Lower-1;i++){
			motorLookup[i] = 0;
		}

	}
	else if(motorLookupSize<canID_Lower){

		uint8_t *temp = realloc(motorLookup,(canID_Lower)*sizeof(uint8_t));

		if(temp){
			motorLookup = temp;
		}else{
			free(temp);
			return LK_MALLOC_ERROR;
		}

		for(uint8_t i = motorLookupSize;i<canID_Lower;i++){
			motorLookup[i] = 0;
		}

		motorLookupSize = canID_Lower;

	}

	motorLookup[canID_Lower-1] = motorIndex;

	return 0;
}



/* Description: Sets the torque to be sent next package.
 * Input: motorID, driving torque from -850 to 850 for MS motors and from -2048 to 2048 for other motors
 */
void setLKTorque(uint8_t motorID, int16_t drivingTorque, uint8_t motorType) {
	if(motorLookupSize<motorID){
		return;
	}

	if(motorLookup[motorID-1]==0){
		return;
	}
	clearMotionCmds(motorID);
	listOfMotors[motorLookup[motorID-1]-1].sendTorque = drivingTorque;
	if (motorType == MOTOR_MS) {
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[3] = LK_SET_POWER_OPEN;
	} else {
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[4] = LK_SET_POWER_CLOSED;
	}
}

/* Description: Gets the motor torque
 *Input: motorID
 *Output: returns the motor torque current from -33 to 33A (will also return 0 if there is an error)
 */
float getLKTorque(uint8_t motorID) {
	if(motorLookupSize<motorID){
		return 0;
	}

	if(motorLookup[motorID-1]==0){
		return 0;
	}
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[16] = LK_READ_GENERAL;
	return (float) (listOfMotors[motorLookup[motorID-1]-1].currentTorque * (33/2048)); // Converts degrees per second to RPM
}
//
///* Description: Gets the last received value of motor speed
// * Input: motorID to get
// * Return: returns the current value of motor speed in RPM (will also return 0 if there is an error)
// */
float getLKRPM(uint8_t motorID) {
	if(motorLookupSize<motorID){
		return 0;
	}

	if(motorLookup[motorID-1]==0){
		return 0;
	}
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[16] = LK_READ_GENERAL;
	return (float) ((listOfMotors[motorLookup[motorID-1]-1].currentSpeed)/6.0); // Converts degrees per second to RPM
}

///* Description: Sets the motor target speed using the built-in PI controller
// * Input: motorID, target velocity in RPM, kp from 0 to 250, and ki from 0 to 250
void setLKRPM(uint8_t motorID, float RPM, uint8_t kp, uint8_t ki) {
	if(motorLookupSize<motorID){
		return;
	}

	if(motorLookup[motorID-1]==0){
		return;
	}
	clearMotionCmds(motorID);
	listOfMotors[motorLookup[motorID-1]-1].sendSpeed = (int32_t) (600.0 * RPM);
	// only send PI values if they are different to not overload the bus
	if ((listOfMotors[motorLookup[motorID-1]-1].sendSpeedKp != kp) || (listOfMotors[motorLookup[motorID-1]-1].sendSpeedKi != ki)) {
		listOfMotors[motorLookup[motorID-1]-1].sendSpeedKp = kp;
		listOfMotors[motorLookup[motorID-1]-1].sendSpeedKi = ki;
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[11] = LK_SET_PID;
	}
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[5] = LK_SET_SPEED;
}


/* Description: Gets the last single turn angle of motor position
 * Input: motorID to get
 * Return: returns the current value of motor position, value from 0 to 36000 (0.01 degrees per tick)
 */
uint32_t getLKAngleSingle(uint8_t motorID){
	if(motorLookupSize<motorID){
		return 0;
	}
	if(motorLookup[motorID -1]==0){
		return 0;
	}

	// return (listOfMotors[motorLookup[(motorID & LK_ID_MASK)-1]-1].currentPos&LK_POS_MASK);
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[13] = LK_READ_ANGLE_SINGLE;
	return listOfMotors[motorLookup[motorID-1]-1].currentAngleSingle;
}

/* Description: Gets the last multi turn rotation angle of motor position
 * Input: motorID to get
 * Return: returns the current value of motor position, each 36000 is 1 rotation (0.01 degrees per tick)
 */
int64_t getLKAngleMulti(uint8_t motorID){
	if(motorLookupSize<motorID){
		return 0;
	}
	if(motorLookup[motorID -1]==0){
		return 0;
	}

	// return (listOfMotors[motorLookup[(motorID & LK_ID_MASK)-1]-1].currentPos&LK_POS_MASK);
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[12] = LK_READ_ANGLE_MULTI;
	return listOfMotors[motorLookup[motorID-1]-1].currentAngleMulti;
}

/* Description: Sets the single rotation angle using the built-in PD controller
 * Input: motorID to set, target angle (from 0 to 36000), an optional speed limit (0 if you don't want a speed limit)
 * the proportional constant to use (from 0 to 250), the derivative constant to use (from 0 to 250),
 * and the spin direction (0x00 for clockwise, 0x01 for counter clockwise)
 */
void setLKAngleSingle(uint8_t motorID, uint32_t targetAngle, uint16_t rpmLimit, uint8_t kp, uint8_t ki, uint8_t spinDirection) {
	if(motorLookupSize<motorID){
		return;
	}

	if(motorLookup[motorID-1]==0){
		return;
	}
	clearMotionCmds(motorID);
	listOfMotors[motorLookup[motorID-1]-1].sendAngleSingle = targetAngle;
	listOfMotors[motorLookup[motorID-1]-1].sendSpinDirection = spinDirection;
	// only send PI values if they are different to not overload the bus
	if ((listOfMotors[motorLookup[motorID-1]-1].sendPosKp != kp) || (listOfMotors[motorLookup[motorID-1]-1].sendPosKi != ki)) {
		listOfMotors[motorLookup[motorID-1]-1].sendPosKp = kp;
		listOfMotors[motorLookup[motorID-1]-1].sendPosKi = ki;
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[11] = LK_SET_PID;
	}

	if (rpmLimit > 0) {
		listOfMotors[motorLookup[motorID-1]-1].sendMaxSpeed = rpmLimit * 6; // to convert rpm to degrees per second
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[9] = LK_SET_ANGLE_SINGLE_LIM;
	} else {
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[8] = LK_SET_ANGLE_SINGLE;
	}
}

/* Description: Sets the multi rotation angle using the built-in PD controller
 * Input: motorID to set, target angle (each rotation is 36000), an optional speed limit (0 if you don't want a speed limit)
 * the proportional constant to use (from 0 to 250), and the derivative constant to use (from 0 to 250),
 */
void setLKAngleMulti(uint8_t motorID, int32_t targetAngle, uint16_t rpmLimit, uint8_t kp, uint8_t ki) {
	if(motorLookupSize<motorID){
		return;
	}

	if(motorLookup[motorID-1]==0){
		return;
	}

	listOfMotors[motorLookup[motorID-1]-1].sendAngleMulti = targetAngle;
	if ((listOfMotors[motorLookup[motorID-1]-1].sendPosKp != kp) || (listOfMotors[motorLookup[motorID-1]-1].sendPosKi != ki)) {
		listOfMotors[motorLookup[motorID-1]-1].sendPosKp = kp;
		listOfMotors[motorLookup[motorID-1]-1].sendPosKi = ki;
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[11] = LK_SET_PID;
	}

	clearMotionCmds(motorID);
	if (rpmLimit > 0) {
		listOfMotors[motorLookup[motorID-1]-1].sendMaxSpeed = rpmLimit * 6; // to convert rpm to degrees per second
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[7] = LK_SET_ANGLE_MULTI_LIM;
	} else {
		listOfMotors[motorLookup[motorID-1]-1].commandBytes[6] = LK_SET_ANGLE_MULTI;
	}
}

void clearMotionCmds(uint8_t motorID) {
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[3] = 0x00;
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[4] = 0x00;
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[5] = 0x00;
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[6] = 0x00;
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[7] = 0x00;
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[8] = 0x00;
	listOfMotors[motorLookup[motorID-1]-1].commandBytes[9] = 0x00;

}

void delay_us(uint16_t us)
{
    uint32_t ticks = 0;
    uint32_t told = 0;
    uint32_t tnow = 0;
    uint32_t tcnt = 0;
    uint32_t reload = 0;
    reload = SysTick->LOAD;
    ticks = us * 168;
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told) {
                tcnt += told - tnow;
            } else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}
//
//uint8_t getLKStatus(uint8_t motorID){
//	return listOfMotors[motorLookup[(motorID & LK_ID_MASK)-1]-1].status;
//}

#endif

# CAN\_LKMotors

### Overview

This library provides a control layer for LingKong motors (under the MS, MF, MH, and MG series) *Note: MF, MH, and MG functionality is WIP*

Tested motors:
- MS4005 V3


### Dependancies


``CAN_Core.h``



### IOC Setup

###### Can 1:

1. Open the .ioc editor window by double clicking on your .ioc file in the Project Explorer view
2. Click on "CAN1" in the "Connectivity" drop down
3. Check the "Activated" check box
4. In the "Parameter Settings" tab do the following in order

   1. Set "Time Quanta in Bit Segment 1" to 10
   2. Then set "Time Quanta in Bit Segment 2" to 3
   3. Then set "Prescaler (for Time Quantum)" to 3
   4. To verify you did this correctly, make sure that the "Time for one Bit" is 1000ns and the "Baud Rate" is 1000000 bit/s
5. Go to the "NVIC Settings" tab and click the "Enabled" checkbox next to "CAN1 RX0 interrupts"
6. Go to the view of the processor pinout (the page with all the circles) and do the following

   1. Find "PD0", click on it and set it to "CAN1\_RX"
   2. Find "PD1" (just below PD0), click on it and set it to "CAN1\_TX"

7\. Generate the code



###### Can 2:

1. Open the .ioc editor window by double clicking on your .ioc file in the Project Explorer view
2. Click on "CAN2" in the "Connectivity" drop down
3. Check the "Activated" check box
4. In the "Parameter Settings" tab do the following in order

   1. Set "Time Quanta in Bit Segment 1" to 10
   2. Then set "Time Quanta in Bit Segment 2" to 3
   3. Then set "Prescaler (for Time Quantum)" to 3
   4. To verify you did this correctly, make sure that the "Time for one Bit" is 1000ns and the "Baud Rate" is 1000000 bit/s
5. Go to the "NVIC Settings" tab and click the "Enabled" checkbox next to "CAN2 RX0 interrupts"
6. Generate the code



### Include Setup

1. Navigate to your main.h file

2\. Include the CAN\_Core, CAN\_LKotors and PID libraries by adding the following to the file in the "USER CODE BEGIN Includes" section:

&#x09;``#define INCLUDE_CAN_CORE``

&#x09;``#include "CAN_Core.h"``



&#x09;``#define INCLUDE_CAN_LKMOTORS``

&#x09;``#include "CAN_LKMotors.h"``


### Library Handler Setup

1. Navigate to the "StartLibraryHandler" task in your main.c file
2. After the "USER CODE BEGIN" comment, but before the for loop, do the following:

   1. Make sure that ``CAN_Init_Buses(``...``);`` is present, where "..." is a comma seperated list of the bus numbers you want to initialize. Eg: ``CAN_Init_Buses(BUS1, BUS2);``
   2. Then add ``CAN_LinkLib(CAN_LKMotors());`` to link the the LK Motor library to the CAN core library. If other libraries are also used, add both libraries to the linker function as a comma seperated list. Eg: ``CAN_LinkLib(CAN_OtherLib1(),CAN_OtherLib2(),CAN_LKMotors());``
   3. Then lastly add ``CAN_LK_InitMotor(``bus number``,``CAN ID``);`` for each motor you want to use. Eg: ``CAN_LK_InitMotor(1,1);``
3. Lastly inside the infinite loop add ``CAN_LK_Update(``1``);``
   the 1 can be replaced with the value of the delay you want in the send cycles. Increase this value if your CAN bus is getting flooded



### Functions

| Function | ``void setLKTorque(uint8_t motorID, int16_t drivingTorque)`` | Sets the open loop torque to be sent to the motor|
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Parameter | drivingTorque | The target torque used to drive the motor. Integer values range from -850 to 850 (int16\_t) |
| Returns | void | |

<br>

| Function | ``float getLKTorque(uint8_t motorID)`` | returns the motor torque current|
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Returns | float | The motor torque current from -33 to 33 Amps (will also return 0 if there is an error)|

<br>

| Function | ``float getLKRPM(uint8_t motorID)`` | returns the motor rpm|
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Returns | float | The motor speed in RPM (will also return 0 if there is an error|

<br>

| Function | ``void setLKRPM(uint8_t motorID, float RPM, uint8_t kp, uint8_t ki)`` | Sets the closed loop RPM of the motor |
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Parameter | RPM | The speed in RPM you want the motor to spin up to, negative values spin in the opposite direction (float) |
| Parameter | kp | The kP value for the motor's internal PI controller, ranges from 0 to 250. The default value is 50 (uint8\_t) |
| Parameter | ki | The kI value for the motor's internal PI controller, ranges from 0 to 250. The default value is 50 (uint8\_t) |
| Returns | void | |

<br>

| Function | ``uint32_t getLKAngleSingle(uint8_t motorID)`` | returns the single turn motor angle|
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Returns | uint32_t | The last absolute angle of the motor from 0 to 36000 (0.01 degree increments) (will also return 0 if there is an error)|

<br>

| Function | ``int64_t getLKAngleMulti(uint8_t motorID)`` | returns the multi turn motor angle|
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Returns | int64_t | The last multi turn angle of the motor. Each 36000 ticks is 1 rotation (will also return 0 if there is an error)|

<br>

| Function | ``void setLKAngleSingle(uint8_t motorID, uint32_t targetAngle, uint16_t rpmLimit, uint8_t kp, uint8_t ki, uint8_t spinDirection)`` | Sets the target closed-loop single rotation angle going either clockwise or counterclockwise |
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Parameter | targetAngle | The target single turn angle you want the motor to go to. Ranges from 0 to 36000 (uint32\_t) |
| Parameter | rpmLimit | An optional limit for the rpm the motor can at rotate to reach the target position (use 0 if you do not want an RPM limit) (uint16\_t) |
| Parameter | kp | The kP value for the motor's internal PI controller, ranges from 0 to 250 (default is 50) (uint8\_t) |
| Parameter | ki | The kI value for the motor's internal PI controller, ranges from 0 to 250 (default is 50) (uint8\_t) |
| Parameter | spinDirection | The direction the motor spins to reach its target. 0 for clockwise, 1 for counter clockwise (uint8\_t) |
| Returns | void | |
| Notes: | | <mark> Be careful when using this function discontinuously as if the target angle is overshot, the motor will attempt to spin an entire rotation to reach the position again. |

<br>

| Function | ``void setLKAngleMulti(uint8_t motorID, int32_t targetAngle, uint16_t rpmLimit, uint8_t kp, uint8_t ki)`` | Sets the target closed-loop multi rotation angle |
| -------- | ----------------------------- | --------- |
| Parameter | motorID | The ID number of the motor controller you want to target. It can be set on the back of the motor using its DIP switch (uint8\_t) |
| Parameter | targetAngle | The target multi turn angle you want the motor to go to. Each turn is 36000 (int16\_t) |
| Parameter | rpmLimit | An optional limit for the rpm the motor can at rotate to reach the target position (use 0 if you do not want an RPM limit) (uint16\_t) |
| Parameter | kp | The kP value for the motor's internal PI controller, ranges from 0 to 250 (default is 50) (uint8\_t) |
| Parameter | ki | The kI value for the motor's internal PI controller, ranges from 0 to 250 (default is 50) (uint8\_t) |
| Returns | void | |






/*
 * CC_Package.h
 *
 *  Created on: Jun 19, 2026
 *      Author: Jason
 */

#ifndef INC_CC_PACKAGE_H_
#define INC_CC_PACKAGE_H_

typedef struct __attribute__ ((packed)){
	uint16_t theta1; // from 0 to 36000
	uint16_t theta2; // from 0 to 36000
	uint16_t theta3; // from 0 to 36000
	uint16_t theta4; // from 0 to 36000
	uint16_t theta5; // from 0 to 36000
	uint16_t theta6; // from 0 to 36000
	uint8_t watchdog; // should be ticking up from 0 to 255
	uint8_t datumSet:1; // 1 means datum set, 0 means datum not set
}CC_Package_t;

#endif /* INC_CC_PACKAGE_H_ */

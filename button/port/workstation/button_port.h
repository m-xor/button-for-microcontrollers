/*
 * button/button_port.h
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#ifndef BUTTON_PORT_H_
#define BUTTON_PORT_H_

typedef unsigned ButtonPort;

/**
 * Global variable for testing purposes
 */
ButtonPort dummyPort;

static inline ButtonPort Button_raw(void)
{
	return (dummyPort);
}

#endif /* BUTTON_PORT_H_ */

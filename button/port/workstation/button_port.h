/*
 * button/button_port.h
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#ifndef BUTTON_PORT_H_
#define BUTTON_PORT_H_

#include "button_config.h"

/** \typedef typedef unsigned ButtonPort;
 *  \brief defines type of input port (platform dependent)
 */
typedef unsigned ButtonPort;

/**
 * Global variable for testing purposes
 */
ButtonPort dummyPort;

/** \fn static inline ButtonPort Button_raw(void)
 *  \brief reads input port (platform dependend)
 * @return ButtonPort input port state
 */
static inline ButtonPort Button_raw(void)
{
	return (dummyPort);
}

#endif /* BUTTON_PORT_H_ */

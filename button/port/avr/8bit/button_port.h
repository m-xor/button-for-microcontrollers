/*
 * button/button_port.h
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#ifndef BUTTON_PORT_H_
#define BUTTON_PORT_H_

#include "button_config.h"
#include <stdint.h>

/** \typedef typedef unsigned ButtonPort;
 *  \brief defines type of input port (platform dependent)
 */
typedef uint8_t ButtonPort;

/** \fn static inline ButtonPort Button_raw(void)
 *  \brief reads input port (platform dependend)
 * @return ButtonPort input port state
 */
static inline ButtonPort Button_raw(void)
{
	return BUTTON_IN_PORT;
}

/** \fn static inline void Button_initInputs(void)
 *  \brief Helper function to set on pull up
 */
static inline void Button_initInputs(void)
{
	/* pull up button inputs */
	*((&BUTTON_IN_PORT)+2) = (BTN0|BTN1|BTN2);
}

#endif /* BUTTON_PORT_H_ */

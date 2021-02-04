/*
 * button/button_config.h
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#ifndef BUTTON_CONFIG_H_
#define BUTTON_CONFIG_H_

#include <avr/io.h>

#define BTN0 (1<<0)
#define BTN1 (1<<3)
#define BTN2 (1<<5)

#define BUTTON_IN_PORT PINC


/** \def
 *  \brief Mandatory definition
 *
 */
#define BUTTON_MASK (BTN0|BTN1|BTN2)
/** \def
 *  \brief Mandatory definition
 */
#define BUTTON_ACTIVE_HIGH (0)

#endif /* BUTTON_CONFIG_H_ */

/*
 * button/button_config.h
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#ifndef BUTTON_CONFIG_H_
#define BUTTON_CONFIG_H_

#define BTN0 (1<<0)
#define BTN1 (1<<3)
#define BTN2 (1<<6)

/** \def BUTTON_MASK
 *  \brief Defines mask for all observed inputs
 *
 *  \warning Mandatory definition
 */
#define BUTTON_MASK (BTN0|BTN1|BTN2)

/** \def BUTTON_ACTIVE_HIGH
 *  \brief Defines mask for inputs which have active state HIGH
 *  \warning Mandatory definition
 */
#define BUTTON_ACTIVE_HIGH (BTN2)

#endif /* BUTTON_CONFIG_H_ */

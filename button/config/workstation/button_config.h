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
#define BUTTON_MASK (BTN0|BTN1|BTN2)
#define BUTTON_ACTIVE_LOW (BTN0|BTN1)

#endif /* BUTTON_CONFIG_H_ */

/*
 * button/button.h
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "button_port.h"

/** \typedef typedef void (*BtnClbck)(ButtonPort buttons);
 *  \brief Type of "press" and "release" events callbacks
 *
 * @param buttons Mask of "pressed" or "released" buttons
 */
typedef void (*BtnClbck)(ButtonPort buttons);

/** \class typedef struct Button Button
 *  \brief Button class
 */
typedef struct Button {
	BtnClbck pressedClbck;
	BtnClbck releasedClbck;
	ButtonPort asserted;
	ButtonPort previous;
} Button;

/** \fn static inline void Button_ctor(Button * const me, BtnClbck pressed, BtnClbck released)
 *
 * @param me	pointer to instance of Button class
 * @param pressed pointer to press event callback
 * @param released pointer to released event callback
 */
static inline void Button_ctor(Button * const me, BtnClbck pressed, BtnClbck released)
{
	me->pressedClbck = pressed;
	me->releasedClbck = released;
	me->asserted = (ButtonPort)(BUTTON_ACTIVE_HIGH^BUTTON_MASK);
	me->previous = (ButtonPort)(BUTTON_ACTIVE_HIGH^BUTTON_MASK);
}

/** \fn static inline void Button_service(Button * const me)
 *  \brief Button polling function
 *
 *  Function should be invoked periodically. Period should allow realizing
 *  reliable debouncing.
 *
 * @param me	pointer to instance of Button class
 */
static inline void Button_service(Button * const me)
{
	ButtonPort current = Button_raw();
	ButtonPort tmp = me->asserted;

	me->asserted |= (me->previous & current); /* Assert newly "on" inputs */
	me->asserted &= (me->previous | current); /* Clear newly "off" inputs */

	me->previous = current;
	tmp ^= me->asserted; /* anything has changed? */
	tmp &= (ButtonPort)BUTTON_MASK;  /* get rid of unneeded bits */

	if(tmp) { /* a button event has occurred */
		ButtonPort result = me->asserted ^ (ButtonPort)(BUTTON_ACTIVE_HIGH^BUTTON_MASK); /* revert button with reverted logic */
		if( (tmp & result) && me->pressedClbck ) { /* that was pressing */
			(*me->pressedClbck)(tmp&result);
		}
		if( (tmp & ~result) && me->releasedClbck ) { /* that was releasing */
			(*me->releasedClbck)(tmp&~result);
		}
	}

}

/** \fn static inline void Button_registerPress(Button * const me, BtnClbck press)
 *  \brief Registers callback for press event
 *
 * @param me pointer to instance of Button class
 * @param press pointer to press event callback
 */
static inline void Button_registerPress(Button * const me, BtnClbck press)
{
	me->pressedClbck = press;
}

/** \fn static inline void Button_registerRelease(Button * const me, BtnClbck release)
 *  \brief Registers callback for release event
 *
 * @param me pointer to instance of Button class
 * @param release pointer to released event callback
 */
static inline void Button_registerRelease(Button * const me, BtnClbck release)
{
	me->releasedClbck = release;
}

#endif /* BUTTON_H_ */

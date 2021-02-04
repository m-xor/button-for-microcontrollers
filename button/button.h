/*
 * button/button.h
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "button_port.h"

typedef void (*BtnClbck)(ButtonPort buttons);
typedef struct Button {
	BtnClbck pressedClbck;
	BtnClbck releasedClbck;
	ButtonPort asserted;
	ButtonPort previous;
} Button;

static inline void Button_ctor(Button * const me, BtnClbck pressed, BtnClbck released)
{
	me->pressedClbck = pressed;
	me->releasedClbck = released;
	me->asserted = (ButtonPort)(BUTTON_ACTIVE_HIGH^BUTTON_MASK);
	me->previous = (ButtonPort)(BUTTON_ACTIVE_HIGH^BUTTON_MASK);
}

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

static inline void Button_registerPress(Button * const me, BtnClbck press)
{
	me->pressedClbck = press;
}

static inline void Button_registerRelease(Button * const me, BtnClbck release)
{
	me->releasedClbck = release;
}

#endif /* BUTTON_H_ */

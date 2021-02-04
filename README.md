## To use:
* define include path to appriopriate port file "button_port.h"
* define include path to appriopriate config file "button_config.h"
* define global (or local) variable of Button type and export variable to every file timer is in use (if applicable).
* include button.h file in every file timer is in use.
* invoke Button_service in fixed intervals. If called from within interrupt service routine  be aware that callbacks'll be runnging in interrupt context.

## Usage example
ATmega328p

```
/* main.c */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "software_timer.h"
#include "button.h"


#define BUTTON_PERIOD_MS 20
#define LED_BLINK 250

Timer buttonPoll;
Timer ledBlink;

Button btns;

void press(ButtonPort mask);
void release(ButtonPort mask);

void led_init(void);
void led_toggle(void);
void led_off(void);

int main() __attribute__((OS_main));
int main()
{
    timer_init();
    led_init();

    Timer_ctor(&buttonPoll);
    Timer_setPeriod(&buttonPoll, TICKS(BUTTON_PERIOD_MS,HARDWARE_TICK_MS));

    Timer_ctor(&ledBlink);
    Timer_setPeriod(&ledBlink, TICKS(LED_BLINK, HARDWARE_TICK_MS));

    /* pull ups on inputs */
    Button_initInputs();
    /* Button class constructor */
    Button_ctor(&btns,press,release);

    sei();

    while(1)
    {
        /* called every BUTTON_PERIOD_MS milliseconds */
        if(Timer_isTime(&buttonPoll)) {
            Button_service(&btns);
            Timer_setPeriod(&buttonPoll, TICKS(BUTTON_PERIOD_MS,HARDWARE_TICK_MS));
        }

        if(Timer_isTime(&ledBlink)) {
            led_toggle();
            Timer_setPeriod(&ledBlink, TICKS(LED_BLINK, HARDWARE_TICK_MS));
        }
    }

}

void press(ButtonPort mask)
{
    /* use mask parameter to identify which button was just pressed */

    Timer_activate(&ledBlink,0);
    led_off();
}

void release(ButtonPort mask)
{
    /* if needed use mask parameter to identify which button was just released */
    Timer_activate(&ledBlink,1);
}

void led_init(void)
{
    DDRB = _BV(5);
}

void led_toggle(void)
{
    PINB = _BV(5);
}

void led_off(void)
{
    PORTB &= ~_BV(5);
}

/* timer.h */

#define HARDWARE_TICK_MS 4

/* timer.c */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "software_timer.h"

Timer buttonPoll;
Timer ledBlink;

void timer_init(void)
{
    TIMSK0 = _BV(TOIE0);
    TCCR0B = _BV(CS02);
}


ISR(TIMER0_OVF_vect)
{
    Timer_count(&buttonPoll);
    Timer_count(&ledBlink);
}
```

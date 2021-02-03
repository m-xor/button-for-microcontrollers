/*
 * button/main.c
 *
 *  Created on: 3 lut 2021
 *      Author: slawek
 */

#include <stdio.h>
#include "minunit.h" /* http://www.jera.com/techinfo/jtns/jtn002.html */
#include "button.h"

int tests_run = 0;

/*
 * Helpers
 */
static ButtonPort getEvent(ButtonPort evt)
{
	#define PORT (ButtonPort)0xaa55
//#define PORT (ButtonPort)0
	/*
	 * Let Btn0 and Btn1 active state be LOW
	 * Btn2 active state HIGH
	 */
	ButtonPort result = PORT;

	if(evt & BTN0) {
		result &= ~(BTN0);
	} else {
		result |= (BTN0);
	}

	if(evt & BTN1) {
		result &= ~(BTN1);
	} else {
		result |= (BTN1);
	}

	if(! (evt & BTN2) ) {
		result &= ~(BTN2);
	} else {
		result |= (BTN2);
	}

	return result;
}

ButtonPort pressResult;
ButtonPort releaseResult;

static void press(ButtonPort btns)
{
	pressResult = btns;
}

static void release(ButtonPort btns)
{
	releaseResult = btns;
}

/*
 * Tests
 */
static char * test_not_pressing() {
	dummyPort = getEvent(0); /* all buttons inactive */
	pressResult = 0;
	releaseResult = 0;
	Button instance;
	Button_ctor(&instance, press, release);

	Button_service(&instance);
	Button_service(&instance); /* debounced */
	mu_assert("error, not_pressing press", !pressResult);
	mu_assert("error, not_pressing release", !releaseResult);
  return 0;
}

static char * test_pressing() {
	dummyPort = getEvent(0); /* all buttons inactive */
	pressResult = 0;
	//releaseResult = 0;
	Button instance;
	Button_ctor(&instance, press, release);

	dummyPort = getEvent(BTN0); /* press 0 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	mu_assert("error, pressing press 0", pressResult&BTN0);
	//mu_assert("error, pressing release 0", !releaseResult);

	//pressResult = 0;
	dummyPort = getEvent(BTN1); /* press 1 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	mu_assert("error, pressing press 1", pressResult&BTN1);
	//mu_assert("error, pressing release 1", !releaseResult);

	//pressResult = 0;
	dummyPort = getEvent(BTN2); /* press 2 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	mu_assert("error, pressing press 2", pressResult&BTN2);
	//mu_assert("error, pressing release 2", !releaseResult);

	dummyPort = getEvent(BTN0|BTN1|BTN2); /* press all */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	mu_assert("error, pressing press all", pressResult&(BTN0|BTN1|BTN2));

  return 0;
}

static char * test_after_pressing() {
	dummyPort = getEvent(0); /* all buttons inactive */
	pressResult = 0;
	//releaseResult = 0;
	Button instance;
	Button_ctor(&instance, press, release);

	dummyPort = getEvent(BTN0); /* press 0 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	pressResult = 0;
	Button_service(&instance);
	mu_assert("error, after_pressing press 0", !pressResult);
	//mu_assert("error, after_pressing release 0", !releaseResult);

	pressResult = 0;
	dummyPort = getEvent(BTN1); /* press 1 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	pressResult = 0;
	Button_service(&instance);
	mu_assert("error, after_pressing press 1", !pressResult);
	//mu_assert("error, after_pressing release 1", !releaseResult);

	pressResult = 0;
	dummyPort = getEvent(BTN2); /* press 2 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	pressResult = 0;
	Button_service(&instance);
	mu_assert("error, after_pressing press 2", !pressResult);
	//mu_assert("error, after_pressing release 2", !releaseResult);

	return 0;
}

static char * test_releasing() {
	dummyPort = getEvent(0); /* all buttons inactive */
	releaseResult = 0;
	Button instance;
	Button_ctor(&instance, press, release);

	dummyPort = getEvent(BTN0); /* press 0 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	dummyPort = getEvent(0); /* press none */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	//mu_assert("error, after_releasing press 0", pressResult&BTN0);
	mu_assert("error, releasing release 0", releaseResult&BTN0);

	dummyPort = getEvent(BTN1); /* press 1 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	dummyPort = getEvent(0); /* press none */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	//mu_assert("error, after_pressing press 1", !pressResult);
	mu_assert("error, releasing release 1", releaseResult&BTN1);

	dummyPort = getEvent(BTN2); /* press 2 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	dummyPort = getEvent(0); /* press none */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
//	mu_assert("error, after_pressing press 2", !pressResult);
	mu_assert("error, releasing release 2", releaseResult&BTN2);

	dummyPort = getEvent(BTN0|BTN1|BTN2); /* press all */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	dummyPort = getEvent(0); /* press none */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
//	mu_assert("error, after_pressing press 2", !pressResult);
	mu_assert("error, releasing release 2", releaseResult&(BTN0|BTN1|BTN2));

	return 0;
}

static char * test_after_releasing() {
	dummyPort = getEvent(0); /* all buttons inactive */
	releaseResult = 0;
	Button instance;
	Button_ctor(&instance, press, release);

	dummyPort = getEvent(BTN0); /* press 0 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	dummyPort = getEvent(0); /* press none */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	releaseResult = 0;
	Button_service(&instance);
	//mu_assert("error, after_releasing press 0", pressResult&BTN0);
	mu_assert("error, after_releasing release 0", !releaseResult);

	dummyPort = getEvent(BTN1); /* press 1 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	dummyPort = getEvent(0); /* press none */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	releaseResult = 0;
	Button_service(&instance);
	//mu_assert("error, after_pressing press 1", !pressResult);
	mu_assert("error, after_releasing release 1", !releaseResult);

	dummyPort = getEvent(BTN2); /* press 2 */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	dummyPort = getEvent(0); /* press none */
	Button_service(&instance);
	Button_service(&instance); /* debounced */
	releaseResult = 0;
	Button_service(&instance);
//	mu_assert("error, after_pressing press 2", !pressResult);
	mu_assert("error, after_releasing release 2", !releaseResult);

	return 0;
}


/*
 * Result
 */

static char * all_tests() {
    mu_run_test(test_not_pressing);
    mu_run_test(test_pressing);
    mu_run_test(test_after_pressing);
    mu_run_test(test_releasing);
    mu_run_test(test_after_releasing);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

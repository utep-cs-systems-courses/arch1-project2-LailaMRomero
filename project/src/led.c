#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "stateMachine.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};


void led_init()

{

  P1DIR |= LEDS;// bits attached to leds are output
  switch_state_changed = 1;
  led_update();

}


void led_update(){
  if(switch_state_changed){
    char ledFlags = LED_RED; //by default, no LEDs on

    ledFlags |= switch_state_down ? LED_GREEN : LED_RED; //if button is pressed, turn LED Green, otherwise, LED Red

    P1OUT &= (0xff ^ LEDS) | ledFlags; //clear bits for off leds

    P1OUT |= ledFlags; //set bits for on leds

    

  }

  switch_state_changed = 0;

}

void toggle_green(){
  green_on=1;
  red_on=0;
}


char toggle_red()/* always toggle! */

{

  static char state = 0;
  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;

  case 1:
    red_on = 0;
    state = 0;
    break;

  }

  return 1;/* always changes an led */

}


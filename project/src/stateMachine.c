#include <msp430.h>

#include "stateMachine.h"

#include "led.h"



char toggle_red()/* always toggle! */

{

  static char state = 0;



  switch (state){

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



char toggle_green()/* only toggle green if red is on!  */

{

  char changed = 0;

  if (red_on) {

    green_on ^= 1;

    changed = 1;

  }

  return changed;

}



void state_advance() /* alternate between toggling red & green */

{
  switch(switch_state_changed){
  case 1:
    toggle_red();
    break;
  case 2:
    toggle_green();
    break;
  case 3:
    toggle_red();
    toggle_green();
    break;
  case 4:
    break;
  }
}
    



#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "switches.h"

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
  default:
  }
}
    



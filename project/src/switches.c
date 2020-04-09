#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachine.h"

char switch_state_down, switch_state_changed, tempo,s1,s2,s3,s4;
static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  //update switch interrupt to detect changes from current button
  P2IES |= (p2val & SWITCHES); //if switch up, sense down
  P2IES &= (p2val | ~SWITCHES); //if switch down, sense up
  return p2val;

}

void switch_init(){ //setup switch
  P2REN |= SWITCHES; //enables resistors for switches
  P2IE = SWITCHES; //enable interrupts from switches
  P2OUT |= SWITCHES; //pull-ups for switches
  P2DIR &= ~SWITCHES; //set switches' bits for input
}

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  s1 = (p2val & SW1) ? 0 : 1; //switch 1
  s2 = (p2val & SW2) ? 0 : 1; //switch 2
  s3 = (p2val & SW3) ? 0 : 1; //switch 3
  s4 = (p2val & SW4) ? 0 : 1; //switch 4
  buzzer_set_period(0);

  if( s1){ // when switch 1 is pressed the green and red leds will turn on and will play a song
    switch_state_down =s1;
    switch_state_changed=1;
    state_advance();
    tempo=5;
    song2();
    
  } else if (s3){ // when switch 3 is pressed the green and red leds will turn on and will play a song
   switch_state_down=s3;
   switch_state_changed=2; 
   tempo=14;
   song3();
   led_update();

  } else if (s4){  // when switch 4 is pressed the green and red leds will turn  on and will play a song
    buzzer_set_period(0);
    tempo=3;
    switch_state_down=s4;
    switch_state_changed=1;
    song1();
    led_update();
    
  } else if(s2){  // when switch 2 is pressed the leds will turn off and will play a song
    tempo=12;
    switch_state_changed=3;
    song4();
    led_update();
   
    
  } else {
    switch_state_down = 0;
    switch_state_changed = 1;
    buzzer_set_period(0);
  }
  switch_state_changed=1;
  led_update();
}

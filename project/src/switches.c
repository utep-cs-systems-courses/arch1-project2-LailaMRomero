#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"


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
  s1 = (p2val & SW1) ? 0 : 1;
  s2 = (p2val & SW2) ? 0 : 1;
  s3 = (p2val & SW3) ? 0 : 1;
  s4 = (p2val & SW4) ? 0 : 1;

  if( s1){
  switch_state_down =s1;
  switch_state_changed=1;
    tempo=5;
    song2();
    led_update();
  } else if (s3){
    switch_state_down=s2;
     switch_state_changed=1; 
    tempo=14;
   song3();
   led_update();

  } else if (s4){
    tempo=11;
    switch_state_down=s3;
    switch_state_changed=1;
    song1();
    led_update();
  } else if(s2){
    tempo=12;
    switch_state_down=s4;
    switch_state_changed=2;
    song4();
    led_update();
  }
  switch_state_changed=1;
  led_update();
}

#include "leds.h"

void leds::set_true(const char* color) {
    if (color == RED) {
        red_led.write( true );
        red_led.flush();
    } else if (color == GREEN) {
        green_led.write( true );
        green_led.flush();
    } else if (color == BLUE) {
        blue_led.write( true );
        blue_led.flush();
    } else return;
}

void leds::set_false(const char* color) {
    if (color == color::RED) {
        red_led.write( false );
        red_led.flush();
    } else if (color == color::GREEN) {
        green_led.write( false );
        green_led.flush();
    } else if (color == color::BLUE) {
        blue_led.write( false );
        blue_led.flush();
    } else return;
}
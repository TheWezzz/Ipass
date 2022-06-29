#include "servo.h"

void servo::angle(const unsigned int angle) {
    const unsigned int sleepsec = angle * 11 + 500;
    servo_pin.write( true );
    servo_pin.flush();
    hwlib::wait_us_busy( sleepsec );
    servo_pin.write( false );
    servo_pin.flush();
}

void servo::pos_set_to(const char* color) {
    if (color == color::RED) {
        angle( angle1 );
    } else if (color == color::GREEN) {
        angle( angle2 );
    } else if (color == color::BLUE) {
        angle( angle3 );
    } else return;
}

void servo::pos_set_to(double hue) {
    angle(180 - static_cast<int>(hue));
}
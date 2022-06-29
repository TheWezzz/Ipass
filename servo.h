#ifndef SERVO_H
#define SERVO_H

#include "hwlib.hpp"
#include "color.h"

class servo : public color{
private:
    hwlib::target::pin_out servo_pin = hwlib::target::pin_out( hwlib::target::pins::d2 );

    const unsigned int angle1 = 0;
    const unsigned int angle2 = 90;
    const unsigned int angle3 = 180;

public:
    servo() {

    };

    void angle(const unsigned int angle);

    void pos_set_to(const char* color);

    void pos_set_to(double hue);



};


#endif //SERVO_H//

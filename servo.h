#ifndef SERVO_H
#define SERVO_H

/*! \file */

#include "hwlib.hpp"
#include "color.h"

class servo : public color{
private:
    hwlib::target::pin_out servo_pin = hwlib::target::pin_out( hwlib::target::pins::d2 );

public:
    servo() {
    };

    /**
     * the variables in which the angles for the simple colors are stored.
     * may be changed to calibrate and match the three corresponding simple colors.
     */
    const unsigned int angle1 = 0;
    const unsigned int angle2 = 90;
    const unsigned int angle3 = 180;

    /**
     * used to set compute the time delay between setting the servo pin high and low.
     * @param angle the angle in degrees from 0 to 180 you want the servo to move to.
     */
    void angle(const unsigned int angle);

    /**
     * used to set the servo at one of three colors, matching the three possible const char*
     * @param color needs to be one of the three simple colors, to set the servo in the
     * corresponding angle.
     */
    void pos_set_to(const char* color);

    /**
     * used to set the servo at the exact hue thats given. hue is divided by two
     * to change the hue range from 0-360 to 0-180.
     * @param hue the hue to which you want the servo to point at.
     */
    void pos_set_to(double hue);



};


#endif //SERVO_H//

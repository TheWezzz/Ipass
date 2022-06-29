#ifndef V1OOPC_EXAMPLES_LEDS_H
#define V1OOPC_EXAMPLES_LEDS_H

#include "hwlib.hpp"
#include "color.h"

class leds : public color{
private:
    hwlib::target::pin_out red_led = hwlib::target::pin_out( hwlib::target::pins::a3 );
    hwlib::target::pin_out green_led = hwlib::target::pin_out( hwlib::target::pins::a4 );
    hwlib::target::pin_out blue_led = hwlib::target::pin_out( hwlib::target::pins::a5 );

public:
    leds() {

    };

    void set_true(const char* color);

    void set_false(const char* color);
};


#endif //V1OOPC_EXAMPLES_LEDS_H

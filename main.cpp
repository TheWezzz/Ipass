#include "hwlib.hpp"
#include "array"
#include "tcs3472.h"
#include "leds.h"
#include "servo.h"

bool get(hwlib::target::pin_in& pin) {
    return pin.read();
}

// MAIN ========================================================================

int main(void) {

    auto sda = hwlib::target::pin_oc( hwlib::target::pins::a0 );
    auto scl = hwlib::target::pin_oc( hwlib::target::pins::a1 );
    auto i2c = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );


    tcs3472 chip( i2c );
    leds l;
    servo s;
    auto button = hwlib::target::pin_in( hwlib::target::pins::d3 );

    const char* color;
    std::array<double, 3> hsl;


    while (true) {
        if (!get( button )) {
            continue;
        } else {

            color = chip.get_color();
            hsl = chip.get_hsl();

            int hue = static_cast<int>(hsl[0]);
            int sat = static_cast<int>(hsl[1]);
            int lum = static_cast<int>(hsl[2]);

            l.set_true( color );
            s.pos_set_to( hsl[0]);
            hwlib::wait_ms_busy( 250 );
            l.set_false( color );


            hwlib::cout
                    << hue
                    << ' '
                    << sat
                    << ' '
                    << lum
                    << '\n';

        }
    }
}

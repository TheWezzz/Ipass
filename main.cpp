#include "hwlib.hpp"
#include "array"
#include "tcs3472.h"
#include "leds.h"
#include "servo.h"

#include "catch.hpp"
#include "ostream"
#include "sstream"


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
            s.pos_set_to( hsl[0] / 2 );
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


//////////////////////////////////////////////
TEST_CASE( "leds" ){
leds l;
l.write();

s << v;
REQUIRE( s.str() == "[3,4]" );
}
//////////////////////////////////////////////
//TEST_CASE( "add vector to vector by positive" ){
//vector v( 20, 150 );
//std::stringstream s;
//
//vector x = v + vector( 5, 90 );
//s << x;
//REQUIRE( s.str() == "[25,240]" );
//
//s.str("");
//
//vector y = vector(50, 15) + v;
//s << y;
//REQUIRE( s.str() == "[70,165]" );
//}
////////////////////////////////////////////////
//TEST_CASE( "add vector to vector by negative" ){
//vector v( 50, 10 );
//std::stringstream s;
//
//vector x = v + vector( -75, 90 );
//s << x;
//REQUIRE( s.str() == "[-25,100]" );
//
//s.str("");
//
//vector y = vector(50, -15) + v;
//s << y;
//REQUIRE( s.str() == "[100,-5]" );
//}
////////////////////////////////////////////////
//TEST_CASE( "add to vector" ){
//vector v( 1, 2 );
//std::stringstream s;
//
//v += vector( 3, 20 );
//s << v;
//REQUIRE( s.str() == "[4,22]" );
//}
////////////////////////////////////////////////
//TEST_CASE( "multiply vector by integer" ){
//vector v( 5, 9 );
//std::stringstream s;
//
//vector x = v * 4;
//s << x;
//REQUIRE( s.str() == "[20,36]" );
//}
////////////////////////////////////////////////
//TEST_CASE( "multiply vector by vector" ){
//vector v( 45, 7 );
//std::stringstream s;
//
//vector x = v * vector( 3, 20 );
//s << x;
//REQUIRE( s.str() == "[135,140]" );
//
//s.str("");
//
//vector y = vector(1, 11) * v;
//s << y;
//REQUIRE( s.str() == "[45,77]" );
//}
////////////////////////////////////////////////
//TEST_CASE( "multiply vector" ){
//vector v( 11, 5 );
//std::stringstream s;
//
//v *= 11;
//s << v;
//REQUIRE( s.str() == "[121,55]" );
//}
////////////////////////////////////////////////
//

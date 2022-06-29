#include "tcs3472.h"

// WRITE/READ REGISTERS ========================================================

void tcs3472::write_reg_data(uint8_t& reg, uint8_t data) {
    {
        hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus * )( &i2c ))->write( address );
        wtrans.write( reg );
        wtrans.write( data );
    }
}

void tcs3472::write_reg(uint8_t& reg) {
    {
        hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus * )( &i2c ))->write( address );
        wtrans.write( reg );
    }
}

unsigned int tcs3472::read_color_reg(uint8_t& reg) {
    write_reg( reg );

    uint8_t results[2];
    {
        hwlib::i2c_read_transaction rtrans = ((hwlib::i2c_bus * )( &i2c ))->read( address );
        rtrans.read( results, 2 );
    }

    uint16_t low = results[0];
    uint16_t high = results[1];
    uint16_t res = (high
            << 8) | low;

    return static_cast<unsigned int>(res / 256); // max bit value is 65536, reduce to 8bit
}

// READ DATA ===================================================================

unsigned int tcs3472::get_red() {
    uint8_t red_low_data_reg = 0x16 | 0xA0;
    unsigned int value = read_color_reg( red_low_data_reg );
    return value;
}

unsigned int tcs3472::get_green() {
    uint8_t green_low_data_reg = 0x18 | 0xA0;
    unsigned int value = read_color_reg( green_low_data_reg );
    return value;
}

unsigned int tcs3472::get_blue() {
    uint8_t blue_low_data_reg = 0x1A | 0xA0;
    unsigned int value = read_color_reg( blue_low_data_reg );
    return value;
}

unsigned int tcs3472::get_brightness() {
    uint8_t brightness_low_data_reg = 0x14 | 0xA0;
    unsigned int value = read_color_reg( brightness_low_data_reg );
    return value;
}

const char* tcs3472::get_color() {
    if (get_brightness() < 20) return "too dark";

    unsigned int red = get_red(), green = get_green(), blue = get_blue();
    std::array<unsigned int, 3> colors = {red, green, blue};

    unsigned int max_value = 0;
    for (unsigned int color: colors) {
        if (color > max_value) max_value = color;
    }

    if (max_value == red) {return color::RED;}
    else if (max_value == green) {return color::GREEN;}
    else if (max_value == blue) {return color::BLUE;}
    else {return "wrong value";}
}

std::array<double, 3> tcs3472::get_hsl() {
    if (get_brightness() < 20) return {-1, -1, -1};

    unsigned int red = get_red(), green = get_green(), blue = get_blue();
    return color::rgb_to_hsl(red, green, blue);
}

// MISC ========================================================================

void tcs3472::enable_rgbc() {
    uint8_t enable_reg = 0x80;
    uint8_t power_on = 0b00000001;
    uint8_t enable = 0b00000011;

    write_reg_data( enable_reg, power_on );
    hwlib::wait_ms_busy( 5 );
    write_reg_data( enable_reg, enable );
    hwlib::wait_ms_busy( 5 );
}

void tcs3472::disable_rgbc() {
    uint8_t enable_reg = 0x80;
    uint8_t power_off = 0b00000000;

    hwlib::wait_ms_busy( 5 );
    write_reg_data( enable_reg, power_off );
}
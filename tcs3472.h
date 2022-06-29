#ifndef TCS3472_H
#define TCS3472_H

/*! \file */

#include "hwlib.hpp"
#include "array"
#include "color.h"

/**
 * \brief class for the tcs3472 and similar color sensors.
 *
 * is used for reading the red, green, blue and clear ADC on the chip.
 */
class tcs3472
        : public color {
private:
    /**
     * the i2c bus on which the sensor is connected.
     * reference since every additional sensor should use the same bus.
     */
    hwlib::i2c_bus_bit_banged_scl_sda& i2c;

    /**
     * the address of this chip. used to communicate over the i2c bus.
     */
    uint8_t address = 0x29; //adres van tcs3472 chip is 0x29

    /**
     * \brief function to write data to a register address
     *
     * is used to compute a write transaction to the chip address, and then send
     * the register number as well as the data.
     *
     * @param reg the register address to which you want to write to.
     *
     * @param data the data you want to store in the specified register.
     */
    void write_reg_data(uint8_t& reg, uint8_t data);

    /**
     * \brief function to write a register address
     *
     * is used to compute a write transaction to the chip address, and then send
     * the register number. needed before any read transaction, to specify
     * which register you wanna read in the next read transaction.
     *
     * @param reg the register address u wanna read from.
     */
    void write_reg(uint8_t& reg);

    /**
     * \brief function to read an earlier specified color register
     *
     * is used to compute a read transaction to the chip address, and then read
     * 2 registers one after another. this is then stored into a 16 bit unsigned integer
     * by bit shifting the first 8 bits.
     *
     * @param reg the register adress u wann read from (inserted in "write_reg")
     *
     * @return the 16 bit unsigned integer as an unsigned int.
     */
    unsigned int read_color_reg(uint8_t& reg);


public:
    /**
     * \brief the constructor.
     *
     * turns on the sensor.
     *
     * @param c_i2c the i2c bus on which the sensor is connected.
     */
    tcs3472(hwlib::i2c_bus_bit_banged_scl_sda& c_i2c)
            : i2c( c_i2c ) {
        enable_rgbc();
    }

    /**
     * \brief the destructor.
     *
     * turns off the sensor.
     */
    ~tcs3472() {
        disable_rgbc();
    }

    /**
     * \brief function to read the red ADC
     *
     * is used to specify the red_low_data_register and calls the
     * "read_color_reg".
     *
     * @return the value from the red ADC's on the chip as an unsigned integer.
     */
    unsigned int get_red();

    /**
     * \brief function to read the green ADC.
     *
     * is used to specify the green_low_data_register and calls the
     * "read_color_reg".
     *
     * @return the value from the green ADC's on the chip as an unsigned integer.
     */
    unsigned int get_green();

    /**
     * \brief function to read the blue ADC.
     *
     * is used to specify the blue_low_data_register and calls the
     * "read_color_reg".
     *
     * @return the value from the blue ADC's on the chip as an unsigned integer.
     */
    unsigned int get_blue();

    /**
     * \brief function to read the clear ADC, also usable as brightness.
     *
     * is used to specify the clear_low_data_register and calls the
     * "read_color_reg".
     *
     * @return the value from the clear ADC's on the chip as an unsigned integer.
     */
    unsigned int get_brightness();

    /**
     * \brief function to get the color as a const char*.
     *
     * is used to get a simple feedback of which color is seen the most by the sensor.
     * calculated by computing an rgb array of ints and finding the max value
     *
     * @return "red", "green", or "blue" as a const char*, except when
     * brightness gets too low, ie there is nothing in front of the sensor,
     * "too dark" is returned. any other option will return "wrong value"
     */
    const char* get_color();

    /**
     * \brief function to get the color as an array containing HSL values.
     *
     * is used to convert the rgb values of the sensor to HSL using the function
     * of class "color"
     *
     * @return hue, saturation, and luminance in a std::array, except when
     * brightness gets too low, ie there is nothing in front of the sensor,
     * -1, -1, -1 is returned.
     */
    std::array<double, 3> get_hsl();

    /**
     * \brief function to turn on the ADC's of the chip
     *
     * is used to write to the enable register. first power on, also known as
     * getting the chip out of sleep mode, using the last bit of the register.
     * then, after 5 ms of warm up time, the second last bit is written as "1" to
     * enable the readings.
     */
    void enable_rgbc();

    /**
     * \brief function to turn off the ADC's of the chip
     *
     * is used to write to the enable register. writes a "0" to all bits to
     * disable the readings and put the sensor into sleep mode.
     */
    void disable_rgbc();

};

#endif //TCS3472_H//

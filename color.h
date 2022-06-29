#ifndef V1OOPC_EXAMPLES_COLOR_H
#define V1OOPC_EXAMPLES_COLOR_H

/*! \file */

#include "array"

class color {
protected:
    const char* RED = "red";
    const char* GREEN = "green";
    const char* BLUE = "blue";

    /**
     * \brief function to translate rgb values to hsl values
     *
     * is used to get an advanced feedback of which color is seen by the sensor.
     * calculated by computing an rgb array of doubles and finding the
     * max and min values. luminance, saturation, and hue are then independently
     * calculated according to the following source:
     * https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
     *
     * @param r the red value that needs to be translated.
     * @param g the green value that needs to be translated.
     * @param b the blue value that needs to be translated.
     *
     * @return hue, saturation, and luminance in a std::array.
     */
    std::array<double, 3> rgb_to_hsl(const unsigned int r, const unsigned int g, const unsigned int b);
};


#endif //V1OOPC_EXAMPLES_COLOR_H

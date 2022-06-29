#include "hwlib.hpp"
#include "array"
#include "color.h"

std::array<double, 3> color::rgb_to_hsl(const unsigned int r, const unsigned int g, const unsigned int b) {
    double red = static_cast<double>(r) / 256, green = static_cast<double>(g) / 256, blue = static_cast<double>(b) / 256;
    std::array<double, 3> colors = {red, green, blue};

    double max = 0;
    double min = r;
    for (double color: colors) {
        if (color > max) max = color;
        if (color < min) min = color;
    }
    double delta = max - min;

    //LUM
    double lum = max * 255;

    //SAT
    double sat;
    max == 0 ? sat = 0 : sat = delta / max * 255;

    //HUE
    double hue;
    if (max == min) {hue = 0;}
    else if (max == red) {hue = 60 * (0 + (green - blue) / delta);}
    else if (max == green) {hue = 60 * (2 + (blue - red) / delta);}
    else if (max == blue) {hue = 60 * (4 + (red - green) / delta);}
    else hue = -1;

    if (hue < 0) hue += 360;
    return std::array<double, 3> {hue, sat, lum};
}

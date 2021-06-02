#include <ldv/color.h>

/*! \file color.h
    \brief Color conversion functions.
    
This file contains free functions and structs in the ldv namespace that are 
used to work with colors.
*/

using namespace ldv;

//!Class constructor using float values.
rgba_color::rgba_color(float _r, float _g, float _b, float _a)
	:r(_r), g(_g), b(_b), a(_a) {
}

//!Copy constructor.
rgba_color::rgba_color(const rgba_color& _c)
	:r(_c.r), g(_c.g), b(_c.b), a(_c.a) {
}

//!Class constructor using float values.
rgb_color::rgb_color(float _r, float _g, float _b)
	:r(_r), g(_g), b(_b) {
}

//!Copy constructor
rgb_color::rgb_color(const rgb_color& _c)
	:r(_c.r), g(_c.g), b(_c.b) {
}

//!Converts an integer in the range 0-255 to a float in the range 0.f 1.f. Ranges are not enforced.

float ldv::colorfi(int v)
{
	return (float)v / 255.f;
}

//!Converts a float in the range 0.f-1.f to 0-255. Ranges are not enforced.

int ldv::colorif(float v)
{
	return v * 255.f;
}

//!Gets rgba_color from integer values. rgba_color is expressed in terms of float values. This function provides a quick conversion.

rgba_color ldv::rgba8(int r, int g, int b, int a)
{
	return rgba_color{colorfi(r), colorfi(g), colorfi(b), colorfi(a)};
}

//!Gets rgb_color from integer values. rgb_color is expressed in terms of float values. This function provides a quick conversion.

rgb_color ldv::rgb8(int r, int g, int b)
{
	return rgb_color{colorfi(r), colorfi(g), colorfi(b)};
}
/*
//!Conversion operator.
rgba_color rgb_color::operator rgba_color() const {

	return rgba8(r,g,b, 1.f);
}

//!Conversion operator.
rgb_color rgba_color::operator rgb_color() const {
	return rgb8(r,g,b);
}
*/

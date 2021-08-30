#include "apollo.h"
#include "rgb.h"

namespace apollo {

// Default constructor; Initializes (0, 0, 0) RGB Color
RGB::RGB() : r(0), g(0), b(0) {}

// Constructor from single float; Initializes (u, u, u) RGB Color
RGB::RGB(float u) : r(u), g(u), b(u) {}

// Constructor from three float values
RGB::RGB(float r, float g, float b) : r(r), g(g), b(b) {}

// Copy constructor
RGB::RGB(const RGB& color) : r(color.r), g(color.g), b(color.b) {}

// Assignment operator
RGB& RGB::operator=(const RGB& color) {
	r = color.r;
	g = color.g;
	b = color.b;
	return *this;
}

// Get by index
// ============
float RGB::operator[](int i) const {
	if (i == 0)
		return r;
	if (i == 1)
		return g;
	return b;
}

float& RGB::operator[](int i) {
	if (i == 0)
		return r;
	if (i == 1)
		return g;
	return b;
}

// Min and Max components
// ======================
float RGB::MinComponent() const {
	if (r < g && r < b)
		return r;
	if (g < b)
		return g;
	return b;
}

float RGB::MaxComponent() const {
	if (r > g && r > b)
		return r;
	if (g > b)
		return g;
	return b;
}

// Clamp color
RGB RGB::Clamp(float low, float high) const {
	return RGB(std::clamp(r, low, high), std::clamp(g, low, high), std::clamp(b, low, high));
}

// Get the square root of each component
RGB RGB::Sqrt() const {
	return RGB(std::sqrt(r), std::sqrt(g), std::sqrt(b));
}

}

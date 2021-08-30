#ifndef APOLLO_SPECTRUM_RGB_H
#define APOLLO_SPECTRUM_RGB_H

#include "apollo.h"

namespace apollo {

// Basic RGB Color representation
// ==============================
class RGB {
	public:
		// Default constructor; Initializes (0, 0, 0) RGB Color
		RGB();

		// Constructor from single float; Initializes (u, u, u) RGB Color
		RGB(const float u);
		
		// Constructor from three float values
		RGB(const float r, const float g, const float b);
		
		// Copy constructor
		RGB(const RGB& color);

		// Assignment operator
		RGB& operator=(const RGB& color);

		// Get by index
		// ============
		float  operator[](int i) const;
		float& operator[](int i);

		// Min and Max components
		// ======================
		float MinComponent() const;
		float MaxComponent() const;
		
		// Basic arithmetic operations
		// ===========================
		inline RGB operator+(const RGB& c) const {
			return RGB(r + c.r, g + c.g, b + c.b);
		}

		inline RGB& operator+=(const RGB& c) {
			r += c.r;
			g += c.g;
			b += c.b;
			return *this;
		}

		inline RGB operator+(const float v) const {
			return RGB(r + v, g + v, b + v);
		}

		inline RGB& operator+=(const float v) {
			r += v;
			g += v;
			b += v;
			return *this;
		}
		
		inline RGB operator-(const RGB& c) const {
			return RGB(r - c.r, g - c.g, b - c.b);
		}
		
		inline RGB& operator-=(const RGB& c) {
			r -= c.r;
			g -= c.g;
			b -= c.b;
			return *this;
		}
		
		inline RGB operator-(const float v) const {
			return RGB(r - v, g - v, b - v);
		}
		
		inline RGB& operator-=(const float v) {	
			r -= v;
			g -= v;
			b -= v;
			return *this;
		}
		
		inline RGB operator*(const RGB& c) const {
			return RGB(r * c.r, g * c.g, b * c.b);
		}
		
		inline RGB& operator*=(const RGB& c) {
			r *= c.r;
			g *= c.g;
			b *= c.b;
			return *this;
		}
		
		inline RGB operator*(const float v) const {	
			return RGB(r * v, g * v, b * v);
		}

		inline RGB& operator*=(const float v) {	
			r *= v;
			g *= v;
			b *= v;
			return *this;
		}	
		
		inline RGB operator/(const RGB& c) const {
			return RGB(r / c.r, g / c.g, b / c.b);
		}
		
		inline RGB& operator/=(const RGB& c) {
			r /= c.r;
			g /= c.g;
			b /= c.b;
			return *this;
		}
		
		inline RGB operator/(const float v) const {
			return RGB(r / v, g / v, b / v);
		}
		
		inline RGB& operator/=(const float v) {
			r /= v;
			g /= v;
			b /= v;
			return *this;
		}

		// Clamp color
		RGB Clamp(float low, float high) const;

		// Get the square root of each component
		RGB Sqrt() const;

		// RGB public data
		float r, g, b;
	
};

// Print RGB Color
inline std::ostream& operator<<(std::ostream &out, const RGB& color) {
	return out << color.r << " " << color.g << " " << color.b;
}

// Compare RGB Colors
// ==================
inline bool operator==(const RGB& color1, const RGB& color2) {
	return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b;
}

inline bool operator!=(const RGB& color1, const RGB& color2) {
	return color1.r != color2.r || color1.g != color2.g || color1.b != color2.b;
}

}

#endif

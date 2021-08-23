#ifndef APOLLO_MATH_BOUNDS_2_H
#define APOLLO_MATH_BOUNDS_2_H

#include "apollo.h"
#include "point2.h"
#include "ray.h"

namespace apollo {

template <typename T> class Bounds2 {
	public:
		// Default constructor creates an empty box 
		// by setting the extent to an invalid configuration
		Bounds2() {
			T minNum = std::numeric_limits<T>::lowest();
			T maxNum = std::numeric_limits<T>::max();
			pMin(maxNum);
			pMax(minNum);
		}

		// Enclose a single point
		Bounds2(const Point2<T> &p) : pMin(p), pMax(p) {}
		
		// Passing two corner points
		Bounds2(const Point2<T> &p1, const Point2<T> &p2) 
			: pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y)), 
			  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {}

		// Use array indexing to select between the two points
		Point2<T> operator[](int i) const {
			return i == 0 ? pMin : pMax;
		}

		Point2<T>& operator[](int i) {
			return i == 0 ? pMin : pMax;
		}

		// Ray-Bounds2 intersection
		bool Intersect(const Ray& r, float& t1, float& t2) {
			float tMin = 0;
			float tMax = r.tMax;

                        for (int i = 0; i < 2; i++) {
				float invD = 1.0f / r.d[i];
				float t0 = (pMin[i] - r.o[i]) * invD;		
				float t1 = (pMax[i] - r.o[i]) * invD;			
				if (invD < 0.0f)				
					std::swap(t0, t1);
				tMin = t0 > tMin ? t0 : tMin;
				tMax = t1 < tMax ? t1 : tMax;		
				if (tMin > tMax)		
					return false;
			}

			t1 = tMin;
			t2 = tMax;

			return true;
		}

		// Enlarge bounding box to contain given point
		Bounds2<T>& Union(const Point2<T> &p) {
			pMin = Point2<T>(std::min(pMin.x, p.x), std::min(pMin.y, p.y));
			pMax = Point2<T>(std::max(pMax.x, p.x), std::max(pMax.y, p.y));
			return *this;
		}

		// Enlarge bounding box to contain given bounding box
		Bounds2<T>& Union(const Bounds2<T> &b) {
			pMin = Point2<T>(std::min(pMin.x, b.pMin.x), std::min(pMin.y, b.pMin.y));
			pMax = Point2<T>(std::max(pMax.x, b.pMax.x), std::max(pMax.y, b.pMax.y));
			return *this;
		}

		// Check if a point is inside the box
		bool Inside(const Point2<T> &p) {
			bool x = pMin.x <= p.x && pMax.x >= p.x;
			bool y = pMin.y <= p.y && pMax.y >= p.y;
			return x && y;
		}

		// Expand bounding box by a constant factor in all dimensions
		template <typename U> Bounds2<T>& Expand(const U delta) {
			pMin -= Vector2<U>(delta);
			pMax += Vector2<U>(delta);
			return *this;
		}

		// Get vector along the box diagonal from pMin to pMax
		Vector2<T> Diagonal() const {
			return pMax - pMin;
		}

		// Box Area
		T Area() const {
			Vector2<T> d = Diagonal();
			return d.x * d.y;
		}

		// Get the index of the axis with maximum edge
		int MaximumExtent() const {
			Vector2<T> d = Diagonal();
			if (d.x > d.y)
				return 0;
			return 1;	
		}

		// Bounds2 public data
		// The minumum and maximum point of the bounding box
		Point2<T> pMin, pMax;
};

// Enlarge bounding box to contain given point
template <typename T> Bounds2<T> Union(const Bounds2<T> &b, const Point2<T> &p) {
	return Bounds2<T>(Point2<T>(std::min(b.pMin.x, p.x), std::min(b.pMin.y, p.y)),
			  Point2<T>(std::max(b.pMax.x, p.x), std::max(b.pMax.y, p.y)));
}

// Enlarge bounding box to contain given bounding box
template <typename T> Bounds2<T> Union(const Bounds2<T> &b1, const Bounds2<T> &b2) {
	return Bounds2<T>(Point2<T>(std::min(b1.pMin.x, b2.pMin.x), std::min(b1.pMin.y, b2.pMin.y)),
			  Point2<T>(std::max(b1.pMax.x, b2.pMax.x), std::max(b1.pMax.y, b2.pMax.y)));
}

// Find the intersection between two bounding boxes
template <typename T> Bounds2<T> Intersect(const Bounds2<T> &b1, const Bounds2<T> &b2) {
	return Bounds2<T>(Point2<T>(std::max(b1.pMin.x, b2.pMin.x), std::max(b1.pMin.y, b2.pMin.y)),
			  Point2<T>(std::min(b1.pMax.x, b2.pMax.x), std::min(b1.pMax.y, b2.pMax.y)));
}

// Expand bounding box by a constant factor in all dimensions
template <typename T, typename U> inline Bounds2<T> Expand(const Bounds2<T> &b, U delta) {
	return Bounds2<T>(b.pMin - Vector2<U>(delta), b.pMax + Vector2<U>(delta));
}

typedef Bounds2<float> Bounds2f;
typedef Bounds2<int> Bounds2i;

}

#endif

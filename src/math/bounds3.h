#ifndef APOLLO_MATH_BOUNDS_3_H
#define APOLLO_MATH_BOUNDS_3_H

#include "apollo.h"
#include "point3.h"
#include "ray.h"

namespace apollo {

template <typename T> class Bounds3 {
	public:
		// Default constructor creates an empty box 
		// by setting the extent to an invalid configuration
		Bounds3() {
			T minNum = std::numeric_limits<T>::lowest();
			T maxNum = std::numeric_limits<T>::max();
			pMin(maxNum);
			pMax(minNum);
		}

		// Enclose a single point
		Bounds3(const Point3<T> &p) : pMin(p), pMax(p) {}
		
		// Passing two corner points
		Bounds3(const Point3<T> &p1, const Point3<T> &p2) 
			: pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)), 
			  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)) {}

		// Use array indexing to select between the two points
		Point3<T> operator[](int i) const {
			return i == 0 ? pMin : pMax;
		}

		Point3<T>& operator[](int i) {
			return i == 0 ? pMin : pMax;
		}

		// Ray-Bounds3 intersection
		bool Intersect(const Ray& r, float& t1, float& t2) {
			float tMin = 0;
			float tMax = r.tMax;
			
			for (int i = 0; i < 3; i++) {
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
		Bounds3<T>& Union(const Point3<T> &p) {
			pMin = Point3<T>(std::min(pMin.x, p.x), std::min(pMin.y, p.y), std::min(pMin.z, p.z));
			pMax = Point3<T>(std::max(pMax.x, p.x), std::max(pMax.y, p.y), std::max(pMax.z, p.z));
			return *this;
		}

		// Enlarge bounding box to contain given bounding box
		Bounds3<T>& Union(const Bounds3<T> &b) {
			pMin = Point3<T>(std::min(pMin.x, b.pMin.x), std::min(pMin.y, b.pMin.y), std::min(pMin.z, b.pMax.z));
			pMax = Point3<T>(std::max(pMax.x, b.pMax.x), std::max(pMax.y, b.pMax.y), std::max(pMax.z, b.pMax.z));
			return *this;
		}

		// Check if a point is inside the box
		bool Inside(const Point3<T> &p) {
			bool x = pMin.x <= p.x && pMax.x >= p.x;
			bool y = pMin.y <= p.y && pMax.y >= p.y;
			bool z = pMin.z <= p.z && pMax.z >= p.z;
			return x && y && z;
		}

		// Expand bounding box by a constant factor in all dimensions
		template <typename U> Bounds3<T>& Expand(const U delta) {
			pMin -= Vector3<U>(delta);
			pMax += Vector3<U>(delta);
			return *this;
		}

		// Get vector along the box diagonal from pMin to pMax
		Vector3<T> Diagonal() const {
			return pMax - pMin;
		}

		// Box Volume and Surface area
		T Volume() const {
			Vector3<T> d = Diagonal();
			return d.x * d.y * d.z;
		}

		T SurfaceArea() const {
			Vector3<T> d = Diagonal();
			return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
		}

		// Get the index of the axis with maximum edge
		int MaximumExtent() const {
			Vector3<T> d = Diagonal();
			if (d.x > d.y && d.x > d.z)
				return 0;
			else if (d.y > d.z)
				return 1;
			return 2;
		}

		// Bounds3 public data
		// The minumum and maximum point of the bounding box
		Point3<T> pMin, pMax;
};

// Enlarge bounding box to contain given point
template <typename T> Bounds3<T> Union(const Bounds3<T> &b, const Point3<T> &p) {
	return Bounds3<T>(Point3<T>(std::min(b.pMin.x, p.x), std::min(b.pMin.y, p.y), std::min(b.pMin.z, p.z)),
			  Point3<T>(std::max(b.pMax.x, p.x), std::max(b.pMax.y, p.y), std::max(b.pMax.z, p.z)));
}

// Enlarge bounding box to contain given bounding box
template <typename T> Bounds3<T> Union(const Bounds3<T> &b1, const Bounds3<T> &b2) {
	return Bounds3<T>(Point3<T>(std::min(b1.pMin.x, b2.pMin.x), std::min(b1.pMin.y, b2.pMin.y), std::min(b1.pMin.z, b2.pMin.z)),
			  Point3<T>(std::max(b1.pMax.x, b2.pMax.x), std::max(b1.pMax.y, b2.pMax.y), std::max(b1.pMax.z, b2.pMax.z)));
}

// Find the intersection between two bounding boxes
template <typename T> Bounds3<T> Intersect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
	return Bounds3<T>(Point3<T>(std::max(b1.pMin.x, b2.pMin.x), std::max(b1.pMin.y, b2.pMin.y), std::max(b1.pMin.z, b2.pMin.z)),
			  Point3<T>(std::min(b1.pMax.x, b2.pMax.x), std::min(b1.pMax.y, b2.pMax.y), std::min(b1.pMax.z, b2.pMax.z)));
}

// Expand bounding box by a constant factor in all dimensions
template <typename T, typename U> inline Bounds3<T> Expand(const Bounds3<T> &b, U delta) {
	return Bounds3<T>(b.pMin - Vector3<U>(delta), b.pMax + Vector3<U>(delta));
}

typedef Bounds3<float> Bounds3f;
typedef Bounds3<int> Bounds3i;

}

#endif

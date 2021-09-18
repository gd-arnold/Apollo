#ifndef APOLLO_SHAPES_TRIANGLE_H
#define APOLLO_SHAPES_TRIANGLE_H

#include "apollo.h"
#include "shape.h"
#include "point3.h"

namespace apollo {

class TriangleMesh {
public:
	// Initialize mesh explicitly
	TriangleMesh(const Transform& objectToWorld, int nTriangles, const int* vertexIndices,
		int nVertices, const Point3f* vertices);

	// Initialize mesh by parsing .obj file
	TriangleMesh(const Transform& objectToWorld, const std::string& filename);
public:
	int nTriangles, nVertices;
	std::vector<int> vertexIndices;
	std::vector<Point3f> vertices;
};

// NOTE: If the triangles are supposed to be front-facing, verticies must be specified in clockwise order (from the point of view of the camera) 
std::vector<std::shared_ptr<Shape>> CreateTriangleMesh(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
	int nTriangles, const int* vertexIndicies, int nVerticies, const Point3f* p);
std::vector<std::shared_ptr<Shape>> CreateTriangleMeshByObj(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
	const std::string& filename);

class Triangle : public Shape 
{
public:
	Triangle(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
		const std::shared_ptr<TriangleMesh>& mesh, int triangleIndex);

	// Check if a triangle is intersected by a ray
	// Apollo implements the Möller–Trumbore ray-triangle intersection algorithm
	bool Intersect(const Ray& ray, SurfaceInteraction* surf = nullptr) const override;

	// Triangle bounding box in object coordinates
	Bounds3f ObjectBound() const override;
	// Triangle bounding box in world coordinates
	Bounds3f WorldBound() const override;

	// Triangle surface area
	float Area() const override;
private:
	std::shared_ptr<TriangleMesh> mesh;
	const int* v;
};

}

#endif
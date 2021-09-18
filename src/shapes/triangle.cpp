#include "apollo.h"
#include "triangle.h"
#include "vector3.h"

namespace apollo {

	TriangleMesh::TriangleMesh(const Transform& objectToWorld, int nTriangles, const int* vertexIndices, int nVertices, const Point3f* P) 
		: nTriangles(nTriangles), nVertices(nVertices), vertexIndices(vertexIndices, vertexIndices + 3 * nTriangles) {
		// Tranform vertices to world space
		p.reset(new Point3f[nVertices]);
		for (int i = 0; i < nVertices; i++)
			p[i] = objectToWorld(P[i]);
	}

	std::vector<std::shared_ptr<Shape>> CreateTriangleMesh(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
		int nTriangles, const int* vertexIndicies, int nVerticies, const Point3f* p) {
		std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(*objectToWorld, nTriangles, vertexIndicies, nVerticies, p);
		std::vector<std::shared_ptr<Shape>> triangles;
		triangles.reserve(nTriangles);
		for (int i = 0; i < nTriangles; i++)
			triangles.push_back(std::make_shared<Triangle>(objectToWorld, worldToObject, reverseOrientation, mesh, i));
		return triangles;
	}

	Triangle::Triangle(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
		const std::shared_ptr<TriangleMesh>& mesh, int triangleIndex)
		: Shape(objectToWorld, worldToObject, reverseOrientation), mesh(mesh) {
		v = &mesh->vertexIndices[3 * triangleIndex];
	}

	bool Triangle::Intersect(const Ray& ray, SurfaceInteraction* surf) const {
		// Get triangle vertices
		const Point3f& v0 = mesh->p[v[0]];
		const Point3f& v1 = mesh->p[v[1]];
		const Point3f& v2 = mesh->p[v[2]];

		// Apply Möller–Trumbore ray-triangle intersection algorithm
		//==========================================================
		Vector3f v0v1 = v1 - v0;
		Vector3f v0v2 = v2 - v0;
		Vector3f translation = ray.o - v0;
		Vector3f pvec = Cross(ray.d, v0v1);
		
		float det = Dot(pvec, v0v2);
		
		// If determinant is close to 0, the ray and the triangle are parallel
		if (det < Epsilon)
			return false;

		float invDet = 1 / det;
		Vector3f qvec = Cross(translation, v0v2) * invDet;

		// Compute barycentric coordinates
		float u = Dot(translation, pvec) * invDet;
		if (u < 0 || u > 1)
			return false;
		
		float v = Dot(ray.d, qvec);
		if (v < 0 || u + v > 1)
			return false;

		// Initialize surface interaction (if defined)
		if (surf) {
			float tHit = Dot(v0v1, qvec) * invDet;
			Point3f p = ray(tHit);

			// TODO: Compute triangle partial derivatives
			Vector3f dpdu(0);
			Vector3f dpdv(0);

			*surf = SurfaceInteraction(p, Point2f(u, v), -ray.d, dpdu, dpdv, ray.time, this);
		}

		return true;
	}

	Bounds3f Triangle::ObjectBound() const {
		const Point3f& v0 = mesh->p[v[0]];
		const Point3f& v1 = mesh->p[v[1]];
		const Point3f& v2 = mesh->p[v[2]];
		return Bounds3f((*worldToObject)(v0), (*worldToObject)(v1)).Union((*worldToObject)(v2));
	}

	Bounds3f Triangle::WorldBound() const {
		const Point3f& v0 = mesh->p[v[0]];
		const Point3f& v1 = mesh->p[v[1]];
		const Point3f& v2 = mesh->p[v[2]];
		return Bounds3f(v0, v1).Union(v2);

	}

	float Triangle::Area() const {
		const Point3f& v0 = mesh->p[v[0]];
		const Point3f& v1 = mesh->p[v[1]];
		const Point3f& v2 = mesh->p[v[2]];
		Vector3f v0v1 = v1 - v0;
		Vector3f v0v2 = v2 - v0;
		return Cross(v0v1, v0v2).Length() * 0.5;
	}

}
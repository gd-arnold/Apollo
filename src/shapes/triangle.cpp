#include "apollo.h"
#include "triangle.h"
#include "vector3.h"

namespace apollo {

	// Initialize mesh explicitly
	TriangleMesh::TriangleMesh(const Transform& objectToWorld, int nTriangles, const int* vertexIndices, int nVertices, const Point3f* P) 
		: nTriangles(nTriangles), nVertices(nVertices), vertexIndices(vertexIndices, vertexIndices + 3 * nTriangles) {
		// Tranform vertices to world space
		vertices.reserve(nVertices);
		for (int i = 0; i < nVertices; i++)
			vertices.push_back(objectToWorld(P[i]));
	}

	// Initialize mesh by parsing .obj file
	TriangleMesh::TriangleMesh(const Transform& objectToWorld, const std::string& filename) {
		std::ifstream in(filename);
		nTriangles = 0;
		nVertices = 0;
		if (!in) {
			std::cerr << "Cannot open " << filename << std::endl;
			exit(1);
		}

		std::string line;
		while (std::getline(in, line)) {
			std::string type;
			std::istringstream iss(line);

			iss >> type;

			if (type == "v") {
				Point3f vertex;
				iss >> vertex.x;
				iss >> vertex.y;
				iss >> vertex.z;
				vertices.push_back(objectToWorld(vertex));
				nVertices++;
			}
			
			else if (type == "f") {
				Point3i face;
				iss >> face.x;
				iss >> face.y;
				iss >> face.z;
				vertexIndices.push_back(face.x - 1);
				vertexIndices.push_back(face.y - 1);
				vertexIndices.push_back(face.z - 1);
				nTriangles++;
			}
		}
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

	std::vector<std::shared_ptr<Shape>> CreateTriangleMeshByObj(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation,
		const std::string& filename) {
		std::shared_ptr<TriangleMesh> mesh = std::make_shared<TriangleMesh>(*objectToWorld, filename);
		std::vector<std::shared_ptr<Shape>> triangles;
		triangles.reserve(mesh->nTriangles);
		for (int i = 0; i < mesh->nTriangles; i++)
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
		const Point3f& v0 = mesh->vertices[v[0]];
		const Point3f& v1 = mesh->vertices[v[1]];
		const Point3f& v2 = mesh->vertices[v[2]];

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
		const Point3f& v0 = mesh->vertices[v[0]];
		const Point3f& v1 = mesh->vertices[v[1]];
		const Point3f& v2 = mesh->vertices[v[2]];
		return Bounds3f((*worldToObject)(v0), (*worldToObject)(v1)).Union((*worldToObject)(v2));
	}

	Bounds3f Triangle::WorldBound() const {
		const Point3f& v0 = mesh->vertices[v[0]];
		const Point3f& v1 = mesh->vertices[v[1]];
		const Point3f& v2 = mesh->vertices[v[2]];
		return Bounds3f(v0, v1).Union(v2);

	}

	float Triangle::Area() const {
		const Point3f& v0 = mesh->vertices[v[0]];
		const Point3f& v1 = mesh->vertices[v[1]];
		const Point3f& v2 = mesh->vertices[v[2]];
		Vector3f v0v1 = v1 - v0;
		Vector3f v0v2 = v2 - v0;
		return Cross(v0v1, v0v2).Length() * 0.5;
	}

}
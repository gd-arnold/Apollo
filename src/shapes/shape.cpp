#include "apollo.h"
#include "shape.h"

namespace apollo {

Shape::Shape(const Transform* objectToWorld, const Transform* worldToObject, bool reverseOrientation)
	: objectToWorld(objectToWorld), worldToObject(worldToObject), reverseOrientation(reverseOrientation),
	  transformChangesHandedness(objectToWorld->ChangesHandedness()) {}

}

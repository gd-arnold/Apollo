#include "interaction.h"

namespace apollo {
	
	Interaction::Interaction(const Point3f &p, const Normal3f &n, const Vector3f &wo, float time) : p(p), n(n), wo(wo), time(time) {}

}

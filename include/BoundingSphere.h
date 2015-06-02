#ifndef _BOUNDING_SPHERE_
#define _BOUNDING_SPHERE_

#include "particle.h"
#include <math.h>

using namespace particle;

namespace boundingsphere
{
	class BoundingSphere
	{
	private:
		Vector2 centre;
		float radius;

	public:
		BoundingSphere(void) : centre(0, 0), radius(0) {}
		BoundingSphere(const Vector2 &centre, float radius);
		BoundingSphere(const BoundingSphere &one, const BoundingSphere &two);

		bool overlaps(const BoundingSphere &other) const;

		float getGrowth(const BoundingSphere &other) const;

		float getSize(void) const
		{
			return(1.333333f) * 3.141592f * radius * radius * radius;
		}

		float getRadius(void) const
		{
			return radius;
		}

		Vector2 getCentre(void) const
		{
			return centre;
		}

		void setRadius(const float r)
		{
			radius = r;
		}

		void setCentre(const float x, const float y)
		{
			centre.x = x;
			centre.y = y;
		}
	};
}
#endif
#include "boundingSphere.h"

using namespace boundingsphere;

BoundingSphere::BoundingSphere(const Vector2 &centre, float radius)
{
	BoundingSphere::centre = centre;
	BoundingSphere::radius = radius;
}

BoundingSphere::BoundingSphere(const BoundingSphere &one, const BoundingSphere &two)
{
	Vector2 distance_centre = one.centre - two.centre;
	float distance = distance_centre.squareMagnitude();
	float dif_radius = one.radius - two.radius;

	// Check if the larger sphere encloses the small one
	if (dif_radius * dif_radius >= distance)
	{
		if (one.radius > two.radius)
		{
			centre = one.centre;
			radius = one.radius;
		}
		else
		{
			centre = two.centre;
			radius = two.radius;
		}
	}
	// Otherwise we need to work with partially overlapping spheres
	else
	{
		distance = sqrt(distance);
		radius = (distance + one.radius + two.radius) * (0.5f);

		// The new centre is based on one's centre, moved towards
		// two's centre by an ammount proportional to the spheres' radii.
		centre = one.centre;
		if (distance > 0)
		{
			centre += distance_centre * ((radius - one.radius) / distance);
		}
	}
}

float BoundingSphere::getGrowth(const BoundingSphere& other) const
{
	BoundingSphere newSphere(*this, other);

	// We return a value proportional to the change in surface area of the sphere.
	return pow(newSphere.radius, 2) - pow(radius, 2);
}

bool BoundingSphere::overlaps(const BoundingSphere& other) const
{
	float distanceSquared = (centre - other.centre).squareMagnitude();
	return distanceSquared < pow((radius + other.radius), 2);
}
#include "particle.h"
#include <math.h>

using namespace particle;

void Particle::setPosition(const float x, const float y)
{
	position.x = x;
	position.y = y;
}

void Particle::setRadius(const float r)
{
	radius = r;
}

Vector2 Particle::getPosition(void) const
{
	return position;
}

float Particle::getRadius(void) const
{
	return radius;
}

void Particle::integrate(float duration)
{
	position.x += velocity.x * duration;
	position.y += velocity.y * duration;

	position.x += 0.5f * acceleration.x * pow(duration, 2);
	position.y += 0.5f * acceleration.y * pow(duration, 2);

	velocity.x += acceleration.x * duration;
	velocity.y += acceleration.y * duration;

	// Impose drag.
	velocity.x *= pow(damping, duration);
	velocity.y *= pow(damping, duration);
}

void Particle::setVelocity(const float x, const float y)
{
	velocity.x = x;
	velocity.y = y;
}

Vector2 Particle::getVelocity(void) const
{
	return velocity;
}

void Particle::setAcceleration(const float x, const float y)
{
	acceleration.x = x;
	acceleration.y = y;
}

Vector2 Particle::getAcceleration(void) const
{
	return acceleration;
}

void Particle::setDamping(const float damping)
{
	Particle::damping = damping;
}

float Particle::getDamping(void) const
{
	return damping;
}
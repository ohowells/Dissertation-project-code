#ifndef _PARTICLE_
#define _PARTICLE_

namespace particle
{
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2(void) : x(0), y(0) {}
		Vector2(const float x, const float y)
			: x(x), y(y)
		{
		}

		// Returns the value of the given vector added to this.
		Vector2 operator+(const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		// Returns a copy of this vector scaled by the given value.
		Vector2 operator*(const float value) const
		{
			return Vector2(x * value, y * value);
		}

		// Returns the value of the given vector subtracted from this.
		Vector2 operator-(const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

		// Adds the given vector to this.
		void operator+=(const Vector2& v)
		{
			x += v.x;
			y += v.y;
		}

		float squareMagnitude(void) const
		{
			return x * x + y * y;
		}
	};

	class Particle
	{
	protected:
		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;

		float damping;
		float radius;

	public:
		void setPosition(const float x, const float y);
		void setVelocity(const float x, const float y);
		void setAcceleration(const float x, const float y);
		void setDamping(const float damping);
		void setRadius(const float r);

		Vector2 getAcceleration(void) const;
		Vector2 getPosition(void) const;
		Vector2 getVelocity(void) const;
		float getRadius(void) const;
		float getDamping(void) const;

		void integrate(float duration);
	};
}
#endif
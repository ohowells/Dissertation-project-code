#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <math.h>

#define PI	3.141592f
#define PHI 2 * PI / 24

namespace vector
{
	class Vector_base
	{
	public:
		explicit Vector_base(void)
		{
		}
		virtual ~Vector_base(void)
		{
		}
	};

	template<typename T, int DIM>
	class Vector
		: public Vector_base
	{
		typedef Vector<T, DIM> ME;
	public:
		explicit Vector(void)
		{
			memset(&v, 0, sizeof(v));
		}

		explicit Vector(T v[DIM])
		{
			memcpy(this->v, v, sizeof(this->v));
		}

		explicit Vector(T, T, T);

		virtual ~Vector(void)
		{
		}

		// Operators

		T &operator [](size_t n)
		{
			return v[n];
		}

		T operator [](size_t n) const
		{
			return v[n];
		}

		ME &operator += (const ME& o)
		{
			for (size_t i = 0; i < DIM; ++i)
			{
				v[i] += o[i];
			}
			return *this;
		}

		ME &operator -= (const ME& o)
		{
			for (size_t i = 0; i < DIM; ++i)
			{
				v[i] -= o[i];
			}
			return *this;
		}

		ME &operator *= (const ME& o)
		{
			for (size_t i = 0; i < DIM; ++i)
			{
				v[i] *= o[i];
			}
			return *this;
		}

		ME &operator /= (const ME& o)
		{
			for (size_t i = 0; i < DIM; ++i)
			{
				v[i] /= o[i];
			}
			return *this;
		}


		ME &operator *= (float scalar)
		{
			for (size_t i = 0; i < DIM; ++i)
			{
				v[i] *= scalar;
			}
			return *this;
		}

		ME &operator /= (float scalar)
		{
			for (size_t i = 0; i < DIM; ++i)
			{
				v[i] /= scalar;
			}
			return *this;
		}

		const ME operator-(const ME &o) const
		{
			ME result = *this;
			result -= o;
			return result;
		}

		const ME operator+(const ME &o) const
		{
			ME result = *this;
			result += o;
			return result;
		}

		const ME operator*(const ME &o) const
		{
			ME result = *this;
			result *= o;
			return result;
		}

		const ME operator*(float scalar) const
		{
			ME result = *this;
			result *= scalar;
			return result;
		}

		const ME operator/(const ME &o) const
		{
			ME result = *this;
			result /= o;
			return result;
		}

		const ME operator/(float scalar) const
		{
			ME result = *this;
			result /= scalar;
			return result;
		}


		// Misc stuff
		ME &get(void)
		{
			return v;
		}

		float length(void)
		{
			float temp = 0.0f;

			for (size_t i = 0; i < DIM; ++i)
			{
				temp += v[i] * v[i];
			}

			return sqrtf(temp);
		}

		void normalize(void)
		{
			float len = length();

			for (size_t i = 0; i < DIM; ++i)
			{
				v[i] /= len;
			}

		}

		// Other than Vector3 gives linker errors
		float dot(const ME &v) const;

	private:
		T v[DIM];
	};


	typedef Vector<float, 3> Vector3;


	float Vector3::dot(const ME &o) const
	{
		return v[0] * o[0] + v[1] * o[1] + v[2] * o[2];
	}

	Vector3::Vector(float x, float y, float z)
	{
		v[0] = x;
		v[1] = y;
		v[2] = 0;
	}
}
#endif 
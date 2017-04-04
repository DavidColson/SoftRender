#ifndef MATHS_
#define MATHS_

#include "SDL.h"

#define ToRadian(x) ((x) * 3.14159 /180.0f)
#define ToDegree(x) ((x) * 180.0f / 3.14159)

namespace Maths {
	
	struct Vec3f
	{
		float X;
		float Y;
		float Z;
		Vec3f()
		{
			X = 0;
			Y = 0;
			Z = 0;
		}
		Vec3f(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		// TODO: rewrite these operators so they're not part of the class and direct edit the LHS so as not to incure a memory assignment cost.
		inline Vec3f operator*(const float& scalar) const
		{
			Vec3f ret;

			ret.X = X * scalar;
			ret.Y = Y * scalar;
			ret.Z = Z * scalar;

			return ret;
		}

		inline Vec3f operator-=(const Vec3f& v)
		{
			X -= v.X;
			Y -= v.Y;
			Z -= v.Z;

			return (*this);
		}

		inline Vec3f operator+=(const Vec3f& v)
		{
			X += v.X;
			Y += v.Y;
			Z += v.Z;

			return (*this);
		}

		inline Vec3f operator+(const Vec3f& v)
		{
			Vec3f result(X + v.X, Y + v.Y, Z + v.Z);
			return result;
		}

		inline Vec3f operator-(const Vec3f& v)
		{
			Vec3f result(X - v.X, Y - v.Y, Z - v.Z);
			return result;
		}

		inline float& operator[] (int x)
		{
			SDL_assert(x < 3);
			switch (x)
			{
			case 0:
				return X; break;
			case 1:
				return Y; break;
			default:
				return Z; break;
			}
		}

		inline const float& operator[] (int x) const
		{
			SDL_assert(x < 3);
			switch (x)
			{
			case 0:
				return X; break;
			case 1:
				return Y; break;
			default:
				return Z; break;
			}
		}
	};

	struct Vec4f
	{
		float X;
		float Y;
		float Z;
		float W;
		Vec4f()
		{
			X = 0;
			Y = 0;
			Z = 0;
			W = 0;
		}
		Vec4f(float x, float y, float z, float w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}
		Vec4f(Vec3f v, float w)
		{
			X = v.X;
			Y = v.Y;
			Z = v.Z;
			W = w;
		}

		inline Vec4f operator*(const float& scalar) const
		{
			Vec4f ret;

			ret.X = X * scalar;
			ret.Y = Y * scalar;
			ret.Z = Z * scalar;
			ret.W = W * scalar;

			return ret;
		}

		inline Vec4f operator-=(const Vec4f& v)
		{
			X -= v.X;
			Y -= v.Y;
			Z -= v.Z;
			W -= v.W;

			return (*this);
		}

		inline Vec4f operator+=(const Vec4f& v)
		{
			X += v.X;
			Y += v.Y;
			Z += v.Z;
			W += v.W;

			return (*this);
		}

		inline Vec4f operator+(const Vec4f& v)
		{
			Vec4f result(X + v.X, Y + v.Y, Z + v.Z, W + v.W);
			return result;
		}

		inline Vec4f operator-(const Vec4f& v)
		{
			Vec4f result(X - v.X, Y - v.Y, Z - v.Z, W + v.W);
			return result;
		}

		inline const float& operator[] (int x) const
		{
			SDL_assert(x < 4);
			switch (x)
			{
			case 0:
				return X; break;
			case 1:
				return Y; break;
			case 2:
				return Z; break;
			default:
				return W; break;
			}
		}

		inline float& operator[] (int x)
		{
			SDL_assert(x < 4);
			switch (x)
			{
			case 0:
				return X; break;
			case 1:
				return Y; break;
			case 2:
				return Z; break;
			default:
				return W; break;
			}
		}
	};

	// Special Vector operations
	inline Vec3f Cross(const Vec3f& v1, const Vec3f& v2)
	{
		float x = v1.Y * v2.Z - v1.Z * v2.Y;
		float y = v1.Z * v2.X - v1.X * v2.Z;
		float z = v1.X * v2.Y - v1.Y * v2.X;

		return Vec3f(x, y, z);
	}
	inline Vec3f Normalize(const Vec3f& v)
	{
		float Length = sqrtf(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
		return Vec3f(v.X / Length, v.Y / Length, v.Z / Length);
	}

	inline float Dot(const Vec3f& v1, const Vec3f& v2)
	{
		return v1.X*v2.X + v1.Y*v2.Y + v1.Z*v2.Z;
	}

	struct Vec2f
	{
		float X;
		float Y;
		Vec2f()
		{
			X = 0;
			Y = 0;
		}
		Vec2f(float x, float y)
		{
			X = x;
			Y = y;
		}

		inline Vec2f operator*(const float& scalar) const
		{
			Vec2f ret;

			ret.X = X * scalar;
			ret.Y = Y * scalar;

			return ret;
		}

		inline Vec2f operator-=(const Vec2f& v)
		{
			X -= v.X;
			Y -= v.Y;

			return (*this);
		}

		inline Vec2f operator+=(const Vec2f& v)
		{
			X += v.X;
			Y += v.Y;

			return (*this);
		}

		inline Vec2f operator+(const Vec2f& v)
		{
			Vec2f result(X + v.X, Y + v.Y);
			return result;
		}

		inline Vec2f operator-(const Vec2f& v)
		{
			Vec2f result(X - v.X, Y - v.Y);
			return result;
		}

		inline float& operator[] (const int x)
		{
			SDL_assert(x < 2);
			switch (x)
			{
			case 0:
				return X; break;
			default:
				return Y; break;
			}
		}

		inline const float& operator[] (const int x) const
		{
			SDL_assert(x < 2);
			switch (x)
			{
			case 0:
				return X; break;
			default:
				return Y; break;
			}
		}
	};

	inline Vec2f Normalize(const Vec2f& v)
	{
		float Length = sqrtf(v.X * v.X + v.Y * v.Y);
		return Vec2f(v.X / Length, v.Y / Length);
	}

	class Mat4f
	{
	public:
		float m[4][4];

		// Constructors
		Mat4f();
		Mat4f(float x00, float x01, float x02, float x03,
			float x10, float x11, float x12, float x13,
			float x20, float x21, float x22, float x23,
			float x30, float x31, float x32, float x33);

		// Matrix Multiplication
		Mat4f operator*(const Mat4f& Right) const;

		Vec4f operator*(const Vec4f& v) const;

		Mat4f Transpose();

		Mat4f Cofactors();

		Mat4f Inverse();

	};

	inline Mat4f MakeScale(Vec3f Scaling)
	{
		return Mat4f(Scaling.X, 0, 0, 0,
			0, Scaling.Y, 0, 0,
			0, 0, Scaling.Z, 0,
			0, 0, 0, 1);
	}

	inline Mat4f MakeTranslate(Vec3f translate)
	{
		return Mat4f(1, 0, 0, translate.X,
					 0, 1, 0, translate.Y,
					 0, 0, 1, translate.Z,
					 0, 0, 0, 1);
	}

	inline Mat4f MakeRotate(Vec3f rotation)
	{
		float x = ToRadian(rotation.X);
		float y = ToRadian(rotation.Y);
		float z = ToRadian(rotation.Z);

		Mat4f rx(1, 0, 0, 0,
			0, cosf(x), -sinf(x), 0,
			0, sinf(x), cosf(x), 0,
			0, 0, 0, 1);

		Mat4f ry(cosf(y), 0, -sinf(y), 0,
			0, 1, 0, 0,
			sinf(y), 0, cosf(y), 0,
			0, 0, 0, 1);

		Mat4f rz(cosf(z), -sinf(z), 0, 0,
			sinf(z), cosf(z), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		return rz * ry * rx;
	}

	inline Mat4f MakePerspective(float ScreenWidth, float ScreenHeight, float Near, float Far, float FOV)
	{
		float ar = ScreenWidth / ScreenHeight;
		float zRange = Near - Far;
		float tanHalfFOV = tanf(ToRadian(FOV * 0.5));

		Mat4f proj((1.0f / (tanHalfFOV * ar)), 0.f,					0.f,					0.f,
				0.f,						   (1.0f / (tanHalfFOV)), 0.f,					0.f,
				0.f,						   0.f,					(-Near - Far) / zRange, (2 * Far * Near) / zRange,
				0.f,						   0.f,					1.f,					0.f);

		return proj;
	}

	inline Mat4f MakeViewport(float width, float height)
	{
		Mat4f proj(	width/2.f,					0.f,					0.f,					width/2.f,
					0.f,						height/2.f,				0.f,					height/2.f,
					0.f,						0.f,					255.0/2.0,				255.0/2.0,
					0.f,						0.f,					0.f,					1.f);

		return proj;
	}

	inline Mat4f MakeLookAt(Vec3f Forward, Vec3f Up)
	{
		Vec3f N = Forward;
		N = Normalize(N);
		Vec3f U = Up;
		U = Normalize(U);
		U = Cross(U, N);
		Vec3f V = Cross(N, U);

		Mat4f lookAt(U.X, U.Y, U.Z, 0,
			V.X, V.Y, V.Z, 0,
			N.X, N.Y, N.Z, 0,
			0, 0, 0, 1);

		return lookAt;
	}

	inline void GetAxesFromRotation(Vec3f Rotation, Vec3f &Forward, Vec3f &Right, Vec3f & Up)
	{
		Mat4f rotMat = MakeRotate(Rotation);

		Forward = Vec3f(rotMat.m[0][2], rotMat.m[1][2], rotMat.m[2][2]);
		Right = Vec3f(rotMat.m[0][0], rotMat.m[1][0], rotMat.m[2][0]);
		Up = Vec3f(rotMat.m[0][1], rotMat.m[1][1], rotMat.m[2][1]);
	}
};
#endif
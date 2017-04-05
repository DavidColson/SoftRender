#ifndef MATHS_
#define MATHS_

#include "SDL.h"
#include <cassert>

#define ToRadian(x) ((x) * 3.14159 /180.0f)
#define ToDegree(x) ((x) * 180.0f / 3.14159)

typedef unsigned int uint;

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
			return Vec4f(X - v.X, Y - v.Y, Z - v.Z, W + v.W);
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

template<uint nrows, uint ncols, typename T>
class mat;

//////////////////
// Vectors ///////
//////////////////

template <uint dim, typename T>
struct vec 
{
	vec() 
	{
		for (uint i = 0; i < dim; i++)
		{
			data[i] = T();
		}
	}

	T& operator[](const uint i) { assert(i < dim); return data[i]; }
	const T& operator[](const uint i) const { assert(i < dim); return data[i]; }

private:
	T data[dim];
};

template <typename T>
struct vec<2, T> 
{
	vec() : x(T()), y(T()) {}

	vec(T X, T Y) : x(X), y(Y) {}

	template <class U>
	vec<2, T>(const vec<2, U> &v);

	T& operator[](const uint i) { assert(i < 2); return i <= 0 ? x : y; }
	const T& operator[](const uint i) const { assert(i < 2); return i <= 0 ? x : y; }

	T x, y;
};

template<typename T> 
struct vec<3, T> 
{
	vec() : x(T()), y(T()), z(T()) {}

	vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

	template <class U> vec<3, T>(const vec<3, U> &v);

	T& operator[](const uint i) { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }
	const T& operator[](const uint i) const { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }

	float mag() { return sqrt(x*x + y*y + z*z); }
	vec<3, T>& normalise() { *this = (*this)*(1 / mag()); return *this; }

	T x, y, z;
};

template<typename T>
struct vec<4, T>
{
	vec() : x(T()), y(T()), z(T()), w(T()) {}

	vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}

	T& operator[](const uint i) { assert(i < 3); return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w)); }
	const T& operator[](const uint i) const { assert(i < 3); return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w)); }

	float mag() { return sqrt(x*x + y*y + z*z + w*w); }
	vec<4, T>& normalise() { *this = (*this)*(1 / mag()); return *this; }

	T x, y, z, w;
};

template<uint dim, typename T>
T operator*(const vec<dim, T>& lhs, const vec<dim, T>& rhs)
{
	T ret = T();
	for (uint i = dim; i--; ret += lhs[i] * rhs[i]);
	return ret;
}

template<uint dim, typename T>
vec<dim, T> operator+(vec<dim, T> lhs, const vec<dim, T>& rhs)
{
	for (uint i = dim; i--; lhs[i] += rhs[i]);
	return lhs;
}

template<uint dim, typename T>
vec<dim, T> operator-(vec<dim, T> lhs, const vec<dim, T>& rhs)
{
	for (uint i = dim; i--; lhs[i] -= rhs[i]);
	return lhs;
}

template<uint dim, typename T, typename U>
vec<dim, T> operator*(vec<dim, T> lhs, const U& rhs)
{
	for (uint i = dim; i--; lhs[i] *= rhs);
	return lhs;
}

template<uint dim, typename T, typename U>
vec<dim, T> operator/(vec<dim, T> lhs, const U& rhs)
{
	for (uint i = dim; i--; lhs[i] /= rhs);
	return lhs;
}

template<uint len, uint dim, typename T>
vec<len, T> embed(const vec<dim, T>& v, T fill = 1)
{
	vec<len, T> ret;
	for (uint i = len; i--; ret[i] = (i < dim ? v[i] : fill));
	return ret;
}

template<uint len, uint dim, typename T>
vec<len, T> proj(const vec<dim, T>& v)
{
	vec<len, T> ret;
	for (uint i = len; i--; ret[i] =  v[i]);
	return ret;
}

template <typename T>
vec<3, T> cross(vec<3, T> v1, vec<3, T> v2)
{
	return vec<3, T>(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

//////////////////
// Matrices //////
//////////////////

// This little helper function will recursively calculate the determinant of any square matrix with dimension "dim"
template<uint dim, typename T>
struct dt
{
	static T det(const mat<dim, dim, T>& src)
	{
		T ret = 0;
		for (uint i=dim; i--; ret += src[0][i]*src.cofactor(0, i));
		return ret;
	}
};

// This is required to make sure the recursion above stops at some point
template<typename T>
struct dt<1, T> {
	static T det(const mat<1, 1, T>& src) {
		return src[0][0];
	}
};

template<uint nrows, uint ncols, typename T>
class mat 
{
	vec<ncols, T> rows[nrows];
public:
	mat() {}

	vec<ncols, T>& operator[] (const uint id)
	{
		assert(id < nrows);
		return rows[id];
	}

	const vec<ncols, T>& operator[] (const uint id) const 
	{
		assert(id < nrows);
		return rows[id];
	}

	vec<nrows, T> col(const uint id) const 
	{
		assert(id < ncols);
		vec<nrows, T> ret;
		for (uint i = nrows; i--; ret[i] = rows[i][id]);
		return ret;
	}

	void setcol(const uint id, vec<nrows, T> v)
	{
		assert(id < ncols);
		for (uint i = nrows; i--; rows[i][id] = v[i]);
	}

	static mat<nrows, ncols, T> identity()
	{
		mat<nrows, ncols, T> ret;
		for (uint i = nrows; i--;)
			for (uint j = ncols; j--; ret[i][j] = (i == j));
		return ret;
	}

	T det() const
	{
		// Determinants only work for square matrices
		assert(nrows == ncols);
		return dt<ncols, T>::det(*this);
	}

	mat<nrows - 1, ncols - 1, T> get_minor(uint row, uint col) const 
	{
		mat<nrows - 1, ncols - 1, T> ret;
		for (uint i = nrows - 1; i--;)
			for (uint j = ncols - 1; j--; ret[i][j] = rows[i < row ? i : i + 1][j < col ? j : j + 1]);
		return ret;
	}

	// Recursive
	T cofactor(uint row, uint col) const
	{
		return get_minor(row, col).det()*((row + col) % 2 ? -1 : 1);
	}

	mat<nrows, ncols, T> adjugate() const 
	{
		mat<nrows, ncols, T> ret;
		for (uint i = nrows; i--;)
			for (uint j = ncols; j--; ret[i][j] = cofactor(i, j));
	}

	mat<nrows, ncols, T> invert_transpose()
	{
		mat<nrows, ncols, T> ret = adjugate();
		T temp = ret[0] * rows[0];
		return ret / temp;
	}

	mat<nrows, ncols, T> invert()
	{
		return invert_transpose().transpose();
	}

	mat<ncols, nrows, T> transpose()
	{
		mat<ncols, nrows, T> ret;
		for (uint i = ncols; i--; ret[i] = this->col(i));
		return ret;
	}
};

template<uint nrows, uint ncols, typename T> 
vec<nrows, T> operator*(const mat<nrows, ncols, T>& lhs, const vec<ncols, T>& rhs)
{
	vec<nrows, T> ret;
	// note that lhs[i] is a vector and this is a dot product operation
	for (uint i = nrows; i--; ret[i] = lhs[i] * rhs);
	return ret;
}

template<uint R1, uint C1, uint C2, typename T>
mat<R1, C2, T> operator*(const mat<R1, C1, T>& lhs, const mat<C1, C2, T>& rhs)
{
	mat<R1, C2, T> ret;
	for (uint i = R1; i--;)
		for (uint j = C2; j--; ret[i][j] = lhs[i] * rhs.col(j));
	return ret;
}

template<uint nrows, uint ncols, typename T>
mat<ncols, nrows, T> operator/(mat<nrows, ncols, T> lhs, const T& rhs)
{
	for (size_t i = nrows; i--; lhs[i] = lhs[i] / rhs);
	return lhs;
}

typedef vec<2, float> vec2;
typedef vec<2, int>   vec2i;
typedef vec<3, float> vec3;
typedef vec<3, int>   vec3i;
typedef vec<4, float> vec4;
typedef mat<4, 4, float> mat4;

mat4 MakeScale(vec3 Scaling);

mat4 MakeTranslate(vec3 translate);

mat4 MakeRotate(vec3 rotation);

mat4 MakePerspective(float ScreenWidth, float ScreenHeight, float Near, float Far, float FOV);

mat4 MakeViewport(float width, float height);

mat4 MakeLookAt(vec3 Forward, vec3 Up);

void GetAxesFromRotation(vec3 Rotation, vec3 &Forward, vec3 &Right, vec3 & Up);

#endif

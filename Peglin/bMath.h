#pragma once
#include <math.h>
#include <random>

#define PI 3.141592

struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vector2(int x, int y)
		: x(x)
		, y(y)
	{

	}

	/*Vector2(UINT32 x, UINT32 y)
		: x(x)
		, y(y)
	{

	}*/

	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator+(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}

	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}

	Vector2 operator*(const float ratio)
	{
		Vector2 temp;
		temp.x = x * ratio;
		temp.y = y * ratio;

		return temp;
	}

	Vector2 operator/(const float ratio)
	{
		Vector2 temp;
		temp.x = x / ratio;
		temp.y = y / ratio;

		return temp;
	}

	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}

	bool operator==(const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}

	void operator-=(const float& value)
	{
		x -= value;
		y -= value;
	}

	void operator+=(const float& value)
	{
		x += value;
		y += value;
	}

	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}
};

namespace b::math
{
	// 벡터를 degree만큼 회전(반시계)
	inline static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		vector.Normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) + vector.y * cosf(radian);

		return Vector2(x, y);
	}

	inline static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	inline static Vector2 Reflect(Vector2& v1, Vector2& v2)
	{
		// v1 = velocity, v2 = dir
		Vector2 reflect = v1 - v2 * math::Dot(v1, v2);
		reflect -= v2 * math::Dot(v1, v2);
		reflect.Normalize();

		return reflect;
	}

	inline static std::vector<int> Random(int n, int max)
	{
		// random_devie : 시드값 생성
		std::random_device rd;
		// random_device를 통해 난수 생성 엔진 초기화
		std::mt19937 gen(rd());
		// 0 ~ max까지 균등하게 나타나는 난수열을 생성하기 위해 귱등 분포 정의
		std::uniform_int_distribution<int> dis(0, max);
		bool flag = true;
		std::vector<int> result = {};

		for (int i = 0; i < n; )
		{
			int num = dis(gen);
			for (int r : result)
			{
				if (num == r)
				{
					flag = false;
				}
				else
				{
					flag = true;
				}
			}

			if (flag)
			{
				result.push_back(num);
				i++;
			}
		}

		return result;
	}
}
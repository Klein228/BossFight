#pragma once
#include <corecrt_math.h>
class Vector2
{
public:
	Vector2() = default;
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	~Vector2() {}
	Vector2 operator+(const Vector2 v) const
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 operator-(const Vector2 v) const
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2 operator*(const float val)const
	{
		return Vector2(x * val, y * val);
	}
	Vector2 operator/(const float val)
	{
		return Vector2(x / val, y / val);
	}
	void operator+=(const Vector2 v)
	{
		x += v.x;
		y += v.y;
	}
	void operator-=(const Vector2 v)
	{
		x -= v.x;
		y -= v.y;
	}
	void operator*=(float v)
	{
		x *= v;
		y *= v;
	}
	void operator/=(float v)
	{
		x /= v;
		y /= v;
	}
	float length() const
	{
		return sqrt(x * x + y * y);
	}
	Vector2 normalize()
	{
		float len = length();
		if (len == 0)return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}
	double dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}
	float x;
	float y;
private:

};

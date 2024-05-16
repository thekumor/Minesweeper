#include "Vectors.h"

namespace mines
{

	Vector2::Vector2(std::int32_t x, std::int32_t y)
		: X(x), Y(y)
	{
	}

	Vector2::Vector2(std::int32_t val)
		: X(val), Y(val)
	{
	}

	Vector2::Vector2(const Vector2& other)
		: X(other.x), Y(other.y)
	{
	}

	Vector2 Vector2::operator+(const Vector2& other)
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 Vector2::operator-(const Vector2& other)
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 Vector2::operator*(const Vector2& other)
	{
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 Vector2::operator/(const Vector2& other)
	{
		return Vector2(x / other.x, y / other.y);
	}

}
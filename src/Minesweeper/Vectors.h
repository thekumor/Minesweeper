#pragma once

#include <cstdint>

namespace mwr
{

	template <typename T>
	struct Vec2
	{
		Vec2(T x, T y) :
			X(x), Y(y)
		{
		}
		Vec2() = default;

		union
		{
			T x;
			T X;
		};
		union
		{
			T y;
			T Y;
		};

		[[nodiscard]] Vec2 operator+(const Vec2&& other) const noexcept
		{
			return Vec2(x + other.x, y + other.y);
		}
		[[nodiscard]] Vec2 operator-(const Vec2&& other) const noexcept
		{
			return Vec2(x - other.x, y - other.y);
		}
		[[nodiscard]] Vec2 operator*(const Vec2&& other) const noexcept
		{
			return Vec2(x * other.x, y * other.y);
		}
		[[nodiscard]] Vec2 operator/(const Vec2&& other) const noexcept
		{
			return Vec2(x / other.x, y / other.y);
		}
	};

	typedef Vec2<std::int32_t> Vec2i;

}
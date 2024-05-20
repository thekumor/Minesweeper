#pragma once

#include <cstdint>

namespace mines
{

	struct Vector2
	{
		Vector2(std::int32_t x, std::int32_t y);
		Vector2(std::int32_t val);
		Vector2(const Vector2& other);
		Vector2() = default;

		[[nodiscard]] Vector2 operator+(const Vector2& other);
		[[nodiscard]] Vector2 operator-(const Vector2& other);
		[[nodiscard]] Vector2 operator*(const Vector2& other);
		[[nodiscard]] Vector2 operator/(const Vector2& other);

		union
		{
			std::int32_t x, X;
		};
		union
		{
			std::int32_t y, Y;
		};
	};

}
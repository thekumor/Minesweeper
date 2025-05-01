#pragma once

#include <cstdint>

#define MWR_VEC0 mwr::Vec2i(0, 0)

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
	typedef Vec2<std::uint32_t> Vec2u;

}

namespace std
{

	template <typename T>
	struct hash<mwr::Vec2<T>>
	{
		size_t operator()(const mwr::Vec2<T>& t) const
		{
			std::hash<T> hasher;
			size_t h1 = hasher(t.x);
			size_t h2 = hasher(t.y);

			return h1 ^ (h2 << 1);
		}
	};

}
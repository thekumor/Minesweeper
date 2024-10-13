//****************************************************************
// File: Vectors.h
// Purpose: Contains mines::Vector2<>, which is used for storing
//			two integers together and allows maths on them.
//  
// Authors: The Kumor
//****************************************************************

#pragma once

#include <cstdint>

#define Vec2 Vector2<>

namespace mines
{

	//----------------------------------------------------------
	// Container for a pair of numbers, allows arithmetic
	// operations on them.
	//----------------------------------------------------------
	template <typename T = std::int32_t>
	struct Vector2
	{
		Vector2(T x, T y)
			: X(x), Y(y)
		{
		}

		Vector2(T val)
			: X(val), Y(val)
		{
		}

		template <typename Y>
		Vector2<T>(const Vector2<Y>& other)
			: X(x), Y(y)
		{
		}

		Vector2(const Vector2& other)
			: X(other.x), Y(other.y)
		{
		}

		[[nodiscard]] Vector2 operator+(const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		[[nodiscard]] Vector2 operator-(const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		template <typename Y>
		[[nodiscard]] Vector2<T> operator*(const Vector2<Y>& other) const
		{
			return Vector2<T>(x * other.x, y * other.y);
		}

		template <typename Y>
		[[nodiscard]] Vector2<T> operator/(const Vector2<Y>& other) const
		{
			return Vector2<T>(x / other.x, y / other.y);
		}

		union
		{
			T x, X;
		};
		union
		{
			T y, Y;
		};
	};

}

// The Kumor
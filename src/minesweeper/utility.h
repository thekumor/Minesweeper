#pragma once

// STL
#include <cstdint>

namespace mwr
{

	template <typename T>
	class Handle
	{
	public:
		Handle(T* value) : m_Value(value), m_IsValid(true) {}
		Handle() = default;
		~Handle() = default;

		bool IsValid() const { return m_IsValid; }
		void SetValid(bool valid) { m_IsValid = valid; }

		T* operator*() const { return m_Value; }

	private:
		T* m_Value;
		bool m_IsValid;
	};

}
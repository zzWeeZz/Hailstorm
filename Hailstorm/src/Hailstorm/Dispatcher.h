#pragma once
#include "Event.h"

namespace Hailstorm
{
	class Dispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		Dispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		};
	private:
		Event& m_Event;
	};
}

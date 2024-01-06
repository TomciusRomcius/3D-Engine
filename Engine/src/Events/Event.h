#pragma once

namespace Engine3D
{
	enum class EventType
	{
		None = 0,
		KeyboardEvent,
		MouseButtonEvent,
		MouseMovedEvent
	};

	class Event
	{
	public:
		Event()
		: m_IsHandled(false) {}
		inline void StopPropagation() { m_IsHandled = true; }
		virtual ~Event() = default;
		private:
		bool m_IsHandled;
	};

	class KeyboardEvent : public Event
	{
	public:
		KeyboardEvent(int keycode, bool isDown)
			: m_KeyCode(keycode), m_IsDown(isDown)
		{}
		inline int GetKeyCode() const { return m_KeyCode; }
	private:
		int m_KeyCode;
		bool m_IsDown;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button, bool isDown)
			: m_Button(button), m_IsDown(isDown)
		{}
		int GetButton() const { return m_Button; }
	private:
		int m_Button;
		bool m_IsDown;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_Pos(x, y) {}
		inline glm::vec2 GetPos() const {
			return m_Pos;
		}
	private:
		glm::vec2 m_Pos;
	};
}
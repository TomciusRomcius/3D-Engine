#include "enpch.h"
#include "Input.h"

namespace Engine3D
{
	std::map<int, bool> Input::m_Keys{};
	std::map<int, bool> Input::m_MouseButtons{};
	std::map<int, std::map<unsigned int, std::function<void()>>> Input::m_KeyPressCallbacks{};
	glm::vec2 Input::m_MousePos{};

	// -----------------------GENERAL-----------------------------
	void Input::OnEvent(Event* event, EventType type)
	{
		switch (type)
		{
		case EventType::KeyboardEvent:
			OnKeyboardEvent(event);
			break;
		case EventType::MouseButtonEvent:
			OnMouseButtonEvent(event);
			break;
		case EventType::MouseMovedEvent:
			OnMouseMoveEvent(event);
			break;
		}
	}

	// -----------------------KEYBOARD-----------------------------
	void Input::OnKeyboardEvent(Event* event)
	{
		auto keyEvent = dynamic_cast<KeyboardEvent*>(event);

		if (keyEvent->IsDown())
		{
			m_Keys[keyEvent->GetKeyCode()] = true;
			auto it = m_KeyPressCallbacks.find(keyEvent->GetKeyCode());
			if (it != m_KeyPressCallbacks.end())
			{
				for (auto& callback : it->second)
				{
					callback.second();
				}
			}
		}
	}

	bool Input::GetKeyDown(int key)
	{
		return m_Keys[key];
	}
	bool Input::GetKeyUp(int key)
	{
		return !m_Keys[key];
	}

	int Input::AddKeyPressCallback(const int key, const std::function<void()> callback)
	{
		static unsigned int id = 0;
		if (m_KeyPressCallbacks.find(key) == m_KeyPressCallbacks.end())
		{
			m_KeyPressCallbacks[key] = std::map<unsigned int, std::function<void()>>();
		}
		m_KeyPressCallbacks[key].insert({ id, callback });
		return id;
		id++;
	}

	bool Input::RemoveKeyPressCallback(const int key, unsigned int id)
	{
		if (m_KeyPressCallbacks.find(key) == m_KeyPressCallbacks.end())
		{
			return false;
		}
		m_KeyPressCallbacks[key].erase(id);
		return true;
	}

	// -----------------------MOUSE-----------------------------
	void Input::OnMouseButtonEvent(Event* event)
	{
		auto mouseEvent = dynamic_cast<MouseButtonEvent*>(event);

		if (mouseEvent->IsDown())
		{
			m_MouseButtons[mouseEvent->GetButton()] = true;
			auto it = m_KeyPressCallbacks.find(mouseEvent->GetButton());
			if (it != m_KeyPressCallbacks.end())
			{
				for (auto& callback : it->second)
				{
					callback.second();
				}
			}
		}
		else
		{
			m_MouseButtons[mouseEvent->GetButton()] = false;
		}
	}

	bool Input::GetMouseButtonDown(int button)
	{
		return m_MouseButtons[button];
	}
	bool Input::GetMouseButtonUp(int button)
	{
		return !m_MouseButtons[button];
	}

	int Input::AddMousePressCallback(const int button, const std::function<void()> callback)
	{
		static unsigned int id = 0;
		if (m_KeyPressCallbacks.find(button) == m_KeyPressCallbacks.end())
		{
			m_KeyPressCallbacks[button] = std::map<unsigned int, std::function<void()>>();
		}
		m_KeyPressCallbacks[button].insert({ id, callback });
		return id;
		id++;
	}

	bool Input::RemoveMousePressCallback(const int button, unsigned int id)
	{
		if (m_KeyPressCallbacks.find(button) == m_KeyPressCallbacks.end())
		{
			return false;
		}
		if (m_KeyPressCallbacks[button].find(id) == m_KeyPressCallbacks[button].end())
		{
			return false;
		}
		m_KeyPressCallbacks[button].erase(id);
		return true;
	}

	void Input::OnMouseMoveEvent(Event* event)
	{
		auto mouseEvent = dynamic_cast<MouseMovedEvent*>(event);
		m_MousePos = mouseEvent->GetPos();
	}

	glm::vec2 Input::GetMousePosition()
	{
		return m_MousePos;
	}
}
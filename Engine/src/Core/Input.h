#pragma once
#include "Events/Event.h"
#include "Core/Log.h"
namespace Engine3D
{
	class Input
	{
	// -----------------------GENERAL-----------------------------
	public:
		static void OnEvent(Event* event, EventType type);
	private:
		static void OnKeyboardEvent(Event* event);
		static void OnMouseButtonEvent(Event* event);
		static void OnMouseMoveEvent(Event* event);

	// -----------------------KEYBOARD EVENTS---------------------
	public:
		static bool GetKeyDown(int key);
		static bool GetKeyUp(int key);
		static int AddKeyPressCallback(const int key, const std::function<void()> callback);
		static bool RemoveKeyPressCallback(const int key, unsigned int id);
	private:
		static std::map<int, bool> m_Keys;
		static std::map<int, std::map<unsigned int, std::function<void()>>> m_KeyPressCallbacks;

	// -----------------------MOUSE EVENTS-----------------------
	public:
		static bool GetMouseButtonDown(int button);
		static bool GetMouseButtonUp(int button);
		static glm::vec2 GetMousePosition();
		static int AddMousePressCallback(const int button, const std::function<void()> callback);
		static bool RemoveMousePressCallback(const int button, unsigned int id);
	private:
		static std::map<int, bool> m_MouseButtons;
		static glm::vec2 m_MousePos;
		static std::map<int, std::map<unsigned int, std::function<void()>>> m_MousePressCallbacks;
	};
}


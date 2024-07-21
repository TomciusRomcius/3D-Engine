#pragma once
#include "Layer.h"

namespace Engine3D
{
	class LayerSystem
	{
	public:
		LayerSystem(GLFWwindow* WINDOW);
		void AttachLayer(Layer* layer);
		void Update();
		std::vector<Layer*>& GetLayers();
		void OnEvent(Event* event, EventType eventType);
		Layer* GetLayerByName(const std::string& name);
	private:
		std::vector<Layer*> m_Layers;
		GLFWwindow* m_WINDOW;
	};
}
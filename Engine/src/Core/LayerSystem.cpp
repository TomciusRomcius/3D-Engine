#include "enpch.h"
#include "LayerSystem.h"

namespace Engine3D
{
	LayerSystem::LayerSystem(GLFWwindow* WINDOW)
		: m_WINDOW(WINDOW)
	{ }

	void LayerSystem::AttachLayer(Layer* layer)
	{
		layer->m_WINDOW = m_WINDOW;
		layer->m_OtherLayers = &m_Layers;
		m_Layers.push_back(layer);
		layer->OnAttach();
	}

	void LayerSystem::Update()
	{
		for (Layer* layer : m_Layers)
		{
			layer->Update();
		}
	}

	std::vector<Layer*>& LayerSystem::GetLayers()
	{
		return m_Layers;
	}

	void LayerSystem::OnEvent(Event* event, EventType eventType)
	{
		// Go backwards through the layers
		for (int i = m_Layers.size() - 1; i >= 0; i--)
		{
			m_Layers[i]->OnEvent(event, eventType);
			if (event->m_IsHandled)
				break;
		}
	}
	Layer* LayerSystem::GetLayerByName(const std::string& name)
	{
		for (Layer* layer : m_Layers)
		{
			if (layer->m_Name == name)
				return layer;
		}
		return nullptr;
	}
}
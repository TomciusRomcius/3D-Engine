#pragma once
#include "Layer.h"

namespace Engine3D
{
	class LayerSystem
	{
	public:
		LayerSystem()
		{
		}
		void AttachLayer(Layer* layer)
		{
			m_Layers.push_back(layer);
			layer->OnAttach();
		}

		void Update()
		{
			for (Layer* layer : m_Layers)
			{
				layer->Update();
			}
		}

		std::vector<Layer*>& GetLayers()
		{
			return m_Layers;
		}

		void OnEvent(Event* event, EventType eventType)
		{
			// Go backwards through the layers
			for (int i = m_Layers.size() - 1; i >= 0; i--)
			{
				m_Layers[i]->OnEvent(event, eventType);
			}
		}

	private:
		std::vector<Layer*> m_Layers;
	};
}
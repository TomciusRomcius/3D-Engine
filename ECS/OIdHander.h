#pragma once

class OIdHander {
public:
	OIdHander();
	// Public method to get the OIdHander instance
	inline std::queue<unsigned int>& GetIds() 
	{
		return mAvailableIds;
	}
	std::queue<unsigned int> mAvailableIds; 
};
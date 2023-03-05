#include "enpch.h"
#include "ObjectSystem.h"

#include <mutex>


// Define the static variables


OIdHander* OIdHander::instance = nullptr;
std::mutex OIdHander::mutex;
std::queue<unsigned int> OIdHander::mAvailableIds;



OIdHander* OIdHander::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex);
	if (instance == nullptr) {
		instance = new OIdHander();
		for (int i = 0; i < MAX_OBJECTS; i++)
		{
			mAvailableIds.push(i);
		}
	}
	return instance;
}

std::queue<unsigned int>& OIdHander::GetIds()
{
	return mAvailableIds;
}

inline Object::Object() {
	if (OIdHander::GetInstance()->mAvailableIds.empty()) {
		std::cout << "Forgot to init queue" << std::endl;
	}
	mId = OIdHander::GetInstance()->mAvailableIds.front();;
	OIdHander::GetInstance()->mAvailableIds.pop();
}

inline Object::~Object() {
	OIdHander::GetInstance()->mAvailableIds.push(mId);
}


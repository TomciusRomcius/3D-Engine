#include "enpch.h"
#include <mutex>

constexpr unsigned int MAX_COMPONENTS = 100;
constexpr unsigned int MAX_OBJECTS = 500;
using ObjectID = unsigned int;

class ENGINE_API Object;


// Interface implementation so we can store different componenet arrays in the component manager

class ENGINE_API IComponentArray
{
public:
	virtual void Update() = 0;
};

template <typename T>
class ENGINE_API ComponentArray : public IComponentArray
{
public:
	void Update()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		for (unsigned int i = 0; i < mSize; ++i)
		{
			if (mAttached[i])
			{
				mComponentArray[i].Update();
			}
		}
	}

	void InsertData(ObjectID id, Object* object) // Adds an object to the component array
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mIndexToObject[mSize] = id;
		mObjectToIndex[id] = mSize;
		mComponentArray[mSize] = T();
		mComponentArray[mSize].object = object;
		mComponentArray[mSize].Start();
		mAttached[mSize] = true;

		++mSize;
	}

	void RemoveData(ObjectID id)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		// Copy element at end into deleted element's place to maintain density
		unsigned int indexOfRemovedObject = mObjectToIndex[id];
		unsigned int indexOfLastElement = mSize - 1;
		mComponentArray[indexOfRemovedObject] = mComponentArray[indexOfLastElement];

		// Update the map to point to moved spot
		ObjectID objectOfLastElement = mIndexToObject[indexOfLastElement];
		mObjectToIndex[objectOfLastElement] = indexOfRemovedObject;
		mIndexToObject[indexOfRemovedObject] = objectOfLastElement;

		mAttached[indexOfRemovedObject] = mAttached[indexOfLastElement];
		mAttached[indexOfLastElement] = false;

		mObjectToIndex.erase(id);
		mIndexToObject.erase(indexOfLastElement);

		--mSize;
	}

	T& GetData(ObjectID id) // Retrieve the object's component
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mComponentArray[mObjectToIndex.at(id)];
	}
private:
	std::array<T, MAX_OBJECTS> mComponentArray; // Stores all the same type components eg. Transform
	std::unordered_map<ObjectID, unsigned int> mObjectToIndex;
	std::map<unsigned int, ObjectID> mIndexToObject;
	std::bitset<MAX_OBJECTS> mAttached;
	unsigned int mSize; // Used for determining mapping
	std::mutex mMutex;
};


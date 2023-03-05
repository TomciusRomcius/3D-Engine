#pragma once
#include <mutex>

constexpr unsigned int MAX_COMPONENTS = 100;
constexpr unsigned int MAX_OBJECTS = 20;
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
	void Update() override // Gets called every frame
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

class ENGINE_API ComponentManager // Holds all component arrays
{
public:
	static ComponentManager& GetInstance();
	static void Update(); // Gets called every frame

	template <typename T>
	void RegisterComponent() // Call this before adding a component for the first tie
	{
		std::lock_guard<std::mutex>lock(mutex);
		const char* typeName = typeid(T).name();
		mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
	}
	template <typename T>
	void AddComponent(ObjectID id, Object* object) // Adds a component to a given object
	{
		GetComponentArray<T>()->InsertData(id, object);
	}
	template <typename T>
	void RemoveComponent(ObjectID id) // Removes component from a given object
	{
		GetComponentArray<T>()->RemoveData(id);
	}
	template <typename T>
	T& GetComponent(ObjectID id) // Returns the component of the given object
	{
		return GetComponentArray<T>()->GetData(id);
	}
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays;

private:
	static std::mutex mutex;
	static ComponentManager* instance;

	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray() // Gets the component array based of the name
	{
		std::string typeName = typeid(T).name();
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays.at(typeName));
	}
};


// OIdHander.h - header file
class ENGINE_API OIdHander {
private:	
	static std::mutex mutex;
	static OIdHander* instance;
	// Private constructor to prevent instantiation
	OIdHander() {}

public:
	// Public method to get the OIdHander instance
	static OIdHander* GetInstance();
	static std::queue<unsigned int> mAvailableIds;

	std::queue<unsigned int>& GetIds();
};


class ENGINE_API Object {
public:
	Object();
	template <typename T>
	void AddComponent() {
		ComponentManager::GetInstance().AddComponent<T>(this->mId, this);
	}

	template <typename T>
	T& GetComponent() {
		return ComponentManager::GetInstance().GetComponent<T>(this->mId);
	}

	template <typename T>
	void RemoveComponent() {
		ComponentManager::GetInstance().RemoveComponent<T>(this->mId);
	}

	~Object();
	unsigned int Id() { return mId; }
private:
	ObjectID mId;
	std::bitset<MAX_COMPONENTS> mComponentBitset;
};

#pragma once

constexpr unsigned int MAX_COMPONENTS = 100;
constexpr unsigned int MAX_OBJECTS = 20;
using ObjectID = unsigned int;

class Object;


// Interface implementation so we can store different componenet arrays in the component manager

class IComponentArray
{
public:
	virtual void Update() = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:

	void Update() override // Gets called every frame
	{
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
		mIndexToObject[mSize] = id;
		mObjectToIndex[id] = mSize;
		mComponentArray[mSize] = T();
		mComponentArray[mSize].object = object;
		mComponentArray[mSize].Start();
		mAttached[mSize] = true;

		mSize++;
	}

	void RemoveData(ObjectID id)
	{

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
		return mComponentArray[mObjectToIndex[id]];
	}
private:
	std::array<T, MAX_OBJECTS> mComponentArray; // Stores all the same type components eg. Transform
	std::map<ObjectID, unsigned int> mObjectToIndex;
	std::map<unsigned int, ObjectID> mIndexToObject;
	std::bitset<MAX_OBJECTS> mAttached;
	unsigned int mSize; // Used for determining mapping
};

class ComponentManager // Holds all component arrays
{
public:
	static ComponentManager& GetInstance() // Singleton implementation, returns the instance
	{
		static ComponentManager instance;
		return instance;
	}
	static void Update() // Gets called every frame
	{
		// Call update on all component arrays
		for (auto componentA : ComponentManager::GetInstance().mComponentArrays)
		{
			componentA.second.get()->Update();
		}
	}
	template <typename T>
	void RegisterComponent() // Call this before adding a component for the first tie
	{
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

private:
	std::map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays;

	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray() // Gets the component array based of the name
	{
		const char* typeName = typeid(T).name();
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
	}
};

class Object // Class, which holds all of the components
{
public:
	Object()
	{
		if (mAvailabeIds.empty())
		{
			std::cout << "Forgot to init queue" << std::endl;
		}
		mId = mAvailabeIds.front();
		mAvailabeIds.pop();
	};
	static void InitQueue() // Call this function before creating any objects
	{
		// Initializes the queue with the ids
		for (int i = 0; i < MAX_OBJECTS; i++)
		{
			mAvailabeIds.push(i);
		}
	}
	template <typename T>
	void AddComponent()
	{
		return ComponentManager::GetInstance().AddComponent<T>(this->mId, this);
	}
	template <typename T>
	T& GetComponent()
	{
		return ComponentManager::GetInstance().GetComponent<T>(this->mId);
	}
	template <typename T>
	void RemoveComponent()
	{
		ComponentManager::GetInstance().RemoveComponent<T>(this->mId);
	}
	~Object()
	{
		mAvailabeIds.push(mId);
	}
	unsigned int Id() { return mId; }
private:
	static std::queue<unsigned int> mAvailabeIds;
	ObjectID mId;
	std::bitset<MAX_COMPONENTS> mComponentBitset;
};


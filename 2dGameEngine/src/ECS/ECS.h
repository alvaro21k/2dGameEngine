#ifndef ECS_H
#define ECS_H
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

struct BaseComponent {
protected:
	static int nextId;
};

template <typename T>
class Component: public BaseComponent {
	static int GetId() {
		static auto id = nextId++;
		return id;
	}
};

class Entity {
private:
	int id;

public:
	Entity(int id): id(id) {}
	int GetId() const;

	bool operator ==(const Entity& other) const { return id == other.id; }
};

class System {
private:
	Signature componentSignature;
	std::vector<Entity> entities;

public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
	std::vector<Entity> GetSystemEntities() const;
	const Signature& GetComponentSignature() const;

	template <typename T> void RequireComponent();
};

class IPool {
public:
	virtual ~IPool() {}
};

template <typename T>
class Pool:public IPool {
private:
	std::vector<T> data;

public:
	Pool(int size = 100) {
		data.resize(size);
	}
	virtual ~Pool() = default;

	bool isEmpty() const {
		return data.empty();
	}

	int GetSize() const {
		return data.size();
	}

	void Resize(int n) {
		data.resize(n);
	}

	void Clear(){
		data.clear();
		}

	void Add(T object) {
		data.push_back(object);
	}

	void Set(int index, T object) {
		data[index] = object;
	}

	T& Get(int index) {
		return static_cast<T&>data[index];
	}

	T& operator [](unsigned int index) {
		return data[index];
	}
};

class Registry {
private:
	int numEntities = 0;

	std::vector<IPool*> componentPools;

	std::vector<Signature> entityComponentSignatures;

	std::unordered_map<std::type_index, System*> systems;

	std::set<Entity> entitiesToBeAdded;

	std::set<Entity> entitiesToBeKilled;

public:
	Registry() = default;

	Entity CreateEntity();

	void Update();

	void AddEntityToSystem(Entity entity);

	template<typename T, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
	template<typename T> void RemoveComponent(Entity entity);
	template<typename T> bool HasComponent(Entity entity);
	template<typename T> T& GetComponent(Entity entity);





};

template <typename T>
void System::RequireComponent() {
	const auto componentId = Component<T>::GetId();
	componentSignature.set(componentId);
}

#endif // !ECS_H


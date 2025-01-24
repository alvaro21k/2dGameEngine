#include "ECS.h"
#include "../Logger/Logger.h"

int Entity::GetId() const {
	return id;
}

void System::AddEntityToSystem(Entity entity) {
	entities.push_back(entity);
}
void System::RemoveEntityFromSystem(Entity entity) {
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[&entity](Entity other) {return entity == other; 
		}), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
	return entities;
}

const Signature& System::GetComponentSignature() const {
	return componentSignature;
}

Entity Registry::CreateEntity(){
	int entityId;

	entityId = numEntities++;

	Entity entity(entityId);
	entitiesToBeAdded.insert(entity);

	Logger::Log("Entity created with Id = " + std::to_string(entityId));

	return entity;

}
	
void Registry::Update() {

}

template<typename T, typename ...TArgs>
void AddComponent(Entity entity, TArgs&& ...args) {
	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.GetId();

	if (componentId >= componentPools.size()) {
		componentPools.resize(componentId + 1, nullptr);
	}

	if (!componentPools[componentId]) {
		Pool<T>* newComponentPool = new Pool<T>();
		componentPools[componentId] = newComponentPool;
	}

	Pool<T>* componentPool = Pool<T>(componentPools[componentId]);

	if (entityId > componentPool->GetSize()) {
		componentPool->Resize(numEntities);
	}

	T newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityId, newComponent);

	entityComponentSignature[entityId].set(componentId);
}
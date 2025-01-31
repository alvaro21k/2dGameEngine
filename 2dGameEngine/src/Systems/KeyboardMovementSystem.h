#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"

class KeyboardMovementSystem : public System {
public:
	KeyboardMovementSystem(){}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardMovementSystem::onKeyPress);
	}

	void onKeyPress(KeyPressedEvent& event) {
		std::string keyCode = std::to_string(event.symbol);
		std::string keySymbol(1, event.symbol);
		Logger::Log("Key pressed event emitted: [" + keyCode + "] " + keySymbol);

	}
};


#endif // !KEYBOARDMOVEMENTSYSTEM_H

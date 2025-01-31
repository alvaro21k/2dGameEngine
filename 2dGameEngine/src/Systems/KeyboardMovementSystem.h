#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/KeyboardMovementComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardMovementSystem : public System {
public:
	KeyboardMovementSystem() {
		RequireComponent<KeyboardMovementComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardMovementSystem::onKeyPress);
	}

	void onKeyPress(KeyPressedEvent& event) {
		for (auto entity : GetSystemEntities()) {
			const auto keyboardControl = entity.GetComponent<KeyboardMovementComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidBody = entity.GetComponent<RigidBodyComponent>();

			switch (event.symbol) {
			case SDLK_UP:

				rigidBody.velocity = keyboardControl.upVelocity;
				sprite.srcRect.y = sprite.height * 0;
				break;

			case SDLK_RIGHT:
				rigidBody.velocity = keyboardControl.rightVelocity;
				sprite.srcRect.y = sprite.height * 1;
				break;

			case SDLK_DOWN:
				rigidBody.velocity = keyboardControl.downVelocity;
				sprite.srcRect.y = sprite.height * 2;
				break;

			case SDLK_LEFT:
				rigidBody.velocity = keyboardControl.leftVelocity;
				sprite.srcRect.y = sprite.height * 3;
				break;
			}
		}
		//Change sprite and velocity of the entity

	}
};


#endif // !KEYBOARDMOVEMENTSYSTEM_H

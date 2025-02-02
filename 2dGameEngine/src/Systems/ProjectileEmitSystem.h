#ifndef PROJECTILEEMITSYSTEM_H
#define PROJECTILEEMITSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/KeyboardMovementComponent.h"
#include "../Events/KeyPressedEvent.h"


#include <SDL.h>

class ProjectileEmitSystem : public System {
public:
	ProjectileEmitSystem() {
		RequireComponent<ProjectileEmitterComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &ProjectileEmitSystem::PlayerShoots);
	}

	void PlayerShoots(KeyPressedEvent& event) {
		if (event.symbol == SDLK_SPACE) {
			for (auto entity : GetSystemEntities()) {
				if (entity.HasComponent<KeyboardMovementComponent>()) {
					auto rigidBody = entity.GetComponent<RigidBodyComponent>();
					auto projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
					auto transform = entity.GetComponent<TransformComponent>();

					glm::vec2 projectilePosition;
					projectilePosition.x = transform.position.x ;
					projectilePosition.y = transform.position.y ;

					if (entity.HasComponent<SpriteComponent>()) {
						auto sprite = entity.GetComponent<SpriteComponent>();

						projectilePosition.x += (transform.scale.x * sprite.width / 2);
						projectilePosition.y += (transform.scale.y * sprite.height / 2);

					}

					glm::vec2 projectileVelocity = projectileEmitter.projectileVelocity;
					int directionX = 0;
					int directionY = 0;

					if (rigidBody.velocity.y < 0) directionY = -1;
					if (rigidBody.velocity.y > 0) directionY = 1;
					if (rigidBody.velocity.x < 0) directionX = -1;
					if (rigidBody.velocity.x > 0) directionX = 1;

					projectileVelocity.x = projectileEmitter.projectileVelocity.x * directionX;
					projectileVelocity.y = projectileEmitter.projectileVelocity.y * directionY;

					Entity projectile = entity.registry->CreateEntity();
					projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0);
					projectile.AddComponent<RigidBodyComponent>(projectileVelocity);
					projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4, true);
					projectile.AddComponent<BoxColliderComponent>(4, 4);
					projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);

				}
			}
		}
			
	}

	void Update(std::unique_ptr<Registry>& registry) {
		for (auto entity : GetSystemEntities()) {
			auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			if (projectileEmitter.repeatFrequency == 0) {
				continue;
			}

			if ((SDL_GetTicks() - projectileEmitter.lastEmissionTime) > projectileEmitter.repeatFrequency){
				glm::vec2 projectilePosition = transform.position;
				if (entity.HasComponent<SpriteComponent>()) {
					const auto sprite = entity.GetComponent<SpriteComponent>();
					projectilePosition.x += (transform.scale.x * sprite.width / 2);
					projectilePosition.y += (transform.scale.y * sprite.height / 2);
				}
				
				//Add new projectile
				Entity projectile = registry->CreateEntity();
				projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0);
				projectile.AddComponent<RigidBodyComponent>(projectileEmitter.projectileVelocity);
				projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
				projectile.AddComponent<BoxColliderComponent>(4, 4);
				projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);

				//Update the projectile emitter component last emission to current time
				projectileEmitter.lastEmissionTime = SDL_GetTicks();
			}
		}
	}
};

#endif // !PROJECTILEEMITSYSTEM_H


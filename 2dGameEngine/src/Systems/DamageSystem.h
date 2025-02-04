#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H


#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"

class DamageSystem: public System {
public:
	DamageSystem() {
		RequireComponent<BoxColliderComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
	}

	void onCollision(CollisionEvent& event) {
		Entity a = event.a;
		Entity b = event.b;

		Logger::Log("The damage system received a collision event between entities " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()));
		
		if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
			OnProjectileHitsPlayer(a, b); //a is projectile, b is player
		}

		if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
			OnProjectileHitsPlayer(b, a); //b is projectile, a is player
		}

		if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
			OnProjectileHitsEnemy(a, b);
		}

		if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
			OnProjectileHitsEnemy(b, a);
		}
	}

	void OnProjectileHitsPlayer(Entity projectile, Entity player) {
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

		if (!projectileComponent.isFriendly) {

			auto& health = player.GetComponent<HealthComponent>();

			health.healthPercentage -= projectileComponent.hitPercentDamage;
			Logger::Log("Player's health is now " + std::to_string(health.healthPercentage));

			if (health.healthPercentage <= 0) {
				player.Kill();
			}

			projectile.Kill();
		}
	}

	void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

		if (projectileComponent.isFriendly) {
			auto& health = enemy.GetComponent<HealthComponent>();

			health.healthPercentage -= projectileComponent.hitPercentDamage;
			Logger::Log("Entity " + std::to_string(enemy.GetId()) + " health is now " + std::to_string(health.healthPercentage));

			if (health.healthPercentage <= 0) {
				enemy.Kill();
			}

			projectile.Kill();
		}
	}

	void Update() {

	}
};

#endif // !DAMAGESYSTEM_H


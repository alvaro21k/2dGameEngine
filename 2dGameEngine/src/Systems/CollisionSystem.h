#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	
	void Update() {
		auto entities = GetSystemEntities();

		for (auto i = entities.begin(); i!= entities.end(); i++) {
			Entity a = *i;
			auto aBoxCollider = a.GetComponent<BoxColliderComponent>();
			auto aTransform = a.GetComponent<TransformComponent>();

			for (auto j = i; j != entities.end(); j++) {
				Entity b = *j;
				if (a == b) {
					continue;
				}
				auto bBoxCollider = b.GetComponent<BoxColliderComponent>();
				auto bTransform = b.GetComponent<TransformComponent>();

				bool collisionHappened = CheckAABBCollision(
					aTransform.position.x + aBoxCollider.offset.x,
					aTransform.position.y + aBoxCollider.offset.y,
					aBoxCollider.width,
					aBoxCollider.height,
					bTransform.position.x + bBoxCollider.offset.x,
					bTransform.position.y + bBoxCollider.offset.y,
					bBoxCollider.width,
					bBoxCollider.height
				);

				if (collisionHappened) {
					Logger::Log("Entity " + std::to_string(a.GetId()) + " is colliding with Entity " + std::to_string(b.GetId()));
					

				}
			}
		}
	}

	bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
		return (
			aX < bX + bW &&
			aX + aW > bX &&
			aY < bY + bH &&
			aY + aH > bY
			);
	}
};
#endif // !COLLISIONSYSTEM_H

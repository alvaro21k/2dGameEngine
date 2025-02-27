#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H

#include "../ECS/ECS.h"
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include <glm/glm.hpp>

class RenderGUISystem : public System {
public:
	RenderGUISystem() = default;

	void Update(const std::unique_ptr<Registry>& registry) {
		ImGui::NewFrame();


		if (ImGui::Begin("Spawn enemies")) {
			static int enemyXPos = 0;
			ImGui::InputInt("enemy x position", &enemyXPos);

			static int enemyYPos = 0;
			ImGui::InputInt("enemy y position", &enemyYPos);

			if (ImGui::Button("Create new enemy")) {
				Entity enemy = registry->CreateEntity();
				enemy.Group("enemies");
				enemy.AddComponent<TransformComponent>(glm::vec2(enemyXPos, enemyYPos), glm::vec2(1.0, 1.0), 0.0);
				enemy.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
				enemy.AddComponent<SpriteComponent>("tank-image", 32, 32, 1);
				enemy.AddComponent<BoxColliderComponent>(32, 32);
				enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(100.0, 0.0), 5000, 3000, 10, false);
				enemy.AddComponent<HealthComponent>(100);
			}
		}

		ImGui::End();

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
	}
};

#endif // !RENDERGUISYSTEM_H

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
#include <math.h>
#include <glm/glm.hpp>

class RenderGUISystem : public System {
public:
	RenderGUISystem() = default;

	void Update(const std::unique_ptr<Registry>& registry) {
		ImGui::NewFrame();


		if (ImGui::Begin("Spawn enemies")) {
			static int enemyXPos = 0;
			static int enemyYPos = 0;
			static int enemyXScale = 1;
			static int enemyYScale = 1;
			static int enemyXVel = 0;
			static int enemyYVel = 0;
			static int enemyHealth = 100;
			static float rotation = 0.0;
			static float projAngle = 0.0;
			static float projSpeed = 100.0;
			static int projRepeat = 10;
			static int projDuration = 10;
			const char* items[]{ "tank-image","truck-image" };
			static int selection = 0;
			
			if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Combo("Select enemy sprite", &selection, items, IM_ARRAYSIZE(items));
			}
			ImGui::Spacing;

			ImGui::InputInt("enemy x position", &enemyXPos);
			ImGui::InputInt("enemy y position", &enemyYPos);
			ImGui::InputInt("enemy x scale", &enemyXScale);
			ImGui::InputInt("enemy y scale", &enemyYScale);
			ImGui::InputInt("enemy x velocity", &enemyXVel);
			ImGui::InputInt("enemy y velocity", &enemyYVel);
			ImGui::SliderInt("enemy health", &enemyHealth, 0, 100);
			ImGui::SliderAngle("enemy rotation (deg)", &rotation, 0, 360);
			

			if (ImGui::Button("Create new enemy")) {
				Entity enemy = registry->CreateEntity();
				enemy.Group("enemies");
				enemy.AddComponent<TransformComponent>(glm::vec2(enemyXPos, enemyYPos), glm::vec2(enemyXScale, enemyYScale), glm::degrees(rotation));
				enemy.AddComponent<RigidBodyComponent>(glm::vec2(enemyXVel, enemyYVel));
				enemy.AddComponent<SpriteComponent>(items[selection], 32, 32, 1);
				enemy.AddComponent<BoxColliderComponent>(32, 32);
				double projVelX = cos(projAngle) * projSpeed;
				double projVelY = sin(projAngle) * projSpeed;
				enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(projVelX, projVelY), projRepeat*1000, projDuration*1000, 10, false);
				enemy.AddComponent<HealthComponent>(enemyHealth);
				enemyXPos = enemyYPos = enemyXScale = enemyYScale = enemyXVel = enemyYVel = rotation = projAngle = 0;
				projRepeat = projDuration = 10;
				projSpeed = 100;
				enemyHealth = 100;
			}


			
		}

		ImGui::End();

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
	}
};

#endif // !RENDERGUISYSTEM_H

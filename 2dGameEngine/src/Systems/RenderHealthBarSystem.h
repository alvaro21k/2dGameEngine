#ifndef RENDERHEALTHBARSYSTEM_H
#define RENDERHEALTHBARSYSTEM_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/TransformComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL.h>

class RenderHealthBarSystem : public System {
public:
	RenderHealthBarSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<HealthComponent>();
	}

	void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera) {
		for (auto entity : GetSystemEntities()) {
			auto sprite = entity.GetComponent<SpriteComponent>();
			auto transform = entity.GetComponent<TransformComponent>();
			auto health = entity.GetComponent<HealthComponent>();

			SDL_Color healthBarColor = { 255,255,255 };

			if (health.healthPercentage <= 40) {
				healthBarColor = { 255,0,0 };
			}
			if (health.healthPercentage > 40 && health.healthPercentage <= 70) {
				healthBarColor = { 255,255,0 };

			}
			if (health.healthPercentage > 70) {
				healthBarColor = { 0,255,0 };
			}

			int healthBarWidth = 15;
			int healthBarHeight = 3;
			double healthBarX = (transform.position.x + (sprite.width * transform.scale.x)) - (sprite.isFixed ? 0 : camera.x);
			double healthBarY = (transform.position.y) - (sprite.isFixed ? 0 : camera.y);

			SDL_Rect healthBarRectangle = {
				static_cast<int>(healthBarX),
				static_cast<int>(healthBarY),
				static_cast<int>(healthBarWidth * health.healthPercentage / 100),
				static_cast<int>(healthBarHeight)
			};

			SDL_SetRenderDrawColor(renderer, healthBarColor.r, healthBarColor.g, healthBarColor.b, 255);
			SDL_RenderFillRect(renderer, &healthBarRectangle);

			std::string healthText = std::to_string(health.healthPercentage);

			SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont("arial-font5"), healthText.c_str(), healthBarColor);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int labelWidth = 0;
			int labelHeight = 0;
			SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

			SDL_Rect healthBarTextRect = {
				static_cast<int>(healthBarX),
				static_cast<int>(healthBarY) + 5,
				labelWidth,
				labelHeight
			};

			SDL_RenderCopy(renderer, texture, NULL, &healthBarTextRect);
			SDL_DestroyTexture(texture);

		}
	}
};

#endif // !RENDERHEALTHBARSYSTEM_H


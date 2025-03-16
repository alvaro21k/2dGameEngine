#include "LevelLoader.h"
#include "Game.h"
#include <fstream>
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/KeyboardMovementComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/SpriteComponent.h"
#include "sol/sol.hpp"

LevelLoader::LevelLoader() {
	Logger::Log("LevelLoader constructor called!");
}

LevelLoader::~LevelLoader() {
	Logger::Log("LevelLoader destructor called!");
}

void LevelLoader::LoadLevel(sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int levelNumber)
{
	sol::load_result script = lua.load_file(". / assets / scripts / Level" + std::to_string(levelNumber) + ".lua");

	//Checks syntax of script but doesnt execute
	if (!script.valid()) {
		sol::error err = script;
		std::string errorMessage = err.what();
		Logger::Err("Eror loading the lua script: " + errorMessage);
		return;
	}

	lua.script_file("./assets/scripts/Level" + std::to_string(levelNumber) + ".lua");

	sol::table level = lua["Level"];

	///Read the level assets
	sol::table assets = level["assets"];

	int i = 0;
	while (true) {
		sol::optional<sol::table> hasAsset = assets[i];
		if (hasAsset == sol::nullopt) {
			break;
		}
		sol::table asset = assets[i];
		std::string assetType = asset["type"];
		std::string assetId = asset["id"];
		if (assetType == "texture") {
			assetStore->AddTexture(renderer, assetId, asset["file"]);
			Logger::Log("A new texture asset was added to the asset store, id: " + assetId);
		}
		if (assetType == "font") {
			assetStore->AddFont(assetId, asset["file"], asset["font_size"]);
			Logger::Log("A new font asset was added to the asset store, id: " + assetId);
		}
		i++;
	}


	// Add textures to our asset store

	//assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");
	//assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");
	//assetStore->AddTexture(renderer, "tree-image", "./assets/images/tree.png");
	//assetStore->AddTexture(renderer, "radar-image", "./assets/images/radar.png");
	//assetStore->AddTexture(renderer, "chopper-image", "./assets/images/chopper-spritesheet.png");
	//assetStore->AddTexture(renderer, "tilemap-image", "./assets/tilemaps/jungle.png");
	//assetStore->AddTexture(renderer, "bullet-image", "./assets/images/bullet.png");
	//assetStore->AddFont("charriot-font20", "./assets/fonts/charriot.ttf", 20);
	//assetStore->AddFont("arial-font5", "./assets/fonts/arial.ttf", 5);
	//assetStore->AddFont("arial-font10", "./assets/fonts/arial.ttf", 10);

	//// Create the background map
	//int tileSize = 32;
	//double tileScale = 2;
	//int mapNumCols = 25;
	//int mapNumRows = 20;

	//std::fstream mapFile;
	//mapFile.open("./assets/tilemaps/jungle.map");

	//for (int y = 0; y < mapNumRows; y++) {
	//	for (int x = 0; x < mapNumCols; x++) {
	//		char ch;
	//		mapFile.get(ch);
	//		int srcRectY = std::atoi(&ch) * tileSize;
	//		mapFile.get(ch);
	//		int srcRectX = std::atoi(&ch) * tileSize;
	//		mapFile.ignore();

	//		Entity tile = registry->CreateEntity();
	//		tile.Group("tiles");
	//		tile.AddComponent<TransformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
	//		tile.AddComponent<SpriteComponent>("tilemap-image", tileSize, tileSize, 0, false, srcRectX, srcRectY);
	//	}
	//}
	//mapFile.close();
	//Game::mapWidth = mapNumCols * tileSize * tileScale;
	//Game::mapHeight = mapNumRows * tileSize * tileScale;

	//// Add entities to the level
	//Entity chopper = registry->CreateEntity();
	//chopper.Tag("player");
	//chopper.AddComponent<TransformComponent>(glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
	//chopper.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 2, true);
	//chopper.AddComponent<AnimationComponent>(2, 15, true);
	//chopper.AddComponent<BoxColliderComponent>(32, 32);
	//chopper.AddComponent<KeyboardMovementComponent>(glm::vec2(0, -80), glm::vec2(80, 0), glm::vec2(0, 80), glm::vec2(-80, 0));
	//chopper.AddComponent<CameraFollowComponent>();
	//chopper.AddComponent<HealthComponent>(100);
	//chopper.AddComponent<ProjectileEmitterComponent>(glm::vec2(100.0, 100.0), 0, 5000, 10, true);

	//Entity radar = registry->CreateEntity();
	//radar.AddComponent<TransformComponent>(glm::vec2(Game::windowWidth - 74, 10), glm::vec2(1.0, 1.0), 0.0);
	//radar.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 1, true);
	//radar.AddComponent<AnimationComponent>(8, 5, true);;

	//Entity tank = registry->CreateEntity();
	//tank.Group("enemies");
	//tank.AddComponent<TransformComponent>(glm::vec2(500.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
	//tank.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	//tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 2);
	//tank.AddComponent<BoxColliderComponent>(25, 18, glm::vec2(5, 7));
	//tank.AddComponent<HealthComponent>(100);

	//Entity truck = registry->CreateEntity();
	//truck.Group("enemies");
	//truck.AddComponent<TransformComponent>(glm::vec2(120.0, 500.0), glm::vec2(1.0, 1.0), 0.0);
	//truck.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	//truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 2);
	//truck.AddComponent<BoxColliderComponent>(25, 20, glm::vec2(5, 5));
	//truck.AddComponent<ProjectileEmitterComponent>(glm::vec2(0, -100.0), 2000, 5000, 10, false);
	//truck.AddComponent<HealthComponent>(100);

	//Entity treeA = registry->CreateEntity();
	//treeA.Group("obstacles");
	//treeA.AddComponent<TransformComponent>(glm::vec2(600.0, 495.0), glm::vec2(1.0, 1.0), 0.0);
	//treeA.AddComponent<SpriteComponent>("tree-image", 16, 32, 2);
	//treeA.AddComponent<BoxColliderComponent>(16, 32);

	//Entity treeB = registry->CreateEntity();
	//treeB.Group("obstacles");
	//treeB.AddComponent<TransformComponent>(glm::vec2(400.0, 495.0), glm::vec2(1.0, 1.0), 0.0);
	//treeB.AddComponent<SpriteComponent>("tree-image", 16, 32, 2);
	//treeB.AddComponent<BoxColliderComponent>(16, 32);

	//Entity label = registry->CreateEntity();
	//SDL_Color white = { 255,255,255 };
	//label.AddComponent<TextLabelComponent>(glm::vec2(Game::windowWidth / 2 - 40, 10), "CHOPPER 1.0", "charriot-font20", white, true);
}

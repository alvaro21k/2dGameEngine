#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"
#include <SDL.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class FlappyBird
{
private:
	bool isRunning;
	bool isDebug;
	int millisecsPreviousFrame = 0;
	int currentLevel;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect camera;

	std::unique_ptr<Registry> registry;
	std::unique_ptr<AssetStore> assetStore;
	std::unique_ptr<EventBus> eventBus;

public:
	FlappyBird();
	~FlappyBird();
	void Initialize();
	void Run();
	void Setup();
	void LoadLevel(int level);
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	static int windowWidth;
	static int windowHeigth;
	//static int mapWidth;
	//static int mapHeight;
};


#endif // !FLAPPYBIRD_H

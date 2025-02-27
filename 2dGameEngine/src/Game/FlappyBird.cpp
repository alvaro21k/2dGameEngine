#include "FlappyBird.h"
#include "../ECS/ECS.h"


int FlappyBird::windowHeigth;
int FlappyBird::windowWidth;


FlappyBird::FlappyBird()
{
	bool isRunning = true;
	bool isDebug = false;
	int currentLevel = 1;
	registry = std::make_unique<Registry>();
	assetStore = std::make_unique<AssetStore>();
	eventBus = std::make_unique<EventBus>();
}

FlappyBird::~FlappyBird()
{

}

void FlappyBird::Initialize()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Err("Error initializing SDL!");
		return;
	}

	if (TTF_Init() != 0) {
		Logger::Err("Error initializing TTF!");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = displayMode.w;
	windowHeigth = displayMode.h;
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeigth,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		Logger::Err("Error creating SDL window");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		Logger::Err("Error creating SDL renderer");
		return;
	}

}

void FlappyBird::Run()
{
	Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void FlappyBird::Setup()
{
	LoadLevel(currentLevel);
}

void FlappyBird::LoadLevel(int level)
{

}

void FlappyBird::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			} 

			if (sdlEvent.key.keysym.sym == SDLK_SPACE) {
				if (currentLevel == 1) {
					currentLevel = 2;
					LoadLevel(currentLevel);
				}
				if (currentLevel == 2) {
					//Maake the bird jump
				}
			}

		}
	}
}

void FlappyBird::Update()
{
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
	{
		SDL_Delay(timeToWait);
	}

	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

	millisecsPreviousFrame = SDL_GetTicks();


}

void FlappyBird::Render()
{

}

void FlappyBird::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

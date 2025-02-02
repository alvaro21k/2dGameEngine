#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"



class KeyPressedEvent : public Event {
public:
	SDL_Keycode symbol;
	SDL_Rect camera;
	KeyPressedEvent(SDL_Keycode symbol, SDL_Rect camera) : symbol(symbol), camera(camera) {

	}

};


#endif // !KEYPRESSEDEVENT_H


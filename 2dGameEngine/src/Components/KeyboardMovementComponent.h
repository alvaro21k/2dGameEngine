#ifndef KEYBOARDMOVEMENTCOMPONENT_H
#define KEYBOARDMOVEMENTCOMPONENT_H

#include <glm/glm.hpp>

struct KeyboardMovementComponent {
	glm::vec2 upVelocity;
	glm::vec2 rightVelocity;
	glm::vec2 downVelocity;
	glm::vec2 leftVelocity;

	KeyboardMovementComponent(glm::vec2 upVelocity = glm::vec2(0,0), glm::vec2 rightVelocity = glm::vec2(0, 0), glm::vec2 downVelocity = glm::vec2(0, 0), glm::vec2 leftVelocity = glm::vec2(0,0)) 
	{
		this->upVelocity	= upVelocity;
		this->rightVelocity = rightVelocity;
		this->downVelocity	= downVelocity;
		this->leftVelocity	= leftVelocity;
	}
};


#endif // !KEYBOARDMOVEMENTCOMPONENT_H

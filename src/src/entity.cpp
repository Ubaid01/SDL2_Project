#include "entity.h"

Entity::Entity() : rev(false), health(100), maxHealth(100), currentAnim(0), nAb(false), newAnim(0) , begin(0)
{
}

int Entity::createCycle(int r, int w, int h, int amount, int speed)
{
    cycle temp;
    temp.row = r - 1;
    temp.width = w;
    temp.height = h;
    temp.amount = amount;
    temp.speed = speed;
    temp.tick = 0;

    animations.push_back(temp);
    return (int) animations.size() - 1;
}

void Entity::setCurrentAnimation(int c)
{
    begin = 0;
    currentAnim = c;
}

void Entity::updateAnimation()
{
	setSource(animations[currentAnim].width * animations[currentAnim].tick, animations[currentAnim].row * animations[currentAnim].height, animations[currentAnim].width, animations[currentAnim].height);

	if (begin > animations[currentAnim].speed) {
		if (!rev )animations[currentAnim].tick++;
		if ( rev )animations[currentAnim].tick--;
		begin = 0;
	}
	begin++;
	if (animations[currentAnim].tick >= animations[currentAnim].amount)
		animations[currentAnim].tick = 0;

	if (animations[currentAnim].tick <= 0) {
		if (nAb) {
			currentAnim = newAnim;
			nAb = 0;
			rev = false;
		}
		else
			animations[currentAnim].tick = 0;
	}
}

void Entity::reverse(bool r)
{
    rev = r ;
}

void Entity::reverse(bool r, int nAnim)
{
    rev = r ;
    nAb = true;
    newAnim = nAnim;
}

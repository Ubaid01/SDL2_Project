#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "object.h"

class Entity : public Object {
public:
    Entity() ;
    void setHealth(int h) { health = h ; }
    int getHealth() const { return health ;}
    void setMaxHealth(int h) {maxHealth = h ;}
    int getMaxHealth() const { return maxHealth ; }
    int createCycle(int r, int w, int h, int amount, int speed);
    void setCurrentAnimation(int c) ;
    int getCurrentAnimation() const { return currentAnim ; }
    void updateAnimation();
    void reverse(bool r) ; 
    void reverse(bool r, int nA) ;
private:
    int health;
    int maxHealth;
    struct cycle {
        int row;
        int width;
        int height;
        int amount;
        int speed;
        int tick;
    };
    std::vector<cycle> animations;
    int currentAnim;
    int begin;
    bool rev;
    bool nAb;
    int newAnim;
};

#endif //ENTITY_H
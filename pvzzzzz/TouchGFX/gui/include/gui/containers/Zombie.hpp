#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <gui_generated/containers/ZombieBase.hpp>
#include <gui/common/GameConfig.hpp>


class Zombie : public ZombieBase {
public:
    enum State {
        STATE_WALKING,
        STATE_EATING,
        STATE_DEAD,
    };

    Zombie();
    virtual ~Zombie();
//    virtual void handleTickEvent();
    void takeDamage(int16_t damage);
    Rect getAttackArea() const;
    Rect getBodyArea() const;
    bool isAlive() const;
    ZombieType getType() const { return zombieType; }
		
    void setState(State newState);
//    void setType(ZombieType type);
    void setLane(uint8_t lane);
    void reset();
		int16_t getLane() const { return lane; }
    int16_t getPositionX() const { return getX(); }
    int16_t getHealth() const { return health; }
		bool isInHouse() const {
        // 设房子左边界在x=100位置
        return getX() <= -100; 
    }
    bool isInAttackRange(int16_t plantX, int16_t plantWidth) const;
		static void preloadBitmaps();
private:
    ZombieType zombieType;
    State currentState;
    int16_t health;
    int16_t speed;
    int16_t lane;
    int16_t tickCounter;
		float accumulatedDistance;
    AnimatedImage zombieAnimation;

//    void updateAnimation();
//    bool checkPlantCollision();
};

#endif // ZOMBIE_HPP

#ifndef PLANT_HPP
#define PLANT_HPP

#include <gui_generated/containers/PlantBase.hpp>
#include <gui/common/GameConfig.hpp>
#include <gui/containers/Bullet.hpp>
#include <gui/containers/Zombie.hpp>
class Plant : public PlantBase {
public:
    enum State {
        STATE_IDLE,
        STATE_ATTACKING,
        STATE_COOLDOWN,
        STATE_DEAD
    };
		Plant(Bullet* bulletPool = NULL, uint8_t poolSize = 0);
    virtual ~Plant();
    virtual void handleTickEvent();

    bool isAlive() const;
    Rect getHitbox() const;
    void reset();
    void forceAttack();
    void setGridRow(uint8_t row);
    void setAttackState(bool canAttack);
		uint8_t getGridRow() const { return gridRow; }
    PlantType getType() const  { return plantType; }
		
		void bindBulletPool(Bullet* pool, uint8_t size) 
		{
        bulletPool = pool;
        bulletPoolSize = size;
    }
		
protected:
		Zombie* currentZombies;
    uint8_t currentZombieCount;

		Bullet* bulletPool;  
    uint8_t bulletPoolSize;//
    PlantType plantType;
    State currentState;
    int16_t health;
    int16_t cooldownTimer;
    uint8_t gridRow; // 植物所在的行号
    uint8_t gridCol;
    int16_t tickCounter;
    bool isForcedAttack;
    AnimatedImage plantAnimation;

    void updateAnimation();
//    bool canAttack();
    void setState(State newState);
    void fireProjectile();
    bool hasEnemyInLane(const Zombie* zombies, uint8_t zombieCount) const;


};

#endif // PLANT_HPP

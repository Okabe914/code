#ifndef BULLET_HPP
#define BULLET_HPP

#include <gui_generated/containers/BulletBase.hpp>
#include <gui/common/GameConfig.hpp>
class Bullet : public BulletBase
{
public:
    enum AnimationState
    {
        MOVING,
        STOPPED,
        HIT_TARGET
    };

    Bullet();
    virtual ~Bullet();

    virtual void handleTickEvent();

    void setState(AnimationState state);
    AnimationState getState()
    {
        return currentAnimationState;
    }

    void reset();
		void launch(int startX, int startY);
		int16_t getDamage() const { return _damage; }
    Rect getAttackArea();
    Rect getBodyArea();
		void setLane(uint8_t lane) { _lane = lane; }
    uint8_t getLane() const { return _lane; }
		
		
		bool hasHit() const { return _hasHit; }
    void markAsHit() { _hasHit = true; }
   

protected:
    AnimationState currentAnimationState;
    int tickCounter;
		int16_t _damage ;
		uint8_t _lane;
    int groundY;
		bool _hasHit;
};

#endif // BULLET_HPP

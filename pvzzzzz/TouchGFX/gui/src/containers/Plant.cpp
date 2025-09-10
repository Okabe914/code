#include <gui/containers/Plant.hpp>
#include <BitmapDatabase.hpp>

extern bool gamecontinue;
//Plant::Plant() : 
Plant::Plant(Bullet* bulletPool, uint8_t poolSize) :
    bulletPool(bulletPool),
    bulletPoolSize(poolSize),
    plantType(PLANT_PEASHOOTER),
    currentState(STATE_IDLE),
    health(100),
    cooldownTimer(0),
    gridRow(0),
    gridCol(0),
    tickCounter(0)
{
    Application::getInstance()->registerTimerWidget(this);
    removeAll();
    add(plantAnimation);
}

Plant::~Plant()
{
}

void Plant::handleTickEvent() {
	if(gamecontinue)
	{
    if (!isAlive()) return;

    tickCounter++;

    switch(currentState) {
        case STATE_IDLE:
            if (tickCounter == 1) {
                plantAnimation.setBitmaps(BITMAP_PEASHOOTER_A_ID, BITMAP_PEASHOOTER_M_ID);
                plantAnimation.setUpdateTicksInterval(8);
                plantAnimation.startAnimation(false, true, true);
            }
            if (tickCounter % 3 == 0) 
						{ // 每N帧发射一次
                setState(STATE_ATTACKING);
            }
            break;

        case STATE_ATTACKING:
            if (tickCounter == 1) {
                fireProjectile(); // 发射子弹
                plantAnimation.setBitmaps(BITMAP_PEASHOOTER_A_ID, BITMAP_PEASHOOTER_M_ID);
                plantAnimation.startAnimation(false, true, true);
            }
            
            if (tickCounter >= ATTACK_DURATION) {
                setState(STATE_COOLDOWN);
            }
            break;

        case STATE_COOLDOWN:
            if (--cooldownTimer <= 0) {
                setState(STATE_IDLE);
            }
            break;
            
        case STATE_DEAD:
            if (tickCounter == 1) {            
                setVisible(false);
            }
            break;
    }
	}
}


void Plant::fireProjectile()
{
    if (!isAlive() || !bulletPool) return;

    for (uint8_t i = 0; i < bulletPoolSize; ++i) 
		{
        if (bulletPool[i].getState() == Bullet::STOPPED) 
				{
            const int16_t bulletX = getX() + PLANT_WIDTH - 20;
            const int16_t bulletY = getY() + (PLANT_HEIGHT - BULLET_HEIGHT) / 2 - 23 ;           
            bulletPool[i].launch(bulletX, bulletY);
						bulletPool[i].setLane(getGridRow());
            break;
        }
    }
//	播放攻击音效（可选）
//  if (playSoundCallback)
//	{
//      playSoundCallback(SOUND_PEA_SHOOT);
//  }
}

void Plant::setState(State newState) {
    if (currentState == newState) return;
    
    currentState = newState;
    tickCounter = 0; // 重置状态计时器
    cooldownTimer = (newState == STATE_COOLDOWN) ? PEASHOOTER_COOLDOWN : 0;
}

bool Plant::isAlive() const {
    return (currentState != STATE_DEAD) && (health > 0);
}


void Plant::setGridRow(uint8_t row) {
    this->gridRow = row;
}

Rect Plant::getHitbox() const {
    return touchgfx::Rect(
        getX() + PLANT_HITBOX_OFFSET_X,
        getY() + PLANT_HITBOX_OFFSET_Y,
        PLANT_HITBOX_WIDTH,
        PLANT_HITBOX_HEIGHT
    );
}

void Plant::reset() {
    health = 100;
    cooldownTimer = 0;
    tickCounter = 0;
    setState(STATE_IDLE);
    setVisible(true);
}
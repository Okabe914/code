#include <gui/containers/Zombie.hpp>
#include <BitmapDatabase.hpp>

extern bool gamecontinue;
Zombie::Zombie() :
    zombieType(ZOMBIE_REGULAR),
    currentState(STATE_WALKING),
    health(ZOMBIE_REGULAR_HEALTH),
    speed(ZOMBIE_WALK_SPEED),
    lane(0),
    tickCounter(0)
{
    Application::getInstance()->registerTimerWidget(this);
		removeAll();  // 先移除所有子控件
    add(zombieAnimation);   
    setState(STATE_WALKING);

}

Zombie::~Zombie()
{
}

//void Zombie::handleTickEvent() {
//	if(gamecontinue)
//	{
//    if (!isAlive()) return;
//    tickCounter++;
//		
//		if (currentState == STATE_WALKING && tickCounter % 8 == 0) {
//        // 根据游戏配置中的速度移动
//        moveRelative(-ZOMBIE_WALK_SPEED, 0);
//        // 移出草坪左侧边界后消失
//        if (getX() < LAWN_LEFT - ZOMBIE_WIDTH) {
//            setVisible(false);
//        }
//    }
//	}
//}
void Zombie::preloadBitmaps() {
    // 预加载僵尸行走动画所有帧 (A-Q)
    Bitmap::cache(BITMAP_ZOMBIE_WALK_A_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_B_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_C_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_D_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_E_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_F_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_G_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_H_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_I_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_J_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_K_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_L_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_M_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_N_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_O_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_P_ID);
    Bitmap::cache(BITMAP_ZOMBIE_WALK_Q_ID);
}
void Zombie::setState(State newState) {
    currentState = newState;
    tickCounter = 0;  // 重置计时器
	
    switch (newState) {
        case STATE_WALKING:
            zombieAnimation.setBitmaps(BITMAP_ZOMBIE_WALK_A_ID, BITMAP_ZOMBIE_WALK_Q_ID);
            zombieAnimation.setUpdateTicksInterval(6);
            zombieAnimation.startAnimation(false, false, true); // 循环播放
            break;
				
        case STATE_EATING:
//            zombieAnimation.setBitmaps(BITMAP_ZOMBIE_ATTACK_00_ID, BITMAP_ZOMBIE_ATTACK_09_ID);
//            zombieAnimation.setUpdateTicksInterval(2);
            zombieAnimation.startAnimation(false, true, true); // 单次播放
            break;

        case STATE_DEAD:
//            zombieAnimation.setBitmaps(BITMAP_ZOMBIE_DEAD_00_ID, BITMAP_ZOMBIE_DEAD_09_ID);
//            zombieAnimation.setUpdateTicksInterval(5);
            zombieAnimation.startAnimation(false, true, true);
//            setVisible(false);
            break;
    }
}


void Zombie::takeDamage(int16_t damage) 
{
    if (!isAlive()) return;

    health = (damage < health) ? health - damage : 0;
		
    if (health <= 0) {
        setState(STATE_DEAD);
        setVisible(false);
    }
}

Rect Zombie::getAttackArea() const {
    return Rect(
        getX() + 30,
        getY() + 20,
        ZOMBIE_WIDTH - 40,
        ZOMBIE_HEIGHT - 40
    );
}

Rect Zombie::getBodyArea() const {
    // 使用游戏配置中的僵尸尺寸参数
    const int16_t BODY_OFFSET_X = 90; // 水平前移90像素（避开手臂摆动区域）
    const int16_t BODY_WIDTH = ZOMBIE_WIDTH - 50; // 166-50=116（有效身体宽度）
    const int16_t BODY_OFFSET_Y = 25;  // 垂直偏移（避开头部装饰）
    const int16_t BODY_HEIGHT = ZOMBIE_HEIGHT - 45; // 144-45=99（有效身体高度）

    return Rect(
        getX() + BODY_OFFSET_X,  // X起点：30
        getY() + BODY_OFFSET_Y,   // Y起点：25
        BODY_WIDTH,               // 宽度：116
        BODY_HEIGHT               // 高度：99
    );
}

bool Zombie::isAlive() const {
    return currentState != STATE_DEAD && health > 0;
}

//void Zombie::setType(ZombieType type) {
//    zombieType = type;
//    switch (type) {
//        case ZOMBIE_REGULAR:
//            health = ZOMBIE_REGULAR_HEALTH;
//            speed = ZOMBIE_REGULAR_SPEED;
//            break;
//        // 其他僵尸类型...
//    }
//}

void Zombie::setLane(uint8_t lane) {
    this->lane = lane;
}


void Zombie::reset() {
    health = 100; // 重置生命值
    speed = ZOMBIE_WALK_SPEED; // 重置速度
    lane = 0; // 重置行号
    tickCounter = 0; // 重置计时器
		setVisible(false);
		setState(STATE_WALKING); // 设置为行走状态
}

//bool Zombie::checkPlantCollision() {
//    // 简化实现：检查本行是否有植物（实际项目需实现真正的碰撞检测）
//    Rect attackArea(
//        getX() + ZOMBIE_HITBOX_OFFSET,      // X起始位置
//        getY() + PLANT_HITBOX_OFFSET_Y,     // Y对齐植物碰撞框
//        ZOMBIE_ATTACK_RANGE,                // 攻击范围宽度
//        PLANT_HITBOX_HEIGHT                 // 碰撞高度
//    );

//    for (uint8_t col = 0; col < LAWN_COL_COUNT; col++) {
//        Plant* plant = GameManager::getInstance().getPlantAt(lane, col);

//        if (plant != NULL && plant->isAlive()) {
//            const Rect plantHitbox = plant->getHitbox();

//            if (attackArea.x < plantHitbox.x + plantHitbox.width &&
//                attackArea.x + attackArea.width > plantHitbox.x &&
//                attackArea.y < plantHitbox.y + plantHitbox.height &&
//                attackArea.y + attackArea.height > plantHitbox.y) 
//            {
//                // 碰撞成功，触发攻击
//                plant->takeDamage(ZOMBIE_DAMAGE);
//                return true;
//            }
//        }
//    }
//    return false;
//}

//void Zombie::updateAnimation() {
//    switch (currentState) {
//        case STATE_WALKING:
//            if (!zombieAnimation.isAnimatedImageRunning()) {
//                zombieAnimation.startAnimation(false, true, true);
//            }
//            zombieAnimation.setUpdateTicksInterval(8);
//            break;

//        case STATE_EATING:
//            zombieAnimation.setUpdateTicksInterval(4);
//            break;

//        case STATE_DEAD:
//            zombieAnimation.setUpdateTicksInterval(12);
//            break;

//        default:
//            break;
//    }
//}
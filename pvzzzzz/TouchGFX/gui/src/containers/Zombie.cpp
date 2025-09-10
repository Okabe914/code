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
		removeAll();  // ���Ƴ������ӿؼ�
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
//        // ������Ϸ�����е��ٶ��ƶ�
//        moveRelative(-ZOMBIE_WALK_SPEED, 0);
//        // �Ƴ���ƺ���߽����ʧ
//        if (getX() < LAWN_LEFT - ZOMBIE_WIDTH) {
//            setVisible(false);
//        }
//    }
//	}
//}
void Zombie::preloadBitmaps() {
    // Ԥ���ؽ�ʬ���߶�������֡ (A-Q)
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
    tickCounter = 0;  // ���ü�ʱ��
	
    switch (newState) {
        case STATE_WALKING:
            zombieAnimation.setBitmaps(BITMAP_ZOMBIE_WALK_A_ID, BITMAP_ZOMBIE_WALK_Q_ID);
            zombieAnimation.setUpdateTicksInterval(6);
            zombieAnimation.startAnimation(false, false, true); // ѭ������
            break;
				
        case STATE_EATING:
//            zombieAnimation.setBitmaps(BITMAP_ZOMBIE_ATTACK_00_ID, BITMAP_ZOMBIE_ATTACK_09_ID);
//            zombieAnimation.setUpdateTicksInterval(2);
            zombieAnimation.startAnimation(false, true, true); // ���β���
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
    // ʹ����Ϸ�����еĽ�ʬ�ߴ����
    const int16_t BODY_OFFSET_X = 90; // ˮƽǰ��90���أ��ܿ��ֱ۰ڶ�����
    const int16_t BODY_WIDTH = ZOMBIE_WIDTH - 50; // 166-50=116����Ч�����ȣ�
    const int16_t BODY_OFFSET_Y = 25;  // ��ֱƫ�ƣ��ܿ�ͷ��װ�Σ�
    const int16_t BODY_HEIGHT = ZOMBIE_HEIGHT - 45; // 144-45=99����Ч����߶ȣ�

    return Rect(
        getX() + BODY_OFFSET_X,  // X��㣺30
        getY() + BODY_OFFSET_Y,   // Y��㣺25
        BODY_WIDTH,               // ��ȣ�116
        BODY_HEIGHT               // �߶ȣ�99
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
//        // ������ʬ����...
//    }
//}

void Zombie::setLane(uint8_t lane) {
    this->lane = lane;
}


void Zombie::reset() {
    health = 100; // ��������ֵ
    speed = ZOMBIE_WALK_SPEED; // �����ٶ�
    lane = 0; // �����к�
    tickCounter = 0; // ���ü�ʱ��
		setVisible(false);
		setState(STATE_WALKING); // ����Ϊ����״̬
}

//bool Zombie::checkPlantCollision() {
//    // ��ʵ�֣���鱾���Ƿ���ֲ�ʵ����Ŀ��ʵ����������ײ��⣩
//    Rect attackArea(
//        getX() + ZOMBIE_HITBOX_OFFSET,      // X��ʼλ��
//        getY() + PLANT_HITBOX_OFFSET_Y,     // Y����ֲ����ײ��
//        ZOMBIE_ATTACK_RANGE,                // ������Χ���
//        PLANT_HITBOX_HEIGHT                 // ��ײ�߶�
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
//                // ��ײ�ɹ�����������
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
#include <gui/containers/Bullet.hpp>
#include <BitmapDatabase.hpp>

extern bool gamecontinue;
Bullet::Bullet() :
		currentAnimationState(STOPPED),
    tickCounter(0),
    _damage(PEA_DAMAGE),		
    groundY(0),
		_hasHit(false)
{
    Application::getInstance()->registerTimerWidget(this);

    setState(MOVING);
}

Bullet::~Bullet()
{
}

void Bullet::handleTickEvent()
{
	if(gamecontinue)
	{
    tickCounter++;

		if (currentAnimationState == MOVING) 
		{
        moveRelative(BULLET_SPEED,0);
        if (getX() > SCREEN_WIDTH) 
					reset();
    }
    // ���д����߼�
    if (currentAnimationState == HIT_TARGET)
    {
        const int FADE_DURATION = 15; // ������ʧ����ʱ��
        
        if (tickCounter == 1)
        {
            // ����ֹͣ�ƶ�����ʼ����
            image1.startFadeAnimation(0, FADE_DURATION, EasingEquations::linearEaseIn);
            setTouchable(false); // ���ý���
        } 
        else if (tickCounter >= FADE_DURATION)
        {
            reset();            // ������������ȫ���ز�����
        }
    }
	}
}

void Bullet::setState(AnimationState state)
{
    currentAnimationState = state;
    tickCounter = 0;
}

void Bullet::reset() {
		_hasHit = false;
    setVisible(false);
    setState(STOPPED);
    moveTo(-100, -100); // �Ƶ���Ļ��
    invalidate(); // ȷ���������

    image1.setAlpha(255); // ����͸����
}

void Bullet::launch(int startX, int startY)
{
    moveTo(startX, startY);
    setVisible(true);
    setState(MOVING);
}


Rect Bullet::getAttackArea() {

    return Rect(
        getX() + 12, // X��㣺12
        getY() + 8, // Y��㣺8
        BULLET_WIDTH / 2,             // ��ȣ�18
        BULLET_HEIGHT - 16             // �߶ȣ�18
    );
}
Rect Bullet::getBodyArea()
{
    return getRect();
}

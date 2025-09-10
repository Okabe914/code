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
    // 命中处理逻辑
    if (currentAnimationState == HIT_TARGET)
    {
        const int FADE_DURATION = 15; // 缩短消失动画时间
        
        if (tickCounter == 1)
        {
            // 立即停止移动并开始淡出
            image1.startFadeAnimation(0, FADE_DURATION, EasingEquations::linearEaseIn);
            setTouchable(false); // 禁用交互
        } 
        else if (tickCounter >= FADE_DURATION)
        {
            reset();            // 动画结束后完全隐藏并重置
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
    moveTo(-100, -100); // 移到屏幕外
    invalidate(); // 确保界面更新

    image1.setAlpha(255); // 重置透明度
}

void Bullet::launch(int startX, int startY)
{
    moveTo(startX, startY);
    setVisible(true);
    setState(MOVING);
}


Rect Bullet::getAttackArea() {

    return Rect(
        getX() + 12, // X起点：12
        getY() + 8, // Y起点：8
        BULLET_WIDTH / 2,             // 宽度：18
        BULLET_HEIGHT - 16             // 高度：18
    );
}
Rect Bullet::getBodyArea()
{
    return getRect();
}

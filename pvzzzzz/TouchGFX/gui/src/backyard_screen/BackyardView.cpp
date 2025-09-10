#include <gui/backyard_screen/BackyardView.hpp>
#include <gui/containers/Bullet.hpp>
#include <gui/containers/Plant.hpp>
#include <gui/containers/Zombie.hpp>
#include <gui/containers/Car.hpp>

bool gamecontinue = true;//��Ϸ�Ƿ�����ı�־λ��TRUEΪ��Ϸ������FALSEΪ��Ϸ��ͣ
bool gamewin = false;
uint8_t score = 0;
int winNum = 0;

BackyardView::BackyardView():
sliderValueChangedCallback(this, &BackyardView::sliderValueChangedCallbackHandler)
{

}	
void BackyardView::handleTickEvent()
{
    if(!gamecontinue || gamewin) return;
    
    BackyardViewBase::handleTickEvent();

    // ��ʬ�����߼�������ʱ����Ǹ��ʣ�
    if (++zombieSpawnTimer >= ZOMBIE_SPAWN_INTERVAL) 
    {
        zombieSpawnTimer = 0;
        
        if (!isSpawningWave) 
        {
            // ��ʼ��һ����ʬ
            isSpawningWave = true;
            zombieWaveCount = nextRand(1, 3); // ÿ��1-3����ʬ
        }
        
        if (zombieWaveCount > 0) 
        {
            spawnZombieAtLane(getRandomLane());
            zombieWaveCount--;
        }
        else 
        {
            isSpawningWave = false;
        }
    }

    // ��ʬ�ƶ����£���ɢ����ִ֡�У�
    static uint8_t updatePhase = 0;
    updatePhase = (updatePhase + 1) % 4; // 4�����
    
    for (int i = 0; i < MAX_ZOMBIES; i++) 
    {
        if (zombiePool[i].isVisible()) 
        {
            // ÿֻ֡���²��ֽ�ʬ
            if ((i % 4) == updatePhase) 
            {
                zombiePool[i].moveRelative(-ZOMBIE_WALK_SPEED, 0);
                
                if(zombiePool[i].isInHouse()) 
                {
                    GameOver();
                    return;
                }
                
                if (zombiePool[i].getX() < -ZOMBIE_WIDTH) 
                {
                    zombiePool[i].setVisible(false);
                }
            }
        }
    }

    bulletcollisionDetection();
}

void BackyardView::spawnZombieAtLane(uint8_t lane) 
{
    if (lane >= LAWN_ROW_COUNT || gamewin) return;

    // ���ҿ��ý�ʬ��λ���Ż����ҷ�ʽ��
    static uint8_t lastUsedIndex = 0;
    for (int i = 0; i < MAX_ZOMBIES; i++) 
    {
        uint8_t index = (lastUsedIndex + i) % MAX_ZOMBIES;
        if (!zombiePool[index].isVisible()) 
        {
            // Ԥ����λ��
            int16_t x = ZOMBIE_LAWN_ROW_X;
            int16_t y = ZOMBIE_LAWN_ROW_Y[lane];
            
            // �����������ԣ����ٺ������ã�
            zombiePool[index].reset();
						zombiePool[index].setXY(x, y);
						zombiePool[index].setLane(lane);
            zombiePool[index].setVisible(true);
            
            lastUsedIndex = index + 1;
            return;
        }
    }
}

uint8_t BackyardView::getRandomLane() 
{
    // ������״̬
    uint8_t laneWeights[LAWN_ROW_COUNT] = {10, 10, 10, 10, 10}; // ����Ȩ��
    
    // �������н�ʬ����Ȩ��
    for (int i = 0; i < MAX_ZOMBIES; i++) 
    {
        if (zombiePool[i].isVisible()) 
        {
            uint8_t lane = zombiePool[i].getLane();
            if (lane < LAWN_ROW_COUNT) 
            {
                laneWeights[lane] = laneWeights[lane] > 2 ? laneWeights[lane] - 2 : 1;
            }
        }
    }
    
    // ��Ȩ���ѡ��
    uint16_t totalWeight = 0;
    for (uint8_t i = 0; i < LAWN_ROW_COUNT; i++) 
    {
        totalWeight += laneWeights[i];
    }
    
    uint16_t random = nextRand(0, totalWeight - 1);
    uint16_t cumulative = 0;
    
    for (uint8_t i = 0; i < LAWN_ROW_COUNT; i++) 
    {
        cumulative += laneWeights[i];
        if (random < cumulative) 
        {
            return i;
        }
    }
    
    return 0; // Ĭ�Ϸ��ص�һ��
}

void BackyardView::setupScreen()
{
		if(!gamecontinue || gamewin) return;
		Zombie::preloadBitmaps();
    slider1.setNewValueCallback(sliderValueChangedCallback);
	
		for (int i = 0; i < MAX_ZOMBIES; i++) 
		{
        zombiePool[i].setVisible(true); 
        zombiePool[i].reset();
        add(zombiePool[i]);
				
    }   
    // ��ʼ���ӵ��ز��󶨵�ֲ��
    for (int i = 0; i < MAX_BULLETS; i++) {
        bulletPool[i].setVisible(true);
				bulletPool[i].reset();
        add(bulletPool[i]);		
    }
		car.setVisible(true);
    car.moveTo(47, PLANT_LAWN_ROW_Y[2]-10); // ��2��
		add(car);
		
		plant.bindBulletPool(bulletPool, MAX_BULLETS); // ���ӵ���
    plant.setVisible(true);
    plant.setGridRow(2); // Ĭ���м���
    plant.moveTo(53, PLANT_LAWN_ROW_Y[2]); // ��2��
    add(plant);
		slider2.setTouchable(false);
    // ���ӵ��ص�ֲ��
    plant.bindBulletPool(bulletPool, MAX_BULLETS);
		
}
void BackyardView::tearDownScreen()
{
    BackyardViewBase::tearDownScreen();
}

void BackyardView::bulletcollisionDetection() {
		if(gamewin) return; 
	
    static const int MAX_ITERATIONS = MAX_BULLETS * MAX_ZOMBIES;
    int iterations = 0;
    
    for (int i = 0; i < MAX_BULLETS && iterations++ < MAX_ITERATIONS; ++i) {
        Bullet& bullet = bulletPool[i];
        
        // ���������л�ǻ�Ծ���ӵ�
        if (bullet.hasHit() ) continue;
        
        Rect bulletRect = bullet.getAttackArea();
        if (bulletRect.isEmpty()) continue;
        
        for (int j = 0; j < MAX_ZOMBIES && iterations++ < MAX_ITERATIONS; ++j) {
            Zombie& zombie = zombiePool[j];
            if (!zombie.isVisible() || !zombie.isAlive()) continue;
            
            if (bullet.getLane() != zombie.getLane()) continue;
            
            Rect zombieRect = zombie.getBodyArea();
            if (zombieRect.isEmpty()) continue;
            
            if (bulletRect.intersect(zombieRect)) {
                zombie.takeDamage(bullet.getDamage());
                bullet.markAsHit(); // ���Ϊ������
                bullet.setState(Bullet::HIT_TARGET);
                
                if (zombie.getHealth() <= 0) 
								{
                  zombie.setState(Zombie::STATE_DEAD);
									score+=10;
									slider2.setValue(100-score);
									
									if(score>=100&& !gamewin)
									{
										GameWin();
										return;
									}
                }
                break;
            }
        }
        
        if (bullet.getX() > SCREEN_WIDTH || bullet.getX() < -BULLET_WIDTH) {
            bullet.reset();
        }
    }
}

void BackyardView::sliderValueChangedCallbackHandler(const Slider& src, int value)
{
    if (&src == &slider1)
    {
			// ����Ŀ����(0-4)������ֵ0����4�У�100����0��
			uint8_t targetRow = (100 - value) * LAWN_ROW_COUNT / 100;
			targetRow = targetRow >= LAWN_ROW_COUNT ? LAWN_ROW_COUNT - 1 : targetRow;

			int16_t newY = PLANT_LAWN_ROW_Y[targetRow];

			plant.setGridRow(targetRow);
			plant.moveTo(plant.getX(), newY);
			car.moveTo(car.getX(),newY-10);
			
		}
}
void BackyardView::GameOver() 
{
    // ��ͣ��Ϸ
    gamecontinue = false;
    
    // ��ʾ��Ϸ��������
    modalWindowgameover.setVisible(true);
    modalWindowgameover.invalidate();

}
void BackyardView::funcChange()
{
	modalWindowPause.setVisible(true);
	modalWindowPause.invalidate();	
	gamecontinue = false;
}

void BackyardView::funcBack()
{
	modalWindowPause.setVisible(false);
	modalWindowPause.invalidate();
	gamecontinue = true;
}

void BackyardView::funcRestart()
{
    // ��������״̬
    gamecontinue = true;
    gamewin = false;
    score = 0;
    winButton.setTouchable(false);
    // ����UIԪ��
    slider2.setValue(100);
    winButton.setVisible(false);
    winButton.invalidate();
		
    modalWindowgameover.setVisible(false);
    modalWindowgameover.invalidate();
    
    // ������Ϸ����
    for(int i = 0; i < MAX_ZOMBIES; i++) {
        zombiePool[i].reset();
        zombiePool[i].setVisible(true);
    }
    
    for(int i = 0; i < MAX_BULLETS; i++) {
        bulletPool[i].reset();
        bulletPool[i].setVisible(true);
    }
    
    plant.setVisible(true);
    plant.invalidate();
    car.setVisible(true);
    car.invalidate();
}
void BackyardView::GameWin()
{
    if(gamewin) return; // ��ֹ�ظ�����
    
    gamecontinue = false;
    gamewin = true;
		winNum += 1 ;
    // ����������Ϸ����
    for(int i = 0; i < MAX_ZOMBIES; i++) {
        zombiePool[i].setVisible(false);
        zombiePool[i].invalidate();
    }

    for(int i = 0; i < MAX_BULLETS; i++) {
        bulletPool[i].setVisible(false);
        bulletPool[i].invalidate();
    }

    // ��ʾ����
    winButton.setVisible(true);
    winButton.invalidate();
}



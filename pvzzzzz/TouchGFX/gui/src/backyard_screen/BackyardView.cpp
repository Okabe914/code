#include <gui/backyard_screen/BackyardView.hpp>
#include <gui/containers/Bullet.hpp>
#include <gui/containers/Plant.hpp>
#include <gui/containers/Zombie.hpp>
#include <gui/containers/Car.hpp>

bool gamecontinue = true;//游戏是否继续的标志位，TRUE为游戏继续，FALSE为游戏暂停
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

    // 僵尸生成逻辑（基于时间而非概率）
    if (++zombieSpawnTimer >= ZOMBIE_SPAWN_INTERVAL) 
    {
        zombieSpawnTimer = 0;
        
        if (!isSpawningWave) 
        {
            // 开始新一波僵尸
            isSpawningWave = true;
            zombieWaveCount = nextRand(1, 3); // 每波1-3个僵尸
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

    // 僵尸移动更新（分散到多帧执行）
    static uint8_t updatePhase = 0;
    updatePhase = (updatePhase + 1) % 4; // 4相更新
    
    for (int i = 0; i < MAX_ZOMBIES; i++) 
    {
        if (zombiePool[i].isVisible()) 
        {
            // 每帧只更新部分僵尸
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

    // 查找可用僵尸槽位（优化查找方式）
    static uint8_t lastUsedIndex = 0;
    for (int i = 0; i < MAX_ZOMBIES; i++) 
    {
        uint8_t index = (lastUsedIndex + i) % MAX_ZOMBIES;
        if (!zombiePool[index].isVisible()) 
        {
            // 预计算位置
            int16_t x = ZOMBIE_LAWN_ROW_X;
            int16_t y = ZOMBIE_LAWN_ROW_Y[lane];
            
            // 批量设置属性（减少函数调用）
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
    // 缓存行状态
    uint8_t laneWeights[LAWN_ROW_COUNT] = {10, 10, 10, 10, 10}; // 基础权重
    
    // 根据现有僵尸调整权重
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
    
    // 加权随机选择
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
    
    return 0; // 默认返回第一行
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
    // 初始化子弹池并绑定到植物
    for (int i = 0; i < MAX_BULLETS; i++) {
        bulletPool[i].setVisible(true);
				bulletPool[i].reset();
        add(bulletPool[i]);		
    }
		car.setVisible(true);
    car.moveTo(47, PLANT_LAWN_ROW_Y[2]-10); // 第2行
		add(car);
		
		plant.bindBulletPool(bulletPool, MAX_BULLETS); // 绑定子弹池
    plant.setVisible(true);
    plant.setGridRow(2); // 默认中间行
    plant.moveTo(53, PLANT_LAWN_ROW_Y[2]); // 第2行
    add(plant);
		slider2.setTouchable(false);
    // 绑定子弹池到植物
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
        
        // 跳过已命中或非活跃的子弹
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
                bullet.markAsHit(); // 标记为已命中
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
			// 计算目标行(0-4)，滑块值0→第4行，100→第0行
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
    // 暂停游戏
    gamecontinue = false;
    
    // 显示游戏结束弹窗
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
    // 重置所有状态
    gamecontinue = true;
    gamewin = false;
    score = 0;
    winButton.setTouchable(false);
    // 重置UI元素
    slider2.setValue(100);
    winButton.setVisible(false);
    winButton.invalidate();
		
    modalWindowgameover.setVisible(false);
    modalWindowgameover.invalidate();
    
    // 重置游戏对象
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
    if(gamewin) return; // 防止重复调用
    
    gamecontinue = false;
    gamewin = true;
		winNum += 1 ;
    // 立即隐藏游戏对象
    for(int i = 0; i < MAX_ZOMBIES; i++) {
        zombiePool[i].setVisible(false);
        zombiePool[i].invalidate();
    }

    for(int i = 0; i < MAX_BULLETS; i++) {
        bulletPool[i].setVisible(false);
        bulletPool[i].invalidate();
    }

    // 显示奖杯
    winButton.setVisible(true);
    winButton.invalidate();
}



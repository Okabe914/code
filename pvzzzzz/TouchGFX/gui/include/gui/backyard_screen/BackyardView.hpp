#ifndef BACKYARDVIEW_HPP
#define BACKYARDVIEW_HPP

#include <gui_generated/backyard_screen/BackyardViewBase.hpp>
#include <gui/backyard_screen/BackyardPresenter.hpp>
#include <gui/common/GameConfig.hpp>
#include <stdlib.h>
#include <cstdlib>  // 为 rand() 函数
#include <ctime>  
#include <gui/containers/Car.hpp>


class BackyardView : public BackyardViewBase {
public:
    BackyardView();
    virtual ~BackyardView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
		virtual void handleTickEvent();	
			
		virtual void funcChange();
		virtual void funcBack();	
		virtual void GameOver();
		virtual void funcRestart();
		virtual void GameWin();

			
		void bulletcollisionDetection();
		void generateZombieWave();
		void spawnZombieAtLane(uint8_t lane);
		uint8_t getRandomLane();
		
    static int nextRand(int min, int max) {
        return (rand() % (max - min + 1)) + min;
    }
		
		
  
protected:
	 
		Zombie zombiePool[MAX_ZOMBIES];  // 实际存储

    Bullet bulletPool[MAX_BULLETS];  // 实际存储
    
//    // 指针数组（指向对象池中的元素）
    Zombie* activeZombies[MAX_ZOMBIES];
    
    Bullet* activeBullets[MAX_BULLETS];
		Plant plant;
		Car car;
		uint8_t zombieCount ;
		uint16_t zombieSpawnTimer;
    uint8_t zombieWaveCount;
    bool isSpawningWave;
		Callback<BackyardView, const Slider&, int> sliderValueChangedCallback;
    void sliderValueChangedCallbackHandler(const Slider& src, int value);
};

#endif 

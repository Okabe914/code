#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* 屏幕尺寸配置 */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

/* 游戏区域(草坪)配置 */
#define LAWN_LEFT     53    /* 草坪左侧起始坐标 */
#define LAWN_TOP      68    /* 草坪顶部起始坐标 */ 
#define LAWN_RIGHT    693   /* 草坪右侧结束坐标 */
#define LAWN_BOTTOM   388   /* 草坪底部结束坐标 */
#define LAWN_WIDTH    (LAWN_RIGHT - LAWN_LEFT)  /* 草坪宽度 640 */
#define LAWN_HEIGHT   (LAWN_BOTTOM - LAWN_TOP)  /* 草坪高度 320 */

const static uint16_t ZOMBIE_LAWN_ROW_Y[5] = {
    0,    // 第1行 (实测y=0)
    81,   // 第2行 (实测y=81)
    168,  // 第3行 (实测y=168)
    227,  // 第4行 (实测y=227) 
    315   // 第5行 (实测y=315)
};
const static uint16_t ZOMBIE_LAWN_ROW_X = 750 ;
/* 草坪网格配置(5行9列) */
#define LAWN_ROW_COUNT 5     /* 行数 */
#define LAWN_COL_COUNT 9     /* 列数 */
#define CELL_WIDTH    (LAWN_WIDTH / LAWN_COL_COUNT)   /* 每格宽度 ≈71 */
#define CELL_HEIGHT   (LAWN_HEIGHT / LAWN_ROW_COUNT)  /* 每格高度 64 */

/* 游戏元素尺寸 */
#define PLANT_WIDTH   81     /* 植物显示宽度 */
#define PLANT_HEIGHT  81     /* 植物显示高度 */
#define ZOMBIE_WIDTH  166     
#define ZOMBIE_HEIGHT 144
#define SUN_SIZE      79     /* 阳光显示尺寸 */
#define BULLET_WIDTH  37
#define BULLET_HEIGHT 34
/* 统一植物碰撞框配置 */
#define PLANT_HITBOX_OFFSET_X  15  // 水平内缩像素
#define PLANT_HITBOX_OFFSET_Y  20  // 垂直内缩像素
#define PLANT_HITBOX_WIDTH     (PLANT_WIDTH - 2*PLANT_HITBOX_OFFSET_X)  // 51
#define PLANT_HITBOX_HEIGHT    (PLANT_HEIGHT - 2*PLANT_HITBOX_OFFSET_Y) // 41

const static uint16_t LAWN_ROW_Y[5] = {
    80,   // 第0行
    168,  // 第1行
    227,  // 第2行 
    315,  // 第3行
    336   // 第4行
};
const static uint16_t PLANT_LAWN_ROW_Y[5] = {68, 145, 230, 305, 387};
/* 植物类型枚举 */
typedef enum {
    PLANT_SUNFLOWER = 0,
    PLANT_PEASHOOTER,
    PLANT_WALLNUT,
    PLANT_CHERRYBOMB,
    PLANT_TYPE_COUNT
} PlantType;

/* 僵尸类型枚举 */
typedef enum {
    ZOMBIE_REGULAR = 0,
//    ZOMBIE_CONEHEAD,
//    ZOMBIE_BUCKETHEAD,
//    ZOMBIE_POLEVAULTING,
//    ZOMBIE_TYPE_COUNT
} ZombieType;

/* 子弹类型枚举 */
typedef enum {
    BULLET_PEA = 0,
    BULLET_FROZENPEA,
    BULLET_FIREPEA,
    BULLET_TYPE_COUNT
} BulletType;

/* 游戏状态枚举 */
typedef enum {
    GAME_READY = 0,
    GAME_PLAYING,
    GAME_PAUSED,
    GAME_OVER,		
    GAME_VICTORY
} GameState;

/* 游戏参数配置 */
#define SUNFLOWER_COST    50
#define PEASHOOTER_COST   100
#define WALLNUT_COST      50
#define CHERRYBOMB_COST   150

#define SUN_VALUE         25     /* 每个阳光的价值 */
#define SUN_FALL_SPEED    2      /* 阳光下落速度 */
#define SUN_LIFETIME      300    /* 阳光存在时间(帧数) */

#define ATTACK_DURATION      20    // 攻击动画持续帧数
#define ATTACK_INTERVAL      50   // 攻击间隔帧数
#define EAT_INTERVAL        20    // 僵尸啃食间隔帧数
#define PLANT_HEALTH        100   // 植物基础生命值
#define ZOMBIE_WALK_SPEED   1     // 僵尸基础移动速度
#define BULLET_SPEED        3     // 子弹基础速度
#define ZOMBIE_SPAWN_INTERVAL 500 /* 僵尸生成间隔(帧数) */
#define ZOMBIE_WAVE_INTERVAL 5000

#define PEA_DAMAGE        20
#define FROZENPEA_DAMAGE  20
#define FIREPEA_DAMAGE    40


/* 僵尸类型特定配置 */
#define ZOMBIE_REGULAR_HEALTH     100
#define ZOMBIE_REGULAR_SPEED      1
#define ZOMBIE_CONEHEAD_HEALTH    250
#define ZOMBIE_CONEHEAD_SPEED     1
#define ZOMBIE_BUCKETHEAD_HEALTH  400 
#define ZOMBIE_BUCKETHEAD_SPEED   0.8f
#define ZOMBIE_POLEVAULTING_HEALTH 150
#define ZOMBIE_POLEVAULTING_SPEED 2.0f

/* 植物类型特定配置 */
#define SUNFLOWER_HEALTH     100
#define PEASHOOTER_HEALTH    100
#define WALLNUT_HEALTH       400
#define CHERRYBOMB_HEALTH    100

/* 碰撞检测参数 */
#define PLANT_HITBOX_OFFSET  10   // 植物碰撞框内缩像素

// 僵尸碰撞参数
#define ZOMBIE_HITBOX_OFFSET   15   // 僵尸碰撞框前伸像素
#define ZOMBIE_ATTACK_RANGE    20   // 攻击范围宽度 
#define ZOMBIE_DAMAGE          10   // 每次攻击伤害值

#define SUNFLOWER_COOLDOWN 300
#define PEASHOOTER_COOLDOWN 100

#define MAX_BULLETS      	3    // 最大子弹数量
#define MAX_ZOMBIES       5   // 最大同时存在的僵尸数  
#define MAX_ZOMBIES_PER_ROW  3 // 每行最多存储的僵尸数量
#define MAX_LANES   5

#define MAX_PLANTS       1   // 最大植物数量

#define ZOMBIE_SPAWN_RATE 3
// 阳光系统参数
#define SUN_DROP_DISTANCE     150   // 下落总距离
#define SUN_FALL_SPEED        2     // 下落速度(像素/帧)
#define SUN_ANIMATION_SPEED   4     // 动画更新间隔(帧)


#ifdef __cplusplus
}
#endif

#endif /* __GAME_CONFIG_H */

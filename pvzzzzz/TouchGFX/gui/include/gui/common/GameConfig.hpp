#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* ��Ļ�ߴ����� */
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 480

/* ��Ϸ����(��ƺ)���� */
#define LAWN_LEFT     53    /* ��ƺ�����ʼ���� */
#define LAWN_TOP      68    /* ��ƺ������ʼ���� */ 
#define LAWN_RIGHT    693   /* ��ƺ�Ҳ�������� */
#define LAWN_BOTTOM   388   /* ��ƺ�ײ��������� */
#define LAWN_WIDTH    (LAWN_RIGHT - LAWN_LEFT)  /* ��ƺ��� 640 */
#define LAWN_HEIGHT   (LAWN_BOTTOM - LAWN_TOP)  /* ��ƺ�߶� 320 */

const static uint16_t ZOMBIE_LAWN_ROW_Y[5] = {
    0,    // ��1�� (ʵ��y=0)
    81,   // ��2�� (ʵ��y=81)
    168,  // ��3�� (ʵ��y=168)
    227,  // ��4�� (ʵ��y=227) 
    315   // ��5�� (ʵ��y=315)
};
const static uint16_t ZOMBIE_LAWN_ROW_X = 750 ;
/* ��ƺ��������(5��9��) */
#define LAWN_ROW_COUNT 5     /* ���� */
#define LAWN_COL_COUNT 9     /* ���� */
#define CELL_WIDTH    (LAWN_WIDTH / LAWN_COL_COUNT)   /* ÿ���� ��71 */
#define CELL_HEIGHT   (LAWN_HEIGHT / LAWN_ROW_COUNT)  /* ÿ��߶� 64 */

/* ��ϷԪ�سߴ� */
#define PLANT_WIDTH   81     /* ֲ����ʾ��� */
#define PLANT_HEIGHT  81     /* ֲ����ʾ�߶� */
#define ZOMBIE_WIDTH  166     
#define ZOMBIE_HEIGHT 144
#define SUN_SIZE      79     /* ������ʾ�ߴ� */
#define BULLET_WIDTH  37
#define BULLET_HEIGHT 34
/* ͳһֲ����ײ������ */
#define PLANT_HITBOX_OFFSET_X  15  // ˮƽ��������
#define PLANT_HITBOX_OFFSET_Y  20  // ��ֱ��������
#define PLANT_HITBOX_WIDTH     (PLANT_WIDTH - 2*PLANT_HITBOX_OFFSET_X)  // 51
#define PLANT_HITBOX_HEIGHT    (PLANT_HEIGHT - 2*PLANT_HITBOX_OFFSET_Y) // 41

const static uint16_t LAWN_ROW_Y[5] = {
    80,   // ��0��
    168,  // ��1��
    227,  // ��2�� 
    315,  // ��3��
    336   // ��4��
};
const static uint16_t PLANT_LAWN_ROW_Y[5] = {68, 145, 230, 305, 387};
/* ֲ������ö�� */
typedef enum {
    PLANT_SUNFLOWER = 0,
    PLANT_PEASHOOTER,
    PLANT_WALLNUT,
    PLANT_CHERRYBOMB,
    PLANT_TYPE_COUNT
} PlantType;

/* ��ʬ����ö�� */
typedef enum {
    ZOMBIE_REGULAR = 0,
//    ZOMBIE_CONEHEAD,
//    ZOMBIE_BUCKETHEAD,
//    ZOMBIE_POLEVAULTING,
//    ZOMBIE_TYPE_COUNT
} ZombieType;

/* �ӵ�����ö�� */
typedef enum {
    BULLET_PEA = 0,
    BULLET_FROZENPEA,
    BULLET_FIREPEA,
    BULLET_TYPE_COUNT
} BulletType;

/* ��Ϸ״̬ö�� */
typedef enum {
    GAME_READY = 0,
    GAME_PLAYING,
    GAME_PAUSED,
    GAME_OVER,		
    GAME_VICTORY
} GameState;

/* ��Ϸ�������� */
#define SUNFLOWER_COST    50
#define PEASHOOTER_COST   100
#define WALLNUT_COST      50
#define CHERRYBOMB_COST   150

#define SUN_VALUE         25     /* ÿ������ļ�ֵ */
#define SUN_FALL_SPEED    2      /* ���������ٶ� */
#define SUN_LIFETIME      300    /* �������ʱ��(֡��) */

#define ATTACK_DURATION      20    // ������������֡��
#define ATTACK_INTERVAL      50   // �������֡��
#define EAT_INTERVAL        20    // ��ʬ��ʳ���֡��
#define PLANT_HEALTH        100   // ֲ���������ֵ
#define ZOMBIE_WALK_SPEED   1     // ��ʬ�����ƶ��ٶ�
#define BULLET_SPEED        3     // �ӵ������ٶ�
#define ZOMBIE_SPAWN_INTERVAL 500 /* ��ʬ���ɼ��(֡��) */
#define ZOMBIE_WAVE_INTERVAL 5000

#define PEA_DAMAGE        20
#define FROZENPEA_DAMAGE  20
#define FIREPEA_DAMAGE    40


/* ��ʬ�����ض����� */
#define ZOMBIE_REGULAR_HEALTH     100
#define ZOMBIE_REGULAR_SPEED      1
#define ZOMBIE_CONEHEAD_HEALTH    250
#define ZOMBIE_CONEHEAD_SPEED     1
#define ZOMBIE_BUCKETHEAD_HEALTH  400 
#define ZOMBIE_BUCKETHEAD_SPEED   0.8f
#define ZOMBIE_POLEVAULTING_HEALTH 150
#define ZOMBIE_POLEVAULTING_SPEED 2.0f

/* ֲ�������ض����� */
#define SUNFLOWER_HEALTH     100
#define PEASHOOTER_HEALTH    100
#define WALLNUT_HEALTH       400
#define CHERRYBOMB_HEALTH    100

/* ��ײ������ */
#define PLANT_HITBOX_OFFSET  10   // ֲ����ײ����������

// ��ʬ��ײ����
#define ZOMBIE_HITBOX_OFFSET   15   // ��ʬ��ײ��ǰ������
#define ZOMBIE_ATTACK_RANGE    20   // ������Χ��� 
#define ZOMBIE_DAMAGE          10   // ÿ�ι����˺�ֵ

#define SUNFLOWER_COOLDOWN 300
#define PEASHOOTER_COOLDOWN 100

#define MAX_BULLETS      	3    // ����ӵ�����
#define MAX_ZOMBIES       5   // ���ͬʱ���ڵĽ�ʬ��  
#define MAX_ZOMBIES_PER_ROW  3 // ÿ�����洢�Ľ�ʬ����
#define MAX_LANES   5

#define MAX_PLANTS       1   // ���ֲ������

#define ZOMBIE_SPAWN_RATE 3
// ����ϵͳ����
#define SUN_DROP_DISTANCE     150   // �����ܾ���
#define SUN_FALL_SPEED        2     // �����ٶ�(����/֡)
#define SUN_ANIMATION_SPEED   4     // �������¼��(֡)


#ifdef __cplusplus
}
#endif

#endif /* __GAME_CONFIG_H */

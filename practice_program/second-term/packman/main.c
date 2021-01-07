#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <poll.h>

//マップチップの横幅
#define MAP_CHIP_WIDTH 21
//マップチップのの縦幅
#define MAP_CHIP_HEIGHT 21
#define ENEMY_NUMBER 6
//表示するアイコン
#define ITEM "\x1b[44m\x1b[49m"
#define PLAYER "\x1b[44m  \x1b[49m"
#define ENEMY "\x1b[41m  \x1b[49m"
#define WALL "\x1b[49m  "
#define INVISIBLE_WALL "\x1b[47m  \x1b[49m"
#define ROAD "\x1b[47m  \x1b[49m"

struct pollfd pollfd = {STDIN_FILENO, POLLIN | POLLPRI};

int map_chip_data[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH] =
    {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 3, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 0, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 0, 2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};
// MapChip構造体
struct MapChip
{
    char *icon;
    int id;
    unsigned int position_x;
    unsigned int position_y;
};
struct MapChip map_chip[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH];
// アイコンの動く方向を示す
enum MoveCommand
{
    Up,
    Down,
    Right,
    Left
};
/**
 * @struct Entity
 * @brief プレイヤーや敵などの動く実体
 */
struct Entity
{
    char *icon;
    unsigned int position_x;
    unsigned int position_y;
    unsigned int velocity_x;
    unsigned int velocity_y;
    enum MoveCommand command;
};
/** @fn
 * @brief mapchipの初期化
 */
void initMapChip()
{
    for (unsigned int i = 0; i < MAP_CHIP_HEIGHT; i++)
    {
        for (unsigned int j = 0; j < MAP_CHIP_WIDTH; j++)
        {
            map_chip[i][j].id = map_chip_data[i][j];
            if (map_chip[i][j].id == 0)
            {
                map_chip[i][j].icon = ROAD;
            }
            if (map_chip[i][j].id == 2)
            {
                map_chip[i][j].icon = WALL;
            }
            if (map_chip[i][j].id == 3)
            {
                map_chip[i][j].icon = INVISIBLE_WALL;
            }
            map_chip[i][j].position_x = j;
            map_chip[i][j].position_y = i;
        }
    }
}
/** @fn 
 * @brief 敵の初期化
 * @param enemies 敵のポインタ配列
 * @param number 作る敵の数
 */
void initEnemy(struct Entity *enemies[], int number)
{
    for (int i = 0; i < number; i++)
    {
        struct Entity *enemy = (struct Entity *)malloc(sizeof(struct Entity));
        enemies[i] = enemy;
        enemies[i]->icon = ENEMY;
        enemies[i]->position_x = MAP_CHIP_WIDTH / 2;
        enemies[i]->position_y = MAP_CHIP_HEIGHT / 2;
        enemies[i]->velocity_x = 0;
        enemies[i]->velocity_y = 0;
    }
    enemies[number] = (struct Entity *)NULL;
}
/** @fn　
 * @brief エンティティの動く方向をセットする
 * @param entity エンティティ構造体
 * @param mvcommand コマンド文字列
 */
void setDirection(struct Entity *entity, char mvcommand)
{
    // char mvcommand;
    // scanf("%c", &mvcommand);
    if (mvcommand == 'f')
    {
        entity->velocity_x = 1;
        entity->velocity_y = 0;
        entity->command = Right;
    }
    if (mvcommand == 'e')
    {
        entity->velocity_x = 0;
        entity->velocity_y = -1;
        entity->command = Up;
    }
    if (mvcommand == 'd')
    {
        entity->velocity_x = 0;
        entity->velocity_y = 1;
        entity->command = Down;
    }
    if (mvcommand == 's')
    {
        entity->velocity_x = -1;
        entity->velocity_y = 0;
        entity->command = Left;
    }
}
/** @fn
 * @brief ランダムなコマンド文字生成
 * @return コマンド文字
 */
char genRndCmd()
{
    char mvcommand;
    int rnd = (float)rand() / (RAND_MAX + 1.0) * 4.0; /* generate random values */
    if (rnd == 1)
        mvcommand = 'f';
    if (rnd == 2)
        mvcommand = 'e';
    if (rnd == 3)
        mvcommand = 'd';
    if (rnd == 4)
        mvcommand = 's';
    return mvcommand;
}
/** @fn
 * @param entity エンティティ構造体
 * @param chip MapChip構造体
 */
int entityMoveCheck(struct Entity *entity, struct MapChip chip[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH])
{
    // printf("chip.id %d", chip.id);
    // printf("chip[entity->position_y][entity->position_x].position_y %d\n", chip[entity->position_y][entity->position_x].position_y);
    // printf("chip[entity->position_y][entity->position_x].position_x %d\n", chip[entity->position_y][entity->position_x].position_x);
    // printf("entity->position_y %d\n", entity->position_y);
    // printf("dentity->position_x %d\n", entity->position_x);
    // printf("chip.icon  %s\n", chip[entity->position_y][entity->position_x].icon);

    int cond1 = entity->position_x == chip[entity->position_y][entity->position_x].position_x;
    int cond2 = entity->position_y == chip[entity->position_y][entity->position_x].position_y;
    // エンティティの座標の位置は歩行可能なエリアであるならばreturn 1
    // そうでないなら，entityの座標を一個戻す
    if (cond1 && cond2 && (chip[entity->position_y][entity->position_x].id != 0))
    {
        entity->position_x -= entity->velocity_x;
        entity->position_y -= entity->velocity_y;
        return 0;
    }
    return 1;
}
/** @fn
 * @brief Entityを指定されたコマンドに従った方向に動かす
 * @param entity エンティティ構造体ポインタ
 * @param chip MapChip構造体
 * @param　mvcommand コマンドもじ
 */
int entityMove(struct Entity *entity, struct MapChip chip[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH], char mvcommand)
{
    char directions[4] = {'f', 'e', 'd', 's'};
    setDirection(entity, mvcommand);
    // entity->position_x + entity->velocity;
    entity->position_x += entity->velocity_x;
    entity->position_y += entity->velocity_y;
    if (entity->position_x > MAP_CHIP_WIDTH - 2)
        entity->position_x = MAP_CHIP_WIDTH - 2;
    if (entity->position_x == 0)
        entity->position_x = 1;
    if (entity->position_y > MAP_CHIP_HEIGHT - 2)
        entity->position_y = MAP_CHIP_HEIGHT - 2;
    if (entity->position_y == 0)
        entity->position_y = 1;
    return entityMoveCheck(entity, map_chip);
}
/** @fn
 * 与えられたentityの構造体の座標が一致しているならば1そうでなければ0を返す
 *  @param player エンティティ構造体
 *  @param enemy エンティティ構造体
 */
int isMatchPosition(struct Entity *player, struct Entity *enemy)
{
    if (player->position_x == enemy->position_x && player->position_y == enemy->position_y)
    {
        printf("GAME OVER\n\n");
        return 1;
    }
    return 0;
}
/** @fn
 * @brief 複数の敵を動かす
 * @param enemies エンティティ構造体のポインタ配列
 * @param chip MapChip構造体
 */
void enemiesMove(struct Entity *enemies[], struct MapChip chip[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH])
{
    for (int i = 0; enemies[i] != NULL; i++)
    {
        char cmd; //コマンド文字
        // 動かした先が歩行可能エリアでないならばやり直す．
        do
        {
            //random生成
            cmd = genRndCmd();
        } while (!entityMove(enemies[i], chip, cmd));
    }
}
/** @fn
 * @brief ゲームオーバーならば1を返す
 * @param enemies エンティティ構造体のポインタ配列
 * @param player エンティティ構造体
 */
int isGameOver(struct Entity *enemies[], struct Entity *player)
{
    for (int i = 0; enemies[i] != NULL; i++)
    {
        if (isMatchPosition(player, enemies[i]))
            return 1;
    }
    return 0;
}
/** @fn
 * @param enemies エンティティ構造体のポインタ配列
 * @param x 座標
   @param y 座標
 */
int printEnemies(struct Entity *enemies[], int x, int y)
{
    for (int i = 0; enemies[i] != NULL; i++)
    {
        if (enemies[i]->position_y == y && enemies[i]->position_x == x)
        {
            printf("%s", enemies[i]->icon);
            return 1;
        }
    }
    return 0;
}
int pollScanf(char *cmd)
{
    if (poll(&pollfd, 1, 1000))
    {
        scanf(" %c", cmd);
    }
    return 0;
}
int main()
{
    char mvcommand;
    struct Entity *enemies[ENEMY_NUMBER];
    struct Entity player;
    player.icon = PLAYER;
    player.position_x = MAP_CHIP_WIDTH / 2;
    player.position_y = MAP_CHIP_HEIGHT / 2 + 4;
    player.velocity_x = 0;
    player.velocity_y = 1;
    initMapChip();
    initEnemy(enemies, ENEMY_NUMBER - 1);
    do
    {
        pollScanf(&mvcommand);
        entityMove(&player, map_chip, mvcommand);
        if (isGameOver(enemies, &player) == 1)
            break;
        enemiesMove(enemies, map_chip);
        for (unsigned int y = 0; y < MAP_CHIP_HEIGHT; y++)
        {
            for (unsigned int x = 0; x < MAP_CHIP_WIDTH; x++)
            {
                if (player.position_y == y && player.position_x == x)
                {
                    printf("%s", player.icon);
                    continue;
                }
                !printEnemies(enemies, x, y) && printf("%s", map_chip[y][x].icon);
            }
            printf("\n");
        }
        printf("\x1b[49m");
    } while (1);
}
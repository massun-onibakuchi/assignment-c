#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//マップチップのデータの横幅
#define MAP_CHIP_WIDTH 21
//マップチップのデータの縦幅
#define MAP_CHIP_HEIGHT 21
#define ENEMY_NUMBER 3
//表示する　文字　の設定。
#define ITEM "\x1b[44m@\x1b[49m"
#define PLAYER "\x1b[44m  \x1b[49m"
#define ENEMY "\x1b[41m  \x1b[49m"
#define WALL "\x1b[49m  "
#define INVISIBLE_WALL "\x1b[47m  \x1b[49m"
#define ROAD "\x1b[47m  \x1b[49m"

//マップチップのデータ。
int map_chip_data[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH] =
    {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 0, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 0, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 0, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 2, 0, 2, 3, 3, 0, 3, 3, 2, 0, 2, 2, 0, 2, 0, 2},
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
// MapChip構造体の定義をする
struct MapChip
{
    char *icon;
    int id;
    unsigned int position_x;
    unsigned int position_y;
};
struct MapChip map_chip[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH];
enum EntityState
{
    None,
    Encount,
};
enum MoveCommand
{
    Up,
    Down,
    Right,
    Left
};
struct Entity
{
    char *icon;
    unsigned int position_x;
    unsigned int position_y;
    unsigned int velocity;
    unsigned int velocity_x;
    unsigned int velocity_y;
    enum MoveCommand command;
    enum EntityState state;
};
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
            map_chip[i][j].position_x = i;
            map_chip[i][j].position_y = j;
        }
    }
}
void setDirection(struct Entity *entity, char mvcommand)
{
    // char mvcommand;
    // scanf("%c", &mvcommand);
    if (mvcommand == 'f')
    {
        entity->velocity = 1;
        entity->velocity_x = 1;
        entity->velocity_y = 0;
        entity->command = entity->command = Right;
    }
    if (mvcommand == 'e')
    {
        entity->velocity = 1;
        entity->velocity_x = 0;
        entity->velocity_y = 1;
        entity->command = entity->command = Up;
    }
    if (mvcommand == 'd')
    {
        entity->velocity = -1;
        entity->velocity_x = 0;
        entity->velocity_y = -1;
        entity->command = entity->command = Down;
    }
    if (mvcommand == 's')
    {
        entity->velocity = -1;
        entity->velocity_x = -1;
        entity->velocity_y = 0;
        entity->command = entity->command = Left;
    }
}
void entityMove(struct Entity *entity, char mvcommand)
{
    char directions[4] = {'f', 'e', 'd', 's'};
    setDirection(entity, mvcommand);
    // entity->position_x + entity->velocity;
    entity->position_x = entity->position_x + entity->velocity_x;
    entity->position_y = entity->position_y + entity->velocity_y;
    if (entity->position_x >= MAP_CHIP_WIDTH)
        entity->position_x = MAP_CHIP_WIDTH;
    if (entity->position_x == 0)
        entity->position_x = 1;
    if (entity->position_y >= MAP_CHIP_HEIGHT)
        entity->position_y = MAP_CHIP_HEIGHT;
    if (entity->position_y == 0)
        entity->position_y = 1;
}
int isMatchPosition(struct Entity *player, struct Entity *enemy)
{
    if (player->position_x == enemy->position_x || player->position_y == enemy->position_y)
    {
        printf("GAME OVER");
        return 1;
    }
    return 0;
}
void initEnemy(struct Entity *enemies[], int number)
{
    for (int i = 0; i < number; i++)
    {
        struct Entity *enemy = (struct Entity *)malloc(sizeof(struct Entity));
        enemies[i] = enemy;
        enemies[i]->icon = ENEMY;
        // enemies[i]->position_x = MAP_CHIP_WIDTH / 2;
        // enemies[i]->position_y = MAP_CHIP_HEIGHT / 2;
        enemies[i]->position_x = 12;
        enemies[i]->position_y = 12;
        enemies[i]->velocity_x = 0;
        enemies[i]->velocity_y = 1;
    }
    enemies[number] = (struct Entity *)NULL;
}
void enemiesMove(struct Entity *enemies[])
{
    for (int i = 0; enemies[i] != NULL; i++)
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
        printf("ge %d", rnd);
        printf("command %c", mvcommand);
        setDirection(enemies[i], mvcommand);
    }
}
int isGameOver(struct Entity *enemies[], struct Entity *player)
{
    for (int i = 0; enemies[i] != NULL; i++)
    {
        if (isMatchPosition(player, enemies[i]))
            return 1;
    }
    return 0;
}
void printEnemies(struct Entity *enemies[], int x, int y)
{
    for (int i = 0; enemies[i] != NULL; i++)
    {
        if (enemies[i]->position_y == y && enemies[i]->position_x == x)
        {
            printf("%s", enemies[i]->icon);
            return;
        }
    }
}
int main()
{
    struct Entity *enemies[ENEMY_NUMBER - 1];
    struct Entity player;
    player.icon = PLAYER;
    player.position_x = 1;
    player.position_y = 1;
    player.velocity_x = 1;
    player.velocity_y = 0;
    initMapChip();
    initEnemy(enemies, ENEMY_NUMBER - 1);
    do
    {
        char mvcommand;
        scanf("%c", &mvcommand);
        entityMove(&player, mvcommand);
        enemiesMove(enemies);
        for (unsigned int y = 0; y < MAP_CHIP_HEIGHT; y++)
        {
            for (unsigned int x = 0; x < MAP_CHIP_WIDTH; x++)
            {
                ///@todo プレイヤーの移動ができるかどうか？
                // if (IsPlayerMoveCheck(map_chip[y][x]))
                // {
                //     PlayerPositionBack();
                // }
                if (player.position_y == y && player.position_x == x)
                {
                    printf("%s", player.icon);
                    continue;
                }
                
                printf("%s", map_chip[y][x].icon);
            }
            printf("\n");
        }
        printf("\x1b[49m");
    } while (isGameOver(enemies, &player) == 0);
}
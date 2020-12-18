#include <stdio.h>
#include <stdlib.h>

//マップチップのデータの横幅
#define MAP_CHIP_WIDTH (16)

//マップチップのデータの縦幅
#define MAP_CHIP_HEIGHT (16)

//表示する　文字　の設定。
#define NONE (" ")
#define WATER ("*")
#define MOUNTAIN ("@")

//マップチップのデータ。
int map_chip_data[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//1行目
	{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },//2行目
	{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },//3行目
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },//4行目
	{ 1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },//5行目
	{ 1, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1 },//6行目
	{ 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1 },//7行目
	{ 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1 },//8行目
	{ 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },//9行目
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },//10行目
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },//11行目
	{ 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },//12行目
	{ 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1 },//13行目
	{ 1, 1, 1, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1 },//14行目
	{ 1, 1, 1, 1, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1 },//15行目
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },//16行目
};


// MapChip構造体の定義をする
struct MapChip
{
	char* icon;
	int id;
	unsigned int position_x;
	unsigned int position_y;
};

// プレイヤーの状態
enum PlayerState
{
	Advance = 1,
	GoBack = -1,
};

//Player構造体の定義をする
struct Player
{
	char* icon;
	unsigned int position_x;
	unsigned int position_y;
	int velocity;
	PlayerState state;
};

//Player型の実態を作る
Player player = { "P" , MAP_CHIP_WIDTH / 2, MAP_CHIP_HEIGHT / 2, 1, PlayerState.Advance };
MapChip map_chip[MAP_CHIP_HEIGHT][MAP_CHIP_WIDTH];

//移動の命令一覧
int move_right_code		 = 'r';
int move_left_code		 = 'l';
int move_up_code		 = 'u';
int move_down_code		 = 'd';
int end_application_code = 'e';
int input_data           = ' ';

// マップチップの初期化
void InitMapChip()
{
	for (unsigned int i = 0; i < MAP_CHIP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_CHIP_WIDTH; j++)
		{
			map_chip[i][j].id = map_chip_data[i][j];
			if (map_chip[i][j].id == 0)
			{
				map_chip[i][j].icon = NONE;
			}
			else if (map_chip[i][j].id == 1)
			{
				map_chip[i][j].icon = WATER;
			}
			else if (map_chip[i][j].id == 2)
			{
				map_chip[i][j].icon = MOUNTAIN;
			}
			map_chip[i][j].position_x = j;
			map_chip[i][j].position_y = i;
		}
	}
}

//プレイヤーの移動処理
void PlayerMove()
{
	int velocity = player.velocity * player.state;

	//左右の移動
	if (input_data == move_right_code)
	{
		player.position_x += velocity;
	}
	if (input_data == move_left_code)
	{
		player.position_x -= velocity;
	}

	//上下の移動
	//配列の場合は下に行くほど数字が大きくなる。
	if (input_data == move_up_code)
	{
		player.position_y -= velocity;
	}
	if (input_data == move_down_code)
	{
		player.position_y += velocity;
	}

}


bool GetCommand()
{
	printf("\n");
	printf("  +-----------------------------------------------------+\n");
	printf("  | コマンドを入力してください。                        |\n");
	printf("  | %c...右へ移動 %c...左へ移動 %c...上へ移動 %c...下へ移動 |\n",move_right_code,move_left_code,move_up_code,move_down_code);
	printf("  | %c...終了する                                        |\n",end_application_code);
	printf("  +-----------------------------------------------------+\n");

	//入力を得る
	input_data = getchar();

	//ループを終える
	if (input_data == 'e')
	{
		//falseを返し、この関数を終了する。
		return false;
	}
	else
	{
		player.state = PlayerState::Advance;
		PlayerMove();
	}

	return true;
}

// プレイヤーの移動ができるかどうか？
// もし、できるなら、falseを返す。
// できないなら、trueを返す
bool IsPlayerMoveCheck(MapChip map_chip)
{
	// マップチップのアイコン（状態）がnoneなら、falseを返すようにしている。
	if (map_chip.icon == NONE) return false;
	if (player.position_x != map_chip.position_x) return false;
	if (player.position_y != map_chip.position_y)return false;

	return true;
}

// プレイヤーの移動を前の座標に戻す
void PlayerPositionBack()
{
	player.state = PlayerState::GoBack;
	PlayerMove();
}

//メイン関数
int main()
{
	InitMapChip();

	//do{}while()
	//do while文と呼ばれるループをする命令。
	//１度とりあえず実行してから、再度ループするかを最後にチェックする仕組み。
	do
	{
		//表示されている文字を全て削除する
		system("cls");

		for (unsigned int i = 0; i < MAP_CHIP_HEIGHT; i++)
		{
			for (unsigned int j = 0; j < MAP_CHIP_WIDTH; j++)
			{
				// プレイヤーの移動ができるかどうか？
				if (IsPlayerMoveCheck(map_chip[i][j]))
				{
					PlayerPositionBack();
				}

				//プレイヤーの位置だった場合
				if (player.position_y == i && player.position_x == j)
				{
					//プレイヤーのアイコンを表示
					printf("%s", player.icon);

					//for文を次に回す
					continue;
				}

				printf("%s", map_chip[i][j].icon);
			}
			printf("\n");
		}
	} 
	while (GetCommand());//whileの後の()内が真(true)ならループする。偽(false)ならばループを終える。

	return 0;
}



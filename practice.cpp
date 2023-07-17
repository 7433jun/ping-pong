#include <stdio.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

#pragma region Enum
enum Color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};
enum Scene {
	MENU,
	SOLO1,
	SOLO2,
	SOLO3,
	DUO
};
enum Side {
	LEFT,
	RIGHT
};
#pragma endregion

#pragma region Define
#define PlayerHp 3
#define EnemyHp 1
#define PlayerLength 7
#define EnemyLength 7
#define BallBeginSpeed 2.0f
#pragma endregion

#pragma region Stage2Block
int Block[21][31] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int BlockInit[21][31];
#pragma endregion

#pragma region Struct
struct Obj {
	int x;
	int y;
	const char* shape;
	Color color;
	int hp;
};
#pragma endregion

#pragma region DoubleBuffer
#define BufferWidth 62
#define BufferHeight 21

HANDLE hBuffer[2];
int screenIndex;

void InitBuffer();
void FlipBuffer();
void ClearBuffer();
void WriteBuffer(int x, int y, const char* shape, int color);
void DestroyBuffer();
#pragma endregion

#pragma region Menu
void MenuInitialize();
void MenuProgress();
void MenuRender();
void MenuRelease();
#pragma endregion

#pragma region SoloStage1
void SoloStage1Initialize();
void SoloStage1Progress();
void SoloStage1Render();
void SoloStage1Release();
#pragma endregion

#pragma region SoloStage2
void SoloStage2Initialize();
void SoloStage2Progress();
void SoloStage2Render();
void SoloStage2Release();
#pragma endregion

#pragma region SoloStage3
void SoloStage3Initialize();
void SoloStage3Progress();
void SoloStage3Render();
void SoloStage3Release();
#pragma endregion

#pragma region DuoStage
void DuoStageInitialize();
void DuoStageProgress();
void DuoStageRender();
void DuoStageRelease();
#pragma endregion

#pragma region Function
void Play();
void SwitchScene();
void SetScene();
void PlayerMove();
void EnemyMove();
void BallTouchLeft();
void BallTouchRight();
void BallTouchUpDown();
void BallAddSpeed();
void CheckWinner();
void StageSet();
#pragma endregion

#pragma region Image
const char* title[11];
const char* keyexplain[18];
const char* you[7];
const char* win[7];
const char* lose[7];
const char* red[7];
const char* blue[7];
#pragma endregion

Obj* cursor = nullptr;

Obj* player = nullptr;
Obj* enemy = nullptr;
Obj* ball = nullptr;

Scene currentScene = MENU;
Scene newScene;

bool keyExplainOn;

Side winSide;
bool ballMove;
float ballSpeed;
float ballTime;
float degree;
int ballBaseX, ballBaseY;
const double D = 3.14 / 180.0;
int playerMoveCount, enemyMoveCount;
int ballSpeedCount;
bool newRound;
bool endRound;
bool keyState;

ULONGLONG changeDegreeTime = GetTickCount64();
int degreeTime;

char ch[20];
char currentScore[20];

int main() {
	InitBuffer();

	SetScene();
	//SoloStage2Initialize();

	srand((unsigned)time(NULL));
	ULONGLONG tickTime = GetTickCount64();

	while (true) {
		if (tickTime + 10 < GetTickCount64()) {
			SwitchScene();

			Play();

			//SoloStage2Progress();
			//SoloStage2Render();

			FlipBuffer();
			ClearBuffer();

			tickTime = GetTickCount64();
		}
	}

	//SoloStage2Release();
	DestroyBuffer();

	return 0;
}

#pragma region Menu
void MenuInitialize() {
	SetConsoleTitle(TEXT("PING PONG"));

	title[0] = "####    ###   #   #   ####";
	title[1] = "#   #    #    ##  #  #    ";
	title[2] = "####     #    # # #  #  ##";
	title[3] = "#        #    #  ##  #   #";
	title[4] = "#       ###   #   #   ####";
	title[5] = " ";
	title[6] = "####    ###   #   #   ####";
	title[7] = "#   #  #   #  ##  #  #    ";
	title[8] = "####   #   #  # # #  #  ##";
	title[9] = "#      #   #  #  ##  #   #";
	title[10] = "#       ###   #   #   ####";

	keyexplain[0] = "==========================================";
	keyexplain[1] = "| 혼자서                                 |";
	keyexplain[2] = "|          위:  ↑                       |";
	keyexplain[3] = "|        아래:  ↓                       |";
	keyexplain[4] = "| 둘이서                                 |";
	keyexplain[5] = "|   파랑   위:   W                       |";
	keyexplain[6] = "|        아래:   S                       |";
	keyexplain[7] = "|   빨강   위:  ↑                       |";
	keyexplain[8] = "|        아래:  ↓                       |";
	keyexplain[9] = "|                                        |";
	keyexplain[10] = "|        선택: ENTER                     |";
	keyexplain[11] = "|    뒤로가기: ESC                       |";
	keyexplain[12] = "==========================================";

	cursor = (Obj*)malloc(sizeof(Obj));
	cursor->x = 18;
	cursor->y = 13;
	cursor->shape = "◀";
	cursor->color = WHITE;

	keyExplainOn = false;
}

void MenuProgress() {
	if (GetAsyncKeyState(VK_UP) && !keyExplainOn) {
		if (keyState) {
			if (cursor->y > 13) {
				cursor->y -= 2;
				keyState = false;
			}
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) && !keyExplainOn) {
		if (keyState) {
			if (cursor->y < 19) {
				cursor->y += 2;
				keyState = false;
			}
		}
	}
	else {
		keyState = true;
	}

	if (GetAsyncKeyState(VK_RETURN) && !keyExplainOn) {
		switch (cursor->y) {
		case 13:
			newScene = SOLO1;
			break;
		case 15:
			newScene = DUO;
			break;
		case 17:
			keyExplainOn = true;
			break;
		case 19:
			exit(0);
			break;
		default:
			break;
		}
	}
	if (GetAsyncKeyState(VK_ESCAPE) && keyExplainOn) {
		keyExplainOn = false;
	}
}

void MenuRender() {
	for (int i = 0; i < 11; i++) {
		WriteBuffer(9, 1 + i, title[i], WHITE);
	}

	WriteBuffer(13, 13, "혼 자 서", WHITE);
	WriteBuffer(13, 15, "둘 이 서", WHITE);
	WriteBuffer(13, 17, "조 작 법", WHITE);
	WriteBuffer(13, 19, "나 가 기", WHITE);

	WriteBuffer(cursor->x, cursor->y, cursor->shape, cursor->color);

	if (keyExplainOn) {
		for (int i = 0; i < 13; i++) {
			WriteBuffer(5, 4 + i, keyexplain[i], WHITE);
		}
	}
}

void MenuRelease() {
	free(cursor);
	cursor = nullptr;
}
#pragma endregion

#pragma region SoloStage1
void SoloStage1Initialize() {
	you[0] = "##    ##   #######   ##     ## ";
	you[1] = " ##  ##   ##     ##  ##     ## ";
	you[2] = "  ####    ##     ##  ##     ## ";
	you[3] = "   ##     ##     ##  ##     ## ";
	you[4] = "   ##     ##     ##  ##     ## ";
	you[5] = "   ##     ##     ##  ##     ## ";
	you[6] = "   ##      #######    #######  ";

	win[0] = "##      ##  ####  ##    ## ";
	win[1] = "##  ##  ##   ##   ###   ## ";
	win[2] = "##  ##  ##   ##   ####  ## ";
	win[3] = "##  ##  ##   ##   ## ## ## ";
	win[4] = "##  ##  ##   ##   ##  #### ";
	win[5] = "##  ##  ##   ##   ##   ### ";
	win[6] = " ###  ###   ####  ##    ## ";

	lose[0] = "##         #######    ######   ######## ";
	lose[1] = "##        ##     ##  ##    ##  ##       ";
	lose[2] = "##        ##     ##  ##        ##       ";
	lose[3] = "##        ##     ##   ######   ######   ";
	lose[4] = "##        ##     ##        ##  ##       ";
	lose[5] = "##        ##     ##  ##    ##  ##       ";
	lose[6] = "########   #######    ######   ######## ";

	player = (Obj*)malloc(sizeof(Obj));
	player->x = 0;
	player->y = 7;
	player->shape = "■";
	player->color = BLUE;
	player->hp = PlayerHp;

	enemy = (Obj*)malloc(sizeof(Obj));
	enemy->x = 30;
	enemy->y = 7;
	enemy->shape = "■";
	enemy->color = RED;
	enemy->hp = EnemyHp;

	ball = (Obj*)malloc(sizeof(Obj));
	ball->x = 15;
	ball->y = 10;
	ball->shape = "●";
	ball->color = YELLOW;

	ballMove = false;
	ballSpeed = BallBeginSpeed;
	ballTime = 0.0f;
	playerMoveCount = 0;
	enemyMoveCount = 0;
	ballSpeedCount = 0;
	newRound = true;
	endRound = false;

	StageSet();
}

void SoloStage1Progress() {
	PlayerMove();

	//라운드 시작
	if (GetAsyncKeyState(VK_SPACE)) {
		if (newRound) {
			degree = rand() % 360 - 180;
			if (degree == 90) {
				degree++;
			}
			ballMove = true;
			newRound = false;
		}
		if (endRound) {
			switch (winSide) {
			case LEFT:
				newScene = SOLO2;
				break;
			case RIGHT:
				endRound = false;
				player->hp = PlayerHp;
				enemy->hp = EnemyHp;
				break;
			default:
				break;
			}
		}
	}

	//공 움직임
	if (ballMove) {
		ballTime += 0.1f;
		ball->x = ballBaseX + ballSpeed * ballTime * cos(degree * D);
		ball->y = ballBaseY + ballSpeed * ballTime * sin(degree * D);
	}

	BallTouchLeft();

	BallTouchRight();

	BallTouchUpDown();

	EnemyMove();

	BallAddSpeed();

	CheckWinner();

	//메뉴로
	if (GetAsyncKeyState(VK_ESCAPE)) {
		newScene = MENU;
	}

	//강제 다음 스테이지 N
	if (GetAsyncKeyState(VK_F2)) {
		newScene = SOLO2;
	}

	//공 각도
	sprintf_s(ch, "%f", degree);
}

void SoloStage1Render() {
	for (int i = 0; i < 7; i++) {
		WriteBuffer(player->x, player->y + i, player->shape, player->color);
	}
	for (int i = 0; i < 7; i++) {
		WriteBuffer(enemy->x, enemy->y + i, enemy->shape, enemy->color);
	}

	for (int i = 0; i < player->hp; i++) {
		WriteBuffer(2 + i, 1, "♥", LIGHTRED);
	}
	for (int i = 0; i < enemy->hp; i++) {
		WriteBuffer(28 - i, 1, "♥", LIGHTRED);
	}

	//WriteBuffer(2, 2, ch, WHITE);
	WriteBuffer(ball->x, ball->y, ball->shape, ball->color);

	if (newRound) {
		WriteBuffer(10, 19, " PRESS SPACE TO START", WHITE);
	}

	//승패 출력
	if (endRound) {
		for (int i = 0; i < 7; i++) {
			WriteBuffer(8, 2 + i, you[i], WHITE);
		}
		switch (winSide) {
		case LEFT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(9, 10 + i, win[i], WHITE);
			}
			WriteBuffer(9, 19, " PRESS SPACE TO NEXT STAGE", WHITE);
			break;
		case RIGHT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(6, 10 + i, lose[i], WHITE);
			}
			WriteBuffer(10, 19, " PRESS SPACE TO RESTART", WHITE);
			break;
		default:
			break;
		}
	}
}

void SoloStage1Release() {
	free(player);
	player = nullptr;
	free(enemy);
	enemy = nullptr;
	free(ball);
	ball = nullptr;
}
#pragma endregion

#pragma region SoloStage2
void SoloStage2Initialize() {
	you[0] = "##    ##   #######   ##     ## ";
	you[1] = " ##  ##   ##     ##  ##     ## ";
	you[2] = "  ####    ##     ##  ##     ## ";
	you[3] = "   ##     ##     ##  ##     ## ";
	you[4] = "   ##     ##     ##  ##     ## ";
	you[5] = "   ##     ##     ##  ##     ## ";
	you[6] = "   ##      #######    #######  ";

	win[0] = "##      ##  ####  ##    ## ";
	win[1] = "##  ##  ##   ##   ###   ## ";
	win[2] = "##  ##  ##   ##   ####  ## ";
	win[3] = "##  ##  ##   ##   ## ## ## ";
	win[4] = "##  ##  ##   ##   ##  #### ";
	win[5] = "##  ##  ##   ##   ##   ### ";
	win[6] = " ###  ###   ####  ##    ## ";

	lose[0] = "##         #######    ######   ######## ";
	lose[1] = "##        ##     ##  ##    ##  ##       ";
	lose[2] = "##        ##     ##  ##        ##       ";
	lose[3] = "##        ##     ##   ######   ######   ";
	lose[4] = "##        ##     ##        ##  ##       ";
	lose[5] = "##        ##     ##  ##    ##  ##       ";
	lose[6] = "########   #######    ######   ######## ";

	player = (Obj*)malloc(sizeof(Obj));
	player->x = 0;
	player->y = 7;
	player->shape = "■";
	player->color = BLUE;
	player->hp = PlayerHp;

	enemy = (Obj*)malloc(sizeof(Obj));
	enemy->x = 30;
	enemy->y = 7;
	enemy->shape = "■";
	enemy->color = RED;
	enemy->hp = EnemyHp;

	ball = (Obj*)malloc(sizeof(Obj));
	ball->x = 15;
	ball->y = 10;
	ball->shape = "●";
	ball->color = YELLOW;

	ballMove = false;
	ballSpeed = BallBeginSpeed;
	ballTime = 0.0f;
	playerMoveCount = 0;
	enemyMoveCount = 0;
	ballSpeedCount = 0;
	newRound = true;
	endRound = false;

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 31; j++) {
			BlockInit[i][j] = Block[i][j];
		}
	}

	StageSet();
}

void SoloStage2Progress() {
	//플레이어 이동
	PlayerMove();

	//라운드 시작
	if (GetAsyncKeyState(VK_SPACE)) {
		if (newRound) {
			degree = rand() % 360 - 180;
			if (degree == 90) {
				degree++;
			}
			ballMove = true;
			newRound = false;
			for (int i = 0; i < 21; i++) {
				for (int j = 0; j < 31; j++) {
					Block[i][j] = BlockInit[i][j];
				}
			}
		}
		if (endRound) {
			switch (winSide) {
			case LEFT:
				newScene = SOLO3;
				break;
			case RIGHT:
				endRound = false;
				player->hp = PlayerHp;
				enemy->hp = EnemyHp;
				break;
			default:
				break;
			}
		}
	}

	//공 움직임
	if (ballMove) {
		ball->x = ballBaseX + ballSpeed * ballTime * cos(degree * D);
		ball->y = ballBaseY + ballSpeed * ballTime * sin(degree * D);
		ballTime += 0.1f;
	}

	//공이 왼쪽에 닿을때
	BallTouchLeft();

	//공이 오른쪽에 닿을때
	BallTouchRight();

	//공이 위아래 닿을때
	BallTouchUpDown();

	//공이 블럭에 닿을때
	if (Block[ball->y][ball->x]) {
		ballTime = 0.0f;
		if (Block[ball->y][ball->x - 1] && Block[ball->y][ball->x + 1]) {
			if (degree > 0) {
				ballBaseX = ball->x;
				ballBaseY = ball->y - 1;
			}
			else {
				ballBaseX = ball->x;
				ballBaseY = ball->y + 1;
			}
			degree = -degree;
		}
		else if (Block[ball->y - 1][ball->x] && Block[ball->y + 1][ball->x]) {
			if (degree < 90 && degree >= -90) {
				ballBaseX = ball->x - 1;
				ballBaseY = ball->y;
			}
			else {
				ballBaseX = ball->x + 1;
				ballBaseY = ball->y;
			}
			if (degree > 0) {
				degree = 180 - degree;
			}
			else {
				degree = -180 - degree;
			}
		}
		else if (degree >= 45 && degree < 135) {
			if (Block[ball->y - 1][ball->x] == 1) {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = 180 - degree;
			}
			else {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = -degree;
			}
		}
		else if (degree<45 && degree>-45) {
			if (Block[ball->y][ball->x - 1] == 1) {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = -degree;
			}
			else if (degree > 0) {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = 180 - degree;
			}
			else {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = -180 - degree;
			}
		}
		else if (degree <= -45 && degree > -135) {
			if (Block[ball->y + 1][ball->x] == 1) {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = -180 - degree;
			}
			else {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = -degree;
			}
		}
		else if (degree >= 135 || degree <= -135) {
			if (Block[ball->y][ball->x + 1] == 1) {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = -degree;
			}
			else if (degree > 0) {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = 180 - degree;
			}
			else {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				degree = -180 - degree;
			}
		}
		Block[ball->y][ball->x] = 0;
	}

	//적 움직임
	EnemyMove();

	//공 속도
	BallAddSpeed();

	//승패 결정
	CheckWinner();

	//메뉴로
	if (GetAsyncKeyState(VK_ESCAPE)) {
		newScene = MENU;
	}

	//강제 다음 스테이지 N
	if (GetAsyncKeyState(VK_F3)) {
		newScene = SOLO3;
	}

	//공 각도
	sprintf_s(ch, "%f", degree);
}

void SoloStage2Render() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 31; j++) {
			switch (Block[i][j])
			{
			case 1:
				WriteBuffer(j, i, "■", WHITE);
				break;
			default:
				break;
			}
		}
	}

	for (int i = 0; i < 7; i++) {
		WriteBuffer(player->x, player->y + i, player->shape, player->color);
	}
	for (int i = 0; i < 7; i++) {
		WriteBuffer(enemy->x, enemy->y + i, enemy->shape, enemy->color);
	}

	for (int i = 0; i < player->hp; i++) {
		WriteBuffer(2 + i, 1, "♥", LIGHTRED);
	}
	for (int i = 0; i < enemy->hp; i++) {
		WriteBuffer(28 - i, 1, "♥", LIGHTRED);
	}

	//WriteBuffer(2, 2, ch, WHITE);
	WriteBuffer(ball->x, ball->y, ball->shape, ball->color);

	if (newRound) {
		WriteBuffer(10, 19, " PRESS SPACE TO START", WHITE);
	}

	//승패 출력
	if (endRound) {
		for (int i = 3; i < 19; i++) {
			for (int j = 8; j < 24; j++) {
				WriteBuffer(j, i, "  ", WHITE);
			}
		}

		for (int i = 0; i < 7; i++) {
			WriteBuffer(8, 2 + i, you[i], WHITE);
		}
		switch (winSide) {
		case LEFT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(9, 10 + i, win[i], WHITE);
			}
			WriteBuffer(9, 19, " PRESS SPACE TO NEXT STAGE", WHITE);
			break;
		case RIGHT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(6, 10 + i, lose[i], WHITE);
			}
			WriteBuffer(10, 19, " PRESS SPACE TO RESTART", WHITE);
			break;
		default:
			break;
		}
	}
}

void SoloStage2Release() {
	free(player);
	player = nullptr;
	free(enemy);
	enemy = nullptr;
	free(ball);
	ball = nullptr;
}
#pragma endregion

#pragma region SoloStage3
void SoloStage3Initialize() {
	you[0] = "##    ##   #######   ##     ## ";
	you[1] = " ##  ##   ##     ##  ##     ## ";
	you[2] = "  ####    ##     ##  ##     ## ";
	you[3] = "   ##     ##     ##  ##     ## ";
	you[4] = "   ##     ##     ##  ##     ## ";
	you[5] = "   ##     ##     ##  ##     ## ";
	you[6] = "   ##      #######    #######  ";

	win[0] = "##      ##  ####  ##    ## ";
	win[1] = "##  ##  ##   ##   ###   ## ";
	win[2] = "##  ##  ##   ##   ####  ## ";
	win[3] = "##  ##  ##   ##   ## ## ## ";
	win[4] = "##  ##  ##   ##   ##  #### ";
	win[5] = "##  ##  ##   ##   ##   ### ";
	win[6] = " ###  ###   ####  ##    ## ";

	lose[0] = "##         #######    ######   ######## ";
	lose[1] = "##        ##     ##  ##    ##  ##       ";
	lose[2] = "##        ##     ##  ##        ##       ";
	lose[3] = "##        ##     ##   ######   ######   ";
	lose[4] = "##        ##     ##        ##  ##       ";
	lose[5] = "##        ##     ##  ##    ##  ##       ";
	lose[6] = "########   #######    ######   ######## ";

	player = (Obj*)malloc(sizeof(Obj));
	player->x = 0;
	player->y = 7;
	player->shape = "■";
	player->color = BLUE;
	player->hp = PlayerHp;

	enemy = (Obj*)malloc(sizeof(Obj));
	enemy->x = 30;
	enemy->y = 7;
	enemy->shape = "■";
	enemy->color = RED;
	enemy->hp = EnemyHp;

	ball = (Obj*)malloc(sizeof(Obj));
	ball->x = 15;
	ball->y = 10;
	ball->shape = "●";
	ball->color = YELLOW;

	ballMove = false;
	ballSpeed = BallBeginSpeed;
	ballTime = 0.0f;
	playerMoveCount = 0;
	enemyMoveCount = 0;
	ballSpeedCount = 0;
	newRound = true;
	endRound = false;

	degreeTime = 5;

	StageSet();
}

void SoloStage3Progress() {
	PlayerMove();

	//라운드 시작
	if (GetAsyncKeyState(VK_SPACE)) {
		if (newRound) {
			degree = rand() % 360 - 180;
			if (degree == 90) {
				degree++;
			}
			ballMove = true;
			newRound = false;
		}
		if (endRound) {
			switch (winSide) {
			case LEFT:
				newScene = MENU;
				break;
			case RIGHT:
				endRound = false;
				player->hp = PlayerHp;
				enemy->hp = EnemyHp;
				break;
			default:
				break;
			}
		}
	}

	//공 움직임
	if (ballMove) {
		ballTime += 0.1f;
		ball->x = ballBaseX + ballSpeed * ballTime * cos(degree * D);
		ball->y = ballBaseY + ballSpeed * ballTime * sin(degree * D);
	}

	//공 방향 꺾기
	if (ballMove) {
		if (changeDegreeTime + 1000 < GetTickCount64()) {
			degreeTime--;
			if (degreeTime <= 0) {
				ballBaseX = ball->x;
				ballBaseY = ball->y;
				ballTime = 0.0f;
				degree = rand() % 360 - 180;
				if (degree == 90) {
					degree++;
				}
				degreeTime = 5;
			}

			changeDegreeTime = GetTickCount64();
		}
	}

	BallTouchLeft();

	BallTouchRight();

	BallTouchUpDown();

	EnemyMove();

	BallAddSpeed();

	CheckWinner();

	//메뉴로
	if (GetAsyncKeyState(VK_ESCAPE)) {
		newScene = MENU;
	}

	//공 각도
	//sprintf_s(ch, "%f", degree);

	sprintf_s(ch, "%d", degreeTime);
}

void SoloStage3Render() {
	for (int i = 0; i < 7; i++) {
		WriteBuffer(player->x, player->y + i, player->shape, player->color);
	}
	for (int i = 0; i < 7; i++) {
		WriteBuffer(enemy->x, enemy->y + i, enemy->shape, enemy->color);
	}

	for (int i = 0; i < player->hp; i++) {
		WriteBuffer(2 + i, 1, "♥", LIGHTRED);
	}
	for (int i = 0; i < enemy->hp; i++) {
		WriteBuffer(28 - i, 1, "♥", LIGHTRED);
	}

	WriteBuffer(15, 1, ch, WHITE);

	//WriteBuffer(2, 2, ch, WHITE);
	WriteBuffer(ball->x, ball->y, ball->shape, ball->color);

	if (newRound) {
		WriteBuffer(10, 19, " PRESS SPACE TO START", WHITE);
	}

	//승패 출력
	if (endRound) {
		for (int i = 0; i < 7; i++) {
			WriteBuffer(8, 2 + i, you[i], WHITE);
		}
		switch (winSide) {
		case LEFT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(9, 10 + i, win[i], WHITE);
			}
			WriteBuffer(10, 19, " PRESS SPACE TO MENU  ", WHITE);
			break;
		case RIGHT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(6, 10 + i, lose[i], WHITE);
			}
			WriteBuffer(10, 19, " PRESS SPACE TO RESTART", WHITE);
			break;
		default:
			break;
		}
	}
}

void SoloStage3Release() {
	free(player);
	player = nullptr;
	free(enemy);
	enemy = nullptr;
	free(ball);
	ball = nullptr;
}
#pragma endregion

#pragma region DuoStage
void DuoStageInitialize() {
	red[0] = "########   ########  ######## ";
	red[1] = "##     ##  ##        ##     ##";
	red[2] = "##     ##  ##        ##     ##";
	red[3] = "########   ######    ##     ##";
	red[4] = "##   ##    ##        ##     ##";
	red[5] = "##    ##   ##        ##     ##";
	red[6] = "##     ##  ########  ######## ";

	blue[0] = "########   ##        ##     ##  ########";
	blue[1] = "##     ##  ##        ##     ##  ##      ";
	blue[2] = "##     ##  ##        ##     ##  ##      ";
	blue[3] = "########   ##        ##     ##  ######  ";
	blue[4] = "##     ##  ##        ##     ##  ##      ";
	blue[5] = "##     ##  ##        ##     ##  ##      ";
	blue[6] = "########   ########   #######   ########";

	win[0] = "##      ##  ####  ##    ## ";
	win[1] = "##  ##  ##   ##   ###   ## ";
	win[2] = "##  ##  ##   ##   ####  ## ";
	win[3] = "##  ##  ##   ##   ## ## ## ";
	win[4] = "##  ##  ##   ##   ##  #### ";
	win[5] = "##  ##  ##   ##   ##   ### ";
	win[6] = " ###  ###   ####  ##    ## ";

	player = (Obj*)malloc(sizeof(Obj));
	player->x = 0;
	player->y = 7;
	player->shape = "■";
	player->color = BLUE;
	player->hp = PlayerHp;

	enemy = (Obj*)malloc(sizeof(Obj));
	enemy->x = 30;
	enemy->y = 7;
	enemy->shape = "■";
	enemy->color = RED;
	enemy->hp = EnemyHp;

	ball = (Obj*)malloc(sizeof(Obj));
	ball->x = 15;
	ball->y = 10;
	ball->shape = "●";
	ball->color = YELLOW;

	ballMove = false;
	ballSpeed = BallBeginSpeed;
	ballTime = 0.0f;
	playerMoveCount = 0;
	enemyMoveCount = 0;
	ballSpeedCount = 0;
	newRound = true;
	endRound = false;

	StageSet();
}

void DuoStageProgress() {
	//플레이어 블루 이동
	playerMoveCount++;
	if (playerMoveCount >= 5) {
		if (GetAsyncKeyState(0x57)) { // W
			player->y--;
			if (player->y < 0) {
				player->y++;
			}
		}
		if (GetAsyncKeyState(0x53)) { // S
			player->y++;
			if (player->y > 14) {
				player->y--;
			}
		}
		playerMoveCount = 0;
	}

	//플레이어 레드 이동
	enemyMoveCount++;
	if (enemyMoveCount >= 5) {
		if (GetAsyncKeyState(VK_UP)) {
			enemy->y--;
			if (enemy->y < 0) {
				enemy->y++;
			}
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			enemy->y++;
			if (enemy->y > 14) {
				enemy->y--;
			}
		}
		enemyMoveCount = 0;
	}

	//라운드 시작
	if (GetAsyncKeyState(VK_SPACE)) {
		if (newRound) {
			degree = rand() % 360 - 180;
			if (degree == 90) {
				degree++;
			}
			ballMove = true;
			newRound = false;
		}
		if (endRound) {
			endRound = false;
			player->hp = PlayerHp;
			enemy->hp = EnemyHp;
		}
	}

	//공 움직임
	if (ballMove) {
		ballTime += 0.1f;
		ball->x = ballBaseX + ballSpeed * ballTime * cos(degree * D);
		ball->y = ballBaseY + ballSpeed * ballTime * sin(degree * D);
	}

	//공이 왼쪽에 닿을때
	BallTouchLeft();

	//공이 오른쪽에 닿을때
	BallTouchRight();

	//공이 위아래 닿을때
	BallTouchUpDown();

	//공 속도
	BallAddSpeed();

	//승패 결정
	CheckWinner();

	//메뉴로
	if (GetAsyncKeyState(VK_ESCAPE)) {
		newScene = MENU;
	}

	//공 각도
	//sprintf_s(ch, "%f", degree);

}

void DuoStageRender() {
	for (int i = 0; i < 7; i++) {
		WriteBuffer(player->x, player->y + i, player->shape, player->color);
	}
	for (int i = 0; i < 7; i++) {
		WriteBuffer(enemy->x, enemy->y + i, enemy->shape, enemy->color);
	}

	for (int i = 0; i < player->hp; i++) {
		WriteBuffer(2 + i, 1, "♥", LIGHTRED);
	}
	for (int i = 0; i < enemy->hp; i++) {
		WriteBuffer(28 - i, 1, "♥", LIGHTRED);
	}

	//WriteBuffer(2, 2, ch, WHITE);

	WriteBuffer(ball->x, ball->y, ball->shape, ball->color);
	WriteBuffer(14, 1, currentScore, WHITE);
	if (newRound) {
		WriteBuffer(10, 19, " PRESS SPACE TO START", WHITE);
	}

	//승패 출력
	if (endRound) {
		for (int i = 0; i < 7; i++) {
			WriteBuffer(9, 10 + i, win[i], WHITE);
		}
		switch (winSide) {
		case LEFT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(6, 2 + i, blue[i], BLUE);
			}
			break;
		case RIGHT:
			for (int i = 0; i < 7; i++) {
				WriteBuffer(8, 2 + i, red[i], RED);
			}
			break;
		default:
			break;
		}
	}
}

void DuoStageRelease() {
	free(player);
	player = nullptr;
	free(enemy);
	enemy = nullptr;
	free(ball);
	ball = nullptr;
}
#pragma endregion

#pragma region Function
void Play() {
	switch (currentScene) {
	case MENU:
		MenuProgress();
		MenuRender();
		break;
	case SOLO1:
		SoloStage1Progress();
		SoloStage1Render();
		break;
	case SOLO2:
		SoloStage2Progress();
		SoloStage2Render();
		break;
	case SOLO3:
		SoloStage3Progress();
		SoloStage3Render();
		break;
	case DUO:
		DuoStageProgress();
		DuoStageRender();
		break;
	default:
		break;
	}
}

//씬 변경
void SwitchScene() {
	if (currentScene != newScene) {
		switch (currentScene) {
		case MENU:
			MenuRelease();
			break;
		case SOLO1:
			SoloStage1Release();
			break;
		case SOLO2:
			SoloStage2Release();
			break;
		case SOLO3:
			SoloStage3Release();
			break;
		case DUO:
			DuoStageRelease();
			break;
		default:
			break;
		}

		currentScene = newScene;

		SetScene();
	}
}

void SetScene() {
	switch (currentScene) {
	case MENU:
		MenuInitialize();
		break;
	case SOLO1:
		SoloStage1Initialize();
		break;
	case SOLO2:
		SoloStage2Initialize();
		break;
	case SOLO3:
		SoloStage3Initialize();
		break;
	case DUO:
		DuoStageInitialize();
		break;
	default:
		break;
	}
}

void PlayerMove() {
	playerMoveCount++;
	if (playerMoveCount >= 5) {
		if (GetAsyncKeyState(VK_UP)) {
			player->y--;
			if (player->y < 0) {
				player->y++;
			}
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			player->y++;
			if (player->y > 14) {
				player->y--;
			}
		}
		playerMoveCount = 0;
	}
}

void EnemyMove() {
	enemyMoveCount++;
	if (enemyMoveCount >= 10) {
		if (enemy->y + 3 > ball->y) {
			enemy->y--;
			if (enemy->y < 0) {
				enemy->y++;
			}
		}
		if (enemy->y + 3 < ball->y) {
			enemy->y++;
			if (enemy->y > 14) {
				enemy->y--;
			}
		}
		enemyMoveCount = 0;
	}
}

void BallTouchLeft() {
	if (ball->x <= 1) {
		if (ball->y >= player->y && ball->y < player->y + PlayerLength) {
			ballBaseX = ball->x + 1;
			ballBaseY = ball->y;
			ballTime = 0.0f;
			if (ball->y < player->y + PlayerLength / 3) {
				if (degree > 0) {
					degree = 180 - degree - 30;
				}
				else {
					degree = -180 - degree - 30;
				}
			}
			else if (ball->y >= player->y + PlayerLength / 3 && ball->y < player->y + PlayerLength / 3 * 2 + PlayerLength % 2) {
				if (degree > 0) {
					degree = 180 - degree + (rand() % 20 - 10);
				}
				else {
					degree = -180 - degree + (rand() % 20 - 10);
				}
			}
			else {
				if (degree > 0) {
					degree = 180 - degree + 30;
				}
				else {
					degree = -180 - degree + 30;
				}
			}
		}
		else {
			player->hp--;
			StageSet();
		}
	}
}

void BallTouchRight() {
	if (ball->x >= 29) {
		if (ball->y >= enemy->y && ball->y < enemy->y + EnemyLength) {
			ballBaseX = ball->x - 1;
			ballBaseY = ball->y;
			ballTime = 0.0f;
			if (ball->y < enemy->y + EnemyLength / 3) {
				if (degree > 0) {
					degree = 180 - degree - 20;
				}
				else {
					degree = -180 - degree - 20;
				}
			}
			else if (ball->y >= enemy->y + EnemyLength / 3 && ball->y < enemy->y + EnemyLength / 3 * 2 + EnemyLength % 2) {
				if (degree > 0) {
					degree = 180 - degree + (rand() % 20 - 10);
				}
				else {
					degree = -180 - degree + (rand() % 20 - 10);
				}
			}
			else {
				if (degree > 0) {
					degree = 180 - degree + 20;
				}
				else {
					degree = -180 - degree + 20;
				}
			}
		}
		else {
			enemy->hp--;
			StageSet();
		}
	}
}

void BallTouchUpDown() {
	if (ball->y < 1) {
		ballBaseX = ball->x;
		ballBaseY = ball->y + 1;
		ballTime = 0.0f;
		degree = -degree;
	}
	if (ball->y > 19) {
		ballBaseX = ball->x;
		ballBaseY = ball->y - 1;
		ballTime = 0.0f;
		degree = -degree;
	}
}

void BallAddSpeed() {
	//1 tick = 10 = 0.01초 (main에서 수정)
	ballSpeedCount++;
	if (ballSpeedCount >= 300) {
		ballSpeed += 0.1f;
		ballSpeedCount = 0;
	}
}

void CheckWinner() {
	if (player->hp <= 0 || enemy->hp <= 0) {
		if (player->hp <= 0) {
			winSide = RIGHT;
		}
		if (enemy->hp <= 0) {
			winSide = LEFT;
		}
		endRound = true;
	}
}

//공 위치 초기화
void StageSet() {
	ballBaseX = 15;
	ballBaseY = 10;
	ball->x = ballBaseX;
	ball->y = ballBaseY;
	ballSpeed = BallBeginSpeed;
	ballTime = 0.0f;
	ballMove = false;
	newRound = true;
}
#pragma endregion

#pragma region DoubleBuffer
void InitBuffer() {
	screenIndex = 0;
	char command[100];

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	sprintf_s(command, "mode con:cols=%d lines=%d", BufferWidth, BufferHeight);
	SetConsoleActiveScreenBuffer(hBuffer[0]);
	system(command);
	SetConsoleActiveScreenBuffer(hBuffer[1]);
	system(command);

	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 1;
	Info.bVisible = FALSE;

	SetConsoleCursorInfo(hBuffer[0], &Info);
	SetConsoleCursorInfo(hBuffer[1], &Info);
}

void FlipBuffer() {
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);
	screenIndex = !screenIndex;
}

void ClearBuffer() {
	COORD pos = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

void WriteBuffer(int x, int y, const char* shape, int color) {
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);
	SetConsoleTextAttribute(hBuffer[screenIndex], color);
	DWORD dw;
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);
}

void DestroyBuffer() {
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}
#pragma endregion
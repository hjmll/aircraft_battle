#include <iostream>
#include <graphics.h>
#include "game.h"
using namespace std;

int main() {
	Game* game = new Game;	// 初始化游戏，帧率为60Hz
	game->run();		// 运行游戏
	delete game;
}


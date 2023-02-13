#include <iostream>
#include <graphics.h>
#include "game.h"
using namespace std;

int main() {
	Game game(60);	// 初始化游戏，帧率为60Hz
	game.run();		// 运行游戏
}


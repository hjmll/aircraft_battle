#include <iostream>
#include <graphics.h>
#include "game.h"
using namespace std;

int main() {
	Game* game = new Game;	// ��ʼ����Ϸ��֡��Ϊ60Hz
	game->run();		// ������Ϸ
	delete game;
}


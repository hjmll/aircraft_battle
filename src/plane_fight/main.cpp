#include <iostream>
#include <graphics.h>
#include "game.h"
using namespace std;

int main() {
	Game game(60);	// ��ʼ����Ϸ��֡��Ϊ60Hz
	game.run();		// ������Ϸ
}


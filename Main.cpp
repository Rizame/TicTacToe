#include<iostream>
#include<SFML/Graphics.hpp>
#include"Game.h"
#include"DEFINITIONS.h"

int main()
{
	Risame::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic Tac Toe");
	return EXIT_SUCCESS;
}
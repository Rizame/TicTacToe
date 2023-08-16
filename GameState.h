#pragma once
#include<SFML/Graphics.hpp>
#include"State.h"
#include"Game.h"

namespace Risame
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		void initGridPieces();
		void checkAndPlacePiece();
		void CheckPlayerWin(int turn);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
		bool checkWin();
		GameDataRef _data;
		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;
		sf::Sprite _gridPieces[3][3];

		int gridArray[3][3];
		int checkArray[3][3];
		int turn;
		int gameState;
		
		sf::Clock _clock;
	};
}
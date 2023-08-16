#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include "PauseState.h"
#include "GameOverState.h"

namespace Risame
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}
	void GameState::Init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->_data->assets.LoadTexture("PauseButton", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("MainBackground", GAME_BG_FILEPATH);
		this->_data->assets.LoadTexture("GridSprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("XPiece", X_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("OPiece", O_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("XWinPiece", X_WIN_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("OWinPiece", O_WIN_SPRITE_FILEPATH);

		_gridSprite.setTexture(this->_data->assets.GetTexture("GridSprite"));
		_pauseButton.setTexture(this->_data->assets.GetTexture ("PauseButton"));
		_background.setTexture(this->_data->assets.GetTexture("MainBackground"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width,
			_pauseButton.getPosition().y);
		_gridSprite.setPosition(SCREEN_WIDTH / 2 - (_gridSprite.getGlobalBounds().width / 2), SCREEN_HEIGHT / 2 - (_gridSprite.getGlobalBounds().height / 2));

		initGridPieces();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				gridArray[x][y] = EMPTY_PIECE;
				checkArray[x][y] = 2;
			}
		}
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_pauseButton,
				sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
				//this->_data->machine.AddState(StateRef(new GameOverState(_data)), true);
			}
			else if (this->_data->input.IsSpriteClicked(this->_gridSprite,
				sf::Mouse::Left, this->_data->window))
			{
				if (STATE_PLAYING == gameState)
				{
					this->checkAndPlacePiece();
				}
				//this->checkWin();

			}
		}
	}

	void GameState::Update(float dt)
	{
		if (STATE_DRAW == gameState || STATE_LOST == gameState || STATE_WON == gameState)
		{
			if (this->_clock.getElapsedTime().asSeconds() > BEFORE_GAME_OVER_TIME)
			{
				this->_data->machine.AddState(StateRef(new GameOverState(_data)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
		}

		this->_data->window.display();
	}
	void GameState::initGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("XPiece").getSize();
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("XPiece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) + 15, _gridSprite.getPosition().y + (tempSpriteSize.y * y) + 15);
				_gridPieces[x][y].setColor(sf::Color::Color(255, 255, 255, 0));
			}
		}
	}
	void GameState::checkAndPlacePiece()
	{
		sf::Vector2i touchpoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideofGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchpoint.x - gapOutsideofGrid.x, touchpoint.y - gapOutsideofGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column, row;

		if (gridLocalTouchPos.x < gridSectionSize.x)
		{
			column = 1;
		}
		else if (gridLocalTouchPos.x < gridSectionSize.x * 2)
		{
			column = 2;
		}
		else if (gridLocalTouchPos.x < gridSize.width)
		{
			column = 3;
		}

		if (gridLocalTouchPos.y < gridSectionSize.y)
		{
			row = 1;
		}
		else if (gridLocalTouchPos.y < gridSectionSize.y * 2)
		{
			row = 2;
		}
		else if (gridLocalTouchPos.y < gridSize.height)
		{
			row = 3;
		}
		
		if (gridArray[column - 1][row - 1] == EMPTY_PIECE)
		{
			gridArray[column - 1][row - 1] = turn;

			if (PLAYER_PIECE == turn)
			{
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("XPiece"));
				this->CheckPlayerWin(turn);
				turn = AI_PIECE;
				
			}
			else if (AI_PIECE == turn)
			{
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture("OPiece"));
				this->CheckPlayerWin(turn);
				turn = PLAYER_PIECE;
			}
			
			_gridPieces[column - 1][row - 1].setColor(sf::Color::Color(255, 255, 255, 255));
		}
	}
	void GameState::CheckPlayerWin(int player)
	{
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

		int emptyNum = 9;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (EMPTY_PIECE != gridArray[x][y])
				{
					emptyNum--;
				}
			}
		}
		if (0 == emptyNum && (STATE_WON != gameState) && (STATE_LOST != gameState))
		{
			gameState = STATE_DRAW;
		}
		if (STATE_DRAW == gameState || STATE_LOST == gameState || STATE_WON == gameState)
		{
			this->_clock.restart();
			
		}
	}
	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
	{
		if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3])
		{
			std::string winningPieceStr;
			if (O_PIECE == pieceToCheck)
			{
				winningPieceStr = "OWinPiece";
			}
			else
			{
				winningPieceStr = "XWinPiece";
			}
			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));

			if (PLAYER_PIECE == pieceToCheck)
			{
				gameState = STATE_WON;
			}
			else
			{
				gameState = STATE_LOST;
			}
		}
	}
}
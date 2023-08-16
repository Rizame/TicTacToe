#include<sstream>
#include"MainMenuState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include "GameState.h"

namespace Risame
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}
	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BG_FILEPATH);
		this->_data->assets.LoadTexture("PlayButton", MAIN_MENU_PLAY_BUTTON);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_playButton.setTexture(this->_data->assets.GetTexture("PlayButton"));

		this->_playButton.setPosition((SCREEN_WIDTH / 2) -
			this->_playButton.getGlobalBounds().width / 2, (SCREEN_HEIGHT / 2) -
			(this->_playButton.getGlobalBounds().height / 2));
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_playButton,
				sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_playButton);

		this->_data->window.display();
	}
}
#include<sstream>
#include <iostream>
#include"GameOverState.h"
#include "DEFINITIONS.h"
#include"GameState.h"
#include"MainMenuState.h"

namespace Risame
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{

	}
	void GameOverState::Init()
	{
		this->_data->assets.LoadTexture("RetryButton", RETRY_BUTTON);
		this->_data->assets.LoadTexture("HomeButton", MENU_HOME_BUTTON);

		this->_retryButton.setTexture(this->_data->assets.GetTexture("RetryButton"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("HomeButton"));

		this->_retryButton.setPosition((SCREEN_WIDTH / 2) - (this->_retryButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 3) - (this->_retryButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((SCREEN_WIDTH / 2) - (this->_homeButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_retryButton,
				sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
			if (this->_data->input.IsSpriteClicked(this->_homeButton,
				sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}
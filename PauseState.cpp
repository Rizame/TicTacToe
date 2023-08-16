#include<sstream>
#include <iostream>
#include"PauseState.h"
#include "DEFINITIONS.h"
#include"GameState.h"
#include"MainMenuState.h"

namespace Risame
{
	PauseState::PauseState(GameDataRef data) : _data(data)
	{

	}
	void PauseState::Init()
	{
		this->_data->assets.LoadTexture("Background", GAME_BG_FILEPATH);
		this->_data->assets.LoadTexture("ResumeButton", MENU_RESUME_BUTTON);
		this->_data->assets.LoadTexture("HomeButton", MENU_HOME_BUTTON);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_resumeButton.setTexture(this->_data->assets.GetTexture("ResumeButton"));
		this->_homeButton.setTexture(this->_data->assets.GetTexture("HomeButton"));

		this->_resumeButton.setPosition( (SCREEN_WIDTH / 2) - (this->_resumeButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y/3) - (this->_resumeButton.getLocalBounds().height/2));
		this->_homeButton.setPosition((SCREEN_WIDTH / 2) - (this->_homeButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
	}

	void PauseState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (this->_data->input.IsSpriteClicked(this->_resumeButton,
				sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
			}
			if (this->_data->input.IsSpriteClicked(this->_homeButton,
				sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.RemoveState();
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void PauseState::Update(float dt)
	{

	}

	void PauseState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resumeButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}
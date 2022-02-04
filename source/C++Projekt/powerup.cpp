#include "objects.h"
#include <SFML/Graphics.hpp>
#include "RunGame.h"

time_powerup::time_powerup(RunGame* game, const sf::Vector2f position, const std::shared_ptr<FileManager>& file_manager)
{
	this->setPosition(position);
	this->set_type(object_type::powerup);
	this->setSize(sf::Vector2f(32.0f, 32.0f));
	this->setOrigin(this->getSize() / 2.0f);
	this->texture = file_manager->get_texture(this->get_type());
	this->setTexture(&texture);
	this->set_active();
	this->game = game;
}

time_powerup::~time_powerup()
= default;

void time_powerup::execute()
{
	if (this->check_active())
	{
		game->powerup_time();
		this->set_inactive();
		this->setFillColor(sf::Color::Black);
	}
}

score_powerup::score_powerup(RunGame* game, const sf::Vector2f position, const std::shared_ptr<FileManager>& file_manager)
{
	this->setPosition(position);
	
	this->set_type(object_type::powerup);
	this->setSize(sf::Vector2f(32.0f, 32.0f));
	this->texture = file_manager->get_texture(this->get_type());
	this->setTexture(&texture);
	this->set_active();
	this->setOrigin(this->getSize() / 2.0f);
	this->game = game;
}

score_powerup::~score_powerup()
= default;

void score_powerup::execute()
{
	if (this->check_active())
	{
		game->powerup_score();
		this->set_inactive();
		this->setFillColor(sf::Color::Black);
	}
}


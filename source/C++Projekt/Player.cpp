#include "objects.h"
#include <iostream>
using namespace std;

sf::Texture texture_player;
int frame = 0, frames = 1, direction = 128;

Player::Player(float* delta_time, const std::shared_ptr<FileManager>& file_manager)
{
	this->texture = file_manager->get_texture(object_type::player);

	this->delta_time = delta_time;
	movement = sf::Vector2f(0.0f, 0.0f);
	this->set_type(object_type::player);
	this->setSize(sf::Vector2f(32.0f, 64.0f));
	this->setTexture(&texture);
	this->setTextureRect(sf::IntRect(frame * 48, direction, 48, 64));
	this->setOrigin(this->getSize() / 2.0f);
	this->setPosition(0.0f, 128.0f);
	this->speed = 3.0f;
	this->jump = false;
}

Player::~Player()
{
	this->delta_time = nullptr;
	std::cout << "Del Player" << std::endl;
}

void Player::Movement()
{
	this->movement.x *= 0.1f;
	this->movement.y += 4096.0f * *this->delta_time;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = 64;
	
		this->movement.x += 256.0f * this->speed;
		
		if (frame <= frames) 
			frame++;
		else 
			frame = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = 192;

		this->movement.x -= 256.0f * this->speed;

		if (frame <= frames) 
			frame++;
		else 
			frame = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->jump)
	{
		this->jump = false;
		this->movement.y = -1300.0f;

		if (frame <= frames)
			frame++;
		else
			frame = 0;
	}

	this->setTextureRect(sf::IntRect(frame * 48, direction, 48, 64));

	this->move(movement * *this->delta_time);
}

void Player::move_x(const float x)
{
	this->move(x, 0.0f);
	this->set_movement_x(0.0f);
	this->set_jump(false);
}

void Player::move_y(const float y)
{
	this->move(0.0f, y);
	this->set_movement_y(0.0f);

	if (y < 0) 
		this->set_jump(true);
}

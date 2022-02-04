#pragma once
#include "SFML/Graphics.hpp"
#include "object_type.h"
#include "FileManager.h"

class RunGame;

class object : public sf::RectangleShape
{
public:
	object() = default;

	void draw(sf::RenderWindow& window) const { window.draw(*this); }
	object_type get_type() const { return type; }
	void set_type(const object_type type) { this->type = type; }
	sf::Vector2f get_halfsize() const { return this->getSize() / 2.0f; }
	sf::Vector2f get_position() const { return this->getPosition(); }
	virtual void move_x(const float x) { this->move(x, 0.0f); }
	virtual void move_y(const float y) { this->move(0.0f, y); }

private:
	object_type type;
protected:
	sf::Texture texture;
};

class level_object : public object
{
public:
	level_object(sf::Vector2f size, sf::Vector2f position, const std::shared_ptr<FileManager>& file_manager, object_type type);
	~level_object() override;
};

class Player : public object
{
public:
	explicit Player(float* delta_time, const std::shared_ptr<FileManager>& file_manager);
	~Player() override;
	
	void set_speed(const float speed) { this->speed = speed; }
	void Movement();
	void set_movement(const sf::Vector2f move) { movement = move; }

	sf::Vector2f get_size() const { return this->getSize(); }

	sf::Vector2f get_movement() const { return this->movement; }

	void move_x(float x) override;
	void move_y(float y) override;

	void set_movement_x(const float mov_x) { this->movement.x = mov_x; }
	void set_movement_y(const float mov_y) { this->movement.y = mov_y; }

	void set_jump(const bool jump) { this->jump = jump; }

private:
	bool jump;
	float speed;
	float* delta_time;
	sf::Vector2f movement;
};

class powerup : public object
{
public:
	void set_active() { this->is_active = true; }
	void set_inactive() { this->is_active = false; }
	bool check_active() const { return this->is_active; }
	virtual void execute() {}

private:
	bool is_active = false;

protected:
	RunGame* game = nullptr;
};

class time_powerup : public powerup
{
public:
	explicit time_powerup(RunGame* game, sf::Vector2f position, const std::shared_ptr<FileManager>& file_manager);
	~time_powerup() override;

	void execute() override;
};

class score_powerup : public powerup
{
public:
	explicit score_powerup(RunGame* game, sf::Vector2f position, const std::shared_ptr<FileManager>& file_manager);
	~score_powerup() override;

	void execute() override;
};
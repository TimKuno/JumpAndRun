#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "WindowContent.h"
#include "CollisionManager.h"
#include "objects.h"
#include "Menus.h"

class CollisionManager;

class RunGame : public Screens
{
public:
	RunGame(WindowContent& cont, float& delta_time, int& score, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager);

	~RunGame() override;
	void run() override;
	void game_over() const;
	void powerup_time();
	void powerup_score() const;
	
private:
	void draw() override
	{
		this->draw_objects_check_collision();
		this->move_player_set_view();
	}

	void delete_objects();
	void add_objects();
	void add_objects_to_buffer();
	void draw_objects_check_collision();
	void move_player_set_view() const;
	static sf::Vector2f rand_position(int min, int max, sf::Vector2f prev_obj_pos);
	void count_score();

	sf::RenderWindow* window;
	CollisionManager* mgr;
	Player* player;
	std::list<object*> plat_buffer;
	std::list<object*> plat_passed;
	std::list<object*>::iterator plat_it;
	sf::View* view;
	float timelimit;
	float* delta_time;
	int* score;
	WindowContent* cont;

	sf::Text score_text;
	sf::Text time_text;

	std::shared_ptr<FileManager> file_manager;
};

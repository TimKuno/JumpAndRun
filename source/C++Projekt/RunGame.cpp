#include "RunGame.h"
#include <thread>
#include <iostream>

#pragma region

/**
 *  Initializes the game, creates an initial starting object and the player.
 */
RunGame::RunGame(WindowContent& cont, float& delta_time, int& score, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager)
{
	this->file_manager = file_manager;
	this->window = &window;

	this->timelimit = 25.0f;
	this->score = &score;
	this->delta_time = &delta_time;
	this->cont = &cont;
	this->mgr = new CollisionManager(this);
	this->view = new sf::View();
	this->view->setSize(sf::Vector2f(2048.0f, 1024.0f));

	this->player = new Player(&delta_time, this->file_manager);
	level_object* plat = new level_object(sf::Vector2f(256.0f, 128.0f), sf::Vector2f(0.0f, 256.0f), this->file_manager, object_type::platform_regular);
	this->plat_buffer.push_back(plat);

	this->score_text.setFont(this->file_manager->get_font());
	
	this->score_text.setCharacterSize(20);
	this->score_text.setFillColor(sf::Color::White);
	this->time_text.setFont(this->file_manager->get_font());
	this->time_text.setCharacterSize(20);
	this->time_text.setFillColor(sf::Color::White);	
}

/**
 * Destructor.
 */
RunGame::~RunGame()
{
	delete this->view;

	for (this->plat_it = this->plat_buffer.begin(); this->plat_it != this->plat_buffer.end(); ++this->plat_it)
	{
		delete *plat_it;
		*plat_it = nullptr;		
	}
	for (this->plat_it = this->plat_passed.begin(); this->plat_it != this->plat_passed.end(); ++this->plat_it)
	{
		delete *plat_it;
		*plat_it = nullptr;
	}
	delete this->mgr;
	delete this->player;
	this->cont = nullptr;
	this->window = nullptr;
	std::cout << "Del game" << std::endl;
}

/**
 *  Runs the game.
 */
void RunGame::run()
{
	this->draw();

	this->score_text.setString("");
	add_objects();
	std::cout << *this->score << std::endl;
	count_score();
	std::cout << *this->score << std::endl;
	delete_objects();

	timelimit -= *delta_time;

	if (timelimit <= 0)
		game_over();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		*cont = WindowContent::pause;
}

/**
 * Gets called to end the game.
 */
void RunGame::game_over() const
{
	*cont = WindowContent::gameover;
}

/**
 * Updates time when time powerup was hit.
 */
void RunGame::powerup_time()
{
	timelimit += 10.0f;
}

void RunGame::powerup_score() const
{
	*this->score += 10;
}
#pragma endregion public methods, constructor, destructor

#pragma  region

/**
 * Draws environmental and player objects, checks collision between player and other objects.
 */
void RunGame::draw_objects_check_collision()
{
	float lowest_obj = plat_buffer.front()->get_position().y;
	for (this->plat_it = this->plat_buffer.begin(); this->plat_it != this->plat_buffer.end(); ++this->plat_it)
	{
		(*this->plat_it)->draw(*this->window);
		this->mgr->manage(this->player, *this->plat_it);
		if ((*this->plat_it)->get_position().y > lowest_obj)
		{
			lowest_obj = (*this->plat_it)->get_position().y;
		}
	}
	for (this->plat_it = this->plat_passed.begin(); this->plat_it != this->plat_passed.end(); ++this->plat_it)
	{
		this->mgr->manage(player, *this->plat_it);
		(*this->plat_it)->draw(*this->window);
		if ((*this->plat_it)->get_position().y > lowest_obj)
		{
			lowest_obj = (*this->plat_it)->get_position().y;
		}
	}
	if (this->player->get_position().y - 250 > lowest_obj)
		this->game_over();

	this->score_text.setString("Score: " + std::to_string(*this->score));
	this->time_text.setString("Zeit: " + std::to_string(this->timelimit));

	this->score_text.setPosition(this->view->getCenter().x + 500, this->view->getCenter().y - 350);
	this->time_text.setPosition(this->view->getCenter().x, this->view->getCenter().y - 350);

	this->player->draw(*this->window);
	this->window->draw(this->score_text);
	this->window->draw(this->time_text);
}

/**
 * Moves the player object, adjusts the view onto the player position.
 */
void RunGame::move_player_set_view() const
{
	this->player->Movement();
	this->view->setCenter(player->get_position());
	this->window->setView(*this->view);
}

/**
 * Creates a new position based on previous object.
 * \param min Minimal (height) distance between new and previous object.
 * \param max maximal distance between new and previous object.
 * \param prev_obj_pos The position of previously created object.
 */
sf::Vector2f RunGame::rand_position(const int min, const int max, const sf::Vector2f prev_obj_pos)
{
	return {prev_obj_pos.x + rand() % max, prev_obj_pos.y + rand() % (max - min + 1) + min};
}

/**
 *  Adds new objects with random position, move them if they collide.
 */
void RunGame::add_objects_to_buffer()
{
	const sf::Vector2f prev_plat_pos = plat_buffer.back()->get_position();

	object* obj;
	if (rand() % 7 == 0)
	{
		if (rand() % 2 == 0)
			obj = new time_powerup(this, rand_position(0, 192, prev_plat_pos), this->file_manager);
		else
			obj = new score_powerup(this, rand_position(0, 192, prev_plat_pos), this->file_manager);
	}
	else
	{
		if (rand() % 10 == 0)
			obj = new level_object(sf::Vector2f(128.0f, 128.0f), rand_position(-192, 192, prev_plat_pos), this->file_manager, object_type::platform_deadly);
		else
			obj = new level_object(sf::Vector2f(128.0f, 128.0f), rand_position(-192, 192, prev_plat_pos), this->file_manager, object_type::platform_regular);
	}
	mgr->manage(obj, plat_buffer.back());
	this->plat_buffer.push_back(obj);
}

/**
 * Checks if objects should be added, adds them if needed.
 */
void RunGame::add_objects()
{
	bool need_more = true;
	while (need_more)
	{
		if (this->plat_buffer.back()->get_position().x < this->player->get_position().x + 1500)
		{
			add_objects_to_buffer();
		}
		else
		{
			need_more = false;
		}
	}
}

/**
 * Deletes objects short after they leave the screen space.
 */
void RunGame::delete_objects()
{
	bool delete_more = true;
	while (delete_more)
	{
		if (!this->plat_passed.empty() && this->plat_passed.front()->get_position().x < this->player->get_position().x - 1500)
		{
			delete this->plat_passed.front();
			this->plat_passed.front() = nullptr;
			this->plat_passed.pop_front();
		}
		else
		{
			delete_more = false;
		}
	}
}

/**
 * Counts the score reached by the player.
 */
void RunGame::count_score()
{
	const int prev_length = this->plat_passed.size();

	while (this->player->get_position().x >= this->plat_buffer.front()->get_position().x + 128)
	{
		plat_passed.push_back(plat_buffer.front());
		plat_buffer.pop_front();
	}

	const int curr_length = this->plat_passed.size();
	const int delta = curr_length - prev_length;
	*this->score += delta;
}

#pragma endregion private methods
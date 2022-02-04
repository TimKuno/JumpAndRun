#pragma once
#include <SFML/Graphics.hpp>
#include "object_type.h"
#include <functional>

class FileManager
{
	typedef std::multimap<int, std::string, std::greater<>> score_map;

public:
	FileManager();
	~FileManager();

	sf::Font& get_font() { return this->font; }
	sf::Texture& get_texture(object_type obj);

	int get_lowest_score() const;

	void add_highscore(int score, std::string name) const;
	std::multimap<int, std::string, std::greater<>>* get_highscores() const;
private:


	void save_highscores() const;
	sf::Font font;
	sf::Texture player_texture;
	sf::Texture platflorm_texture;
	sf::Texture deadly_texture;
	sf::Texture powerup;
	score_map* highscore_map;

	void read_highscores() const;
};

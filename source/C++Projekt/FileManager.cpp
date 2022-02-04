#include "FileManager.h"
#include <iostream>
#include <fstream>
#include "Exception.h"

FileManager::FileManager()
{
	this->highscore_map = new score_map();

	if (!this->font.loadFromFile("resources/font/sansation.ttf"))
		throw FileNotFoundException("Font not found.");
	if (!this->player_texture.loadFromFile("resources/textures/Santa_48x64.png"))
		throw FileNotFoundException("Player texture not found.");
	if (!this->platflorm_texture.loadFromFile("resources/textures/Brick.jpg"))
		throw FileNotFoundException("Platform texture not found.");
	if (!this->deadly_texture.loadFromFile("resources/textures/Brick_deadly.jpg"))
		throw FileNotFoundException("Deadly texture not found.");
	if (!this->powerup.loadFromFile("resources/textures/powerup.png"))
		throw FileNotFoundException("Powerup texture not found.");

	this->read_highscores();

	while (this->highscore_map->size() > 10)
	{
		const score_map::iterator it = --highscore_map->end();
		this->highscore_map->erase(it);
	}
}

sf::Texture& FileManager::get_texture(const object_type obj)
{
	switch (obj)
	{
	case object_type::player:
		return this->player_texture;
		
	case object_type::platform_regular:
		return this->platflorm_texture;

	case object_type::platform_deadly:
		return this->deadly_texture;

	case object_type::powerup:
		return this->powerup;
	}
}

std::multimap<int, std::string, std::greater<>>* FileManager::get_highscores() const
{
	return this->highscore_map;
}

int FileManager::get_lowest_score() const
{
	const score_map::iterator it = --highscore_map->end();
	return it->first;
}

void FileManager::add_highscore(int score, std::string name) const
{
	this->highscore_map->emplace(std::make_pair(score, name));

	while (this->highscore_map->size() > 10)
	{
		const score_map::iterator it = --highscore_map->end();
		this->highscore_map->erase(it);
	}
}

void FileManager::save_highscores() const
{
	std::ofstream file("resources/highscorelist/highscores.txt");

	if (!file)
		throw FileNotFoundException("Highscores not found.");

	for (auto& it : *this->highscore_map)
	{
		std::string str = std::to_string(it.first) + " " + it.second;
		file << str << std::endl;		
	}
	file.close();
}

FileManager::~FileManager()
{
	this->save_highscores();
	delete highscore_map;
	std::cout << "FileMGR DELETED" << std::endl;
}

void FileManager::read_highscores() const
{
	std::ifstream file("resources/highscorelist/highscores.txt");

	if (!file)
		throw FileNotFoundException("Highscores not found.");

	std::string str;

	while (std::getline(file, str))
	{
		if (str.empty())
			break;

		std::string score = str.substr(0, str.find(' '));
		str.erase(0, score.size() + 1);

		this->highscore_map->emplace(std::make_pair(std::stoi(score), str));
	}

	file.close();
}

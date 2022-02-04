#include "Menus.h"
#include <iostream>
#include <thread>
using namespace std;

Highscore::Highscore(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager)
{
	this->file_manager = file_manager;

	this->window = &window;

	this->cont = &cont;
	this->view = new sf::View();
	this->view->setSize(sf::Vector2f(2048.0f, 1024.0f));
	this->view->setCenter(sf::Vector2f(1024.0f, 512.0f));

	this->background.setFillColor(sf::Color::White);
	this->background.setSize(sf::Vector2f(400, 800));
	this->background.setPosition(900, 100);

	this->button1Highscore.setFillColor(default_btn_color);
	this->button1Highscore.setSize(sf::Vector2f(200, 50));
	this->button1Highscore.setPosition(1000, 750);

	this->text1Highscore.setFont(file_manager->get_font());
	this->text1Highscore.setString("Highscores");
	this->text1Highscore.setCharacterSize(20);
	this->text1Highscore.setFillColor(sf::Color::Blue);
	this->text1Highscore.setPosition(1025, 160);

	this->text2Highscore.setFont(file_manager->get_font());
	this->text2Highscore.setCharacterSize(20);
	this->text2Highscore.setFillColor(sf::Color::Blue);

	this->text3Highscore.setFont(file_manager->get_font());
	this->text3Highscore.setString("zurück");
	this->text3Highscore.setCharacterSize(20);
	this->text3Highscore.setFillColor(sf::Color::Blue);
	this->text3Highscore.setPosition(1025, 760);
}

void Highscore::draw()
{
	this->window->setView(*this->view);
	this->window->draw(this->background);
	this->window->draw(this->button1Highscore);
	this->window->draw(this->text1Highscore);
	this->window->draw(this->text3Highscore);
	
	int height = 220;

	for (auto& it : *file_manager->get_highscores())
	{
		std::string str = std::to_string(it.first) + " " + it.second;
		this->text2Highscore.setString(str);
		this->text2Highscore.setPosition(1025, height);
		this->window->draw(this->text2Highscore);
		height += 50;
	}
}

void Highscore::run()
{
	this->button1Highscore.setFillColor(sf::Color::Green);
	const sf::Vector2i position = sf::Mouse::getPosition(*this->window);

	if (position.x >= 1000 && position.x <= 1200 && position.y >= 750 && position.y <= 800)
	{
		button1Highscore.setFillColor(sf::Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
			*this->cont = WindowContent::mainmenu;
		}
	}

	this->draw();
}

Highscore::~Highscore()
{
	delete this->view;
	this->view = nullptr;

	std::cout << "Highscore deleted." << std::endl;
}

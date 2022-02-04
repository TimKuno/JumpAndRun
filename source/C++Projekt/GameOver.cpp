#include "Menus.h"
#include<iostream>
#include <chrono>
#include <thread>
using namespace std;

GameOver::GameOver(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager, int& score)
{
	this->window = &window;
	this->score = &score;
	this->cont = &cont;
	this->file_manager = file_manager;
	this->view = new sf::View();
	this->view->setSize(sf::Vector2f(2048.0f, 1024.0f));
	this->view->setCenter(sf::Vector2f(1024.0f, 512.0f));
	
	this->background.setFillColor(sf::Color::White);
	this->background.setSize(sf::Vector2f(400, 800));
	this->background.setPosition(900, 100);

	this->button1GameOver.setFillColor(default_btn_color);
	this->button1GameOver.setSize(sf::Vector2f(200, 50));
	this->button1GameOver.setPosition(1000, 250);

	this->button2GameOver.setFillColor(default_btn_color);
	this->button2GameOver.setSize(sf::Vector2f(200, 50));
	this->button2GameOver.setPosition(1000, 750);

	this->button3GameOver.setFillColor(default_btn_color);
	this->button3GameOver.setSize(sf::Vector2f(200, 50));
	this->button3GameOver.setPosition(1000, 500);

	this->text1GameOver.setFont(file_manager->get_font());
	this->text1GameOver.setString("GameOver!");
	this->text1GameOver.setCharacterSize(20);
	this->text1GameOver.setFillColor(sf::Color::Blue);
	this->text1GameOver.setPosition(1025, 160);

	this->text2GameOver.setFont(file_manager->get_font());
	this->text2GameOver.setString("Neues Spiel");
	this->text2GameOver.setCharacterSize(20);
	this->text2GameOver.setFillColor(sf::Color::Blue);
	this->text2GameOver.setPosition(1025, 260);

	this->text3GameOver.setFont(file_manager->get_font());
	this->text3GameOver.setString("Hauptmenü");
	this->text3GameOver.setCharacterSize(20);
	this->text3GameOver.setFillColor(sf::Color::Blue);
	this->text3GameOver.setPosition(1025, 760);


	this->text4GameOver.setFont(file_manager->get_font());
	this->text4GameOver.setString("Score speichern");
	this->text4GameOver.setCharacterSize(20);
	this->text4GameOver.setFillColor(sf::Color::Blue);
	this->text4GameOver.setPosition(1025, 510);

	this->playerText.setFont(file_manager->get_font());
	this->playerText.setCharacterSize(20);
	this->playerText.setFillColor(sf::Color::Blue);
	this->playerText.setPosition(1025, 350);
}

void GameOver::draw()
{
	this->window->setView(*this->view);
	this->window->draw(this->background);
	this->window->draw(this->button1GameOver);
	this->window->draw(this->button2GameOver);
	this->window->draw(this->button3GameOver);
	this->window->draw(this->text1GameOver);
	this->window->draw(this->text2GameOver);
	this->window->draw(this->text3GameOver);
	this->window->draw(this->text4GameOver);
}

void GameOver::run()
{
	this->button1GameOver.setFillColor(default_btn_color);
	this->button2GameOver.setFillColor(default_btn_color);
	this->button3GameOver.setFillColor(default_btn_color);

	//Position der Maus
	const sf::Vector2i position = sf::Mouse::getPosition(*this->window);
	//Überprüfe welcher Buttongeklickt wurde
	if (position.x >= 1000 && position.x <= 1200 && position.y >= 250 && position.y <= 300)
	{
		this->button1GameOver.setFillColor(sf::Color::Yellow);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			*this->cont = WindowContent::newgame;
	}
	else if (position.x >= 1000 && position.x <= 1200 && position.y >= 750 && position.y <= 800)
	{
		this->button2GameOver.setFillColor(sf::Color::Yellow);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
			*this->cont = WindowContent::mainmenu;
		}			
	}
	else if (position.x >= 1000 && position.x <= 1200 && position.y >= 500 && position.y <= 550)
	{
		if (*this->score > this->file_manager->get_lowest_score())
		{
			this->button3GameOver.setFillColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}
				*this->cont = WindowContent::add_highscore;
			}				
		}
		else
		{
			this->button3GameOver.setFillColor(sf::Color::Black);
		}
	}

	this->draw();
}

GameOver::~GameOver()
{
	delete this->view;
	this->view = nullptr;

	std::cout << "GameOver deleted." << std::endl;
}

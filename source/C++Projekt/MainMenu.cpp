#include "Menus.h"
#include <iostream>

MainMenu::MainMenu(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager)
{
	this->window = &window;

	this->cont = &cont;
	this->view = new sf::View();
	this->view->setSize(sf::Vector2f(2048.0f, 1024.0f));
	this->view->setCenter(sf::Vector2f(1024.0f, 512.0f));

	this->background.setFillColor(sf::Color::White);
	this->background.setSize(sf::Vector2f(400, 800));
	this->background.setPosition(900, 100);
	
	this->button1MainMenu.setFillColor(default_btn_color);
	this->button1MainMenu.setSize(sf::Vector2f(200, 50));
	this->button1MainMenu.setPosition(1000, 250);

	this->button2MainMenu.setFillColor(default_btn_color);
	this->button2MainMenu.setSize(sf::Vector2f(200, 50));
	this->button2MainMenu.setPosition(1000, 500);

	this->button3MainMenu.setFillColor(default_btn_color);
	this->button3MainMenu.setSize(sf::Vector2f(200, 50));
	this->button3MainMenu.setPosition(1000, 750);

	this->text1MainMenu.setFont(file_manager->get_font());
	this->text1MainMenu.setString("Hauptmenü");
	this->text1MainMenu.setCharacterSize(20);
	this->text1MainMenu.setFillColor(sf::Color::Blue);
	this->text1MainMenu.setPosition(1025, 160);

	this->text2MainMenu.setFont(file_manager->get_font());
	this->text2MainMenu.setString("Spiel Starten");
	this->text2MainMenu.setCharacterSize(20);
	this->text2MainMenu.setFillColor(sf::Color::Blue);
	this->text2MainMenu.setPosition(1025, 260);

	this->text3MainMenu.setFont(file_manager->get_font());
	this->text3MainMenu.setString("Highscoreliste");
	this->text3MainMenu.setCharacterSize(20);
	this->text3MainMenu.setFillColor(sf::Color::Blue);
	this->text3MainMenu.setPosition(1025, 510);

	this->text4MainMenu.setFont(file_manager->get_font());
	this->text4MainMenu.setString("Programm beenden");
	this->text4MainMenu.setCharacterSize(20);
	this->text4MainMenu.setFillColor(sf::Color::Blue);
	this->text4MainMenu.setPosition(1025, 760);
}

void MainMenu::draw()
{
	this->window->setView(*this->view);
	this->window->draw(this->background);
	this->window->draw(this->button1MainMenu);
	this->window->draw(this->button2MainMenu);
	this->window->draw(this->button3MainMenu);
	this->window->draw(this->text1MainMenu);
	this->window->draw(this->text2MainMenu);
	this->window->draw(this->text3MainMenu);
	this->window->draw(this->text4MainMenu);
}

void MainMenu::run()
{
	this->button1MainMenu.setFillColor(default_btn_color);
	this->button2MainMenu.setFillColor(default_btn_color);
	this->button3MainMenu.setFillColor(default_btn_color);
	
	//Position der Maus
	const sf::Vector2i position = sf::Mouse::getPosition(*this->window);
	//Überprüfe welcher Buttongeklickt wurde
	if (position.x >= 1000 && position.x <= 1200 && position.y >= 250 && position.y <= 300)
	{
		this->button1MainMenu.setFillColor(sf::Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			*this->cont = WindowContent::newgame;
	}
	else if (position.x >= 1000 && position.x <= 1200 && position.y >= 500 && position.y <= 550)
	{
		button2MainMenu.setFillColor(sf::Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			*this->cont = WindowContent::highscore;
	}
	else if (position.x >= 1000 && position.x <= 1200 && position.y >= 750 && position.y <= 800)
	{
		button3MainMenu.setFillColor(sf::Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			*this->cont = WindowContent::quit;
	}
	this->draw();
}

MainMenu::~MainMenu()
{
	delete this->view;
	this->view = nullptr;

	std::cout << "MainMenu deleted." << std::endl;
}

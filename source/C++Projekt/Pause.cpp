#include "Menus.h"
#include <iostream>

Pause::Pause(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager)
{
	this->window = &window;

	this->cont = &cont;
	this->view = new sf::View();
	this->view->setSize(sf::Vector2f(2048.0f, 1024.0f));
	this->view->setCenter(sf::Vector2f(1024.0f, 512.0f));


	this->button1Pause.setFillColor(this->default_btn_color);
	this->button1Pause.setSize(sf::Vector2f(200, 50));
	this->button1Pause.setPosition(1000, 250);

	this->button2Pause.setFillColor(this->default_btn_color);
	this->button2Pause.setSize(sf::Vector2f(200, 50));
	this->button2Pause.setPosition(1000, 500);

	this->background.setFillColor(sf::Color::White);
	this->background.setSize(sf::Vector2f(400, 500));
	this->background.setPosition(900, 100);

	this->text1Pause.setFont(file_manager->get_font());
	this->text1Pause.setString("Das Spiel wurde pausiert!");
	this->text1Pause.setCharacterSize(20);
	this->text1Pause.setFillColor(sf::Color::Blue);
	this->text1Pause.setPosition(1025, 160);

	this->text2Pause.setFont(file_manager->get_font());
	this->text2Pause.setString("Spiel fortsetzen");
	this->text2Pause.setCharacterSize(20);
	this->text2Pause.setFillColor(sf::Color::Blue);
	this->text2Pause.setPosition(1025, 260);

	this->text3Pause.setFont(file_manager->get_font());
	this->text3Pause.setString("Spiel beenden");
	this->text3Pause.setCharacterSize(20);
	this->text3Pause.setFillColor(sf::Color::Blue);
	this->text3Pause.setPosition(1025, 510);
}

void Pause::draw()
{
	this->window->setView(*this->view);
	this->window->draw(this->background);
	this->window->draw(this->button1Pause);
	this->window->draw(this->button2Pause);
	this->window->draw(this->text1Pause);
	this->window->draw(this->text2Pause);
	this->window->draw(this->text3Pause);
}

void Pause::run()
{
	this->button1Pause.setFillColor(this->default_btn_color);
	this->button2Pause.setFillColor(this->default_btn_color);

	//Position der Maus
	const sf::Vector2i position = sf::Mouse::getPosition(*this->window);
	//Überprüfe welcher Buttongeklickt wurde
	if (position.x >= 1000 && position.x <= 1200 && position.y >= 250 && position.y <= 300)
	{
		button1Pause.setFillColor(sf::Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			*this->cont = WindowContent::game;
	}
	else if (position.x >= 1000 && position.x <= 1200 && position.y >= 500 && position.y <= 550)
	{
		button2Pause.setFillColor(sf::Color::Yellow);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			*this->cont = WindowContent::quit;
	}
	this->draw();
}

Pause::~Pause()
{
	delete this->view;
	this->view = nullptr;

	std::cout << "Pause deleted." << std::endl;
}

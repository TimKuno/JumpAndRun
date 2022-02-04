#include "Menus.h"
#include <chrono>
#include <thread>

NewHighscore::NewHighscore(WindowContent& cont, const std::shared_ptr<FileManager>& file_manager, int& score, sf::RenderWindow& window)
{
	this->cont = &cont;
	this->window = &window;
	this->file_manager = file_manager;
	this->score = &score;

	this->view = new sf::View();
	this->view->setSize(sf::Vector2f(2048.0f, 1024.0f));
	this->view->setCenter(sf::Vector2f(1024.0f, 512.0f));

	this->background.setFillColor(sf::Color::White);
	this->background.setSize(sf::Vector2f(400, 800));
	this->background.setPosition(900, 100);

	this->button_save.setFillColor(default_btn_color);
	this->button_save.setSize(sf::Vector2f(200, 50));
	this->button_save.setPosition(1000, 500);

	this->button_home.setFillColor(default_btn_color);
	this->button_home.setSize(sf::Vector2f(200, 50));
	this->button_home.setPosition(1000, 750);

	this->headline.setFont(file_manager->get_font());
	this->headline.setString("Namen eingeben:");
	this->headline.setCharacterSize(20);
	this->headline.setFillColor(sf::Color::Blue);
	this->headline.setPosition(1025, 160);


	this->button_save_text.setFont(file_manager->get_font());
	this->button_save_text.setString("Speichern");
	this->button_save_text.setCharacterSize(20);
	this->button_save_text.setFillColor(sf::Color::Blue);
	this->button_save_text.setPosition(1025, 510);


	this->button_home_text.setFont(file_manager->get_font());
	this->button_home_text.setString("Hauptmenü");
	this->button_home_text.setCharacterSize(20);
	this->button_home_text.setFillColor(sf::Color::Blue);
	this->button_home_text.setPosition(1025, 760);

	this->input.setFont(file_manager->get_font());
	this->input.setString(" - - - ");
	this->input.setCharacterSize(20);
	this->input.setFillColor(sf::Color::Blue);
	this->input.setPosition(1025, 260);
}

void NewHighscore::draw()
{
	this->window->setView(*this->view);
	this->window->draw(this->background);
	this->window->draw(this->button_save);
	this->window->draw(this->button_home);
	this->window->draw(this->headline);
	this->window->draw(this->button_save_text);
	this->window->draw(this->button_home_text);
	this->window->draw(this->input);
}


void NewHighscore::run()
{
	sf::Event event{};
	std::string str;
	while (*cont == WindowContent::add_highscore)
	{
		window->clear();

		this->button_home.setFillColor(default_btn_color);
		this->button_save.setFillColor(default_btn_color);
		const sf::Vector2i position = sf::Mouse::getPosition(*this->window);

		if (position.x >= 1000 && position.x <= 1200 && position.y >= 500 && position.y <= 550 && !saved)
		{
			this->button_save.setFillColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && input.getString() != " - - - ")
			{
				this->file_manager->add_highscore(*score, input.getString());
				this->button_save_text.setString("Gespeichert!");
				this->saved = true;
			}
		}
		else if (position.x >= 1000 && position.x <= 1200 && position.y >= 750 && position.y <= 800)
		{
			this->button_home.setFillColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}
				*this->cont = WindowContent::mainmenu;
			}
		}
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					str += event.text.unicode;
					input.setString(str);
				}
			}
		}
		this->draw();
		window->display();
	}
}

NewHighscore::~NewHighscore()
{
	this->score = nullptr;
	file_manager.reset();
}
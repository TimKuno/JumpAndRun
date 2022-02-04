#include "Menus.h"
#include <iostream>
#include <chrono>
#include <thread>

void Error(sf::RenderWindow& window, const std::string& error_msg)
{
	if (error_msg == "Font not found.")
	{
		window.close();
		std::cout << error_msg << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(20000));
	}

	sf::View view;
	view.setSize(sf::Vector2f(2048.0f, 1024.0f));
	view.setCenter(sf::Vector2f(1024.0f, 512.0f));

	sf::RectangleShape background;
	background.setFillColor(sf::Color::White);
	background.setSize(sf::Vector2f(400, 800));
	background.setPosition(900, 100);
	sf::Event event{};

	sf::RectangleShape button;
	button.setFillColor(sf::Color::Green);
	button.setSize(sf::Vector2f(200, 50));
	button.setPosition(1000, 750);

	sf::Text button_text;
	sf::Font font;
	font.loadFromFile("resources/font/sansation.ttf");
	button_text.setFont(font);
	button_text.setString("Programm beenden");
	button_text.setCharacterSize(20);
	button_text.setFillColor(sf::Color::Blue);
	button_text.setPosition(1025, 760);

	sf::Text msg;
	msg.setFont(font);
	msg.setString(error_msg);
	msg.setCharacterSize(20);
	msg.setFillColor(sf::Color::Red);
	msg.setPosition(1000, 250);
	while (window.isOpen())
	{
		window.clear();
		window.setView(view);
		button.setFillColor(sf::Color::Green);

		const sf::Vector2i position = sf::Mouse::getPosition(window);
		if (position.x >= 1000 && position.x <= 1200 && position.y >= 750 && position.y <= 800)
		{
			button.setFillColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.close();
				exit(0);
			}
		}

		window.draw(background);
		window.draw(button);
		window.draw(button_text);
		window.draw(msg);
		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
	}
}

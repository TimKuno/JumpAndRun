#include <SFML/Graphics.hpp>
#include "RunGame.h"
#include <thread>
#include "WindowContent.h"
#include "Menus.h"
#include <unordered_map>
#include "FileManager.h"
#include <iostream>
#include "Exception.h"

int main()
{
	typedef std::unordered_map<WindowContent, std::unique_ptr<Screens>> screen;
	typedef std::pair<WindowContent, std::unique_ptr<Screens>> pair;

	sf::RenderWindow window(sf::VideoMode(2048, 1024), "C++ Projekt", sf::Style::Close);
	WindowContent cont = WindowContent::mainmenu;
	std::shared_ptr<FileManager> filemgr;

	try
	{
		filemgr = std::make_shared<FileManager>();
	} 
	catch (FileNotFoundException& file_not_found_exception)
	{
		Error(window, file_not_found_exception.get_error());
	}
	

	screen* screens = new screen();

	int score = 0;
	float delta_time;

	if (filemgr != nullptr)
	{
		screens->emplace(pair(WindowContent::mainmenu, std::make_unique<MainMenu>(cont, window, filemgr)));
		screens->emplace(pair(WindowContent::pause, std::make_unique<Pause>(cont, window, filemgr)));
		screens->emplace(pair(WindowContent::highscore, std::make_unique<Highscore>(cont, window, filemgr)));
		screens->emplace(pair(WindowContent::gameover, std::make_unique<GameOver>(cont, window, filemgr, score)));
		screens->emplace(pair(WindowContent::game, std::make_unique<RunGame>(cont, delta_time, score, window, filemgr)));
		screens->emplace(pair(WindowContent::add_highscore, std::make_unique<NewHighscore>(cont, filemgr, score, window)));
	}

	sf::Clock clock;
	
	sf::Event event{};

	while (window.isOpen())
	{
		window.clear();

		delta_time = clock.restart().asSeconds();

		switch (cont)
		{
		case WindowContent::newgame: 		
			screens->at(WindowContent::game) = std::make_unique<RunGame>(cont, delta_time, score, window, filemgr);
			score = 0;
			cont = WindowContent::game;
			break;

		case WindowContent::quit:
			window.close();
			break;

		default:
			screens->at(cont)->run();
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			cont = WindowContent::newgame;
	}

	delete screens;
	filemgr.reset();
	return 0;
}

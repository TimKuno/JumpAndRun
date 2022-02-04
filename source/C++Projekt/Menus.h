#pragma once
#include <SFML/Graphics.hpp>
#include "WindowContent.h"
#include "FileManager.h"

class Screens
{
public:
	virtual ~Screens() = default;
	virtual void run() {}

private:
	virtual void draw() {}
};

class Menu : public Screens
{
public:
	~Menu() override = default;
	void run() override {}

private:
	void draw() override {}

protected:
	sf::RenderWindow* window = nullptr;
	sf::View* view = nullptr;
	WindowContent* cont = nullptr;
	sf::RectangleShape background;
	const sf::Color default_btn_color = sf::Color::Green;
};

class MainMenu : public Menu
{
public:
	explicit MainMenu(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager);
	void run() override;
	~MainMenu() override;

private:
	void draw() override;

	sf::RectangleShape button1MainMenu;
	sf::RectangleShape button2MainMenu;
	sf::RectangleShape button3MainMenu;
	sf::Text text1MainMenu;
	sf::Text text2MainMenu;
	sf::Text text3MainMenu;
	sf::Text text4MainMenu;
};

class GameOver : public Menu
{
public:
	explicit GameOver(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager, int& score);
	void run() override;
	~GameOver() override;

private:
	void draw() override;

	sf::RectangleShape button1GameOver;
	sf::RectangleShape button2GameOver;
	sf::RectangleShape button3GameOver;
	sf::Text text1GameOver;
	sf::Text text2GameOver;
	sf::Text text3GameOver;
	sf::Text text4GameOver;
	sf::String playerInput;
	sf::Text playerText;
	std::shared_ptr<FileManager> file_manager;
	int* score;
};

class Pause : public Menu
{
public:
	explicit Pause(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager);
	void run() override;
	~Pause() override;

private:
	void draw() override;

	sf::RectangleShape button1Pause;
	sf::RectangleShape button2Pause;
	sf::RectangleShape backgroundPause;
	sf::Text text1Pause;
	sf::Text text2Pause;
	sf::Text text3Pause;
};

class Highscore : public Menu
{
public:
	explicit Highscore(WindowContent& cont, sf::RenderWindow& window, const std::shared_ptr<FileManager>& file_manager);
	void run() override;
	~Highscore() override;

private:
	void draw() override;

	std::shared_ptr<FileManager> file_manager;

	sf::RectangleShape button1Highscore;
	sf::Text text1Highscore;
	sf::Text text2Highscore;
	sf::Text text3Highscore;
};

class NewHighscore : public Menu
{
public:
	NewHighscore(WindowContent& cont, const std::shared_ptr<FileManager>& file_manager, int& score, sf::RenderWindow& window);
	void run() override;
	~NewHighscore() override;

private:
	bool saved = false;
	void draw() override;
	std::shared_ptr<FileManager> file_manager;
	int* score;
	sf::RectangleShape button_home;
	sf::RectangleShape button_save;
	sf::Text button_home_text;
	sf::Text button_save_text;
	sf::Text input;
	sf::Text headline;
};

void Error(sf::RenderWindow& window, const std::string& error_msg);
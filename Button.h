#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <algorithm>
class Button
{
private:
public:
	// Different types of buttons for the ui
	/*question */ Button(sf::Vector2f,int,sf::Font&);
	/*category */ Button(sf::Vector2f, std::string, sf::Font&);
	/*special */ Button(sf::Vector2f, std::string, sf::Font&, bool);
	bool askQuestion();

	//Variables that are stored inside of each button
	sf::RectangleShape button;
	sf::Text number;
	std::string question;
	std::string answer;
	
	// boolean variables to aid in logic for clicking
	bool clicked;
	bool category;
	bool special;
};





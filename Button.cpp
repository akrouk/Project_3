#include "Button.h"

//Button for the questions
Button::Button(sf::Vector2f vec, int value, sf::Font& font)
{
	sf::Vector2f size = sf::Vector2f(225.0f, 75.0f);
	button.setPosition(vec);
	button.setSize(size);
	button.setFillColor(sf::Color::Blue);
	clicked = false;
	category = false;
	number.setFont(font);
	number.setPosition(sf::Vector2f(vec.x+80.0f,vec.y+15.0f));
	number.setFillColor(sf::Color::Yellow);
	number.setString(std::to_string(value));
	number.setCharacterSize(40);
	special = false;
}

//Button for catagories
Button::Button(sf::Vector2f vec, std::string category, sf::Font& font)
{
	sf::Vector2f size = sf::Vector2f(225.0f, 75.0f);
	button.setPosition(vec);
	button.setSize(size);
	button.setFillColor(sf::Color::Blue);
	clicked = true;
	this->category = true;
	number.setFont(font);
	number.setPosition(sf::Vector2f(vec.x + 25.0f, vec.y + 25.0f));
	number.setFillColor(sf::Color::White);
	number.setOutlineColor(sf::Color::Black);
	number.setOutlineThickness(0.5f);
	number.setString(category);
	number.setCharacterSize(24);
	special = false;
}

//Button for Hash and Tree reloads
Button::Button(sf::Vector2f vec, std::string text, sf::Font& font, bool special)
{
	sf::Vector2f size = sf::Vector2f(100.0f, 50.0f);
	button.setPosition(vec);
	button.setSize(size);
	button.setFillColor(sf::Color::Blue);
	clicked = true;
	this->category = false;
	number.setFont(font);
	number.setPosition(sf::Vector2f(vec.x + 25.0f, vec.y + 25.0f));
	number.setFillColor(sf::Color::White);
	number.setString(text);
	number.setCharacterSize(24);
	this->special = special;
}

 bool Button::askQuestion()
{
	std::string playeranswer;
	std::string dummy_answer = answer;

	//Displays question to player
	std::cout << question << std::endl;

	//Gets input and based on the comparison between a lowercase version of both input and answer, will return true or false
	std::getline(std::cin, playeranswer);
	std::transform(dummy_answer.begin(), dummy_answer.end(), dummy_answer.begin(), ::tolower);
	std::transform(playeranswer.begin(), playeranswer.end(), playeranswer.begin(), ::tolower);
	if (dummy_answer == playeranswer)
	{
		std::cout << "Correct!" << std::endl;
		return true;
	}
	std::cout << "Incorrect!  The correct answer was: " << answer << std::endl;
	return false;
}





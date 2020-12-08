#pragma once
#include "Button.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include "JeopardyData.h"
class Menu
{
private:
	//Contains the Jeopardy questions stored inside of both an ordered and unordered map
	JeopardyData data;
	
	//All the ui elements in a container or seperate depending on whether they have special funcitonality
	sf::Font font;
	sf::Text header;
	sf::Text scoreText;
	std::vector<std::vector<Button>> buttons;
	std::vector<Button> special;

	//Player's score
	int score;

	//Functions to initialize board and special buttons in different ways
	void initializeSpecial();
	void initializeQuestions();
	void initializeQuestionsUnordered();
	void initializeQuestionsOrdered();

	void checkComplete();
public:
	Menu();
	//Used to check if an element is clicked
	void checkClick(sf::Vector2f);

    //Function to draw all elements to the screen
	void Draw(sf::RenderWindow&);
};





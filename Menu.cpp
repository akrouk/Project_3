#include "Menu.h"


void Menu::checkClick(sf::Vector2f pos)
{
	//Loop through all the questions and ask question, apply score whether right or wrong
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		for (unsigned int j = 0; j < buttons[i].size(); j++)
		{
			if (buttons[i].at(j).button.getGlobalBounds().contains(pos) && !buttons[i].at(j).clicked)
			{
				buttons[i].at(j).clicked = true;
				if (buttons[i].at(j).askQuestion())
					score += j * 100;
				else
					score -= j * 100;
				scoreText.setString("Score: " + std::to_string(score));
			}
		}
	}
	//Check if either special button is clicked
	if (special[1].button.getGlobalBounds().contains(pos))
		this->initializeQuestionsOrdered();
	if (special[0].button.getGlobalBounds().contains(pos))
		this->initializeQuestionsUnordered();
	//Check if the board is cleared
	this->checkComplete();
}

//Initialize the UI for the special buttons
void Menu::initializeSpecial()
{
	Button hash(sf::Vector2f(1280.0f, 0.0f), "Hash", font, true);
	Button tree(sf::Vector2f(1180.0f, 0.0f), "Tree", font, true);
	special.push_back(hash);
	special.push_back(tree);
}

//Unordered Version
void Menu::initializeQuestionsUnordered()
{
	//Clear the buttons vector if its full
	buttons.clear();

	//Find random catagories to use for the round
	std::vector<std::string> categories = data.RandCategories();

	//Loop through the board and apply the questions to each of the buttons
	for (int i = 0; i < 5; i++)
	{
		std::vector<Button> s_buttons;
		Button catagory(sf::Vector2f((i + 1) * 250.0f, 150.0f),categories[i], this->font);
		std::vector<JeopardyQ> cur_category = data.FindUnordered(categories[i]);
		s_buttons.push_back(catagory);
		for (int j = 1; j < 6; j++)
		{
			Button button(sf::Vector2f((i+1) * 250.0f, (j + 1) * 130.0f),(j) * 100.0f, this->font);
			button.question = cur_category[j-1][5];
			button.answer = cur_category[j-1][6];
			s_buttons.push_back(button);
		}
		buttons.push_back(s_buttons);
	}
}

//Ordered version
void Menu::initializeQuestionsOrdered()
{
	//Clear the buttons vector if its full
	buttons.clear();

	//Find random catagories to use for the round
	std::vector<std::string> categories = data.RandCategories();

	//Loop through the board and apply the questions to each of the buttons
	for (int i = 0; i < 5; i++)
	{
		std::vector<Button> s_buttons;
		Button catagory(sf::Vector2f((i + 1) * 250.0f, 150.0f), categories[i], this->font);
		std::vector<JeopardyQ> cur_category = data.FindOrdered(categories[i]);
		s_buttons.push_back(catagory);
		for (int j = 1; j < 6; j++)
		{
			Button button(sf::Vector2f((i + 1) * 250.0f, (j + 1) * 130.0f), (j) * 100.0f, this->font);
			button.question = cur_category[j - 1][5];
			button.answer = cur_category[j - 1][6];
			s_buttons.push_back(button);
		}
		buttons.push_back(s_buttons);
	}
}

//Both Unordered and Ordered
void Menu::initializeQuestions()
{
	//Clear the buttons vector if its full
	buttons.clear();

	//Find random catagories to use for the round
	std::vector<std::string> categories = data.RandCategories();

	//Loop through the board and apply the questions to each of the buttons
	for (int i = 0; i < 5; i++)
	{
		std::vector<Button> s_buttons;
		Button catagory(sf::Vector2f((i + 1) * 250.0f, 150.0f), categories[i], this->font);
		std::vector<JeopardyQ> cur_category = data.Find(categories[i]);
		s_buttons.push_back(catagory);
		for (int j = 1; j < 6; j++)
		{
			Button button(sf::Vector2f((i + 1) * 250.0f, (j + 1) * 130.0f), (j) * 100.0f, this->font);
			button.question = cur_category[j - 1][5];
			button.answer = cur_category[j - 1][6];
			s_buttons.push_back(button);
		}
		buttons.push_back(s_buttons);
	}
}

//Initialzie all the UI for the board (including the header and the score)
Menu::Menu()
{
	score = 0;
	font.loadFromFile("gyparody.ttf");
	header.setFont(font);
	header.setString("Jeopardy");
	header.setPosition(750.0f, 0.0f);
	header.setCharacterSize(90);
	header.setFillColor(sf::Color::White);
	header.setOutlineColor(sf::Color::Black);
	header.setOutlineThickness(0.5f);
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setPosition(1550.0f, 900.0f);
	scoreText.setCharacterSize(70);
	scoreText.setFillColor(sf::Color::White);
	this->initializeSpecial();
	this->initializeQuestions();
}

//Draws all of the elements to the screen
void Menu::Draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		for (unsigned int j = 0; j < buttons.at(i).size(); j++)
		{
			window.draw(buttons.at(i).at(j).button);
			if(!buttons[i].at(j).clicked || buttons[i].at(j).category)
				window.draw(buttons.at(i).at(j).number);
			window.draw(special.at(0).button);
			window.draw(special.at(1).button);
			window.draw(special.at(0).number);
			window.draw(special.at(1).number);
			window.draw(header);
			window.draw(scoreText);
		}
	}
}


void Menu::checkComplete()
{
	//Checks if all of the questions have been answered
	for (unsigned int i = 0; i < buttons.size(); i++)
	{
		for (unsigned int j = 0; j < buttons[i].size(); j++)
		{
			if (!buttons.at(i).at(j).clicked && !buttons.at(i).at(j).category)
				return;
		}
	}
	//Reinitializes the board with or without the score based on user input
	char letter;
	std::cout << "Congratulations! Your score was: " << score << std::endl;
	std::cout << "Would you like to continue with or without your score? (y/n)";
	std::cin >> letter;
	if (letter == 'y')
		this->initializeQuestions();
	else if (letter == 'n')
	{
		score = 0;
		this->initializeQuestions();
	}
}

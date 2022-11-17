#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	x = Length / 2;
	y = 10;

	color = sf::Color(0, 0, 255);

	total_score = 0;
}

void Scoreboard::set_total_score(int _total_score)
{
	total_score = _total_score;
}

void Scoreboard::add_point()
{
	++total_score;
}

void Scoreboard::reset()
{
	x = Length / 2;
	y = 10;

	color = sf::Color(0, 0, 255);

	total_score = 0;
}

void Scoreboard::draw()
{
	sf::Text text;
}
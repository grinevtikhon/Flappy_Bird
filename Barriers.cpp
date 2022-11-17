#include "Barriers.h"

Barriers::Barriers()
{
	first_element = 0;

	generate_pipes();
	update_pipes();


}

void Barriers::generate_pipes()
{
	amount = Length / horizontal_distance + 5;

	for (int i = 0; i < amount; ++i)
		pipes.push_back({ Pipe(), Pipe() });

}

void Barriers::next_tick()
{
	for (int i = 0; i < amount; ++i)
	{
		pipes[i].first.next_tick();
		pipes[i].second.next_tick();
	}

	update_pipes();

	return;
}

void Barriers::update_pipes()
{

	while (true)
	{
		if (pipes[first_element].first.x2 > -horizontal_distance)
			break;

		int x = max(pipes[((first_element - 1) % amount + amount) % amount].first.x2 + horizontal_distance, 1.5 * Length);
		int y = rand() % (Height - 2 * min_dist) + min_dist;

		pipes[first_element].first.set_position(x, 0, y - vertical_distance / 2);
		pipes[first_element].second.set_position(x, Height, y + vertical_distance / 2);

		first_element = ((first_element + 1) % amount + amount) % amount;

	}

	return;

}

void Barriers::stop_pipes()
{
	for (int i = 0; i < amount; ++i)
	{
		pipes[i].first.stop();
		pipes[i].second.stop();
	}

	return;
}

void Barriers::start_pipes()
{
	for (int i = 0; i < amount; ++i)
	{
		pipes[i].first.start();
		pipes[i].second.start();
	}

	return;
}

void Barriers::reset()
{
	pipes.resize(0);

	amount = Length / horizontal_distance + 5;

	for (int i = 0; i < amount; ++i)
		pipes.push_back({ Pipe(), Pipe() });

	update_pipes();

	return;
}

void Barriers::draw_pipes(sf::RenderWindow& _window)
{
	for (int i = 0; i < amount; ++i)
	{
		pipes[i].first.draw(_window);
		pipes[i].second.draw(_window);
	}

	return;
}

void Barriers::draw_grass(sf::RenderWindow& _window)
{
	sf::RectangleShape ground;
	ground.setPosition(0, Height - high_grass);
	ground.setSize(sf::Vector2f(Length, high_grass));
	ground.setFillColor(sf::Color(65, 25, 0));
	_window.draw(ground);

	return;
}

void Barriers::draw_all(sf::RenderWindow& _window)
{
	draw_pipes(_window);
	draw_grass(_window);

	return;
}
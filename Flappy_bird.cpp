#include "Flappy_bird.h"

Flappy_bird::Flappy_bird()
{

	between_roof = 0;
	between_floor = 0;
	x_to_pipe = 0;
	y_to_roof_pipe = 0;
	y_to_floor_pipe = 0;

	information.resize(5, 0.0);

	r = 27;
	v_x = 0;
	v_y = 0;
	x = Length / 2;
	y = Height / 2;
	alive = true;
	color = sf::Color::Yellow;

	score = 0;
}

void Flappy_bird::reset()
{
	r = 27;
	v_x = 0;
	v_y = 0;
	x = Length / 2;
	y = Height / 2;
	alive = true;
	color = sf::Color::Yellow;

	score = 0;

	return;
}

void Flappy_bird::next_tick()
{
	y = y + v_y * tick + ((g * tick * tick) / 2.0f);
	v_y = v_y + g * tick;
	//x = x + v_x * tick;
	if (y > Height - high_grass - r) {
		v_y = -abs(v_y) * 0.4;
		y = Height - high_grass - r;
	}
	if (y < 0) {
		v_y = abs(v_y);
		y = r;
	}
	//if (x > Length) {
	//	v_x = -abs(v_x);
	//}
	//if (x < 0) {
	//	v_x = abs(v_x);
	//}

	if (alive)
		score += tick;

	return;
}

void Flappy_bird::jump()
{
	if (alive == false) {
		return;
	}

	v_y = -700;

	return;
}

void Flappy_bird::die()
{
	//jump();

	alive = false;

	color = sf::Color::Red;

	return;
}

bool Flappy_bird::bird_touch_pipe(Pipe& _p)
{
	if (x < _p.x1) {
		if (y < _p.y1) {
			if ((x - _p.x1) * (x - _p.x1) + (y - _p.y1) * (y - _p.y1) < r * r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (_p.y1 <= y && y <= _p.y2) {
			if (_p.x1 - x < r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (_p.y2 < y) {
			if ((x - _p.x1) * (x - _p.x1) + (y - _p.y2) * (y - _p.y2) < r * r) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	if (_p.x1 <= x && x <= _p.x2) {
		if (y < _p.y1) {
			if (_p.y1 - y < r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (_p.y1 <= y && y <= _p.y2) {
			return true;
		}
		if (_p.y2 < y) {
			if (y - _p.y2 < r) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	if (_p.x2 < x) {
		if (y < _p.y1) {
			if ((x - _p.x2) * (x - _p.x2) + (y - _p.y1) * (y - _p.y1) < r * r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (_p.y1 <= y && y <= _p.y2) {
			if (x - _p.x2 < r) {
				return true;
			}
			else {
				return false;
			}
		}
		if (_p.y2 < y) {
			if ((x - _p.x2) * (x - _p.x2) + (y - _p.y2) * (y - _p.y2) < r * r) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void Flappy_bird::check_bird_with_barriers(Barriers _bar)
{
	int ans = false;

	if (y + r >= Height - high_grass) {
		ans = true;
	}

	for (int i = 0; i < _bar.amount; ++i)
	{
		if (alive == true && ans == false && bird_touch_pipe(_bar.pipes[i].first))
			ans = true;

		if (alive == true && ans == false && bird_touch_pipe(_bar.pipes[i].second))
			ans = true;
	}

	if (ans)
		die();
}

void Flappy_bird::draw(sf::RenderWindow& _window)
{
	sf::CircleShape circle(r);

	circle.setOutlineThickness(2);
	circle.setOutlineColor(sf::Color(153, 0, 153));
	circle.setFillColor(color);
	circle.setPosition(x - r, y - r);
	_window.draw(circle);

	return;

}

void Flappy_bird::update_between_roof()
{
	between_roof = y;
}

void Flappy_bird::update_between_floor()
{
	between_floor = Height - y;
}

void Flappy_bird::update_x_to_pipe(Barriers &_bar)
{
	double ans = 100000;
	for (int i = 0; i < _bar.pipes.size(); ++i)
	{
		if (_bar.pipes[i].first.x2 > x)
			ans = min(ans, _bar.pipes[i].first.x2 - x);
	}

	x_to_pipe = ans;
}

void Flappy_bird::update_y_to_roof_pipe(Barriers& _bar)
{
	double ans = 100000;
	for (int i = 0; i < _bar.pipes.size(); ++i)
	{
		if (_bar.pipes[i].first.x2 > x && ans > _bar.pipes[i].first.x2 - x)
		{
			ans = _bar.pipes[i].first.x2 - x;
			y_to_roof_pipe = y - _bar.pipes[i].first.y2;
		}
	}
}

void Flappy_bird::update_y_to_floor_pipe(Barriers& _bar)
{
	double ans = 100000;
	for (int i = 0; i < _bar.pipes.size(); ++i)
	{
		if (_bar.pipes[i].first.x2 > x && ans > _bar.pipes[i].first.x2 - x)
		{
			ans = _bar.pipes[i].first.x2 - x;
			y_to_floor_pipe = _bar.pipes[i].second.y1 - y - r;
		}
	}
}

void Flappy_bird::update_information(Barriers& _bar)
{
	if (information.size() != 5)
		information.resize(5);

	update_between_roof();
	update_between_floor();
	update_x_to_pipe(_bar);
	update_y_to_roof_pipe(_bar);
	update_y_to_floor_pipe(_bar);

	information[0] = between_roof;
	information[1] = between_floor;
	information[2] = x_to_pipe;
	information[3] = y_to_roof_pipe;
	information[4] = y_to_floor_pipe;

}
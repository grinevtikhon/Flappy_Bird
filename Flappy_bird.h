#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
#include <queue>

#include "Pipe.h"
#include "Barriers.h"

using namespace std;

class Flappy_bird
{

public:

	const double g = 2400;

	const double tick = 0.004f;

	const int Height = 720;
	const int Length = 1080;

	const int high_grass = 50;



	double r;
	double v_x, v_y;
	double x, y;

	bool alive;

	double score;

	sf::Color color;

	Flappy_bird();

	void reset();

	void next_tick();

	void jump();

	void die();

	bool bird_touch_pipe(Pipe& _p);

	void check_bird_with_barriers(Barriers _bar);

	void draw(sf::RenderWindow &_window);
};

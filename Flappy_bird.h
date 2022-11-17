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


#include "MyCostants.h"

#include "Pipe.h"
#include "Barriers.h"

using namespace std;

class Flappy_bird
{

public:


	double r;
	double v_x, v_y;
	double x, y;

	bool alive;

	double score;

	double between_roof;
	double between_floor;
	double x_to_pipe;
	double y_to_roof_pipe;
	double y_to_floor_pipe;

	vector<double> information;

	sf::Color color;

	Flappy_bird();

	void reset();

	void next_tick();

	void jump();

	void die();

	bool bird_touch_pipe(Pipe& _p);

	void check_bird_with_barriers(Barriers _bar);

	void draw(sf::RenderWindow &_window);

	void update_between_roof();

	void update_between_floor();

	void update_x_to_pipe(Barriers &_bar);

	void update_y_to_roof_pipe(Barriers& _bar);

	void update_y_to_floor_pipe(Barriers& _bar);

	void update_information(Barriers& _bar);

};

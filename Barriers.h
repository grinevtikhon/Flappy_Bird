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

using namespace std;

class Barriers
{

public:

	const double tick = 0.004f;

	const int Height = 720;
	const int Length = 1080;

	const int high_grass = 50;

	const int min_dist = 200;
	const double width_pipe = 100;
	const double horizontal_distance = 300;
	const double vertical_distance = 200;

	int amount;

	int first_element;

	vector<pair<Pipe, Pipe>> pipes; 

	Barriers();

	void generate_pipes();

	void next_tick();

	void update_pipes();

	void stop_pipes();

	void start_pipes();

	void reset();

	void draw_pipes(sf::RenderWindow& _window);

	void draw_grass(sf::RenderWindow& _window);

	void draw_all(sf::RenderWindow& _window);

};

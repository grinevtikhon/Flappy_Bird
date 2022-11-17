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

class Pipe
{

public:

	const double tick = 0.004f;

	const double width_pipe = 100;
	const double horizontal_distance = 300;
	const double vertical_distance = 200;


	double x1, y1, x2, y2;
	double v_x;

	Pipe();

	Pipe(double _x1, double _y1, double _y2);

	void set_position(double _x1, double _y1, double _y2);

	void next_tick();

	void stop();

	void start();

	void draw(sf::RenderWindow& _window);

};

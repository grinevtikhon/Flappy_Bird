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

using namespace std;

class Scoreboard
{
	double x;
	double y;

	sf::Color color;

	int total_score;

	Scoreboard();

	void set_total_score(int _total_score);

	void add_point();

	void reset();

	void draw();


};

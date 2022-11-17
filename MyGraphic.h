#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "Network.h"

using namespace std;

class MyGraphic
{
public:

	int windowHeight;
	int windowLength;

	double zoomX;
	double zoomY;

	sf::RenderWindow window;

	MyGraphic();

	void create_window();

	void set_zoomX(double _zoomX);
	void set_zoomY(double _zoomY);

	void draw_dot(double _x, double _y, double _radius, sf::Color _c);

	void draw_axis();

	void display();
	void clear();

	void draw_function(double(*_func)(double), double _thickness, double _accuracy, sf::Color _c);
	void draw_function(Network& _n, double _thickness, double _accuracy, sf::Color _c);

	void draw_dot(vector<double> _x, vector<double> _y, double _radius, sf::Color _c);
};
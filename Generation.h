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

class Generation
{

public:

	vector<Network> gen;

	int group_size;

	int number_of_generations;

	double dispersion;

	vector<double> input;

	vector<double> ans;

	Generation(vector<int> _v, int _group_size, int _n, double _dispersion);

	void calculate_generation();

	void set_input(vector<double> _v);
	vector<double> get_input();

	void set_ans(vector<double> _v);
	vector<double> get_ans();

	void generate_next_generation();

};
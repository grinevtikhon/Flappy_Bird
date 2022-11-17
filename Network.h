#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

using namespace std;

class Network
{
public:

	vector<vector<double>> value;
	vector<vector<double>> bias;

	vector<vector<vector<double>>> w;

	vector<double> ans;

	double mistake;

	Network(vector<int> _v);

	void generateRandomW();
	void generateRandomBias();

	void calculate_neuron(int& _x, int& _y);
	void calculate_line(int _x);
	void calculate_network();

	void setInput(vector<double> _v);

	void setAnswer(vector<double> _v);
	vector<double> getAnswer();

	void calculate_mistake();

	void clear_mistake();
	double get_mistake();

	bool operator<(Network& _n);
	bool operator<=(Network& _n);
	bool operator==(Network& _n);
	bool operator>(Network& _n);
	bool operator>=(Network& _n);

	void mutate(Network& _n, double _dispersion);

	double fuction(double _x);

	void calculate_mistake_for_dots(vector<double> _dot, vector<double> _ans);

};
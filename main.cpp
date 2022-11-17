#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include "MyGraphic.h"
#include "Network.h"
#include "Generation.h"

using namespace std;

double foo(double x)
{
	return sqrt(abs(x)) * 5;
}

int main()
{

	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));

	vector<double> input;

	for (double i = -6; i <= 6; i += 0.5)
	{
		input.push_back(i);
	}

	vector<double> ans;

	for (int i = 0; i < input.size(); ++i)
		ans.push_back(foo(input[i]));

	vector<double> mistake_x{ 0 };
	vector<double> mistake_y{ 0 };

	MyGraphic debug("Mistake");
	MyGraphic da("Generation");

	vector<int> sloi{ 1, 10, 10 , 1 };

	Generation gen(sloi, 50, 4, 1); // (vector<int> _v, int _group_size, int _n, double _dispersion)
	Network net(sloi);

	gen.set_input(input);
	gen.set_ans(ans);

	for (int i = 0; true; i = (i + 10) % 256)
	{
		debug.set_zoomX(1);
		debug.set_zoomY(1);

		da.set_zoomX(15);
		da.set_zoomY(15);

		gen.calculate_generation();


		///////////////////////
		da.clear();

		da.draw_function(foo, 1, 10, sf::Color::Blue);

		for (int j = 1; j < gen.number_of_generations; ++j)
		{
			//da.draw_function(gen.gen[j], 0.4, 5, sf::Color::Yellow);
		}

		da.draw_function(gen.gen[0], 1, 1, sf::Color::Green);

		mistake_x.push_back(mistake_x.back() + 0.2);
		mistake_y.push_back(gen.best_mistake);

		da.draw_dot(input, ans, 2, sf::Color(228, 0, 224));

		da.display();

		gen.generate_next_generation();
		////////////////////////

		debug.clear();

		debug.draw_dot(mistake_x, mistake_y, 1.5, sf::Color::Green);

		debug.display();


		cout << "+" << endl;

	}

}
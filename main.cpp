#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
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

	for (double i = -10; i <= 10; ++i)
	{
		input.push_back(i);
	}

	vector<double> ans;

	for (int i = 0; i < input.size(); ++i)
		ans.push_back(foo(input[i]));

	MyGraphic da;

	vector<int> sloi{ 1, 10, 10 , 1 };

	Generation gen(sloi, 20, 20, 2); // (vector<int> _v, int _group_size, int _n, double _dispersion)
	Network net(sloi);

	gen.set_input(input);
	gen.set_ans(ans);

	for (int i = 0; true; i = (i + 10) % 256)
	{
		da.set_zoomX(15);
		da.set_zoomY(15);

		gen.calculate_generation();

		da.clear();



		da.draw_function(foo, 1, 10, sf::Color::Blue);

		for (int j = 1; j < gen.number_of_generations; ++j)
		{
			//da.draw_function(gen.gen[j], 0.4, 5, sf::Color::Yellow);
		}

		da.draw_function(gen.gen[0], 1, 10, sf::Color::Green);

		da.draw_dot(input, ans, 2, sf::Color(228, 0, 224));

		da.display();

		gen.generate_next_generation();

		//cout << "+" << endl;

	}

}
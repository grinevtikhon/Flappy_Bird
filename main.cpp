#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#define EXPONENT 2.71828182846
#define SPEED_LEARNING 0.00001
#define GRAN_LEARN 0.01
#define ZOOM 30
#define HEIGHT 800
#define LENGTH 800
#define DETALISATION_ANS 200
#define DETALISATION_DEBUG 1

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


sf::RenderWindow window(sf::VideoMode(LENGTH, HEIGHT), "SFML works!");
sf::CircleShape shape(1.f);

vector<int> str{ 1, 10, 10, 1 };
vector<long double> parametr;
vector<long double> ans;
long double bred = 30;
int gran_chance = 1;
int gran_da = 50;

void calculate_dannue()
{
	for (int i = 0; i < 10; ++i)
		parametr.push_back(i);
	for (int i = 0; i < parametr.size(); ++i)
		ans.push_back(sqrt(parametr[i]));

}

long double fun(long double x)
{
	return max(x, long double(0));
}

void print_vector(vector<long double> v)
{
	cout << "[";
	for (int i = 0; i < v.size(); ++i)
		if (i == v.size() - 1)
			cout << v[i];
		else
			cout << v[i] << ", ";
	cout << "]";
}

struct network {

	vector<vector<long double>> value;
	vector<vector<long double>> bias;
	vector<vector<long double>> delta;

	vector<vector<vector<long double>>> w;

	network(vector<int> v) {

		value.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
			value[i].resize(v[i], 0);

		bias.resize(v.size());
		for (int i = 0; i < bias.size(); ++i)
			bias[i].resize(v[i], 0);

		delta.resize(v.size());
		for (int i = 0; i < delta.size(); ++i)
			delta[i].resize(v[i], 0);

		w.resize(v.size() - 1);
		for (int i = 0; i < w.size(); ++i)
		{
			w[i].resize(v[i]);
			for (int j = 0; j < w[i].size(); ++j)
				w[i][j].resize(v[i + 1]);
		}

		generateRandomBias();
		generateRandomW();
	}

	void generateRandomW()
	{
		for (int i = 0; i < w.size(); ++i)
			for (int j = 0; j < w[i].size(); ++j)
				for (int k = 0; k < w[i][j].size(); ++k)
					w[i][j][k] = rand() % 5 - 2;

		return;
	}
	void generateRandomBias()
	{
		for (int i = 0; i < bias.size(); ++i)
			for (int j = 0; j < bias[i].size(); ++j)
				bias[i][j] = rand() % 10 - 5;

		return;
	}

	void print_neuron(int x, int y)
	{
		cout << "Neuron (" << x << ", " << y << ")";
		cout << " value = " << value[x][y] << " ; ";
		cout << "weights : [";
		if (x < w.size()) {
			for (int k = 0; k < w[x][y].size(); ++k)
			{
				if (k == w[x][y].size() - 1)
					cout << w[x][y][k];
				else
					cout << w[x][y][k] << ", ";
			}
		}
		cout << "] ;";
		cout << "\t bias = " << bias[x][y];
		cout << endl;

		return;
	}
	void print_line(int x)
	{
		cout << "Line = " << x << " : (" << endl;
		for (int i = 0; i < value[x].size(); ++i)
			print_neuron(x, i);
		cout << ")" << endl;

		return;
	}
	void print_network()
	{

		window.clear();

		shape.setRadius(1);
		shape.setFillColor(sf::Color::Green);

		for (long double i = 0; i < LENGTH * DETALISATION_DEBUG; i += 1)
		{
			long double x = (i - LENGTH * DETALISATION_DEBUG / 2) / ZOOM / DETALISATION_DEBUG;
			long double y = function({ x })[0];
			shape.setPosition(x * ZOOM + LENGTH / 2, HEIGHT / 2 - y * ZOOM);
			window.draw(shape);
		}

		shape.setRadius(3.2f);
		shape.setFillColor(sf::Color::Red);

		for (int i = 0; i < parametr.size(); ++i)
		{
			long double x = parametr[i];
			long double y = ans[i];
			shape.setPosition(x * ZOOM + LENGTH / 2 - shape.getRadius() / 2, HEIGHT / 2 - y * ZOOM - shape.getRadius() / 2);
			window.draw(shape);
		}

		//sleep_for(100ms);

		window.display();
		/*
		cout << "Network : {" << endl << endl;
		for (int i = 0; i < value.size(); ++i)
			print_line(i);
		cout << endl;
		cout << "}   <---- This my network ^_^";
		cout << endl;
		*/
	}

	void print_answer()
	{
		cout << "Answer = [";

		for (int i = 0; i < value.back().size(); ++i)
		{
			if (i == value.back().size() - 1)
				cout << value.back()[i];
			else
				cout << value.back()[i] << ", ";
		}

		cout << "]" << endl;

		return;
	}

	void clear_delta()
	{
		for (int i = 0; i < delta.size(); ++i)
			for (int j = 0; j < delta[i].size(); ++j)
				delta[i][j] = 0;

		return;
	}

	void setInput(vector<long double> v)
	{
		value[0] = v;

		return;
	}
	void setAnswer(vector<long double>& v)
	{
		if (v.size() != delta.back().size())
		{
			cout << "ALARM!!! OUT OF RANGE ANSWER -_-" << endl;
			return;
		}

		for (int i = 0; i < v.size(); ++i)
		{
			delta.back()[i] = (value.back()[i] - v[i]);
		}
	}

	vector<long double> getAnswer()
	{
		return value.back();
	}

	void calculate_neuron(int& x, int& y)
	{
		value[x][y] = 0;
		for (int i = 0; i < value[x - 1].size(); ++i) {
			value[x][y] += value[x - 1][i] * w[x - 1][i][y];
		}
		value[x][y] += bias[x][y];

		value[x][y] = fun((value[x][y]));

		return;
	}
	void calculate_line(int x)
	{
		for (int i = 0; i < value[x].size(); ++i)
			calculate_neuron(x, i);

		return;
	}
	void calculate_network()
	{

		//setInput(v);

		for (int i = 1; i < value.size(); ++i)
			calculate_line(i);

		return;
	}

	void update_neuron(int& x, int& y)
	{
		if (x == 0)
			return;

		for (int i = 0; i < w[x - 1].size(); ++i)
		{
			delta[x - 1][i] += w[x - 1][i][y] * delta[x][y];
			w[x - 1][i][y] -= value[x - 1][i] * delta[x][y] * SPEED_LEARNING;
			//cout << w[x - 1][i][y] << endl;


		}

		bias[x][y] -= delta[x][y] * SPEED_LEARNING;

		return;
	}
	void update_line(int& x)
	{
		for (int i = 0; i < value[x].size(); ++i)
			update_neuron(x, i);

		return;
	}
	void update_network()
	{
		for (int i = value.size() - 1; i > 0; --i)
			update_line(i);

		return;
	}

	long long learn(vector<long double> v, vector<long double> ans)
	{
		setInput(v);
		calculate_network();
		clear_delta();
		setAnswer(ans);
		long long st = 0;
		// bred = rand() % 200 + 10;

		while (!is_right())
		{
			//if (st % 2000 == 0 && st != 0)
				//print_network();
			//cout << "< " << getMistake() << " >" << endl;
			//if (st % 50000 == 0 && st != 0)
				//print_network();
			++st;
			update_network();
			calculate_network();
			clear_delta();
			setAnswer(ans);
			int chance = rand() % 101;
			if (st >= bred && chance > gran_chance)
				break;
		}
		return st;
	}

	long double getMistake()
	{
		long double mistake = 0;
		for (int i = 0; i < delta.back().size(); ++i)
			mistake += delta.back()[i];
		return mistake;
	}

	bool is_right()
	{
		long double mistake = 0;
		for (int i = 0; i < delta.back().size(); ++i)
			mistake += delta.back()[i] * delta.back()[i];

		return (mistake < GRAN_LEARN);

	}

	vector<long double> function(vector<long double> v)
	{
		setInput(v);
		calculate_network();
		return getAnswer();
	}

};

int main()
{

	calculate_dannue();

	cout.setf(ios::fixed);
	cout.precision(10);
	srand(time(NULL));

	network diana(str);

	long double k = 3;
	long double c = 23;



	diana.print_network();

	int da = 1;

	while (true)
	{
		int gr = 0;
		for (int i = parametr.size() - 1; i >= 0; --i)
		{
			int buf;
			buf = diana.learn({ parametr[i] }, { ans[i] });
			cout << buf << "\t";
			gr += buf;
			//diana.print_network();
		}
		cout << endl;
		if (gr <= parametr.size())
			break;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		++da;
		if (da % gran_da == 0) {
			diana.print_network();
		}
	}

	window.clear();

	shape.setRadius(1);
	shape.setFillColor(sf::Color::Blue);

	for (long double i = 0; i < LENGTH * DETALISATION_ANS; i += 1)
	{
		long double x = (i - LENGTH * DETALISATION_ANS / 2) / ZOOM / DETALISATION_ANS;
		long double y = diana.function({ x })[0];
		shape.setPosition(x * ZOOM + LENGTH / 2, HEIGHT / 2 - y * ZOOM);
		window.draw(shape);
	}

	shape.setRadius(3);
	shape.setFillColor(sf::Color::Red);

	for (int i = 0; i < parametr.size(); ++i)
	{
		long double x = parametr[i];
		long double y = ans[i];
		shape.setPosition(x * ZOOM + LENGTH / 2 - shape.getRadius() / 2, HEIGHT / 2 - y * ZOOM - shape.getRadius() / 2);
		window.draw(shape);
	}

	window.display();

	while (true) {
		long double buf;
		cin >> buf;
		diana.setInput({ buf });
		diana.calculate_network();
		cout << buf * buf * k + c << " | ";
		diana.print_answer();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.display();
	}

	diana.print_network();

	cout << "Hello World!\n";
}
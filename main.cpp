#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <time.h>

#define EXPONENT 2.71828182846
#define SPEED_LEARNING 0.0001;

using namespace std;

double sigma(double value)
{
	return 1.0f / (1.0f + pow(EXPONENT, -value));
}

struct network
{
	vector<vector<double>> value;
	vector<vector<double>> delta;

	vector<vector<vector<double>>> w;

	vector<vector<double>> bias;

	network(vector<int> v)
	{
		value.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
			for (int j = 0; j < v[i]; ++j)
				value[i].push_back(0);

		delta.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
			for (int j = 0; j < v[i]; ++j)
				delta[i].push_back(0);

		bias.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
			for (int j = 0; j < v[i]; ++j)
				if (i != 0)
					bias[i].push_back(0);
				else
					bias[i].push_back(0);

		w.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
		{
			w[i].resize(v[i]);
			if (i != v.size() - 1)
				for (int j = 0; j < v[i]; ++j)
					for (int k = 0; k < v[i + 1]; ++k)
						w[i][j].push_back(0);
		}

	}

	void print_neuron(int x, int y)
	{
		cout << "Neuron (" << x << ", " << y << ")";
		cout << " value = " << value[x][y] << " ; ";
		cout << "weights : [";
		for (int k = 0; k < w[x][y].size(); ++k)
		{
			if (k == w[x][y].size() - 1)
				cout << w[x][y][k];
			else
				cout << w[x][y][k] << ", ";
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
		cout << "Network : {" << endl << endl;
		for (int i = 0; i < value.size(); ++i)
			print_line(i);
		cout << endl;
		cout << "}   <---- This my network ^_^";
		cout << endl;
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

	void calculate_neuron(int x, int y)
	{
		value[x][y] = 0;
		for (int i = 0; i < value[x - 1].size(); ++i) {
			value[x][y] += value[x - 1][i] * w[x - 1][i][y];
		}
		value[x][y] += bias[x][y];

		//value[x][y] = sigma(value[x][y]);

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

		for (int i = 1; i < value.size(); ++i)
			calculate_line(i);

		return;
	}

	void setInput(vector<double> v)
	{
		if (v.size() != value[0].size())
		{
			cout << "ALARM!!! OUT OF RANGE INPUT -_-" << endl;
			return;
		}

		for (int i = 0; i < v.size(); ++i)
			value[0][i] = v[i];

		return;
	}
	void setAnswer(vector<double> v)
	{
		if (v.size() != delta.back().size())
		{
			cout << "ALARM!!! OUT OF RANGE ANSWER -_-" << endl;
			return;
		}

		for (int i = 0; i < v.size(); ++i)
		{
			delta.back()[i] = value.back()[i] - v[i];
		}
	}

	vector<double> getAnswer()
	{
		return value.back();
	}

	vector<double> function(vector<double> v)
	{
		setInput(v);
		calculate_network();
		return getAnswer();
	}

	void generateRandomInput()
	{
		for (int i = 0; i < value[0].size(); ++i)
			value[0][i] = rand() % 21 - 10;

		return;
	}

	void clear_delta()
	{
		for (int i = 0; i < delta.size(); ++i)
			for (int j = 0; j < delta[i].size(); ++j)
				delta[i][j] = 0;
	}

	void update_neuron(int x, int y)
	{
		if (x == 0)
			return;

		for (int i = 0; i < w[x - 1].size(); ++i)
		{
			delta[x - 1][i] -= w[x - 1][i][y] * delta[x][y] * SPEED_LEARNING;
			w[x - 1][i][y] -= value[x - 1][i] * delta[x][y] * SPEED_LEARNING;
		}

		bias[x][y] -= delta[x][y] * SPEED_LEARNING;

		return;
	}
	void update_line(int x)
	{
		for (int i = 0; i < value[x].size(); ++i)
			update_neuron(x, i);

		return;
	}
	void update_network()
	{
		//clear_delta();

		for (int i = value.size() - 1; i > 0; --i)
			update_line(i);

		return;
	}

	void learn(vector<double> v, vector<double> ans)
	{
		function(v);
		clear_delta();
		setAnswer(ans);
		update_network();
	}

};


int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));
	//vector <int> v { 5, 5, 2 };

	network ns({ 5,  1 });

	ns.print_network();

	for (int i = 0; i < 300; ++i) {
		int ans = 0;
		vector<double> vec;
		for (int j = 0; j < 5; ++j)
		{
			vec.push_back(rand() % 21 - 10);
			cout << vec.back() << " ";
			ans += vec.back() * j;
		}
		for (int k = 0; k < 10; ++k) {
			cout << " ------>  " << ans << " | ";
			ns.learn(vec, { double(ans) });
			ns.print_answer();
		}
	}

	ns.print_network();

	while (true)
	{
		vector<double> vec(5);
		for (int j = 0; j < 5; ++j)
			cin >> vec[j];
		ns.function(vec);
		ns.print_answer();
	}

	//ns.print_network();

	cout << "da TbI horosh!";
	return 0;
}

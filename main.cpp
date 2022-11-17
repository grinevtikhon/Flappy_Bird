#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <time.h>

#define EXPONENT 2.71828182846

using namespace std;

double sigma(double value)
{
	return 1.0f / (1.0f + pow(EXPONENT, -value));
}

struct network
{
	vector<vector<double>> value;

	vector<vector<vector<double>>> w;

	vector<vector<double>> bias;

	network(vector<int> v)
	{
		value.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
			for (int j = 0; j < v[i]; ++j)
				value[i].push_back(0);

		bias.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
			for (int j = 0; j < v[i]; ++j)
				if (i != 0)
					bias[i].push_back(rand() % 21 - 10);
				else
					bias[i].push_back(0);

		w.resize(v.size());
		for (int i = 0; i < v.size(); ++i)
		{
			w[i].resize(v[i]);
			if (i != v.size() - 1)
				for (int j = 0; j < v[i]; ++j)
					for (int k = 0; k < v[i + 1]; ++k)
						w[i][j].push_back(rand() % 21 - 10);
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
};


int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));
	//vector <int> v { 5, 5, 2 };
	network da({ 784, 16, 10, 10 });
	da.generateRandomInput();
	da.calculate_network();
	da.print_network();
	cout << "da TbI horosh!";
	return 0;
}
